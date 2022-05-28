#pragma once

#include <geometry.hpp>

namespace gui {
namespace system {
struct Mouse {
  Vector position, previous_position;
  bool button_left_pressed, button_right_pressed;
  bool button_left_clicked, button_right_clicked;
};
} // namespace system
} // namespace gui
