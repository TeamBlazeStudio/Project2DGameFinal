#include "LoadWorldMenu.h"

LoadWorldMenu::LoadWorldMenu(float width, float height) {
	if (!font.loadFromFile("Font/Movistar Text Regular.ttf")) {
		std::cerr << "Error Loading Font" << std::endl;
		std::exit(EXIT_FAILURE);
	}

	for (const auto& entry : std::filesystem::directory_iterator(folderPath)) {
		if (entry.is_directory()) {
			sf::Text* text = new sf::Text();
			text->setString(entry.path().filename().string());
			//std::cout << static_cast<std::string>(text->getString()) << std::endl;
			mainMenu.push_back(*text);
		}
	}

	if (mainMenu.size() > 0) {
		int y = 50;
		for (auto& c : mainMenu) {
			c.setFont(font);
			c.setFillColor(sf::Color::White);
			c.setCharacterSize(70);
			c.setPosition(400, y);
			y += 100;
		}
	}


	MainMenuSelected = -1;
}

LoadWorldMenu::~LoadWorldMenu() {}

void LoadWorldMenu::draw(sf::RenderWindow& window) {
	for (int i = 0; i < mainMenu.size(); ++i) window.draw(mainMenu[i]);
}

void LoadWorldMenu::MoveUp() {
	if (MainMenuSelected - 1 >= 0) {
		mainMenu[MainMenuSelected].setFillColor(sf::Color::White);

		--MainMenuSelected;
		if (MainMenuSelected == -1) {
			MainMenuSelected = 2;
		}
		mainMenu[MainMenuSelected].setFillColor(sf::Color::Blue);
	}
}

void LoadWorldMenu::MoveDown() {
	if (MainMenuSelected + 1 <= mainMenu.size()) {
		mainMenu[MainMenuSelected].setFillColor(sf::Color::White);
		++MainMenuSelected;
		if (MainMenuSelected == mainMenu.size()) {
			MainMenuSelected = 0;
		}
		mainMenu[MainMenuSelected].setFillColor(sf::Color::Blue);
	}
}

