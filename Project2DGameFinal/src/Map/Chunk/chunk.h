#pragma once
#include "../../TextureManager/TextureManager.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include <filesystem>


class chunk {
	static TextureManager txManager;

	static const int CHUNK_SIZE = 4;
	int x, y;
	int tiles_type[CHUNK_SIZE][CHUNK_SIZE];
	

	std::string ID;
	std::string folderPath;
public:
	sf::RectangleShape tiles[CHUNK_SIZE][CHUNK_SIZE];
	
	chunk(int xPos, int yPos, const std::string& folderPath, bool choise);
	chunk();
	~chunk();

	void saveToFile() const;
	void loadFromFile();

	void unloadChunk();
	void loadChunk();

	void draw(sf::RenderWindow& window);
	sf::Texture& textureCase(int i);
	int getPosX() { return x; }
	int getPosY() { return y; }
};

