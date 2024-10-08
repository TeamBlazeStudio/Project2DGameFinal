#pragma once
#include <enet/enet.h>
#include <iostream>
#include <string>
#include <vector>

class Server {
	ENetHost* server{};
	ENetAddress address{};
	ENetEvent event{};

	std::vector<std::string> users;

public:
	Server();
	~Server();

	bool init();
	void run();

	bool ReceivePacket(ENetHost* server, char* data);
	void SendPacket(const std::string& data);
};

