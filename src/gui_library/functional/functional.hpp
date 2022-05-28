#pragma once

#include <event.hpp>
#include <system_state.hpp>

namespace gui {

/**
 * @brief used for event processing
 */
class Functional {
public:
  virtual ~Functional() = default;

public:
  virtual void process_event(const Event &, const SystemState &) = 0;
  virtual EventMask required_event() = 0;
};

} // namespace gui
