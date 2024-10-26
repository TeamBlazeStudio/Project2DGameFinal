#include "NewWorldMenu.h"

NewWorldMenu::NewWorldMenu(float width, float height) {
	if (!font.loadFromFile("Font/Movistar Text Regular.ttf")) {
		std::cerr << "Error Loading Font" << std::endl;
		std::exit(EXIT_FAILURE);
	}

	worldName.setFont(font);
	worldName.setFillColor(sf::Color::White);
	worldName.setCharacterSize(70);

	//New World
	mainMenu[0].setFont(font);
	mainMenu[0].setFillColor(sf::Color::White);
	mainMenu[0].setString("World Name: ");
	mainMenu[0].setCharacterSize(70);
	mainMenu[0].setPosition(400, 200);

	//Load World
	mainMenu[1].setFont(font);
	mainMenu[1].setFillColor(sf::Color::White);
	mainMenu[1].setString("Options");
	mainMenu[1].setCharacterSize(70);
	mainMenu[1].setPosition(400, 300);

	//Delete World
	mainMenu[2].setFont(font);
	mainMenu[2].setFillColor(sf::Color::White);
	mainMenu[2].setString("Create World");
	mainMenu[2].setCharacterSize(70);
	mainMenu[2].setPosition(400, 400);

	worldName.setPosition(mainMenu[0].getPosition().x + 400, mainMenu[0].getPosition().y);

	MainMenuSelected = -1;
}

NewWorldMenu::~NewWorldMenu() {}

void NewWorldMenu::draw(sf::RenderWindow& window) {
	for (int i = 0; i < Max_main_menu; ++i) window.draw(mainMenu[i]);
}

void NewWorldMenu::MoveUp() {
	if (MainMenuSelected - 1 >= 0) {
		mainMenu[MainMenuSelected].setFillColor(sf::Color::White);

		--MainMenuSelected;
		if (MainMenuSelected == -1) {
			MainMenuSelected = 2;
		}
		mainMenu[MainMenuSelected].setFillColor(sf::Color::Blue);
	}
}

void NewWorldMenu::MoveDown() {
	if (MainMenuSelected + 1 <= Max_main_menu) {
		mainMenu[MainMenuSelected].setFillColor(sf::Color::White);
		++MainMenuSelected;
		if (MainMenuSelected == 3) {
			MainMenuSelected = 0;
		}
		mainMenu[MainMenuSelected].setFillColor(sf::Color::Blue);
	}
}

void NewWorldMenu::update(const std::string& content, sf::RenderWindow& window) {
	worldName.setString(content);
	drawWorldName(window);
}
