#pragma once

#include <drawing_target.hpp>
#include <event.hpp>
#include <geometry.hpp>

#include <string>

namespace gui {

class Window : public DrawingTarget {
public:
  Window(Rectangle area, const std::string &title);
  ~Window();

public:
  void move(Vector diff) { area_.position += diff; }
  void move_to(Vector position) { area_.position = position; }
  void set_size(Vector size) { area_.size = size; }
  Vector get_size() const { return area_.size; }
  /**
   * @brief try to get event from window
   */
  bool poll_event(Event &event);
  void display();
  void *get_impl() override;
  void clear();

private:
  Rectangle area_;
};

} // namespace gui
