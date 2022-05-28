#include <block.hpp>

#include <log.hpp>

namespace gui {

void Block::exchange_successor(Block &swap) {
  LOG(self_.get());
  LOG(swap.self_.get());
  std::swap(swap, self_->successor_);
  LOG(swap.self_.get());
}

void Block::exchange_next(Block &swapping) {
  std::swap(swapping, self_->next_);
}

void Block::exchange_look(std::unique_ptr<Drawable> &swap) {
  std::swap(swap, self_->drawable_);
}

void Block::exchange_positioning(std::unique_ptr<Frame> &swap) {
  std::swap(swap, self_->frame_);
}

void Block::update(Rectangle available) {
  if (self_.get()) {
    LOG(self_->area_.position.x << ' ' << self_->area_.position.y << ' '
                                << self_->area_.size.x << ' '
                                << self_->area_.size.y);
    auto vsp = self_->frame_->update(available, self_->area_.size);
    if (vsp.size == Vector{0, 0}) {
      self_->fit_ = false;
      return;
    } else {
      self_->fit_ = true;
    }
    self_->area_ = vsp;
    LOG(self_->area_.size.x << ' ' << self_->area_.size.y);
    self_->successor_.update(self_->area_);
    self_->next_.update(available);
  }
}

void Block::draw(DrawingTarget &target) {
  if (self_.get()) {
    LOG(self_.get());
    LOG(self_->fit_);
    if (!self_->fit_) {
      return;
    }
    auto size = self_->drawable_->set_size(self_->area_.size);
    LOG(size.x << ' ' << size.y);
    LOG(self_->area_.size.x << ' ' << self_->area_.size.y);
    if (size <= self_->area_.size) {
      self_->drawable_->draw(target, self_->area_.position, {{0, 0}, size});
      self_->successor_.draw(target);
      self_->next_.draw(target);
    }
  }
}

void Block::process_event(const Event &, const SystemState &) {
  void();
  void();
}

} // namespace gui
