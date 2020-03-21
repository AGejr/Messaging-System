#pragma once

#include "SFML/Network.hpp"
#include <iostream>
#include <thread>

class Client
{
public:

	Client(const short port)
		: m_IP_adress(sf::IpAddress::getLocalAddress()),
		m_port(port)
	{
	}

	void launch()
	{
		connect_to_server();

		std::thread recieve(&Client::recieve_message, this);

		std::string message;

		while (true)
		{
			std::getline(std::cin, message);

			send_message(message);
		}		
	}

private:

	void connect_to_server()
	{
		if (m_socket.connect(m_IP_adress, m_port) != sf::Socket::Done)
		{
			std::cout << "ERROR: failed to connect to server\n";

			return;
		}
		else
		{
			std::cout << "Connection established\n";
			send_message("Connected to client");

			return;

		}
	}

	void send_message(std::string message)
	{
		sf::Packet packet;
		packet << message;

		m_socket.send(packet);

		return;
	}

	void recieve_message()
	{
		while (true)
		{
			sf::Packet packet;

			m_socket.receive(packet);

			std::string message;

			packet >> message;

			std::cout << message << "\n";
		}
	}

	sf::IpAddress m_IP_adress;
	sf::TcpSocket m_socket;
	const short m_port;
};