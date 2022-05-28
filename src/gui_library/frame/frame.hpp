#pragma once

#include <geometry.hpp>

namespace gui {

/**
 * @brief calculate area to use from available area
 *        contains strategy of positioning
 */
class Frame {
public:
  virtual ~Frame() = default;

public:
  /**
   * @brief calculate required space for given available
   * @param available_area proposed by ancestor
   *                       will be changed to meaning remaining_area
   * @param requested_size required by successor
   * @return position after update, size=0 if it does not fit
   */
  virtual Rectangle update(Rectangle &available_area,
                           Vector requested_size) = 0;
};

} // namespace gui
