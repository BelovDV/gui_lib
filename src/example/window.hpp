#pragma once

#include "settings.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

namespace Graphic {
	class Window {
	public:
		Window(Settings& settings);
		~Window();
	public:
		/**
		 * @brief try to get event from window
		 */
		bool poll_event(sf::Event& event) { return window_.pollEvent(event); }
		/**
		 * @brief draw the only one object
		 */
		void draw(const sf::Drawable& object);
	private:
		sf::RenderWindow window_;
		Settings& settings_;
	};
}
