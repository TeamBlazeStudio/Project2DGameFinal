#pragma once
#include <enet/enet.h>
#include <iostream>
#include <string>

class Client {
	ENetHost* client;
	ENetAddress address;
	ENetEvent evnt;
	ENetPeer* peer;

public:
	Client();
	~Client();

	bool init();
	void run();

	void SendPacket(const std::string& data);
};

