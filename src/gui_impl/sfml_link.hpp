#pragma once

#include <SFML/Graphics/Color.hpp>
#include <color.hpp>

namespace gui {

sf::Color color_transform(Color color) {
  return {color.r, color.g, color.b, color.a};
}

} // namespace gui
