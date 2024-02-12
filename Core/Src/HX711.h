/*
 * HX711.h
 *
 *  Created on: Jan 5, 2024
 *      Author: greatreyhan
 */

#ifndef SRC_HX711_H_
#define SRC_HX711_H_

#include "stdint.h"
#include "stdbool.h"
#include "main.h"

#define CHANNEL_A 0
#define CHANNEL_B 1
#define interrupts() __enable_irq()
#define noInterrupts() __disable_irq()

typedef struct
{
  GPIO_TypeDef  *clk_gpio;
  GPIO_TypeDef  *dat_gpio;
  uint16_t      clk_pin;
  uint16_t      dat_pin;
  long       	Aoffset;
  float         Ascale;
  uint8_t		Again;
  long       	Boffset;
  float         Bscale;
  uint8_t		Bgain;

}hx711_t;

void hx711_init(hx711_t *hx711, GPIO_TypeDef *clk_gpio, uint16_t clk_pin, GPIO_TypeDef *dat_gpio, uint16_t dat_pin);
void set_scale(hx711_t *hx711, float Ascale, float Bscale);
void set_gain(hx711_t *hx711, uint8_t Again, uint8_t Bgain);
void tare(hx711_t *hx711, uint8_t times, uint8_t channel);
void tare_all(hx711_t *hx711, uint8_t times);
float get_weight(hx711_t *hx711, int8_t times, uint8_t channel);
void set_offset(hx711_t *hx711, long offset, uint8_t channel);
uint8_t shiftIn(hx711_t *hx711, uint8_t bit_count);
bool is_ready(hx711_t *hx711);
void wait_ready(hx711_t *hx711);
long read(hx711_t *hx711, uint8_t channel);
long read_average(hx711_t *hx711, int8_t times, uint8_t channel);
double get_value(hx711_t *hx711, int8_t times, uint8_t channel);

// User Defined Function
void hx711_start(hx711_t *hx711, GPIO_TypeDef *clk_gpio, uint16_t clk_pin, GPIO_TypeDef *dat_gpio, uint16_t dat_pin);
void hx711_calibration(hx711_t *hx711, GPIO_TypeDef *clk_gpio, uint16_t clk_pin, GPIO_TypeDef *dat_gpio, uint16_t dat_pin);
float hx711_measure_channel(hx711_t hx711, uint8_t channel);
float hx711_measure_weight(hx711_t hx711, hx711_t hx711b);

#endif /* SRC_HX711_H_ */