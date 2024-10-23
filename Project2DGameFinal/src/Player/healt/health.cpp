#include "health.h"

TextureManager health::txManager;

health::health() { init(); }

void health::init() {
	Hearths.resize(hearths);
	for (int i = 0; i < hearths; ++i) {
		Hearths[i].setSize(sf::Vector2f(35.f, 35.f));
		Hearths[i].setTexture(&textureCase(1));
		Hearths[i].setPosition(i * 38.f + 740, 20.f);
	}
}

health::~health() {}

void health::changeTextureR(int val) {
	int v = Hearths.size() - 1;
	bool doIt = false;

	if (val % 10 == 5) { val -= 5; doIt = true; }

	while (val) {
		Hearths[v--].setTexture(&textureCase(3));
		val -= 10;
	}

	if (doIt) Hearths[v].setTexture(&textureCase(2));
}

void health::changeTextureA(int val) {
	int v = Hearths.size() - 1;
	bool doIt = false;

	if (val % 10 == 5) { val -= 5; doIt = true; }

	while (val) {
		Hearths[v--].setTexture(&textureCase(1));
		val -= 10;
	}

	if (doIt) Hearths[v].setTexture(&textureCase(2));
}

void health::removeLife(int value) {
	life -= value;

	if (life <= 95 && life > 90) changeTextureR(5);
	else if (life == 90) changeTextureR(10);
	else if (life <= 85 && life > 80) changeTextureR(15);
	else if (life == 80) changeTextureR(20);
	else if (life <= 75 && life > 70) changeTextureR(25);
	else if (life == 70) changeTextureR(30);
	else if (life <= 65 && life > 60) changeTextureR(35);
	else if (life == 60) changeTextureR(40);
	else if (life <= 55 && life > 50) changeTextureR(45);
	else if (life == 50) changeTextureR(50);
	else if (life <= 45 && life > 40) changeTextureR(55);
	else if (life == 40) changeTextureR(60);
	else if (life <= 35 && life > 30) changeTextureR(65);
	else if (life == 30) changeTextureR(70);
	else if (life <= 25 && life > 20) changeTextureR(75);
	else if (life == 20) changeTextureR(80);
	else if (life <= 15 && life > 10) changeTextureR(85);
	else if (life == 10) changeTextureR(90);
	else if (life <= 5 && life > 0) changeTextureR(95);
	else if (life == 0) { changeTextureR(100); isAlive = false; }

}

void health::addLife(int value) {
	if (life != 0) {
		life += value;

		if (life <= 95 && life > 90) changeTextureA(5);
		else if (life == 90) changeTextureA(10);
		else if (life <= 85 && life > 80) changeTextureA(15);
		else if (life == 80) changeTextureA(20);
		else if (life <= 75 && life > 70) changeTextureA(25);
		else if (life == 70) changeTextureA(30);
		else if (life <= 65 && life > 60) changeTextureA(35);
		else if (life == 60) changeTextureA(40);
		else if (life <= 55 && life > 50) changeTextureA(45);
		else if (life == 50) changeTextureA(50);
		else if (life <= 45 && life > 40) changeTextureA(55);
		else if (life == 40) changeTextureA(60);
		else if (life <= 35 && life > 30) changeTextureA(65);
		else if (life == 30) changeTextureA(70);
		else if (life <= 25 && life > 20) changeTextureA(75);
		else if (life == 20) changeTextureA(80);
		else if (life <= 15 && life > 10) changeTextureA(85);
		else if (life == 10) changeTextureA(90);
		else if (life <= 5 && life > 0) changeTextureA(95);
	}
}
