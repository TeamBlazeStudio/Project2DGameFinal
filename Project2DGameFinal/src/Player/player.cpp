#include "Player.h"
#include <iostream>

Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float x, float y) :
	animation(texture, imageCount, switchTime), playertexture(*texture)
{
	row = 0;
	faceRight = true;

	player.setSize(sf::Vector2f(135.0f, 135.0f));
	player.setTexture(texture);
	player.setPosition(x, y);
	position.x = x;
	position.y = y;

	plLife.init(player.getPosition());

}

void Player::Update(float deltaTime) {
	sf::Vector2f movement(0.0f, 0.0f);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) movement.x -= speed * deltaTime;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) movement.x += speed * deltaTime;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) { movement.y -= speed * deltaTime; row = 2; }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) { movement.y += speed * deltaTime; row = 2; }

	if (movement.x == 0.0f && movement.y == 0.0f) row = 0;
	else if (movement.x != 0.0f) {
		row = 1;
		if (movement.x > 0.0f) faceRight = true;
		else faceRight = false;
	}
	animation.Update(row, deltaTime, faceRight);
	player.setTextureRect(animation.uvRect);
	player.move(movement);
	plLife.update(player.getPosition());
}

Player::~Player() {}