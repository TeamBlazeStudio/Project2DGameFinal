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

    sf::Vector2f getclosestTile(float x, float y, int ChunkX, int ChunkY) {
        sf::Vector2f finalPos;
        for (int i = 0; i < tileMap.size(); ++i) {
            for (int j = 0; j < tileMap[i].size(); ++j) {
                if (std::abs(tileMap[ChunkX][ChunkY]->tiles[i][j].getPosition().x - x) <= 50 &&
                    std::abs(tileMap[ChunkX][ChunkY]->tiles[i][j].getPosition().y - y) <= 50) {
                    finalPos.x = tileMap[ChunkX][ChunkY]->tiles[i][j].getPosition().x;
                    finalPos.y = tileMap[ChunkX][ChunkY]->tiles[i][j].getPosition().y;
                    return finalPos;
                }
            }
        }
    }

    //void unloadChunk();
    //void loadChunk();

    //int getSize() { return RenderDistance; }
    void draw(sf::RenderWindow& window);

};