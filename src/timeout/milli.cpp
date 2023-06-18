#include "milli.hpp"

#include <stm32f1xx.h>

namespace yvk::timeout {

uint32_t const Milli::tick_time_ = 1;
bool Milli::hw_initialized_ = false;
Timeout* Milli::first_ = nullptr;

void Milli::TickTimers_ms() {
  CLEAR_BIT(TIM3->SR, TIM_SR_UIF);

  if (first_ != nullptr) {
    ((Milli*)first_)->TickAll();
  }
}

void Milli::InitHardware() {
  if (!hw_initialized_) {
    // ### USE TIM3 ###

    // enable TIM3 clock
    SET_BIT(RCC->APB1ENR, RCC_APB1ENR_TIM3EN);

    // PSC, ARR: 1 tick per Milli::tick_time_ ms
    TIM3->PSC = Milli::tick_time_ * 1000 - 1;
    TIM3->ARR = SystemCoreClock / 1000000UL;

    // enable counter
    SET_BIT(TIM3->CR1, TIM_CR1_CEN);
  }
}

Milli::Milli()
    : Timeout(Milli::tick_time_, first_) {
  InitHardware();
}

Milli::~Milli() {
  Unregister(first_);
}

void Milli::StartHardware() {
  // reset timer
  TIM3->CNT = 0;

  // enable interrupt
  CLEAR_BIT(TIM3->SR, TIM_SR_UIF);
  SET_BIT(TIM3->DIER, TIM_DIER_UIE);
  NVIC_EnableIRQ(TIM3_IRQn);
}

void Milli::StopHardware() {
  // disable interrupt
  NVIC_DisableIRQ(TIM3_IRQn);
  CLEAR_BIT(TIM3->DIER, TIM_DIER_UIE);
  CLEAR_BIT(TIM3->SR, TIM_SR_UIF);
}

}  // namespace yvk::timeout