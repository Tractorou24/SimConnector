#include "spch.h"

#include <core/response/ResponseFactory.h>

#include <server/NetworkConnection.h>

server::NetworkConnection::NetworkConnection(std::string ip, const uint16_t& port)
    : m_ip(std::move(ip)), m_port(port), m_isConnected(false), m_socket(m_ioService) {}

server::NetworkConnection::NetworkConnection(const std::string& connection_string)
    : m_ip(connection_string.substr(0, connection_string.find_first_of(':') + 1))
      , m_port(static_cast<uint16_t>(std::stoi(connection_string.substr(connection_string.find_first_of(':')))))
      , m_isConnected(false), m_socket(m_ioService) {}

server::NetworkConnection::~NetworkConnection() = default;

bool server::NetworkConnection::send(const core::interfaces::IRequest* request) noexcept
{
    const json::json data = request->serialize();

    boost::system::error_code error;
    boost::asio::write(m_socket, boost::asio::buffer(data.dump()), error);
    return !error ? true : false;
}

bool server::NetworkConnection::connect() noexcept
{
    try
    {
        m_socket.connect(boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string(m_ip), m_port));
        m_isConnected = true;
    } catch (const std::exception&)
    {
        m_isConnected = false;
        return false;
    }

    m_thread = std::thread([&]
    {
        ResponseFactory factory;
        boost::system::error_code error;
        while (m_isConnected)
        {
            boost::asio::streambuf receive_buffer;
            boost::asio::read(m_socket, receive_buffer, boost::asio::transfer_all(), error);
            if (!error || error == boost::asio::error::eof)
            {
                const char* data = boost::asio::buffer_cast<const char*>(receive_buffer.data());
                json::json json_data = json::json::parse(data);

                auto response = factory.create(json_data.at("type"));
                response->deserialize(data);
                responseSignal.emitSignal(std::move(response));
            }
        }
    });
    return true;
}
