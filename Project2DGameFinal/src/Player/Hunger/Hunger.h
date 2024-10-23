#pragma once
#include <SFML/Graphics.hpp>
#include "../../TextureManager/TextureManager.h"
#include <vector>

class Hunger {
	int hunger = 100;
	int hungers = 10;

	std::vector<sf::RectangleShape> Hungers;
	static TextureManager txManager;

public:
	Hunger();
	~Hunger();
	void init();

	void removeHunger(int value);
	void changeTextureR(int val);
	void changeTextureA(int val);
	void addHunger(int value);

	sf::Texture& textureCase(int i) {
		if (i == 1) return txManager.getTexture("assets/gui/hunger.png");
		else if (i == 2) return txManager.getTexture("assets/gui/half_hunger.png");
		else if (i == 3) return txManager.getTexture("assets/gui/no_hunger.png");
	}

	void Draw(sf::RenderWindow& window) { for (const auto& c : Hungers) window.draw(c); }
	int getHunger() { return hunger; }

};

