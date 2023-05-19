#ifndef LIB_STM32_TIMEOUT_SRC_TIMER_MICRO_H_
#define LIB_STM32_TIMEOUT_SRC_TIMER_MICRO_H_

// parent includes
#include "../timeout/micro.hpp"

// local includes
#include "timer.hpp"

namespace timer {

class Micro : public Timer {
 public:
  Micro();
};

}  // namespace timer

#endif /* LIB_STM32_TIMEOUT_SRC_TIMER_MICRO_H_ */
