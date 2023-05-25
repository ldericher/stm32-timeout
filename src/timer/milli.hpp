#ifndef LIB_STM32_TIMEOUT_SRC_TIMER_MILLI_H_
#define LIB_STM32_TIMEOUT_SRC_TIMER_MILLI_H_

// parent includes
#include "../timeout/milli.hpp"

// local includes
#include "timer.hpp"

namespace timer {

class Milli : public Timer {
 public:
  Milli();
};

}  // namespace timer

#endif /* LIB_STM32_TIMEOUT_SRC_TIMER_MILLI_H_ */