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
	std::cout << "client running...";
	while (enet_host_service(client, &evnt, 1000) > 0) {
		switch (evnt.type) {
			case ENET_EVENT_TYPE_RECEIVE:
				std::cout << "Packet received from server.\n";
				break;
		}
	}

	enet_peer_disconnect(peer, 0);
	while (enet_host_service(client, &evnt, 3000) > 0) {
		switch (evnt.type) {
			case ENET_EVENT_TYPE_RECEIVE:
				enet_packet_destroy(evnt.packet);
				break;
			case ENET_EVENT_TYPE_DISCONNECT:
				puts("Disconnection succeded.");
				break;
		}
	}

	return;
}
