#pragma once

// !!! This file is only for the main !!!

#include <iostream>
#include <filesystem>
#include <string>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <enet/enet.h>


// ##### Custom Library #####

#include "Window/window.h"
#include "Animation/animation.h"
#include "Player/player.h"
#include "Map/Map.h"
#include "Camera/camera.h"
#include "MainMenu/MainMenu.h"
#include "MainMenu/SingleplayerMenu/SingleplayerMenu.h"
#include "MainMenu/NewWorldMenu/NewWorldMenu.h"
#include "MainMenu/LoadWorldMenu/LoadWorldMenu.h"
#include "Entity/Zombie/Zombie.h"


// ##### Multiplayer #####
#include "Server/Server.h"
#include "Client/Client.h"
#include "Server/Threads.h"
#include <thread>