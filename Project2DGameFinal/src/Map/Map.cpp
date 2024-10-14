#include "Map.h"
#include <iostream>


Map::Map(sf::Vector2u windowSize) {
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    unsigned int windowWidth = windowSize.x;
    unsigned int windowHeight = windowSize.y;

    int chunkPixelWidth = 400;
    int chunkPixelHeight = 400;

    int numChunksX = (windowWidth + chunkPixelWidth - 1) / chunkPixelWidth;
    int numChunksY = (windowHeight + chunkPixelHeight - 1) / chunkPixelHeight;

    RenderDistanceX = numChunksX;
    RenderDistanceY = numChunksY;

    tileMap = std::vector<std::vector<chunk*>>(RenderDistanceX, std::vector<chunk*>(RenderDistanceY, nullptr));
}

void Map::init(float gridSizeF, sf::Vector2f plPos) {
    this->gridSizeF = gridSizeF;
    int playerChunkX = static_cast<int>(plPos.x / 400);
    int playerChunkY = static_cast<int>(plPos.y / 400);

    //player chunk positon
    std::cout << playerChunkX << " - " << playerChunkY << std::endl;

    for (int i = 0; i < RenderDistanceX; ++i) {
        for (int j = 0; j < RenderDistanceY; ++j) {
            tileMap[i][j] = new chunk(i, j);

            float globalPosX = i * 400;
            float globalPosY = j * 400;

            for (int k = 0; k < 4; ++k) {
                for (int l = 0; l < 4; ++l) {
                    tileMap[i][j]->tiles[k][l].setPosition(globalPosX + k * 100, globalPosY + l * 100);
                }
            }
        }
    }

}

void Map::draw(sf::RenderWindow& window) {
    for (int x = 0; x < RenderDistanceX; ++x) {
        for (int y = 0; y < RenderDistanceY; ++y) {
            tileMap[x][y]->draw(window);

        }
    }
}

Map::~Map() {}
