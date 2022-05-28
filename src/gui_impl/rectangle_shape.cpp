#include <drawing_target.hpp>
#include <rectangle_shape.hpp>
#include <sfml_link.hpp>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include <log.hpp>

namespace gui {

Vector RectangleDrawable::draw(DrawingTarget &target, Vector position,
                               Rectangle source) {
  auto sf_target = reinterpret_cast<sf::RenderTarget *>(target.get_impl());
  static sf::RectangleShape sf_rectangle;
  sf_rectangle.setFillColor(color_transform(color_));
  sf_rectangle.setSize({(float)source.size.x, (float)source.size.y});
  sf_rectangle.setPosition({(float)position.x, (float)position.y});
  sf_target->draw(sf_rectangle);
  return source.size;
}

Vector RectangleShape::draw(DrawingTarget &target, Vector position,
                            Rectangle source) {
  LOG((int)color_.r);
  auto sf_target = reinterpret_cast<sf::RenderTarget *>(target.get_impl());
  static sf::RectangleShape sf_rectangle;
  sf_rectangle.setFillColor(color_transform(color_));
  sf_rectangle.setSize({(float)source.size.x, (float)source.size.y});
  sf_rectangle.setPosition({(float)position.x, (float)position.y});
  sf_rectangle.setOutlineColor(color_transform(outline_color_));
  sf_rectangle.setOutlineThickness(outline_thickness_);
  LOG(sf_rectangle.getPosition().x << ' ' << sf_rectangle.getPosition().y);
  LOG(sf_rectangle.getSize().x << ' ' << sf_rectangle.getSize().y);
  sf_target->draw(sf_rectangle);
  return source.size;
}

} // namespace gui
