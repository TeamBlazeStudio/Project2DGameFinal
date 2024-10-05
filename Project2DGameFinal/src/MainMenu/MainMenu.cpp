#include "MainMenu.h"

MainMenu::MainMenu(float width, float height) {
	if (!font.loadFromFile("Font/Movistar Text Regular.ttf")) {
		std::cerr << "Error Loading Font" << std::endl;
		std::exit(EXIT_FAILURE);
	}

	//Singleplayer
	mainMenu[0].setFont(font);
	mainMenu[0].setFillColor(sf::Color::White);
	mainMenu[0].setString("SinglePlayer");
	mainMenu[0].setCharacterSize(70);
	mainMenu[0].setPosition(400, 200);

	//MultiPlayer join
	mainMenu[1].setFont(font);
	mainMenu[1].setFillColor(sf::Color::White);
	mainMenu[1].setString("MultiPlayer join");
	mainMenu[1].setCharacterSize(70);
	mainMenu[1].setPosition(400, 300);

	//MultiPlayer host
	mainMenu[2].setFont(font);
	mainMenu[2].setFillColor(sf::Color::White);
	mainMenu[2].setString("MultiPlayer host");
	mainMenu[2].setCharacterSize(70);
	mainMenu[2].setPosition(400, 400);

	//Options
	mainMenu[3].setFont(font);
	mainMenu[3].setFillColor(sf::Color::White);
	mainMenu[3].setString("Options");
	mainMenu[3].setCharacterSize(70);
	mainMenu[3].setPosition(400, 500);

	//Exit
	mainMenu[4].setFont(font);
	mainMenu[4].setFillColor(sf::Color::White);
	mainMenu[4].setString("Exit");
	mainMenu[4].setCharacterSize(70);
	mainMenu[4].setPosition(400, 600);

	MainMenuSelected = -1;
}

MainMenu::~MainMenu() {}

void MainMenu::draw(sf::RenderWindow& window) {
	for (int i = 0; i < Max_main_menu; ++i) window.draw(mainMenu[i]);
}

void MainMenu::MoveUp() {
	if (MainMenuSelected - 1 >= 0) {
		mainMenu[MainMenuSelected].setFillColor(sf::Color::White);

		--MainMenuSelected;
		if (MainMenuSelected == -1) {
			MainMenuSelected = 2;
		}
		mainMenu[MainMenuSelected].setFillColor(sf::Color::Blue);
	}
}

void MainMenu::MoveDown() {
	if (MainMenuSelected + 1 <= Max_main_menu) {
		mainMenu[MainMenuSelected].setFillColor(sf::Color::White);
		++MainMenuSelected;
		if (MainMenuSelected == 5) {
			MainMenuSelected = 0;
		}
		mainMenu[MainMenuSelected].setFillColor(sf::Color::Blue);
	}
}