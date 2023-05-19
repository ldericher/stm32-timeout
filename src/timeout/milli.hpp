#ifndef LIB_STM32_TIMEOUT_SRC_TIMEOUT_MILLI_H_
#define LIB_STM32_TIMEOUT_SRC_TIMEOUT_MILLI_H_

// local includes
#include "timeout.hpp"

// parent includes
#include "../timer/milli.hpp"

namespace timer {
class Milli;
}

namespace timeout {

/**
 * @brief triggers after a set amount of milliseconds, uses TIM3
 */
class Milli : public Timeout {
 private:
  /// time units passed per tick
  static uint32_t const tick_time_;
  
  /// true if and only if TIM3 has been initialized
  static bool hw_initialized_;

  /// the first object of this class
  static Timeout* first_;

  /// the TIM3 interrupt
  static void TickTimers_ms() asm("TIM3_IRQHandler");

  /// initialize TIM3
  static void InitHardware();

  // allow timer::Milli to call InitHardware
  friend class timer::Milli;

 public:
  /**
   * @brief Construct a new Milli object
   */
  Milli();

  /**
   * @brief Start TIM3 interrupt
   */
  static void StartHardware();

  /**
   * @brief Stop TIM3 interrupt
   */
  static void StopHardware();
};

}  // namespace timeout

#endif /* LIB_STM32_TIMEOUT_SRC_TIMEOUT_MILLI_H_ */
