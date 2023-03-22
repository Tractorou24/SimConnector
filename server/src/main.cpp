#include "spch.h"

#include <SimConnectLoader.h>
#include <core/request/ReadRequest.h>
#include <core/simconnect/SimVar.h>

#include <server/Runner.h>

#include <thread>

#include "server/NetworkConnection.h"

int main(int argc, char* argv[])
{
    SimConnectLoader::LoadSimConnect();
    auto* runner = simconnect::Runner::GetInstance();

    server::NetworkConnection connection("127.0.0.1", 1234);
    connection.connect();

    auto simvar = std::make_shared<simconnect::SimVar>("GPS GROUND SPEED", "Meters per second", false);
    auto simvar2 = std::make_shared<simconnect::SimVar>("HSI STATION IDENT", "String", true);

    auto simvar3 = std::make_shared<simconnect::SimVar>("HSI DISTANCE", "Nautical miles", false);
    auto simvar4 = std::make_shared<simconnect::SimVar>("FUEL RIGHT QUANTITY", "Gallons", false);

    std::shared_ptr<core::interfaces::IRequest> rq = std::make_shared<core::request::ReadRequest>();
    std::shared_ptr<core::interfaces::IRequest> rq2 = std::make_shared<core::request::ReadRequest>();
    rq->addSimVar(simvar);
    rq->addSimVar(simvar2);

    rq->responseSignal.connect(core::Slot<const std::shared_ptr<core::interfaces::IResponse>&>(
        [&connection](const std::shared_ptr<core::interfaces::IResponse>& x)
        {
            connection.send(x.get());
        }));

    rq2->addSimVar(simvar3);
    rq2->addSimVar(simvar4);
    rq2->responseSignal.connect(core::Slot<const std::shared_ptr<core::interfaces::IResponse>&>(
        [&connection](const std::shared_ptr<core::interfaces::IResponse>& x)
        {
            connection.send(x.get());
        }));

    runner->openConnection();
    runner->addRequest(rq);
    runner->addRequest(rq2);

    while (runner->isRunning())
    {
        runner->pollEvents();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    runner->closeConnection();
    SimConnectLoader::UnloadSimConnect();
    return 0;
}
