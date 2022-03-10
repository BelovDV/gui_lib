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

	tree_ = create<SplitVert>(
		create<FillColor>(drawer_rectangle_, Color(30, 30, 30)),
		SplitVert::Holder{ SplitVert::Type::Absolute, 50, create<FillColor>(drawer_rectangle_, Color(10, 10, 10, 200)) },
		SplitVert::Holder{ SplitVert::Type::Absolute, 50, create<Overlay>(nullptr,
			Overlay::Holder{ create<FillColor>(drawer_rectangle_, Color(10, 20, 30, 100))},
			Overlay::Holder{ create<Button>([](void*) {std::cout << "log\n";})}
			) },
		SplitVert::Holder{ SplitVert::Type::Absolute, 50, create<Highlighted>(
			create<FillColor>(drawer_rectangle_, Color(10, 20, 30, 100)),
			create<FillColor>(drawer_rectangle_, Color(100, 20, 30, 100))
		) },
		SplitVert::Holder{ SplitVert::Type::Absolute, 0, create<FillColor>(drawer_rectangle_, Color::Transparent, Color{200, 200, 200, 200}, 1) },
		SplitVert::Holder{ SplitVert::Type::Absolute, 50, create<Overlay>(
			nullptr,
			Overlay::Holder{ create<FillColor>(drawer_rectangle_, Color(0, 0, 30, 100))},
			Overlay::Holder{ create<FillTexture>(drawer_sprite_menu_icons_, sf::IntRect{0, 0, 100, 100})}
			) },
		SplitVert::Holder{ SplitVert::Type::Absolute, 50, create<SplitHor>(
			nullptr,
			SplitHor::Holder{SplitHor::Type::Absolute, 50, create<Highlighted>(
				create<FillTexture>(drawer_sprite_menu_icons_, sf::IntRect{0, 0, 100, 100}),
				create<FillTexture>(drawer_sprite_menu_icons_, sf::IntRect{0, 100, 100, 100})
			) },
			SplitHor::Holder{SplitHor::Type::Absolute, 50, create<Highlighted>(
				create<FillTexture>(drawer_sprite_menu_icons_, sf::IntRect{0, 0, 100, 100}),
				create<FillTexture>(drawer_sprite_menu_icons_, sf::IntRect{0, 100, 100, 100})
			) },
			SplitHor::Holder{SplitHor::Type::Absolute, 50, create<Highlighted>(
				create<FillTexture>(drawer_sprite_menu_icons_, sf::IntRect{0, 0, 100, 100}),
				create<FillTexture>(drawer_sprite_menu_icons_, sf::IntRect{0, 100, 100, 100})
			) }
			) },
		SplitVert::Holder{ SplitVert::Type::Absolute, 50, create<Overlay>(
			create<FillColor>(drawer_rectangle_, Color(30, 20, 30, 100)),
			Overlay::Holder{ create<Highlighted>(
				create<FillTexture>(drawer_sprite_menu_icons_, sf::IntRect{0, 0, 100, 100}),
				create<FillTexture>(drawer_sprite_menu_icons_, sf::IntRect{0, 100, 100, 100})
			)}
			) }
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
