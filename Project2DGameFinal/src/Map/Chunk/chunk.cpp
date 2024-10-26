#include "chunk.h"

TextureManager chunk::txManager;

//create new chunks
chunk::chunk(int xpos, int ypos, const std::string& folderPath, bool choise) : x(xpos), y(ypos), folderPath(folderPath) {
    for (int i = 0; i < CHUNK_SIZE; ++i) {
        for (int j = 0; j < CHUNK_SIZE; ++j) {
            tiles_type[i][j] = 1;
            tiles[i][j].setSize(sf::Vector2f(100.f, 100.f));
            tiles[i][j].setOutlineColor(sf::Color::Green);
            tiles[i][j].setOutlineThickness(2.f);
            tiles[i][j].setTexture(&textureCase(tiles_type[i][j]));
            tiles[i][j].setPosition(i * 100.f, j * 100.f);
        }
    }
    
    if (!choise) saveToFile();
    else loadFromFile();
}

//load old chunks
chunk::chunk() {}

chunk::~chunk() {}


void chunk::saveToFile() const {
    
    //load directory
    if (std::filesystem::exists(folderPath) && std::filesystem::is_directory(folderPath)) {
        std::string fileName = folderPath + "/c" + std::to_string(x) + "_" + std::to_string(y) + ".txt";
        std::ofstream file(fileName);
        if (file.is_open()) {
            for (int i = 0; i < CHUNK_SIZE; ++i) {
                for (int j = 0; j < CHUNK_SIZE; ++j) {
                    file << tiles_type[i][j];
                    if (j < CHUNK_SIZE - 1) file << ",";
                }
                file << "\n";
            }
        }
        else {
            std::cerr << "error while trying to open the folderpath" << std::endl;
            exit(EXIT_FAILURE);
        }

        file.close();
    }
    //create a directory
    else if (std::filesystem::create_directories(folderPath)) {
        std::string fileName = folderPath + "/c" + std::to_string(x) + "_" + std::to_string(y) + ".txt";
        std::ofstream file(fileName);
        if (file.is_open()) {
            for (int i = 0; i < CHUNK_SIZE; ++i) {
                for (int j = 0; j < CHUNK_SIZE; ++j) {
                    file << tiles_type[i][j];
                    if (j < CHUNK_SIZE - 1) file << ",";
                }
                file << "\n";
            }
        }
        else {
            std::cerr << "error while trying to open the folderpath" << std::endl;
            exit(EXIT_FAILURE);
        }

        file.close();
    }
    
}

void chunk::loadFromFile() {
    std::string fileName = folderPath + "/c" + std::to_string(x) + "_" + std::to_string(y) + ".txt";
    std::ifstream file(fileName);
    if (file.is_open()) {
        std::string line;
        for (int i = 0; i < CHUNK_SIZE && std::getline(file, line); ++i) {
            size_t start = 0;
            size_t end = line.find(",");
            int j = 0;
            while (end != std::string::npos && j < CHUNK_SIZE) {
                tiles_type[i][j] = std::stoi(line.substr(start, end - start));
                start = end + 1;
                end = line.find(",", start);
                ++j;
            }
        }
    }
    else {
        std::cerr << "error: folderpath not found or file not found" << std::endl;
        exit(EXIT_FAILURE);
    }
    file.close();
}

void chunk::unloadChunk() {
    
}

void chunk::loadChunk() {

}

void chunk::draw(sf::RenderWindow& window) {
    for (int i = 0; i < CHUNK_SIZE; ++i) {
        for (int j = 0; j < CHUNK_SIZE; ++j) {
            int val = tiles_type[i][j];
            window.draw(tiles[i][j]);
        }
    }
}

sf::Texture& chunk::textureCase(int i) {
    if (i == 1) return txManager.getTexture("assets/block/grass_block.png");
    else if (i == 2) return txManager.getTexture("assets/block/sand.png");
}
