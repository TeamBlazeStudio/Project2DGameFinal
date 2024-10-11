#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#define Max_main_menu 3

class SinglePlayerMenu {
	int MainMenuSelected = 0;
	sf::Font font;
	sf::Text mainMenu[Max_main_menu];

	bool SingleMenu = false;

public:
	SinglePlayerMenu(float width, float height);
	~SinglePlayerMenu();

	void draw(sf::RenderWindow& window);
	void MoveUp();
	void MoveDown();

	bool GetSingleplayerMenu() { return SingleMenu; }
	void changeSingleMenu() { (SingleMenu) ? SingleMenu = false : SingleMenu = true; }

	int MainMenuPressed() {
		return MainMenuSelected;
	}
};