#include <boost/asio.hpp>

#include <core/response/ResponseFactory.h>

#include <iostream>

std::string read_(boost::asio::ip::tcp::socket& socket)
{
    boost::asio::streambuf buf;
    boost::asio::read_until(socket, buf, "\n");
    std::string data = boost::asio::buffer_cast<const char*>(buf.data());
    return data;
}

int main(int, char**)
{
    ResponseFactory factory;
    boost::asio::io_context io_context;
    boost::asio::ip::tcp::socket socket(io_context);

    std::this_thread::sleep_for(std::chrono::seconds(2));

    boost::system::error_code error;
    socket.connect(boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 1234));
    if (error)
        return 1;

    while (true)
    {
        auto data = read_(socket);
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
