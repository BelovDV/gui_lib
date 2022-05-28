#include <block.hpp>
#include <frames.hpp>
#include <rectangle_shape.hpp>
#include <window.hpp>

#include <SFML/System/Sleep.hpp>
#include <log.hpp>

#include <SFML/Graphics.hpp>

#include <iostream>

using namespace gui;

#if 0
std::unique_ptr<RectangleShape> g_fill(Color color) {
  return std::make_unique<RectangleShape>(color, Color{200, 0, 0, 50}, 3);
}
#else
std::unique_ptr<RectangleDrawable> g_fill(Color color) {
  return std::make_unique<RectangleDrawable>(color);
}
#endif

std::unique_ptr<FrameAttach> g_frame(FrameAttach::Type type) {
  return std::make_unique<FrameAttach>(type);
}

auto attach_fill = FrameAttach::Fill;
auto attach_up = FrameAttach::Up;
auto attach_down = FrameAttach::Down;
auto attach_left = FrameAttach::Left;
auto attach_right = FrameAttach::Right;

using color::gray;

int main() {
  Rectangle pos = {{500, 100}, {200, 200}};
  gui::Window window(pos, "test");

  Color outline = {200, 0, 0, 50};

  Block all({}, g_fill(gray(35)), g_frame(attach_fill));
  Block top({{}, {0, 20}}, g_fill(gray(30, 200)), g_frame(attach_up));
  Block header({{}, {0, 40}}, g_fill(gray(70, 200)), g_frame(attach_up));
  Block bottom({{}, {0, 20}}, g_fill(Color{40, 80, 200, 255}),
               g_frame(attach_down));
  Block menu({{}, {50, 0}}, g_fill(gray(55, 200)), g_frame(attach_left));
  Block explorer({{}, {150, 0}}, g_fill(gray(30, 200)), g_frame(attach_left));
  Block console({{}, {400, 0}}, g_fill(gray(20, 200)), g_frame(attach_right));
  Block text_part({}, g_fill(gray(30, 200)), g_frame(attach_fill));
  Block text_tabs({{}, {0, 50}}, g_fill(gray(70, 200)), g_frame(attach_up));
  Block text_path({{}, {0, 10}}, g_fill(gray(30, 200)), g_frame(attach_up));
  Block text_text({}, g_fill(gray(30, 200)), g_frame(attach_fill));

  text_path.exchange_next(text_text);
  text_tabs.exchange_next(text_path);
  text_part.exchange_successor(text_tabs);
  console.exchange_next(text_part);
  explorer.exchange_next(console);
  menu.exchange_next(explorer);
  bottom.exchange_next(menu);
  header.exchange_next(bottom);
  top.exchange_next(header);
  all.exchange_successor(top);

  while (true) {
    std::cout << '\n';
    Event event;
    while (window.poll_event(event)) {
      if (event.type == Event::Close) {
        return 0;
      }
    }
    sf::sleep(sf::milliseconds(300));
    std::cout << "update\n";
    all.update({{}, window.get_size()});
    std::cout << "draw\n";
    all.draw(window);
    std::cout << "display\n";
    window.display();
  }
}