#pragma once
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include "../Animation/animation.h"
#include "healt/health.h"
#include "Hunger/Hunger.h"
#include "mana/mana.h"

class Player {
	sf::RectangleShape player;
	sf::Vector2i position;

	float speed = 120.f;
	float lifePoints = 100.f;
	bool isAlive = false;

	unsigned int row;
	bool faceRight;
	Animation animation;
	health plLife;
	Hunger plhunger;
	Mana plmana;

public:
	Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float x = 0, float y = 0);
	~Player();

	void MoveXpos(float dt) { player.move(speed * dt, 0.f); }
	void MoveXneg(float dt) { player.move(-speed * dt, 0.f); }
	void MoveYpos(float dt) { player.move(0.f, speed * dt * 2); }
	void Moveyneg(float dt) { player.move(0.f, -speed * dt); }

	void setTextureRect(sf::IntRect uvRect) { player.setTextureRect(uvRect); }
	//need a function for remove and add life (i think i need to put it inside the update)
	void Update(float deltaTime, int val);

	void Draw(sf::RenderWindow& window) { window.draw(player); }
	void drawPlayerBars(sf::RenderWindow& window) {
		plLife.Draw(window);
		plhunger.Draw(window);
		plmana.Draw(window);
	}

	const sf::Vector2f& getPosition() const { return player.getPosition(); }

	sf::RectangleShape draw() { return player; }
	

	sf::Texture playertexture;
};

