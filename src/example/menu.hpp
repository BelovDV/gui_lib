#pragma once

#include "settings.hpp"

#include "gui.hpp"

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>

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
	struct Theme {
		Theme& operator=(const Theme&) = default;
		sf::Color background;
		sf::Color bar;
		sf::Color line;
		sf::Color box;
		sf::Color text;
	};
public:
	Menu(Settings& settings);
	virtual ~Menu() = default;
public:
	// return - is active
	bool process_event(const sf::Event&);
	virtual void draw(sf::RenderTarget&, sf::RenderStates) const override;
private:
	void generate_tree();
private:
	Settings& settings_;
	gui::BlockPtr tree_;
	gui::BlockPtr menu_windows_[(int)State::Count];
	gui::basic::Block* menu_current_ = nullptr;
	sf::RectangleShape drawer_rectangle_;
	sf::Texture texture_menu_icons_;
	sf::Sprite drawer_sprite_menu_icons_;
	sf::Texture texture_games_icons_;
	sf::Sprite drawer_sprite_games_icons_;
	sf::Text drawer_text_;
	sf::Font font_text_;
	int menu_size_ = 50;
	int game_size_ = 50;
	Theme theme_dark_, theme_light_;
	Theme theme_chosen_;
	bool regenerate_tree_ = true;
};
