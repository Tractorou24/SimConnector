﻿#include <server/NetworkConnection.h>

server::NetworkConnection::NetworkConnection(std::string ip, const uint16_t& port)
	: m_ip(std::move(ip)), m_port(port), m_socket(m_ioService)
{
}

server::NetworkConnection::NetworkConnection(const std::string& connection_string)
	: m_ip(connection_string.substr(0, connection_string.find_first_of(':') + 1))
	  , m_port(static_cast<uint16_t>(std::stoi(connection_string.substr(connection_string.find_first_of(':')))))
	  , m_socket(m_ioService)
{
}

server::NetworkConnection::~NetworkConnection() = default;

bool server::NetworkConnection::send(const core::interfaces::IResponse* request) noexcept
{
	const json::json data = request->serialize();
	boost::system::error_code error;
	boost::asio::write(m_socket, boost::asio::buffer(data.dump() + "\n"), error);
	return !error ? true : false;
}

size_t server::NetworkConnection::available_bytes() const
{
	return m_socket.available();
}

std::string server::NetworkConnection::read() noexcept
{
	boost::system::error_code error;
	boost::asio::streambuf buffer;

	while (boost::asio::buffer_cast<const char*>(buffer.data())[buffer.size() - 1] != '\n')
	{
		boost::asio::read(m_socket, buffer, boost::asio::transfer_exactly(1), error);
		if (error)
			return "";
	}

	std::string data = boost::asio::buffer_cast<const char*>(buffer.data());
	const size_t end = data.find('\n');
	if (end == std::string::npos)
		return "";

	if (data.size() == end)
		data += '\n';

	data[end] = '\0';
	data[end + 1] = '\n';
	return data;
}

bool server::NetworkConnection::connect() noexcept
{
	boost::asio::ip::tcp::acceptor acceptor(m_ioService, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), m_port));
	acceptor.accept(m_socket);
	return true;
}
