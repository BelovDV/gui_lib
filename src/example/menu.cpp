#include "menu.hpp"

#include <iostream>

using namespace gui;

#define ICONS_GAME_SIZE 190

using sf::Color;

Menu::Menu(Settings& settings) :
	settings_(settings),
	drawer_sprite_menu_icons_(texture_menu_icons_),
	drawer_sprite_games_icons_(texture_games_icons_),
	theme_dark_(Theme{
		.background = {30, 30, 30},
		.bar = {10, 10, 10, 200},
		.line = {200, 200, 200, 150},
		.box = {0, 0, 0, 50},
		.text = {255, 255, 255, 180}
		}),
	theme_light_(Theme{
		.background = {200, 200, 200},
		.bar = {10, 10, 10, 150},
		.line = {20, 20, 20, 150},
		.box = {240, 240, 220, 50},
		.text = {0, 0, 0, 180}
		})
{
	theme_chosen_ = theme_dark_;
	if (!texture_menu_icons_.loadFromFile(settings.get_path_to_data() + "/menu.png"))
		std::cout << settings.get_path_to_data() + "/menu.png\n";
	drawer_sprite_menu_icons_.setScale((float)menu_size_ / 100, (float)menu_size_ / 100);
	if (!texture_games_icons_.loadFromFile(settings.get_path_to_data() + "/icons2.png"))
		std::cout << settings.get_path_to_data() + "/icons.png\n";
	drawer_sprite_games_icons_.setScale((float)game_size_ / ICONS_GAME_SIZE, (float)game_size_ / ICONS_GAME_SIZE);
	if (!font_text_.loadFromFile(settings.get_path_to_data() + "/font.ttf"))
		std::cout << "cannot load font\n";
	drawer_text_.setFont(font_text_);
	drawer_text_.setCharacterSize(20);
}

void Menu::generate_tree() {
	regenerate_tree_ = false;

	drawer_text_.setFillColor(theme_chosen_.text);
	FillTextureGenerator texture_menu(drawer_sprite_menu_icons_);
	FillTextureGenerator texture_game(drawer_sprite_games_icons_);
	FillColorGenerator rectangle(drawer_rectangle_);
	ButtonGenerator button;
	TextGenerator text_generator(drawer_text_);
	auto icon_pos = [](int x, int y) { return sf::IntRect{ x * 100, y * 100, 100, 100 }; };

	menu_windows_[(int)State::Home] = button([](void*) { std::cout << "Home\n"; }, rectangle(Color::Transparent));

#define GAME_BUTTON(TEXTURE_X, TEXTURE_Y, TEXT)                     		         \
	box({ 300, 100 }, padding({ 15, 15 }, box({ 270, 70 }, button(  		         \
		[this](void*) {this->menu_current_ = nullptr;}, 	                         \
		overlay(     	                                                             \
			hightlighted(rectangle(theme_chosen_.box),                               \
				rectangle(theme_chosen_.box, theme_chosen_.line, 2)),                \
			texture_game({ TEXTURE_X * ICONS_GAME_SIZE, TEXTURE_Y * ICONS_GAME_SIZE, \
				ICONS_GAME_SIZE, ICONS_GAME_SIZE }),                                 \
			padding({(unsigned)game_size_ + 20, 10}, text_generator({TEXT}))         \
	)))))

	menu_windows_[(int)State::Games] = tile({ 300, 100 },
		GAME_BUTTON(0, 0, "some text should\n  be here"),
		GAME_BUTTON(0, 1, "some text should\n  be here"),
		GAME_BUTTON(0, 2, "some text should\n  be here"),
		GAME_BUTTON(0, 3, "some text should\n  be here"),
		GAME_BUTTON(0, 4, "some text should\n  be here"),
		GAME_BUTTON(1, 0, "some text should\n  be here"),
		GAME_BUTTON(1, 1, "some text should\n  be here"),
		GAME_BUTTON(1, 2, "some text should\n  be here"),
		GAME_BUTTON(1, 3, "some text should\n  be here"),
		GAME_BUTTON(1, 4, "some text should\n  be here"),
		GAME_BUTTON(2, 0, "some text should\n  be here"),
		GAME_BUTTON(2, 1, "some text should\n  be here"),
		GAME_BUTTON(2, 2, "some text should\n  be here"),
		GAME_BUTTON(2, 3, "some text should\n  be here"),
		GAME_BUTTON(2, 4, "some text should\n  be here"),
		GAME_BUTTON(3, 0, "some text should\n  be here"),
		GAME_BUTTON(3, 1, "some text should\n  be here"),
		GAME_BUTTON(3, 2, "some text should\n  be here")
	);
#undef GAME_BUTTON

	menu_windows_[(int)State::Stats] = padding({ 0, 20 }, center_vert({ 500, 500 }, unfold_list(
		box({ 400, 100 }, button([](void*) { std::cout << "Stats0\n"; }, rectangle(Color(0, 50, 0, 50)))),
		box({ 400, 100 }, button([](void*) { std::cout << "Stats1\n"; }, rectangle(Color(0, 100, 0, 50)))),
		box({ 400, 100 }, button([](void*) { std::cout << "Stats2\n"; }, rectangle(Color(0, 150, 0, 50)))),
		box({ 400, 100 }, button([](void*) { std::cout << "Stats3\n"; }, rectangle(Color(0, 200, 0, 50)))),
		box({ 400, 100 }, button([](void*) { std::cout << "Stats4\n"; }, rectangle(Color(0, 250, 0, 50))))
	)));

#define SETTINGS_BUTTON(ACTION, TEXT)                     		                 \
	box({ 400, 50 }, padding({ 15, 5 }, box({ 270, 40 }, overlay(                \
		rectangle(theme_chosen_.box),	                                         \
		button( ACTION, padding({15, 5}, text_generator({TEXT})))                \
	))))

	menu_windows_[(int)State::Settings] = padding({ 0, 20 }, center_vert({ 400, 0 }, split_hor(nullptr,
		split_holder(0, unfold_list(SETTINGS_BUTTON([](void*) {}, "some text"),
			SETTINGS_BUTTON([](void*) { std::cout << "set 1 but 1\n"; }, "some text 1"),
			SETTINGS_BUTTON([](void*) { std::cout << "set 1 but 2\n"; }, "some text 2"),
			SETTINGS_BUTTON([](void*) { std::cout << "set 1 but 3\n"; }, "some text 3")
		), Type::Float),
		split_holder(0, unfold_list(SETTINGS_BUTTON([](void*) {}, "some text"),
			SETTINGS_BUTTON([](void*) { std::cout << "set 2 but 1\n"; }, "some text 1"),
			SETTINGS_BUTTON([](void*) { std::cout << "set 2 but 2\n"; }, "some text 2"),
			SETTINGS_BUTTON([](void*) { std::cout << "set 2 but 3\n"; }, "some text 3")
		), Type::Float),
		split_holder(0, unfold_list(SETTINGS_BUTTON([](void*) {}, "theme"),
			SETTINGS_BUTTON([this](void*) { theme_chosen_ = theme_dark_; regenerate_tree_ = true; }, "dark"),
			SETTINGS_BUTTON([this](void*) { theme_chosen_ = theme_light_; regenerate_tree_ = true; }, "light")
		), Type::Float)
	)));
#undef SETTINGS_BUTTON

	menu_windows_[(int)State::More] = center_vert({ 200, 100 }, overlay(
		button([](void*) { std::cout << "More\n"; }, rectangle(theme_chosen_.box)),
		rectangle(theme_chosen_.box)
	));
	menu_current_ = menu_windows_[(int)State::Home].get();

#define MENU_BUTTON(NUMBER, NAME)   		                                                  \
	split_holder(menu_size_, button(	                                                      \
		[this](void*) { this->menu_current_ = this->menu_windows_[(int)State::NAME].get(); }, \
		hightlighted(texture_menu(icon_pos(NUMBER, 0)), texture_menu(icon_pos(NUMBER, 1)))    \
		))

	tree_ = split_vert(rectangle(theme_chosen_.background),
		split_holder(menu_size_, split_hor(rectangle(theme_chosen_.bar),
			MENU_BUTTON(0, Home),
			MENU_BUTTON(1, Games),
			MENU_BUTTON(2, Stats),
			MENU_BUTTON(3, Settings),
			MENU_BUTTON(4, More)
		)),
		split_holder(0, rectangle(Color::Transparent, theme_chosen_.line, 1)),
		split_holder(0, selector(&menu_current_), gui::Type::Fill)
	);
#undef MENU_BUTTON
}

void Menu::draw(sf::RenderTarget& target, sf::RenderStates) const {
	if (regenerate_tree_)
		const_cast<Menu*>(this)->generate_tree();
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
