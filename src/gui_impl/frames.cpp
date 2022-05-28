#include <frames.hpp>

#include <log.hpp>

namespace gui {

Rectangle FrameAttach::update(Rectangle &area, Vector size) {
  LOG(area.position.x << ' ' << area.position.y << ' ' << area.size.x << ' '
                      << area.size.y);
  LOG(size.x << ' ' << size.y);
  if (((type_ == Left || type_ == Right) && size.x > area.size.x) ||
      (((type_ == Up) || type_ == Down) && size.y > area.size.y)) {
    LOG("do not fit");
    return {};
  }
  if ((type_ != Left && type_ != Right) /*|| size.x > area.size.x*/) {
    size.x = area.size.x;
  }
  if ((type_ != Up && type_ != Down) /*|| size.y > area.size.y*/) {
    size.y = area.size.y;
  }
  Rectangle result = {area.position, size};
  switch (type_) {
  case Up:
    area.position.y += size.y;
    area.size.y -= size.y;
    break;
  case Left:
    area.position.x += size.x;
    area.size.x -= size.x;
    break;
  case Down:
    result.position.y += area.size.y - size.y;
    area.size.y -= size.y;
    break;
  case Right:
    result.position.x += area.size.x - size.x;
    area.size.x -= size.x;
    break;
  case Fill:
    area.size = {0, 0};
    break;
  }
  LOG(result.size.x << ' ' << result.size.y);
  return result;
}

} // namespace gui
