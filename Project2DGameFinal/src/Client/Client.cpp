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

void Client::Exit() {
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
				std::string packet = (char*)evnt.packet->data;
				std::cout << "Client: Packet received: " << packet  << std::endl;
				
				int data_type;
				if (sscanf(packet.c_str(), "%d|", &data_type) == 1) {
					if (data_type == 2) {
						//%*d skip the first value and take only the second
						if (sscanf(packet.c_str(), "%*d|%d", &ID)) {
							if (!ID) {
								std::cerr << "Client: ID Error, server haven't send back the ID" << std::endl;
								break;
							}
							std::cout << "Client ID: " << ID << std::endl;
						}
						else std::cerr << "Client: Failed to parse ID" << std::endl;
					}
					else std::cerr << "Client: Unexpected data_type: " << data_type << std::endl;
				}
				else std::cerr << "Client: Failed to parse data_type" << std::endl;

				// Destroy packet any way
				enet_packet_destroy(evnt.packet);
			}
			else if (evnt.type == ENET_EVENT_TYPE_DISCONNECT) {
				std::cout << "Client: Disconnected" << std::endl;
			}
		}

	}

	Exit();

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