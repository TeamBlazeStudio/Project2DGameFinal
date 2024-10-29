#include "Zombie.h"
#include <iostream>

void Zombie::Update(sf::Vector2f plPos, float deltaTime) {
	if (isAlive) {
		float dx = plPos.x - position.x;
		float dy = plPos.y - position.y;
		float distance = std::sqrt(dx * dx + dy * dy);

		if (distance <= 400.f ) {
			float directionX = dx / distance;
			float directionY = dy / distance;

			if (directionX == -1) {
				position.x += directionX * speed * deltaTime;
				position.y += directionY * speed * deltaTime;
			}
			else {
				position.x += directionX + speed * deltaTime;
				position.y += directionY + speed * deltaTime;
			}

			entity.setPosition(position.x, position.y);

			if (std::abs(directionX) > std::abs(directionY)) {
				row = 1;
				faceRight = (directionX > 0);
			}
			else {
				row = (directionY > 0) ? 3 : 2;
			}
		
		}
		else row = 0;

		animation.Update(row, deltaTime, faceRight);
		entity.setTextureRect(animation.uvRect);
	
	}
}
