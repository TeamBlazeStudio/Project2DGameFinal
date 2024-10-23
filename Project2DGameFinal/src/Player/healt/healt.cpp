#include "healt.h"

TextureManager healt::txManager;

healt::healt() {}

void healt::init(const sf::Vector2f& plPos) {
	Hearths.resize(10);
	for (int i = 0; i < hearths; ++i) {
		Hearths[i].setSize(sf::Vector2f(50.f, 50.f));
		Hearths[i].setTexture(&textureCase(1));
		Hearths[i].setPosition(plPos.x + i * 60.f, plPos.y + 100.f);
	}
}

healt::~healt() {}

void healt::removeLife(int value) {

}

void healt::addLife(int value) {

}
