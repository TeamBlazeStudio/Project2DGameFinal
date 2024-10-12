#pragma once
#include "../../TextureManager/TextureManager.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>
#include <string>
#include <iostream>

class chunk {
	static TextureManager txManager;

	static const int CHUNK_SIZE = 4;
	int x, y;
	int tiles_type[CHUNK_SIZE][CHUNK_SIZE];
	

	std::string ID;
	std::string forlderPath;
public:
	sf::RectangleShape tiles[CHUNK_SIZE][CHUNK_SIZE];
	
	chunk(int xPos, int yPos);
	chunk();
	~chunk();

	void saveToFile(const std::string& folderPath) const;
	void loadFromFile();

	void unloadChunk();
	void loadChunk();

	void draw(sf::RenderWindow& window);
	sf::Texture& textureCase(int i);
};

