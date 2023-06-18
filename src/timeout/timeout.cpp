#include "timeout.hpp"

#include <cmsis_gcc.h>
#include <stdbool.h>

namespace yvk::timeout {

Timeout::Timeout(uint32_t tick_time, Timeout*& first)
    : remaining_(0),
      tick_time_(tick_time),
      callback_(nullptr),
      context_(nullptr) {
  // register Timeout
  next_ = first;
  first = this;
}

void Timeout::Unregister(Timeout*& first) {
  // check if first Timeout is "this"
  if (first == this) {
    // unregister Timeout
    first = this->next_;
    return;
  }

  // find "this" in Timeout chain
  auto current = first;
  while (current->next_ != this) {
    // check if Timeout already unregistered
    if (current->next_ == nullptr) {
      return;
    }

    current = current->next_;
  }

  // unregister Timeout
  current->next_ = current->next_->next_;
}

void Timeout::Tick() {
  if (remaining_ > 0) {
    if (remaining_ > tick_time_) {
      // there was more than one tick remaining
      remaining_ -= tick_time_;
    } else {
      // exactly or less than one tick remaining
      remaining_ = 0;
      Trigger();
    }
  }
}

void Timeout::TickAll() {
  // iterate list, call Tick()
  Timeout* current = this;
  while (current != nullptr) {
    current->Tick();
    current = current->next_;
  }
}

void Timeout::Trigger() {
  // trigger the callback
  (*callback_)(context_);
}

void Timeout::Start(uint32_t target) {
  if (target > 0) {
    // start timer
    remaining_ = target;
  } else {
    // instantly trigger the callback
    remaining_ = 0;
    Trigger();
  }
}

void Timeout::Start(uint32_t target, Callback callback, void* context) {
  bool interrupts_enabled = (__get_PRIMASK() == 0);
  __disable_irq();

  callback_ = callback;
  context_ = context;
  Start(target);

  if (interrupts_enabled) {
    __enable_irq();
  }
}

void Timeout::Start(uint32_t target, SimpleCallback callback) {
  Start(target, (Callback)callback, nullptr);
}

bool Timeout::IsRunning() const {
  return remaining_ != 0;
}

void Timeout::Wait() {
  while (IsRunning()) {
    asm volatile("nop;");
  }
}

void Timeout::Stop() {
  remaining_ = 0;
}

}  // namespace yvk::timeout