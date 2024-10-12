#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
#include <iostream>

class TextureManager {
	std::unordered_map<std::string, sf::Texture> textures;

public:
	TextureManager();
	~TextureManager();

	sf::Texture& getTexture(const std::string& filename);

	void clear() { textures.clear(); }
};

