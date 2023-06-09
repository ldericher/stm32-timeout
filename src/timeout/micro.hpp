#ifndef LIB_STM32_TIMEOUT_SRC_TIMEOUT_MICRO_H_
#define LIB_STM32_TIMEOUT_SRC_TIMEOUT_MICRO_H_

// local includes
#include "timeout.hpp"

// parent includes
#include "../timer/micro.hpp"

namespace yvk::timer {
class Micro;
}

namespace yvk::timeout {

/**
 * @brief triggers after a set amount of microseconds, uses TIM2
 */
class Micro : public Timeout {
 private:
  /// time units passed per tick
  static uint32_t const tick_time_;

  /// true if and only if TIM2 has been initialized
  static bool hw_initialized_;

  /// the first object of this class
  static Timeout* first_;

  /// the TIM2 interrupt
  static void TickTimers_us() asm("TIM2_IRQHandler");

  /// initialize TIM2
  static void InitHardware();

  // allow timer::Micro to call InitHardware
  friend class timer::Micro;

 public:
  /**
   * @brief Construct a new Micro object
   */
  Micro();

  virtual ~Micro();

  /**
   * @brief Start TIM2 interrupt
   */
  static void StartHardware();

  /**
   * @brief Stop TIM2 interrupt
   */
  static void StopHardware();
};

}  // namespace yvk::timeout

#endif /* LIB_STM32_TIMEOUT_SRC_TIMEOUT_MICRO_H_ */
