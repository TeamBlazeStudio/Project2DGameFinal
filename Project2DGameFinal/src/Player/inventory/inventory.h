#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "../../Animation/animation.h"

class inventory {
	sf::RectangleShape inv;
	sf::Texture invTexture;

	sf::RectangleShape miniPlayer;
	sf::Texture miniPlTexture;

	static const int invSlot = 27;
	sf::RectangleShape slot[invSlot][invSlot];
	sf::Texture slotTex;

public:
	inventory();
	~inventory();

	void update(const sf::IntRect& animation, const bool& faceRight);

	void draw(sf::RenderWindow& window) { 
		window.draw(inv); 
		window.draw(miniPlayer); 
		for (int i = 0; i < 9; ++i) for (int j = 0; j < 3; ++j) window.draw(slot[i][j]);
	}

};

