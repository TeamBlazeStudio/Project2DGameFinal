#pragma once
#include <SFML/Graphics.hpp>
#include "../../TextureManager/TextureManager.h"
#include <vector>

class Mana {
	int mana = 250;

	sf::RectangleShape ManaIcon;
	sf::Text textMana;
	sf::Font font;
	sf::Texture textureMana;

public:
	Mana();
	~Mana();
	void init();

	void removeMana(int value);
	void addMana(int value);

	void Draw(sf::RenderWindow& window) { window.draw(ManaIcon); window.draw(textMana); }
	int getHunger() { return mana; }

};

