// local includes
#include "milli.hpp"

namespace timer {

Milli::Milli()
    : timer::Timer(timeout::Milli::tick_time_, timeout::Milli::first_) {
  timeout::Milli::InitHardware();
}

void Milli::StartHardware() {
  timeout::Milli::StartHardware();
}

void Milli::StopHardware() {
  timeout::Milli::StopHardware();
}

}  // namespace timer
