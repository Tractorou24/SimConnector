#include <core/simconnect/SimVar.h>
#include <core/request/RequestFactory.h>

#include <server/NetworkConnection.h>
#include <server/Runner.h>
#include <SimConnectLoader.h>

#include <iostream>

int main(int argc, char** argv)
{
	std::string ip = "127.0.0.1";
	uint16_t port = 1234;

	if (argc != 3)
	{
		std::cout << "Usage: " << argv[0] << " <ip> <port>" << std::endl;
		std::cout << "Using default values: " << ip << ":" << port << std::endl;
	}
	else
	{
		ip = argv[1];
		port = static_cast<uint16_t>(std::stoi(argv[2]));
	}

	SimConnectLoader::LoadSimConnect();
	auto* runner = simconnect::Runner::GetInstance();

	server::NetworkConnection connection(ip, port);
	[[maybe_unused]] const auto status = connection.connect();
	assert(status);

	// Open SimConnect connection
	while (!runner->openConnection())
	{
		std::cout << "Waiting for SimConnect to open..." << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}
	std::cout << "SimConnect connected!" << std::endl;

	RequestFactory factory;

	while (runner->isRunning())
	{
		// Check if there is data to read
		if (connection.available_bytes() > 0)
		{
			std::string data = connection.read();
			json::json json_data = json::json::parse(data);
			if (!json_data.contains("type"))
			{
				std::cout << "Invalid request : No type found..." << std::endl;
				std::cout << json_data.dump() << std::endl;
				continue;
			}

			std::shared_ptr request = factory.create(json_data["type"]);
			request->deserialize(json_data.dump());

			if (request->requestType() == core::request::Type::Remove)
			{
				runner->removeRequest(request);
			}
			else
			{
				request->responseSignal.connect(core::Slot<const std::shared_ptr<core::interfaces::IResponse>&>(
					[&connection](const std::shared_ptr<core::interfaces::IResponse>& x)
					{
						[[maybe_unused]] const auto status = connection.send(x.get());
						assert(status);
					}));
				runner->addRequest(request);
			}
		}

		// Poll SimConnect events
		runner->pollEvents();
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}

	runner->closeConnection();
	SimConnectLoader::UnloadSimConnect();
	return 0;
}
