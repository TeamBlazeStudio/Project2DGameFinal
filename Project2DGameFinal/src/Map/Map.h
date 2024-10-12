#pragma once
#include "SFML/Graphics.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <utility>
#include "Chunk/chunk.h"

class Map {
    int RenderDistanceX;
    int RenderDistanceY;

    std::vector<std::vector<chunk*>> tileMap;

    int lastX{}, lastY{};
    float gridSizeF;

public:
    Map(sf::Vector2u windowSize);
    ~Map();

    void init(float gridSizeF);

    //void unloadChunk();
    //void loadChunk();
    //void saveChunk();

    //int getSize() { return RenderDistance; }
    void draw(sf::RenderWindow& window);

};