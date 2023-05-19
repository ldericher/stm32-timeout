// local includes
#include "milli.hpp"

namespace timer {

Milli::Milli()
    : timer::Timer(timeout::Milli::tick_time_, timeout::Milli::first_) {
  timeout::Milli::InitHardware();
}

}  // namespace timer
