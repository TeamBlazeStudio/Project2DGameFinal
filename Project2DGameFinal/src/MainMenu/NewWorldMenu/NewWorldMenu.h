#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

#define Max_main_menu 3

class NewWorldMenu {
	int MainMenuSelected = 0;
	sf::Font font;
	sf::Text mainMenu[Max_main_menu];
	sf::Text worldName;

	bool newWorldMenu = false;
	bool inputName = false;

	std::string folderPath;

public:
	NewWorldMenu(float width, float height);
	~NewWorldMenu();

	void draw(sf::RenderWindow& window);
	void drawWorldName(sf::RenderWindow& window) { window.draw(worldName); }
	void MoveUp();
	void MoveDown();

	void update(const std::string& content, sf::RenderWindow& window);

	void setPath(const std::string& path) { folderPath = path; }
	std::string getPath() { return folderPath; }

	bool GetNewWorldMenu() { return newWorldMenu; }
	void changeNewWorldMenu() { (newWorldMenu) ? newWorldMenu = false : newWorldMenu = true; }

	bool GetInputName() { return inputName; }
	void changeInputName() { (inputName) ? inputName = false : inputName = true; }

	int newWorldMenuPressed() {
		return MainMenuSelected;
	}
};

