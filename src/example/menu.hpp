#pragma once

#include "settings.hpp"

#include "gui.hpp"

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

class Menu : public sf::Drawable {
public:
	enum class State {
		Home,
		Games,
		Stats,
		Settings,
		More,
		Count
	};
	enum class Buttons {
		AllWindow,
		Home,
		Games,
		Stats,
		Settings,
		More,
	};
public:
	Menu(Settings& settings);
public:
	// return - is active
	bool process_event(const sf::Event&);
	virtual void draw(sf::RenderTarget&, sf::RenderStates) const override;
private:
	void generate_tree() {}
private:
	Settings& settings_;
	std::unique_ptr<gui::logic::Block> tree_;
	sf::RectangleShape drawer_rectangle_;
	sf::Texture texture_menu_icons_;
	sf::Sprite drawer_sprite_menu_icons_;
};
