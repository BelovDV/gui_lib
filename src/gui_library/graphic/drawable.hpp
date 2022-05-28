#pragma once

#include <geometry.hpp>

namespace gui {

class DrawingTarget;
/**
 * @brief to be drawn on DrawingTarget
 */
class Drawable {
public:
  virtual ~Drawable() = default;

public:
  /**
   * @brief  try to set desired size
   * @return size that was set
   */
  virtual Vector set_size(Vector size) = 0;
  /**
   * @brief draw source from object to dest on target
   * @param position there to draw on target
   * @param source   part of object to be drawn, use default to draw whole
   * @return size of drawn
   */
  virtual Vector draw(DrawingTarget &, Vector position, Rectangle source) = 0;
};

} // namespace gui
