#include "Entity.h"

Entity::Entity(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, int x, int y) :
	animation(texture, imageCount, switchTime) 
{
	entity.setSize(sf::Vector2f(135.0f, 135.0f));
	entity.setTexture(texture);
	entity.setPosition(x, y);
	position.x = x;
	position.y = y;

	isAlive = true;
}

Entity::~Entity() {}
