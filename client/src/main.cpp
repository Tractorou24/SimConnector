#include <boost/asio.hpp>

#include <core/response/ResponseFactory.h>
#include <core/request/ReadRequest.h>
#include <core/request/RemoveRequest.h>

#include <client/Connection.h>

#include <iostream>

int main(int, char**)
{
    ResponseFactory factory;

    Connection c("127.0.0.1", 1234);
    if (!c.connect())
        return 1;

    auto simvar1 = std::make_shared<simconnect::SimVar>("GPS GROUND SPEED", "Meters per second", false);
    auto simvar2 = std::make_shared<simconnect::SimVar>("HSI STATION IDENT", "String", true);

    auto simvar3 = std::make_shared<simconnect::SimVar>("HSI DISTANCE", "Nautical miles", false);
    auto simvar4 = std::make_shared<simconnect::SimVar>("FUEL RIGHT QUANTITY", "Gallons", false);

    std::shared_ptr<core::interfaces::IRequest> rq = std::make_shared<core::request::ReadRequest>();
    std::shared_ptr<core::interfaces::IRequest> rq2 = std::make_shared<core::request::ReadRequest>();
    rq->addSimVar(simvar1);
    rq->addSimVar(simvar2);

    //rq->responseSignal.connect(core::Slot<const std::shared_ptr<core::interfaces::IResponse>&>(
    //    [&connection](const std::shared_ptr<core::interfaces::IResponse>& x)
    //    {
    //        [[maybe_unused]] const auto status = connection.send(x.get());
    //        assert(status);
    //    }));

    rq2->addSimVar(simvar3);
    rq2->addSimVar(simvar4);
    //rq2->responseSignal.connect(core::Slot<const std::shared_ptr<core::interfaces::IResponse>&>(
    //    [&connection](const std::shared_ptr<core::interfaces::IResponse>& x)
    //    {
    //        [[maybe_unused]] const auto status = connection.send(x.get());
    //        assert(status);
    //    }));

    assert(c.send(rq->serialize()));
    assert(c.send(rq2->serialize()));

    while (true)
    {
        auto data = c.read();
        if (data.empty())
			continue;
        auto json_data = json::json::parse(data);

        auto response = factory.create(json_data.at("type"));
        response->deserialize(data);
        while (response->size() != 0)
        {
            const auto simvar = response->pop();
            std::cout << simvar->name() << ": ";
            if (simvar->isString())
                std::cout << simvar->stringValue() << std::endl;
            else
                std::cout << simvar->value() << std::endl;
        }
    }
}
