#include "delay.hpp"
#include "micro.hpp"
#include "milli.hpp"

namespace yvk {

template <typename T>
void Delay(uint32_t target) {
  static timeout::SimpleCallback nop = []() {
    asm volatile("nop;");
  };

  auto timeout = T();
  timeout.Start(target, nop);
  timeout.Wait();
}

template void Delay<timeout::Milli>(uint32_t target);
template void Delay<timeout::Micro>(uint32_t target);

}  // namespace yvk
