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
    int halfRenderX, halfRenderY;

    std::vector<std::vector<chunk*>> tileMap;
    //chunk* tileMap[7][5];

    int lastX{}, lastY{};
    int X1 = 7, Y1 = 0;
    int X_1 = 0;
    float gridSizeF;

    std::string folderPath;

public:
    Map(sf::Vector2u windowSize);
    ~Map();

    void init(float gridSizeF, sf::Vector2f plPos, const std::string& path, bool choise);
    void checkChunks(sf::Vector2f plPos);

    void placeBlock(int chunkX, int chunkY, int tileX, int tileY) {
        if (tileMap[chunkX][chunkY] != nullptr) {
            if (tileX >= 0 && tileX < 4 && tileY >= 0 && tileY < 4) {
                tileMap[chunkX][chunkY]->tiles[tileX][tileY].setTexture(NULL);
            }
        }
    }

    //void unloadChunk();
    //void loadChunk();

    //int getSize() { return RenderDistance; }
    void draw(sf::RenderWindow& window);

};