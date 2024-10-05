#pragma once
#include <enet/enet.h>
#include <iostream>
#include <string>

class Server {
	ENetHost* server{};
	ENetAddress address{};
	ENetEvent event{};

public:
	Server();
	~Server();

	bool init();
	void run();
};

