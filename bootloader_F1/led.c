/*
* STM32 HID Bootloader - USB HID bootloader for STM32F10X
* Copyright (c) 2018 Bruno Freitas - bruno@brunofreitas.com
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stm32f10x.h>
#include "config.h"

#if defined HAS_LED1_PIN	
void led_off() {
  LED1_OFF;
}

void led_on() {
  LED1_ON;
}
#endif

#if defined HAS_LED2_PIN	
void led2_off() {
  LED2_OFF;
}

void led2_on() {
  LED2_ON;
}
#endif

void pins_init() {
#if defined HAS_LED1_PIN	
  LED1_CLOCK_EN;
  LED1_BIT_0;
  LED1_BIT_1;
  LED1_MODE;
#endif

#if defined HAS_LED2_PIN	
  LED2_CLOCK_EN;
  LED2_BIT_0;
  LED2_BIT_1;
  LED2_MODE;
#endif

#if defined HAS_DISC_PIN
  DISC_CLOCK_EN;
  DISC_BIT_0;
  DISC_BIT_1;
  DISC_MODE;
  DISC_LOW;
#endif
  
#if defined PB2_PULLDOWN
  RCC->APB2ENR |= RCC_APB2ENR_IOPBEN; // Turn GPIOB clock on
  GPIOB->CRL &= ~(GPIO_CRL_CNF2_0);
  GPIOB->CRL |=  (GPIO_CRL_CNF2_1);
  GPIOB->CRL &= ~(GPIO_CRL_MODE2);
  GPIOB->ODR &= ~(GPIO_ODR_ODR2);
#else //PB2 is in FLOATING mode.
  RCC->APB2ENR |= RCC_APB2ENR_IOPBEN; // Turn GPIOB clock on
  GPIOB->CRL &= ~GPIO_CRL_MODE2;
  GPIOB->CRL &= ~(GPIO_CRL_MODE2);
#endif

}
