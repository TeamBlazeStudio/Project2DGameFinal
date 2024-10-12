#include "TextureManager.h"

sf::Texture& TextureManager::getTexture(const std::string& filename) {

	//check if the texture is already loaded in memory
	auto it = textures.find(filename);
	if (it != textures.end()) it->second;

	//if the texture isn't already loaded in memory, load it
	sf::Texture texture;
	if (texture.loadFromFile(filename)) textures[filename] = std::move(texture);
	else throw std::runtime_error("Unable to load texture: " + filename);

	return textures[filename];
}

TextureManager::TextureManager() {}

TextureManager::~TextureManager() {}