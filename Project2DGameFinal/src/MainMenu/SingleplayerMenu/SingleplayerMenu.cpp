#include "SingleplayerMenu.h"

SinglePlayerMenu::SinglePlayerMenu(float width, float height) {
	if (!font.loadFromFile("Font/Movistar Text Regular.ttf")) {
		std::cerr << "Error Loading Font" << std::endl;
		std::exit(EXIT_FAILURE);
	}

	//New World
	mainMenu[0].setFont(font);
	mainMenu[0].setFillColor(sf::Color::White);
	mainMenu[0].setString("New World");
	mainMenu[0].setCharacterSize(70);
	mainMenu[0].setPosition(400, 200);

	//Load World
	mainMenu[1].setFont(font);
	mainMenu[1].setFillColor(sf::Color::White);
	mainMenu[1].setString("Load World");
	mainMenu[1].setCharacterSize(70);
	mainMenu[1].setPosition(400, 300);

	//Delete World
	mainMenu[2].setFont(font);
	mainMenu[2].setFillColor(sf::Color::White);
	mainMenu[2].setString("Delete World");
	mainMenu[2].setCharacterSize(70);
	mainMenu[2].setPosition(400, 400);

	MainMenuSelected = -1;
}

SinglePlayerMenu::~SinglePlayerMenu() {}

void SinglePlayerMenu::draw(sf::RenderWindow& window) {
	for (int i = 0; i < Max_main_menu; ++i) window.draw(mainMenu[i]);
}

void SinglePlayerMenu::MoveUp() {
	if (MainMenuSelected - 1 >= 0) {
		mainMenu[MainMenuSelected].setFillColor(sf::Color::White);

		--MainMenuSelected;
		if (MainMenuSelected == -1) {
			MainMenuSelected = 2;
		}
		mainMenu[MainMenuSelected].setFillColor(sf::Color::Blue);
	}
}

void SinglePlayerMenu::MoveDown() {
	if (MainMenuSelected + 1 <= Max_main_menu) {
		mainMenu[MainMenuSelected].setFillColor(sf::Color::White);
		++MainMenuSelected;
		if (MainMenuSelected == 5) {
			MainMenuSelected = 0;
		}
		mainMenu[MainMenuSelected].setFillColor(sf::Color::Blue);
	}
}