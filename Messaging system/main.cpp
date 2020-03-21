
#include <iostream>
#include <SFML/Network.hpp>

#include "TCP_SERVER.h"
#include "TCP_CLIENT.h"

void test();

int main() {

	char mode;
	std::cout << "(s) for server or (c) for client: ";
	std::cin >> mode;

	if (mode == 's') 
	{
		Server server(2000);
		server.launch();
	}
	else if (mode == 'c')
	{
		Client client(2000);
		client.launch();
	}

	return 0;
}
