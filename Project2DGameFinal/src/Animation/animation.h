#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class Animation {
	sf::Vector2u imageCount;
	sf::Vector2u currentImage;

	float totalTime;
	float switchTime;

public:
	Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime);
	~Animation();

	void Update(int row, float deltaTime, bool faceRight);

	sf::IntRect uvRect;
};