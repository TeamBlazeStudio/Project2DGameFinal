#pragma once
#include <SFML/Graphics.hpp>
#include "../../TextureManager/TextureManager.h"

class OverlayBlock {
	sf::RectangleShape hover;

public:
	OverlayBlock();
	~OverlayBlock();

	void update(float x, float y) { hover.setPosition(x, y); }

	void draw(sf::RenderWindow& window) { window.draw(hover); }
};

