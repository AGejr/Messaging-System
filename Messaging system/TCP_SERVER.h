#pragma once

#include "SFML/Network.hpp"
#include <iostream>
#include <thread>
#include <string>
#include <sstream>

class Server
{
public:

	Server(const short port) 
		: m_IP_adress(sf::IpAddress::getLocalAddress()),
		m_port(port)
	{
	}

	void launch()
	{
		accept_connections();

		std::thread recieve(&Server::recieve_message,this);

		std::string message;

		while (true)
		{
			std::getline(std::cin, message);

			send_message(message);
		}
	}

private:

	void accept_connections()
	{
		std::cout << "IP Adress: " << m_IP_adress << "\n";

		if (m_listener.listen(m_port) != sf::Socket::Done)
		{
			std::cout << "ERROR: error occured while listening to port " << m_port << "\n";
		}

		if (m_listener.accept(m_socket) != sf::Socket::Done)
		{
			std::cout << "ERROR: no connections accepted\n";

			return;
		}
		else
		{
			std::cout << "Connection established\n";
			send_message("Connected to server");

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
	const short m_port;
	sf::TcpSocket m_socket;
	sf::TcpListener m_listener;
};