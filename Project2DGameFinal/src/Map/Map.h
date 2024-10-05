#pragma once
#include "SFML/Graphics.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <utility>

class Map {
    const int mapSize = 100;
    std::vector<std::vector<sf::RectangleShape>> tileMap;

    sf::Texture grass, sand;

    int lastX{}, lastY{};
    float gridSizeF;
    //int chunkSize{};

    //int chunkCounter{};

public:
    Map();
    ~Map();

    void init(float gridSizeF);

    //void unloadChunk();
    //void loadChunk();
    //void saveChunk();

    int getSize() { return mapSize; }
    sf::RectangleShape draw(int x, int y) { return tileMap[x][y]; }

    void draw(sf::RenderWindow& window);

};