#pragma once
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include "../Animation/animation.h"
#include "healt/health.h"
#include "Hunger/Hunger.h"
#include "mana/mana.h"
#include "inventory/inventory.h"
#include "hotbar/hotbar.h"
#include "overlay/OverlayBlock.h"

class Player {
	sf::RectangleShape player;
	sf::Vector2i position;

	float speed = 120.f;
	float lifePoints = 100.f;
	bool isAlive = false;

	unsigned int row;
	bool faceRight;

	sf::Clock clock;
	bool buttonLocked = false;
	sf::Time lockDuration = sf::seconds(0.2f);
	sf::Time elapsedTime;

	bool invBtn = false;

	Animation animation;
	health plLife;
	Hunger plhunger;
	Mana plmana;
	inventory Inv;
	hotbar plHotbar;
	OverlayBlock blockHover;

public:
	Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float x = 0, float y = 0);
	~Player();

	void MoveXpos(float dt) { player.move(speed * dt, 0.f); }
	void MoveXneg(float dt) { player.move(-speed * dt, 0.f); }
	void MoveYpos(float dt) { player.move(0.f, speed * dt * 2); }
	void Moveyneg(float dt) { player.move(0.f, -speed * dt); }

	void setTextureRect(sf::IntRect uvRect) { player.setTextureRect(uvRect); }
	//need a function for remove and add life (i think i need to put it inside the update)
	void Update(float deltaTime, int val, sf::RenderWindow& window, float o_x, float o_y);

	void Draw(sf::RenderWindow& window) { window.draw(player); }
	void drawPlayerBars(sf::RenderWindow& window) {
		plLife.Draw(window);
		plhunger.Draw(window);
		plmana.Draw(window);
		plHotbar.draw(window);
		if (invBtn) Inv.draw(window);
	}
	void drawHover(sf::RenderWindow& window) { blockHover.draw(window); }
	const sf::Vector2f& getPosition() const { return player.getPosition(); }

	sf::RectangleShape draw() { return player; }
	

	sf::Texture playertexture;
};

