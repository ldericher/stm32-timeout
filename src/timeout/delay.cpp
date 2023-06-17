#include "delay.hpp"
#include "micro.hpp"
#include "milli.hpp"

namespace yvk::timeout {

template <typename T>
void Delay(uint32_t target) {
  static SimpleCallback nop = []() {
    asm volatile("nop;");
  };

  static auto timeout = T();
  timeout.Start(target, nop);

  while (timeout.IsRunning()) {
    asm volatile("nop;");
  }
}

template void Delay<Milli>(uint32_t target);
template void Delay<Micro>(uint32_t target);

}  // namespace yvk::timeout
