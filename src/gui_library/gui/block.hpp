#pragma once

#include <drawable.hpp>
#include <frame.hpp>
#include <functional.hpp>

#include <memory>

#include <iostream>

namespace gui {

namespace details {
class BlockImpl;
}
class Block {
public:
  Block() : self_(nullptr) {}
  Block(Rectangle area, std::unique_ptr<Drawable> &&look,
        std::unique_ptr<Frame> &&positioning, Block successor = Block(),
        Block next = Block())
      : self_(std::make_unique<details::BlockImpl>(
            area, std::move(look), std::move(positioning), std::move(successor),
            std::move(next))) {
    std::cout << self_.get() << '\n';
  }

public:
  void exchange_successor(Block &);
  void exchange_next(Block &);
  void exchange_look(std::unique_ptr<Drawable> &);
  void exchange_positioning(std::unique_ptr<Frame> &);

  void update(Rectangle available_area);
  void draw(DrawingTarget &);
  void process_event(const Event &, const SystemState &);

private:
  std::unique_ptr<details::BlockImpl> self_;
};

namespace details {
class BlockImpl {
  friend class gui::Block;

public:
  BlockImpl(Rectangle area, std::unique_ptr<Drawable> &&look,
            std::unique_ptr<Frame> &&positioning, Block &&successor,
            Block &&next)
      : area_(area), drawable_(std::move(look)), frame_(std::move(positioning)),
        successor_(std::move(successor)), next_(std::move(next)) {}

public:
private:
  Rectangle area_;
  std::unique_ptr<Drawable> drawable_;
  std::unique_ptr<Frame> frame_;
  std::unique_ptr<Functional> functional_;
  Block successor_;
  Block next_;
  bool fit_ = false;
};
} // namespace details

} // namespace gui
