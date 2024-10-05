#include <enet/enet.h>
#include <thread>
#include "Server.h"
#include "../Client/Client.h"

void ServerThread(Server* server);
void ClientThread(Client* client);