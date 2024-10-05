#include "Camera.h"

Camera::Camera(const Window& game, float centerX, float centerY, float lerpFactor) : lerpFactor(lerpFactor) {
	view.setSize(game.window.getSize().x, game.window.getSize().y);
	view.setCenter(centerX, centerY);
	game.window.setView(view);
	position.x = centerX;
	position.y = centerY;
}

void Camera::MoveXpos(float dt) { view.move(viewSpeed * dt, 0.f); }
void Camera::MoveXneg(float dt) { view.move(-viewSpeed * dt, 0.f); }
void Camera::MoveYpos(float dt) { view.move(0.f, viewSpeed * dt); }
void Camera::Moveyneg(float dt) { view.move(0.f, -viewSpeed * dt); }

Camera::~Camera() {}

void Camera::update(const sf::Vector2f& playerPosition) {
	position.x += (playerPosition.x - position.x + 100) * lerpFactor;
	position.y += (playerPosition.y - position.y) * lerpFactor;
	view.setCenter(position);
}