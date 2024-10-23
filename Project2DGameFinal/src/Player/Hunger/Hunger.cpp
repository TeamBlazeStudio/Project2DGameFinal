#include "Hunger.h"

TextureManager Hunger::txManager;

Hunger::Hunger() { init(); }

Hunger::~Hunger() {}

void Hunger::init() {
	Hungers.resize(hungers);
	for (int i = 0; i < hungers; ++i) {
		Hungers[i].setSize(sf::Vector2f(35.f, 35.f));
		Hungers[i].setTexture(&textureCase(1));
		Hungers[i].setPosition(i * 38.f + 740, 60.f);
	}
}

