#ifndef LIB_STM32_TIMEOUT_SRC_TIMER_MICRO_H_
#define LIB_STM32_TIMEOUT_SRC_TIMER_MICRO_H_

// parent includes
#include "../timeout/micro.hpp"

// local includes
#include "timer.hpp"

namespace yvk::timer {

class Micro : public Timer {
 public:
  Micro();

  /**
   * @brief Start TIM2 interrupt
   */
  static void StartHardware();

  /**
   * @brief Stop TIM2 interrupt
   */
  static void StopHardware();
};

}  // namespace yvk::timer

#endif /* LIB_STM32_TIMEOUT_SRC_TIMER_MICRO_H_ */
