#pragma once

namespace gui {

/**
 * @brief where to draw
 *        implementation defined
 */
class DrawingTarget {
public:
  /**
   * @brief this class thoroughly implementation defined
   * @param impl should be freed (if it's necessary) by caller
   */
  DrawingTarget(void *impl) : implementation_(impl) {}

public:
  virtual void *get_impl() { return implementation_; }

protected:
  void *implementation_; ///< implementation defined
};

} // namespace gui
