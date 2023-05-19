#ifndef LIB_STM32_TIMEOUT_SRC_TIMER_TIMER_H_
#define LIB_STM32_TIMEOUT_SRC_TIMER_TIMER_H_

#include "../timeout/timeout.hpp"

namespace timer {

/**
 * @brief triggers callback function every set amount of time units,
 * non-blocking
 */
class Timer : public timeout::Timeout {
 private:
  /// time units between callbacks
  uint32_t target_;

  /// true if and only if the timer is running
  volatile bool running_;

 protected:
  /**
   * @brief Construct a new Timer object
   *
   * @param tick_time time units passing between each tick
   * @param first reference to head of Object List for this class
   */
  explicit Timer(uint32_t tick_time, Timeout*& first);

  /**
   * @brief Starts a new timer
   *
   * @param target time units between triggers
   */
  virtual void Start(uint32_t target);

  virtual void Trigger();

 public:
  /**
   * @brief Starts a new timer
   *
   * @param target time units between triggers
   * @param callback function to be triggered
   * @param context parameter to be passed to callback
   */
  inline void Start(uint32_t target, timeout::Callback callback,
                    void* context) {
    timeout::Timeout::Start(target, callback, context);
  }

  /**
   * @brief Starts a new timer
   *
   * @param target time units between triggers
   * @param callback function to be triggered
   */
  inline void Start(uint32_t target, timeout::SimpleCallback callback) {
    timeout::Timeout::Start(target, callback);
  }

  /**
   * @brief Check if timer is runnning
   *
   * @return true timer is runnning
   * @return false timer is stopped
   */
  virtual bool IsRunning() const;

  /**
   * @brief Stop the timer
   */
  virtual void Stop();

  /**
   * @brief Resumes a stopped, previously started timer. Do not use on timers
   * that have never been started!
   */
  void Resume();
};

}  // namespace timer

#endif /* LIB_STM32_TIMEOUT_SRC_TIMER_TIMER_H_ */
