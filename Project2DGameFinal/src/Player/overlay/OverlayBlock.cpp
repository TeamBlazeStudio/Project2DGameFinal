#include "OverlayBlock.h"

OverlayBlock::OverlayBlock() {
	hover.setSize(sf::Vector2f(100.f, 100.f));
	hover.setFillColor(sf::Color::Transparent);
	hover.setOutlineColor(sf::Color::White);
	hover.setOutlineThickness(2);
}

OverlayBlock::~OverlayBlock() {}
