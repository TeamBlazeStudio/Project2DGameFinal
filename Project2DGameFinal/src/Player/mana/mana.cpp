#include "mana.h"

Mana::Mana() { init(); }

Mana::~Mana() {}

void Mana::init() {
	textureMana.loadFromFile("assets/gui/mana.png");
	font.loadFromFile("Font/Movistar Text Regular.ttf");
	ManaIcon.setSize(sf::Vector2f(35.f, 35.f));
	ManaIcon.setTexture(&textureMana);
	ManaIcon.setPosition(1125, 20.f);
	textMana.setFont(font);
	textMana.setString("0/250");
	textMana.setPosition(1165, 20.f);
}

void Mana::removeMana(int value) {}

void Mana::addMana(int value) {}
