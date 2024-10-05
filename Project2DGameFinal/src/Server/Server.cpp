#include "Server.h"

Server::Server() {}

Server::~Server() {
	if (server) {
		enet_host_destroy(server);
	}
	enet_deinitialize();
}

bool Server::init() {
	if (enet_initialize() != 0) {
		std::cerr << "An error occured while initializing ENet (Server)" << std::endl;
		return false;
	}
	atexit(enet_deinitialize);

	address.host = ENET_HOST_ANY;
	address.port = 25565;

	//1 = address, 2 = player limit, 3 = channels, 4/5 = bandwith
	server = enet_host_create(&address, 16, 1, 0, 0);

	if (server == NULL) {
		std::cerr << "An error occured while trying to create an ENet Server" << std::endl;
		return false;
	}

	return true;
}

void Server::run() {
	system("cls");
	std::cout << "Server Debug Menu:\n\nServer Running..." << std::endl;
	while (true) {
		while (enet_host_service(server, &event, 1000) > 0) {
			switch (event.type) {
			case ENET_EVENT_TYPE_CONNECT:
				printf("A new client connected from %x:%u.\n", 
					event.peer->address.host, event.peer->address.port);
				break;
			case ENET_EVENT_TYPE_RECEIVE:
				std::cout << "Packet received from client.\n";
				enet_packet_destroy(event.packet);
				break;
			case ENET_EVENT_TYPE_DISCONNECT:
				printf("%x:%u disconnected.\n",
					event.peer->address.host, event.peer->address.port);
				break;
			default:
				break;
			}
		}
	}
	Server::~Server();
	return;
}