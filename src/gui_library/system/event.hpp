#pragma once

namespace gui {

struct Event {
  enum Type { None, Close, MouseEntered, MouseLeft, MousePressed, TypesAmount };
  Type type;
};

struct EventMask {
  bool used[Event::TypesAmount];
  bool requires(const Event &event) { return used[event.type]; }
};

} // namespace gui
