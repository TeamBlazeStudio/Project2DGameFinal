#include "Client.h"

Client::Client() {}

Client::~Client() {}

bool Client::init() {
	if (enet_initialize() != 0) {
		std::cerr << "An error while initializing ENet!" << std::endl;
		return false;
	}
	atexit(enet_deinitialize);

	client = enet_host_create(NULL, 1, 1, 0, 0);

	if (client == NULL) {
		std::cerr << "An error occured while trying to create an ENet client " << std::endl;
		return false;
	}

	enet_address_set_host(&address, "127.0.0.1");
	address.port = 25565;

	peer = enet_host_connect(client, &address, 1, 0);
	if (peer == NULL) {
		std::cerr << "No available peers for ENet connection" << std::endl;
		return false;
	}

	if (enet_host_service(client, &evnt, 5000) > 0 && 
		evnt.type == ENET_EVENT_TYPE_CONNECT) {
		puts("Connection to 127.0.0.1:25565 succeeded.");
	}
	else {
		enet_peer_reset(peer);
		puts("Connection to 127.0.0.1:25565 failed.");
		return false;
	}
	return true;

}

void Client::run() {
	system("cls");
	std::cout << "client running..." << std::endl;
	std::cout << "Client Connected to server: " << address.host << ":" << address.port << std::endl;

	std::string name = "";
	std::cout << "Client Enter Username: ";
	std::cin >> name;
	
	// work in progress
	if (name == "") { std::cerr << "Invalid Name"; return; }

	std::string msg = "1|";
	msg += name;
	SendPacket(msg);

	while (true) {

		while (enet_host_service(client, &evnt, 1000) > 0) {
			if (evnt.type == ENET_EVENT_TYPE_RECEIVE) {
				std::cout << "Client: Packet received: " << evnt.packet->data  << std::endl;
				ID = (int)evnt.packet->data;
				enet_packet_destroy(evnt.packet);
			}
			else if (evnt.type == ENET_EVENT_TYPE_DISCONNECT) {
				std::cout << "Client: Disconnected" << std::endl;
			}
		}

	}

	enet_peer_disconnect(peer, 0);
	while (enet_host_service(client, &evnt, 3000) > 0) {
		switch (evnt.type) {
			case ENET_EVENT_TYPE_RECEIVE:
				enet_packet_destroy(evnt.packet);
				break;
			case ENET_EVENT_TYPE_DISCONNECT:
				puts("Client: Disconnection succeded.");
				break;
		}
	}

	return;
}

void Client::SendPacket(const std::string& data) {
	//Make a packet
	ENetPacket* packet = enet_packet_create(data.c_str(), data.size() + 1, ENET_PACKET_FLAG_RELIABLE);
	
	//Send the packet
	enet_peer_send(peer, 0, packet);

	//Check if the packet is been send correctly
	enet_host_flush(client);
}