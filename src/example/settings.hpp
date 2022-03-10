#pragma once

#include <SFML/System/Vector2.hpp>
#include <string>

#define SETTINGS_WINDOW_DEFAULT_POSITION 10, 10
#define SETTINGS_WINDOW_DEFAULT_SIZE 800, 600

class Settings {
public:
	enum class ColorScheme {
		Light,
		Dark,

		Count
	};
public:
	Settings(std::string&& filepath_temp, std::string&& filepath_data);
	~Settings();
public:
	sf::Vector2i get_window_position() const { return data_.window_position; }
	sf::Vector2u get_window_size() const { return data_.window_size; }
	ColorScheme get_color_scheme() const { return data_.color_scheme; }

	void set_window_position(sf::Vector2i new_position) { data_.window_position = new_position; }
	void set_window_size(sf::Vector2u new_size) { data_.window_size = new_size; }
	void set_color_scheme(ColorScheme new_scheme) { data_.color_scheme = new_scheme; }
public:
	const std::string& get_path_to_data() const { return path_data_; }
private:
	std::string path_temp_;
	std::string path_data_;
	struct {
		sf::Vector2i window_position{ SETTINGS_WINDOW_DEFAULT_POSITION };
		sf::Vector2u window_size{ SETTINGS_WINDOW_DEFAULT_SIZE };
		ColorScheme color_scheme{ ColorScheme::Light };
	} data_;
};

#undef SETTINGS_WINDOW_DEFAULT_POSITION
#undef SETTINGS_WINDOW_DEFAULT_SIZE
