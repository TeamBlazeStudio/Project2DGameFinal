#include "Map.h"
#include <iostream>


Map::Map() : mapSize(4), tileMap(mapSize, std::vector<sf::RectangleShape>(mapSize)) {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
}

void Map::init(float gridSizeF) {
    this->gridSizeF = gridSizeF;

    grass.loadFromFile("assets/block/grass_block.png");
    sand.loadFromFile("assets/block/sand.png");
    int counter = 0;

    for (int x = 0; x < mapSize; ++x) {
        for (int y = 0; y < mapSize; ++y) {
            ++counter;

            tileMap[x][y].setSize(sf::Vector2f(gridSizeF, gridSizeF));
            tileMap[x][y].setTexture(&grass);

            tileMap[x][y].setPosition(x * gridSizeF, y * gridSizeF);

        }
    }

    int ran = rand() % 4;
    int ran2 = rand() % 4;
    tileMap[ran][ran2].setTexture(&sand);

}

void Map::draw(sf::RenderWindow& window) {
    for (int x = 0; x < mapSize; ++x) {
        for (int y = 0; y < mapSize; ++y) {
            window.draw(tileMap[x][y]);
        }
    }
}

Map::~Map() {}
