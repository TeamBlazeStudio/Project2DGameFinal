#pragma once
#include <SFML/Graphics.hpp>
#include "../../TextureManager/TextureManager.h"
#include <vector>

class healt {
	int life = 100;
	int hearths = 10;
	std::vector<sf::RectangleShape> Hearths;
	static TextureManager txManager;

public:
	healt();
	~healt();
	void init(const sf::Vector2f& plPos);

	void update(const sf::Vector2f& plPos) {
		for (int i = 0; i < hearths; ++i) Hearths[i].setPosition(plPos.x + i * 60.f, plPos.y + 300.f);
	}

	void removeLife(int value);
	void addLife(int value);

	sf::Texture& textureCase(int i) {
		if (i == 1) return txManager.getTexture("assets/gui/heart.png");
		else if (i == 2) return txManager.getTexture("assets/gui/half_heart.png");
		else if (i == 3) return txManager.getTexture("assets/gui/no_heart.png");
	}

	void Draw(sf::RenderWindow& window) { for (const auto& c : Hearths) window.draw(c); }
	int getLif() { return life; }
};

