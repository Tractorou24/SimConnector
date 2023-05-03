#pragma once

#include "boost/asio/io_service.hpp"
#include "boost/asio/ip/tcp.hpp"
#include "nlohmann/json.hpp"
namespace json = nlohmann;

#include <string>

class Connection final
{
public:
    explicit Connection(std::string ip, const uint16_t& port);
    explicit Connection(const std::string& connection_string);

    [[nodiscard]] bool connect() noexcept;
    [[nodiscard]] bool send(const json::json& request) noexcept;
    [[nodiscard]] std::string read();

private:
    const std::string m_ip;
    const uint16_t m_port;

    boost::asio::io_service m_ioService;
    boost::asio::ip::tcp::socket m_socket;
};
