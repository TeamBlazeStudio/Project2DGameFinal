#pragma once
#include <SFML/Graphics.hpp>
#include "../Animation/animation.h"

class Entity {
protected:
	sf::RectangleShape entity;
	sf::Texture entityT;
	sf::Vector2i position;

	float speed = 90.f;
	float lifePoints = 100.f;
	bool isAlive = false;

	unsigned int row;
	bool faceRight;

	Animation animation;

public:
	Entity(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, int x, int y);
	~Entity();

	void draw(sf::RenderWindow& window) { window.draw(entity); }
};

