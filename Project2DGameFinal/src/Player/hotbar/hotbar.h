#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class hotbar {
	sf::RectangleShape Hotbar;
	sf::Texture hotbarT;

public:
	hotbar();
	~hotbar();

	void draw(sf::RenderWindow& window) { window.draw(Hotbar); }
};

