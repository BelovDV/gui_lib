#include <window.hpp>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Sleep.hpp>
#include <SFML/Window/Event.hpp>

namespace gui {

Window::Window(Rectangle area, const std::string &title)
    : DrawingTarget(new sf::RenderWindow(sf::VideoMode(1, 1), title)),
      area_(area) {
  auto sf_window = reinterpret_cast<sf::RenderWindow *>(implementation_);
  sf_window->setVerticalSyncEnabled(true);
  sf_window->setPosition({area.position.x, area.position.y});
  sf::sleep(sf::milliseconds(200)); // prevent window from "jumping"
  sf_window->setSize({(unsigned)area.size.x, (unsigned)area.size.y});
  // sf::FloatRect visible(0, 0, 100, 100);
  // sf::FloatRect visible(0, 0, area.size.x, area.size.y);
  // sf_window->setView(sf::View(visible));
}

Window::~Window() {
  delete reinterpret_cast<sf::RenderWindow *>(implementation_);
}

bool Window::poll_event(Event &event) {
  auto sf_window = reinterpret_cast<sf::RenderWindow *>(implementation_);
  sf::Event sf_event;
  event.type = Event::None;
  while (sf_window->pollEvent(sf_event)) {
    switch (sf_event.type) {
    case sf::Event::EventType::Closed:
      event.type = Event::Close;
      return true;
    case sf::Event::EventType::Resized: {
      auto vsp = sf_window->getSize();
      area_.size = {(int)vsp.x, (int)vsp.y};
      sf_window->setView(
          sf::View(sf::FloatRect{0, 0, (float)vsp.x, (float)vsp.y}));
    } break;
    default:
      break;
    }
  }
  return false;
}

void Window::display() {
  auto sf_window = reinterpret_cast<sf::RenderWindow *>(implementation_);
  sf_window->display();
}

void *Window::get_impl() {
  auto sf_window = reinterpret_cast<sf::RenderWindow *>(implementation_);
  return static_cast<sf::RenderTarget *>(sf_window);
}

void Window::clear() {
  reinterpret_cast<sf::RenderWindow *>(implementation_)->clear();
}

} // namespace gui
