// local includes
#include "micro.hpp"

namespace timer {

Micro::Micro()
    : timer::Timer(timeout::Micro::tick_time_, timeout::Micro::first_) {
  timeout::Micro::InitHardware();
}

void Micro::StartHardware() {
  timeout::Micro::StartHardware();
}

void Micro::StopHardware() {
  timeout::Micro::StopHardware();
}

}  // namespace timer
