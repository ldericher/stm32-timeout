#include "timer.hpp"

namespace timer {

Timer::Timer(uint32_t tick_time, Timeout*& first)
    : timeout::Timeout::Timeout(tick_time, first),
      running_(false) {}

void Timer::Start(uint32_t target) {
  // minimum one tick per trigger
  running_ = true;
  target_ = (target > 0) ? target : 1;
  timeout::Timeout::Start(target_);
}

void Timer::Trigger() {
  if (running_) {
    timeout::Timeout::Trigger();
    Start(target_);
  }
}

bool Timer::IsRunning() const {
  return running_;
}

void Timer::Stop() {
  running_ = false;
}

void Timer::Resume() {
  if (!running_) {
    Start(target_);
  }
}

}  // namespace timer
