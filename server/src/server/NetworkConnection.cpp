#include "spch.h"

#include <server/NetworkConnection.h>

server::NetworkConnection::NetworkConnection(std::string ip, const uint16_t& port)
    : m_ip(std::move(ip)), m_port(port)
{
    throw std::logic_error("Not implemented");
}

server::NetworkConnection::NetworkConnection(const std::string& connection_string)
    : m_ip(connection_string.substr(0, connection_string.find_first_of(',') + 1))
      , m_port(static_cast<uint16_t>(std::stoi(connection_string.substr(connection_string.find_first_of(',')))))
{
    throw std::logic_error("Not implemented");
}

server::NetworkConnection::~NetworkConnection() = default;

bool server::NetworkConnection::send(const core::interfaces::IRequest* request) noexcept
{
    throw std::logic_error("Not implemented");
}

bool server::NetworkConnection::connect() noexcept
{
    throw std::logic_error("Not implemented");
}
