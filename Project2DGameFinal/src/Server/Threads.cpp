#include "Threads.h"

void ServerThread(Server* server) {
	server->run();
}

void ClientThread(Client* client) {
	client->run();
}