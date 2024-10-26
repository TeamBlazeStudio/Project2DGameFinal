#include "inventory.h"

//const int inventory::invSlot = 27;

inventory::inventory() {
	if (!invTexture.loadFromFile("assets/gui/inventory.png") ) {
		std::cerr << "Error while loading inventory texture." << std::endl;
		exit(EXIT_FAILURE);
	}
	if (!miniPlTexture.loadFromFile("assets/player/Player.png")) {
		std::cerr << "Error while loading mini player in the inventory texture." << std::endl;
		exit(EXIT_FAILURE);
	}
	
	inv.setTexture(&invTexture);
	inv.setSize(sf::Vector2f(750.f, 750.f));
	inv.setPosition(580.f, 125.f);

	miniPlayer.setTexture(&miniPlTexture);
	miniPlayer.setSize(sf::Vector2f(150.f, 150.f));
	miniPlayer.setPosition(700.f, 635.f);

	
	slotTex.loadFromFile("assets/items/null.png");
	int y = 275;
	for (int i = 0; i < 9; ++i) {
		for (int j = 0; j < 3; ++j) {
			//add a function for load an inventory if there is an inventory to load
			slot[i][j].setTexture(&slotTex);
			slot[i][j].setSize(sf::Vector2f(60.f, 60.f));
			slot[i][j].setPosition(i * 76 + 625, y);
			y += 80;
		}
		y = 275;
	}
}

void inventory::update(const sf::IntRect& animation,const bool& faceRight) {
	miniPlayer.setTextureRect(animation);
	if (!faceRight) miniPlayer.setPosition(690.f, 635.f);
	else miniPlayer.setPosition(705.f, 640.f);
}

inventory::~inventory() {}