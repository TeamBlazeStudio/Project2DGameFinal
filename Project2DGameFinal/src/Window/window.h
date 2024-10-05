#pragma once
#include <SFML/Graphics.hpp>

class Window {

	bool isRunning = false;

public:
	Window(int x, int y, const char* title);
	~Window();

	

	void render();
	void clear();
	void end();

	bool running() { return isRunning; }
	static sf::Event evnt;
	static sf::RenderWindow window;
};