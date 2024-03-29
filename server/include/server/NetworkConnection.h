﻿#pragma once

#include <core/interfaces/IConnection.h>

#include <boost/asio.hpp>

namespace server
{
    class NetworkConnection final : protected core::interfaces::IConnection
    {
    public:
        explicit NetworkConnection(std::string ip, const uint16_t& port);
        explicit NetworkConnection(const std::string& connection_string);
        ~NetworkConnection() override;

        NetworkConnection(const NetworkConnection& other) = delete;
        NetworkConnection(NetworkConnection&& other) noexcept = delete;
        NetworkConnection& operator=(const NetworkConnection& other) = delete;
        NetworkConnection& operator=(NetworkConnection&& other) noexcept = delete;

        [[nodiscard]] bool send(const core::interfaces::IResponse* request) noexcept override;
        [[nodiscard]] size_t available_bytes() const;
        [[nodiscard]] std::string read() noexcept;
        [[nodiscard]] bool connect() noexcept override;

    private:
        const std::string m_ip;
        const uint16_t m_port;

        boost::asio::io_service m_ioService;
        boost::asio::ip::tcp::socket m_socket;
    };
}
