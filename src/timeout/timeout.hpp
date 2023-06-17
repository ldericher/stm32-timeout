#ifndef LIB_STM32_TIMEOUT_SRC_TIMEOUT_TIMEOUT_H_
#define LIB_STM32_TIMEOUT_SRC_TIMEOUT_TIMEOUT_H_

// lib includes
#include <stdint.h>
#include <timeout/delay.hpp>

namespace timeout {

/// a standard callback function with context
typedef void (*Callback)(void*);

/// a simple callback function without context
typedef void (*SimpleCallback)();

/**
 * @brief triggers callback function after a set amount of time units,
 * non-blocking
 */
class Timeout {
 private:
  /// remaining time units until callback
  volatile uint32_t remaining_;

  /// time units passed per tick
  uint32_t const tick_time_;

  /// the callback function
  Callback callback_;

  /// parameter to be passed to callback
  void* context_;

  /// next timeout to be ticked
  Timeout* next_;
  /**
   * @brief Lets a tick pass, triggers callback if timeout reached
   */
  virtual void Tick();

 protected:
  /**
   * @brief Construct a new Timeout object
   *
   * @param tick_time time units passing between each tick
   * @param first reference to head of Object List for this class
   */
  explicit Timeout(uint32_t tick_time, Timeout*& first);

  /**
   * @brief Lets a tick pass for all objects linked behind a chosen one
   */
  virtual void TickAll();

  /**
   * @brief Triggers the callback instantly
   */
  virtual void Trigger();

  /**
   * @brief Starts a new timeout
   *
   * @param target time units until timeout
   */
  virtual void Start(uint32_t target);

 public:
  /**
   * @brief Starts a new timeout
   *
   * @param target time units until timeout
   * @param callback function to be called on timeout
   * @param context parameter to be passed to callback
   */
  void Start(uint32_t target, Callback callback, void* context);

  /**
   * @brief Starts a new timeout
   *
   * @param target time units until timeout
   * @param callback function to be called on timeout
   */
  void Start(uint32_t target, SimpleCallback callback);

  virtual bool IsRunning() const;

  /**
   * @brief Block until timeout finishes
  */
  virtual void Wait();

  virtual void Stop();
};

}  // namespace timeout

#endif /* LIB_STM32_TIMEOUT_SRC_TIMEOUT_TIMEOUT_H_ */
