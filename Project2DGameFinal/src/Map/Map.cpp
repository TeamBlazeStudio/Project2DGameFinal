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

    if (RenderDistanceX <= 0 || RenderDistanceY <= 0) {
        std::cerr << "Error: Invalid RenderDistanceX or RenderDistanceY values." << std::endl;
        exit(EXIT_FAILURE);
    }

    //tileMap = std::vector<std::vector<chunk*>>(RenderDistanceX, std::vector<chunk*>(RenderDistanceY, nullptr));

}

void Map::init(float gridSizeF, sf::Vector2f plPos) {
    this->gridSizeF = gridSizeF;
    int playerChunkX = static_cast<int>(plPos.x / 400);
    int playerChunkY = static_cast<int>(plPos.y / 400);
    lastX = playerChunkX;
    lastY = playerChunkY;

    halfRenderX = RenderDistanceX / 2;
    halfRenderY = RenderDistanceY / 2;

    //need to add a function for load a chunk already generated
    if (tileMap.empty()) {
        tileMap.resize(RenderDistanceX);
        for (int i = 0; i < RenderDistanceX; ++i) {
            tileMap[i].resize(RenderDistanceY);
        }
    }

    //this code generate new chunks
    for (int i = 0; i < RenderDistanceX; ++i) {
        for (int j = 0; j < RenderDistanceY; ++j) {
            int chunkX = playerChunkX + (i - halfRenderX);
            int chunkY = playerChunkY + (j - halfRenderY);

            if (tileMap[i][j] == nullptr) tileMap[i][j] = new chunk(chunkX, chunkY);

            float globalPosX = chunkX * 400;
            float globalPosY = chunkY * 400;

            for (int k = 0; k < 4; ++k) {
                for (int l = 0; l < 4; ++l) {
                    tileMap[i][j]->tiles[k][l].setPosition(globalPosX + k * 100, globalPosY + l * 100);
                }
            }
        }
    }
}

void Map::checkChunks(sf::Vector2f plPos) {
    int playerChunkX = static_cast<int>(plPos.x / 400);
    int playerChunkY = static_cast<int>(std::floor(plPos.y / 400));
    const float activationDistance = 200.0f;
    std::cout << playerChunkX << " - " << playerChunkY << std::endl;


    //right
    if (lastX < playerChunkX) {

        //std::cout << playerChunkX << " - 0" << std::endl;

        if (0 < tileMap.size()) {
            for (int i = 0; i < RenderDistanceY; ++i) {
                if (tileMap[0][i] != nullptr) {
                    tileMap[0][i]->unloadChunk();
                    delete tileMap[0][i];
                    tileMap[0][i] = nullptr;
                    //std::cout << "deleted " << "0 : " << i << std::endl;
                }
            }

            tileMap.erase(tileMap.begin());
            tileMap.push_back(std::vector<chunk*>(RenderDistanceY, nullptr));


            for (int i = 0; i < RenderDistanceY; ++i) {
                int chunkX = playerChunkX + 2;
                int chunkY = playerChunkY + (i - halfRenderY);

                float globalPosX = chunkX * 400;
                float globalPosY = chunkY * 400;

                tileMap.back()[i] = new chunk(chunkX, chunkY);

                for (int k = 0; k < 4; ++k) {
                    for (int l = 0; l < 4; ++l) {
                        tileMap.back()[i]->tiles[k][l].setPosition(globalPosX + k * 100, globalPosY + l * 100);
                    }
                }
            }
        }
        //std::cout << "generated" << std::endl;
        
    }
    //left
    else if (lastX > playerChunkX) {
        int deleteChunkX = tileMap.size() - 1;

        if (deleteChunkX >= 0) {
            for (int i = 0; i < RenderDistanceY; ++i) {
                if (tileMap[deleteChunkX][i] != nullptr) {
                    tileMap[deleteChunkX][i]->unloadChunk();
                    delete tileMap[deleteChunkX][i];
                    tileMap[deleteChunkX][i] = nullptr;
                }
            }

            tileMap.erase(tileMap.begin() + deleteChunkX);
        }

        tileMap.insert(tileMap.begin(), std::vector<chunk*>(RenderDistanceY, nullptr));

        for (int i = 0; i < RenderDistanceY; ++i) {
            int chunkX = playerChunkX - 2;
            int chunkY = playerChunkY + (i - halfRenderY);

            float globalPosX = chunkX * 400;
            float globalPosY = chunkY * 400;

            tileMap.front()[i] = new chunk(chunkX, chunkY);

            for (int k = 0; k < 4; ++k) {
                for (int l = 0; l < 4; ++l) {
                    tileMap.front()[i]->tiles[k][l].setPosition(globalPosX + k * 100, globalPosY + l * 100);
                }
            }
        }
    }
    //up
    else if (lastY > playerChunkY) {
        int deleteChunkY = tileMap[0].size() - 1;
        //std::cout << deleteChunkY << "-" << RenderDistanceY << std::endl;

        if (deleteChunkY >= 0) {
            for (int i = 0; i < RenderDistanceX; ++i) {
                if (tileMap[i][deleteChunkY] != nullptr) {
                    tileMap[i][deleteChunkY]->unloadChunk();
                    delete tileMap[i][deleteChunkY];
                    tileMap[i][deleteChunkY] = nullptr;
                }
            }

            for (int i = 0; i < RenderDistanceX; ++i) {
                tileMap[i].erase(tileMap[i].begin() + deleteChunkY);
            }

            for (int i = 0; i < RenderDistanceX; ++i) tileMap[i].insert(tileMap[i].begin(), nullptr);

            for (int i = 0; i < RenderDistanceX; ++i) {
                int chunkX = playerChunkX + (i - halfRenderX);
                int chunkY = playerChunkY - 1;

                float globalPosX = chunkX * 400;
                float globalPosY = chunkY * 400;

                tileMap[i][0] = new chunk(chunkX, chunkY);

                for (int k = 0; k < 4; ++k) {
                    for (int l = 0; l < 4; ++l) {
                        tileMap[i][0]->tiles[k][l].setPosition(globalPosX + k * 100, globalPosY + l * 100);
                    }
                }
            }
        }
        
    }
    //down
    else if (lastY < playerChunkY) {
        int deleteChunkY = 0;

        if (tileMap[0].size() > 0) {
            for (int i = 0; i < RenderDistanceX; ++i) {
                if (tileMap[i][deleteChunkY] != nullptr) {
                    tileMap[i][deleteChunkY]->unloadChunk();
                    delete tileMap[i][deleteChunkY];
                    tileMap[i][deleteChunkY] = nullptr;
                    tileMap[i].erase(tileMap[i].begin() + deleteChunkY);
                }
            }

            for (int i = 0; i < RenderDistanceX; ++i) tileMap[i].push_back(nullptr);

            for (int i = 0; i < RenderDistanceX; ++i) {
                int chunkX = playerChunkX + (i - halfRenderX);
                int chunkY = playerChunkY + (RenderDistanceY / 2);

                float globalPosX = chunkX * 400;
                float globalPosY = chunkY * 400;

                tileMap[i].back() = new chunk(chunkX, chunkY);

                for (int k = 0; k < 4; ++k) {
                    for (int l = 0; l < 4; ++l) {
                        tileMap[i].back()->tiles[k][l].setPosition(globalPosX + k * 100, globalPosY + l * 100);
                    }
                }
            }
        }

    }

    

    lastX = playerChunkX;
    lastY = playerChunkY;
}

void Map::draw(sf::RenderWindow& window) {

    for (int x = 0; x < tileMap.size(); ++x) {
        for (int y = 0; y < tileMap[x].size(); ++y) {
            tileMap[x][y]->draw(window);
        }
    }
    
}

Map::~Map() {}
