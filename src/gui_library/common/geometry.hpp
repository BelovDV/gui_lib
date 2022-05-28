#pragma once

namespace gui {

namespace details {
using CoordinateMeasure = int;
}

struct Vector {
  details::CoordinateMeasure x = {}, y = {};

  Vector &operator+=(const Vector &other) {
    x += other.x;
    y += other.y;
    return *this;
  }
  Vector &operator-=(const Vector &other) {
    x -= other.x;
    y -= other.y;
    return *this;
  }
  Vector &operator*=(float multiplier) {
    x *= multiplier;
    y *= multiplier;
    return *this;
  }
  Vector operator+(const Vector &other) {
    return Vector{x + other.x, y + other.y};
  }

  bool operator==(const Vector &over) { return x == over.x && y == over.y; }
  bool operator!=(const Vector &over) { return x != over.x && y != over.y; }
  bool operator<(const Vector &over) { return x < over.x && y < over.y; }
  bool operator>(const Vector &over) { return x > over.x && y > over.y; }
  bool operator<=(const Vector &over) { return x <= over.x && y <= over.y; }
  bool operator>=(const Vector &over) { return x >= over.x && y >= over.y; }
};

struct Rectangle {
  Vector position;
  Vector size;
  void move(Vector change) { position += change; }
  bool operator==(const Rectangle &over) { return size == over.size; }
  bool operator!=(const Rectangle &over) { return size != over.size; }
  bool operator<(const Rectangle &over) { return size < over.size; }
  bool operator>(const Rectangle &over) { return size > over.size; }
  bool operator<=(const Rectangle &over) { return size <= over.size; }
  bool operator>=(const Rectangle &over) { return size >= over.size; }
};

struct Border {
  details::CoordinateMeasure upper = {}, lower = {};
  details::CoordinateMeasure right = {}, left = {};

  Vector get_lu() const { return Vector{left, upper}; }
  Vector get_rd() const { return Vector{right, lower}; }
};

} // namespace gui
