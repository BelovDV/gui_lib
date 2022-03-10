#include "objects.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>

void gui::graphic::FillColor::draw(sf::RenderTarget& target) {
	drawer_.setPosition({ (float)position_.x, (float)position_.y });
	drawer_.setSize({ (float)size_.x, (float)size_.y });
	drawer_.setFillColor(fill_color_);
	drawer_.setOutlineColor(outline_color_);
	drawer_.setOutlineThickness(outline_thickness_);
	target.draw(drawer_);
}

void gui::graphic::FillTexture::draw(sf::RenderTarget& target) {
	drawer_.setPosition({ (float)position_.x, (float)position_.y });
	drawer_.setTextureRect(texture_rect_);
	target.draw(drawer_);
}
