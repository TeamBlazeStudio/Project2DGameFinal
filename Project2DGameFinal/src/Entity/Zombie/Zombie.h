#pragma once
#include "../Entity.h"

class Zombie : public Entity{

public:
	Zombie(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, int x, int y) : 
		Entity(texture, imageCount, switchTime, x, y) {}
	~Zombie() {}

	void Update(sf::Vector2f plPos, float deltaTime);
};

