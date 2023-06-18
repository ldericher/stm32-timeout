#ifndef LIB_STM32_TIMEOUT_SRC_TIMEOUT_DELAY_H_
#define LIB_STM32_TIMEOUT_SRC_TIMEOUT_DELAY_H_

#include <stdint.h>

namespace yvk {

/**
 * @brief Blocking wait for (a minimum of) given time units
 *
 * @param target time units to wait
 */
template <typename T>
void Delay(uint32_t target);

}  // namespace yvk

#endif /* LIB_STM32_TIMEOUT_SRC_TIMEOUT_DELAY_H_ */
