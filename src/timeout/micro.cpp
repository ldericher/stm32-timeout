#include "micro.hpp"

#include <stm32f1xx.h>

#define TICK_TIME 8

namespace timeout {

bool Micro::hw_initialized_ = false;
Timeout* Micro::first_ = nullptr;

void Micro::TickTimers_us() {
  CLEAR_BIT(TIM2->SR, TIM_SR_UIF);

  if (first_ != nullptr) {
    ((Micro*)first_)->TickAll();
  }
}

void Micro::InitHardware() {
  if (!hw_initialized_) {
    // ### USE TIM2 ###

    // enable TIM2 clock
    SET_BIT(RCC->APB1ENR, RCC_APB1ENR_TIM2EN);

    // PSC, ARR: 1 tick per TICK_TIME us
    TIM2->PSC = TICK_TIME - 1;
    TIM2->ARR = SystemCoreClock / 1000000UL;

    // enable counter
    SET_BIT(TIM2->CR1, TIM_CR1_CEN);
  }
}

Micro::Micro() : Timeout(TICK_TIME, first_) {
  InitHardware();
}

void Micro::StartHardware() {
  // reset timer
  TIM2->CNT = 0;

  // enable interrupt
  CLEAR_BIT(TIM2->SR, TIM_SR_UIF);
  SET_BIT(TIM2->DIER, TIM_DIER_UIE);
  NVIC_EnableIRQ(TIM2_IRQn);
}

void Micro::StopHardware() {
  // disable interrupt
  NVIC_DisableIRQ(TIM2_IRQn);
  CLEAR_BIT(TIM2->DIER, TIM_DIER_UIE);
  CLEAR_BIT(TIM2->SR, TIM_SR_UIF);
}

}  // namespace timeout