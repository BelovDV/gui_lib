#include "window.hpp"

#include <SFML/System/Sleep.hpp>

#include "log.hpp"

Graphic::Window::Window(Settings& settings)
	: window_(sf::VideoMode(1, 1), ""), settings_(settings)
{
	window_.setVerticalSyncEnabled(true);
	window_.setPosition(settings_.get_window_position());
	sf::sleep(sf::milliseconds(200)); // prevent window from "jumping"
	auto size = settings_.get_window_size();
	window_.setSize(size);
	sf::FloatRect visible(0, 0, size.x, size.y);
	window_.setView(sf::View(visible));
	settings_.set_window_size(size);
}

Graphic::Window::~Window() {
	settings_.set_window_position(window_.getPosition());
}

void Graphic::Window::draw(const sf::Drawable& object) {
	auto size = window_.getSize();
	if (size != settings_.get_window_size()) {
		sf::FloatRect visible(0, 0, size.x, size.y);
		window_.setView(sf::View(visible));
		settings_.set_window_size(size);
	}
	window_.draw(object);
	window_.display();
}
