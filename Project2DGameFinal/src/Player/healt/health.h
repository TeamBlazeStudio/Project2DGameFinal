#pragma once
#include <SFML/Graphics.hpp>
#include "../../TextureManager/TextureManager.h"
#include <vector>

class health {
	int life = 100;
	int hearths = 10;
	bool isAlive = true;
	std::vector<sf::RectangleShape> Hearths;
	static TextureManager txManager;

public:
	health();
	~health();
	void init();

	void removeLife(int value);
	void changeTextureR(int val);
	void changeTextureA(int val);
	void addLife(int value);

	sf::Texture& textureCase(int i) {
		if (i == 1) return txManager.getTexture("assets/gui/heart.png");
		else if (i == 2) return txManager.getTexture("assets/gui/half_heart.png");
		else if (i == 3) return txManager.getTexture("assets/gui/no_heart.png");
	}

	void Draw(sf::RenderWindow& window) { for (const auto& c : Hearths) window.draw(c); }
	int getLif() { return life; }

	int getIsAlive() { return isAlive; }
};

