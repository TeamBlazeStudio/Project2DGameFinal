#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "../window/window.h"

class Camera {
	sf::View view;
	sf::Vector2f position;
	float viewSpeed = 200.f;
	float lerpFactor;

public:
	Camera(const Window& game, float centerX = 0, float centerY = 0, float lerpFactor = 0.1f);
	~Camera();

	sf::View getView() { return view; }
	float getSpeed() { return viewSpeed; }

	float getCenterXneg(float gridSizeF, int i) { return view.getCenter().x / gridSizeF - i; }
	float getCenterXpos(float gridSizeF, int i) { return view.getCenter().x / gridSizeF + i; }
	float getCenterYneg(float gridSizeF, int i) { return view.getCenter().y / gridSizeF - i; }
	float getCenterYpos(float gridSizeF, int i) { return view.getCenter().y / gridSizeF + i; }

	void MoveXpos(float dt);
	void MoveXneg(float dt);
	void MoveYpos(float dt);
	void Moveyneg(float dt);

	const sf::View& getView() const { return view; }

	void update(const sf::Vector2f& playerPos);
};

