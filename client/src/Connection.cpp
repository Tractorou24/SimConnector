#include <client/Connection.h>

#include "boost/asio/read.hpp"
#include "boost/asio/streambuf.hpp"
#include "boost/asio/write.hpp"

Connection::Connection(std::string ip, const uint16_t& port)
	: m_ip(std::move(ip)), m_port(port), m_socket(m_ioService)
{
}

Connection::Connection(const std::string& connection_string)
	: m_ip(connection_string.substr(0, connection_string.find_first_of(':') + 1))
	  , m_port(static_cast<uint16_t>(std::stoi(connection_string.substr(connection_string.find_first_of(':')))))
	  , m_socket(m_ioService)
{
}

bool Connection::connect() noexcept
{
	boost::system::error_code error;
	m_socket.connect(boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string(m_ip), m_port), error);
	return !error ? true : false;
}

bool Connection::send(const json::json& request) noexcept
{
	boost::system::error_code error;
	boost::asio::write(m_socket, boost::asio::buffer(request.dump() + "\n"), error);
	return !error ? true : false;
}

std::string Connection::read()
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
