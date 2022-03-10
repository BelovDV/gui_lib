#include "menu.hpp"

#include <iostream>

using namespace gui;
using namespace gui::basic;
using namespace gui::logic;
using namespace gui::graphic;

using sf::Color;

Menu::Menu(Settings& settings) :
	settings_(settings),
	drawer_sprite_menu_icons_(texture_menu_icons_)
{
	if (!texture_menu_icons_.loadFromFile(settings.get_path_to_data() + "/menu.png"))
		std::cout << settings.get_path_to_data() + "/menu.png\n";
	drawer_sprite_menu_icons_.setScale(0.5, 0.5);

	FillTextureGenerator texture_menu(drawer_sprite_menu_icons_);
	FillColorGenerator rectangle(drawer_rectangle_);
	ButtonGenerator button;
	auto icon_pos = [](int x, int y) { return sf::IntRect{ x * 100, y * 100, 100, 100 }; };

	//
	// as for my highlighting - all conceptual (not structure) blocks are highlighted with separate color
	// of course, comments are should be
	//
	tree_ = split_vert(rectangle(Color(30, 30, 30)),
		split_holder(50, rectangle(Color(10, 10, 10, 200))),
		split_holder(50, overlay(rectangle(Color(10, 20, 30, 100)), button([](void*) {std::cout << "log\n";}))),
		split_holder(50, hightlighted(rectangle(Color(10, 20, 30, 100)), rectangle(Color(100, 20, 30, 100)))),
		split_holder(0, rectangle({}, Color{ 200, 200, 200, 200 }, 1)),
		split_holder(50, overlay(rectangle(Color(0, 0, 30, 100)), texture_menu(icon_pos(1, 0)))),
		split_holder(50, split_hor(nullptr,
			split_holder(50, hightlighted(texture_menu(icon_pos(0, 0)), texture_menu(icon_pos(0, 1)))),
			split_holder(50, hightlighted(texture_menu(icon_pos(0, 0)), texture_menu(icon_pos(0, 1)))),
			split_holder(50, hightlighted(texture_menu(icon_pos(0, 0)), texture_menu(icon_pos(0, 1))))
		)),
		split_holder(50, overlay(rectangle(Color(30, 20, 30, 100)),
			hightlighted(texture_menu(icon_pos(0, 0)), texture_menu(icon_pos(0, 1)))
		))
	);
}

void Menu::draw(sf::RenderTarget& target, sf::RenderStates) const {
	tree_->update(settings_.get_window_size(), { 0, 0 });
	tree_->draw(target);
}

bool Menu::process_event(const sf::Event& event) {
	switch (event.type) {
	case sf::Event::EventType::Closed:
		return false;
	case sf::Event::EventType::KeyPressed:
		if (event.key.code == sf::Keyboard::Escape)
			return false;
		break;
	case sf::Event::EventType::MouseButtonPressed:
	case sf::Event::EventType::MouseMoved:
		tree_->process_event(event, this);
	default:
		break;
	}
	return true;
}
