#include "window.h"

sf::Event Window::evnt;
sf::RenderWindow Window::window;

Window::Window(int x, int y, const char* title) {
	window.create(sf::VideoMode(x, y), title, sf::Style::Close | sf::Style::Resize);
	window.setPosition(sf::Vector2i(0.f, 0.f));
	isRunning = true;
	window.setFramerateLimit(120);
}

Window::~Window() {}

void Window::render() {
	window.display();
}

void Window::clear() {
	window.clear(sf::Color(150, 150, 150));
}

void Window::end() {
	window.close();
	isRunning = false;
	Window::~Window();
}
