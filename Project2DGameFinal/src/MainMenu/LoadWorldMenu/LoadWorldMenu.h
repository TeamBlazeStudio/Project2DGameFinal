#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <filesystem>


class LoadWorldMenu {
	int MainMenuSelected = 0;
	sf::Font font;
	std::vector<sf::Text> mainMenu;

	bool newWorldMenu = false;
	bool load = false;

	std::string folderPath = "../.game";
	int folderCount = 0;
	int loadMapCounter;

public:
	LoadWorldMenu(float width, float height);
	~LoadWorldMenu();

	void draw(sf::RenderWindow& window);
	void MoveUp();
	void MoveDown();

	void setPath(const std::string& path) { folderPath = path; }
	std::string getPath() { return folderPath; }

	bool GetLoadWorldMenu() { return newWorldMenu; }
	void changeLoadWorldMenu() { (newWorldMenu) ? newWorldMenu = false : newWorldMenu = true; }
	int getSize() { return mainMenu.size() - 1; }

	std::string getFolderName(int n) { return mainMenu[n].getString(); }

	void changeLoad() { (load) ? load = false : load = true; }
	bool getLoad() { return load; }

	void setLoadMapCounter(int val) { loadMapCounter = val; }
	int getLoadMap() { return loadMapCounter; }

	int LoadWorldPressed() {
		return MainMenuSelected;
	}
};

