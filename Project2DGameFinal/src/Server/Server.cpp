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
				printf("Server: A new client connected from %x:%u.\n", 
					event.peer->address.host, event.peer->address.port);
				
				break;
			case ENET_EVENT_TYPE_RECEIVE:
				std::cout << "Server: Packet received from client.\n";
				if (!ReceivePacket(server, (char*)event.packet->data)) std::cerr << "Server: Error packet parsing" << std::endl;
				enet_packet_destroy(event.packet);
				break;

			case ENET_EVENT_TYPE_DISCONNECT:
				printf("Server: %x:%u disconnected.\n",
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

void Server::SendPacket(const std::string& data) {
	//Make a packet
	ENetPacket* packet = enet_packet_create(data.c_str(), data.size() + 1, ENET_PACKET_FLAG_RELIABLE);

	//Send the packet
	enet_peer_send(event.peer, 0, packet);

	//Check if the packet is been send correctly
	enet_host_flush(server);
}

bool Server::ReceivePacket( ENetHost* server, char* data) {
	std::cout << "Server: packet sended by client: " << data << std::endl;
	srand(time(NULL));

	int data_type;
	if (!sscanf(data, "%d|", &data_type)) return false;
	
	switch (data_type) {
		//1 -> Username player
		case 1:
			//generate a random ID of 6 digits
			int RId = 100000 + (rand() % 900000);
			std::string RIds = std::to_string(RId);

			//push the id in to the user vector
			users.push_back(RIds);
			std::string temp = "2|";
			temp += RIds;
			SendPacket(temp);

			break;
	}

	return true;
}