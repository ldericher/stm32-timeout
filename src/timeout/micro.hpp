#ifndef LIB_STM32_TIMEOUT_SRC_TIMEOUT_MICRO_H_
#define LIB_STM32_TIMEOUT_SRC_TIMEOUT_MICRO_H_

// local includes
#include "timeout.hpp"

// parent includes
// #include "../timer/micro.h"

// namespace timer {
// class Micro;
// }

namespace timeout {

/**
 * @brief triggers after a set amount of microseconds, uses TIM2
 */
class Micro : public Timeout {
 private:
  /// true if and only if TIM2 has been initialized
  static bool hw_initialized_;

  /// the first object of this class
  static Timeout* first_;

  /// the TIM2 interrupt
  static void TickTimers_us() asm("TIM2_IRQHandler");

  /// initialize TIM2
  static void InitHardware();

  // // allow timer::Micro to call InitHardware
  // friend class timer::Micro;

 public:
  /**
   * @brief Construct a new Micro object
   */
  Micro();

  /**
   * @brief Start TIMER2 interrupt
   */
  static void StartHardware();

  /**
   * @brief Stop TIMER2 interrupt
   */
  static void StopHardware();
};

}  // namespace timeout

#endif /* LIB_STM32_TIMEOUT_SRC_TIMEOUT_MICRO_H_ */
