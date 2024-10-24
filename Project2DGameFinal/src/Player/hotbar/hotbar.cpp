#include "hotbar.h"

hotbar::hotbar(){
	if (!hotbarT.loadFromFile("assets/gui/hotbar.png")) {
		std::cerr << "Error while loading the hotbar texture." << std::endl;
		exit(EXIT_FAILURE);
	}
	Hotbar.setTexture(&hotbarT);
	Hotbar.setSize(sf::Vector2f(750.f, 100.f));
	Hotbar.setPosition(580.f, 900.f);
}

hotbar::~hotbar() {}
