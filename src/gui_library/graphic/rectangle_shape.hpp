#pragma once

#include <color.hpp>
#include <drawable.hpp>

namespace gui {

class RectangleDrawable : public Drawable {
public:
  RectangleDrawable(Color color) : color_(color) {}

public:
  Vector set_size(Vector size) override { return size; }
  Vector draw(DrawingTarget &, Vector position, Rectangle source) override;

protected:
  Color color_;
};

class RectangleShape : public RectangleDrawable {
public:
  RectangleShape(Color color, Color outline, details::CoordinateMeasure thick)
      : RectangleDrawable(color), outline_color_(outline),
        outline_thickness_(thick) {}

public:
  Vector draw(DrawingTarget &, Vector position, Rectangle source) override;

protected:
  Color outline_color_;
  details::CoordinateMeasure outline_thickness_;
};

} // namespace gui
