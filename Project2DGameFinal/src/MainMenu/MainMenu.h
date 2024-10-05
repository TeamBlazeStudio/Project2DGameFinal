#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#define Max_main_menu 5

class MainMenu {
	int MainMenuSelected = 0;
	sf::Font font;
	sf::Text mainMenu[Max_main_menu];

	bool singleplayer = false;
	bool multiplayer = false;
	bool options = false;
	bool exit = false;

	bool menu = true;

public:
	MainMenu(float width, float height);
	~MainMenu();

	void draw(sf::RenderWindow& window);
	void MoveUp();
	void MoveDown();

	bool getSingleplayer() { return singleplayer; }
	bool getMultiplayer() { return multiplayer; }
	bool getOptions() { return options; }
	bool getExit() { return exit; }
	bool getMenu() { return menu; }

	void changeSing() { (singleplayer) ? singleplayer = false : singleplayer = true; }
	void changeMulti() { (multiplayer) ? multiplayer = false : multiplayer = true; }
	void changeOpti() { (options) ? options = false : options = true; }
	void changeExit() { (exit) ? exit = false : exit = true; }
	void changeMenu() { (menu) ? menu = false : menu = true; }

	int MainMenuPressed() {
		return MainMenuSelected;
	}
};

