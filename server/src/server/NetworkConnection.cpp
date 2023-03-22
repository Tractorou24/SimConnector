#include "spch.h"

#include <server/NetworkConnection.h>

server::NetworkConnection::NetworkConnection(std::string ip, const uint16_t& port)
    : m_ip(std::move(ip)), m_port(port), m_socket(m_ioService) {}

server::NetworkConnection::NetworkConnection(const std::string& connection_string)
    : m_ip(connection_string.substr(0, connection_string.find_first_of(':') + 1))
      , m_port(static_cast<uint16_t>(std::stoi(connection_string.substr(connection_string.find_first_of(':')))))
      , m_socket(m_ioService) {}

server::NetworkConnection::~NetworkConnection() = default;

bool server::NetworkConnection::send(const core::interfaces::IResponse* request) noexcept
{
    const json::json data = request->serialize();
    boost::system::error_code error;
    boost::asio::write(m_socket, boost::asio::buffer(data.dump() + "\n"), error);
    return !error ? true : false;
}

bool server::NetworkConnection::connect() noexcept
{
    boost::system::error_code error;
    boost::asio::ip::tcp::acceptor acceptor_(
        m_ioService, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), m_port));
    acceptor_.accept(m_socket);
    return true;
}
