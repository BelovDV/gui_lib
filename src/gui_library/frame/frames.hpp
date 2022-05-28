#pragma once

#include <frame.hpp>

namespace gui {

class FrameAttach : public Frame {
public:
  enum Type { Up, Right, Left, Down, Fill };

public:
  FrameAttach(Type type) : type_(type) {}

public:
  Rectangle update(Rectangle &area, Vector size) override;

private:
  Type type_;
};

} // namespace gui
