#pragma once

namespace gui {

struct Color {
  unsigned char r, g, b, a;
  auto set_r(unsigned char v) {
    r = v;
    return *this;
  }
  auto set_g(unsigned char v) {
    g = v;
    return *this;
  }
  auto set_b(unsigned char v) {
    b = v;
    return *this;
  }
  auto set_a(unsigned char v) {
    a = v;
    return *this;
  }
};

namespace color {
static const auto white = Color{255, 255, 255, 255};
static const auto black = Color{0, 0, 0, 255};
static const auto red = Color{255, 0, 0, 255};
static const auto green = Color{0, 255, 0, 255};
static const auto blue = Color{0, 0, 255, 255};
static const auto yellow = Color{255, 255, 0, 255};
static const auto magenta = Color{255, 0, 255, 255};
static const auto cyan = Color{0, 255, 255, 255};
static const auto transparent = Color{0, 0, 0, 0};
static auto gray(unsigned char v, unsigned char a = 255) {
  return Color{v, v, v, a};
}
} // namespace color

} // namespace gui
