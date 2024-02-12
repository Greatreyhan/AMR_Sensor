/*
 * Voltage_Current.c
 *
 *  Created on: Feb 12, 2024
 *      Author: greatreyhan
 */
#include "Voltage_Current.h"
static uint32_t value[2];
static float sensitivity = 0.1;
static float const_voltage = 1.488;

ADC_HandleTypeDef hadc;

void VoltCurrent_Init(ADC_HandleTypeDef *hadc_config){
	hadc = *hadc_config;
	HAL_ADC_Start_DMA(&hadc, value, 2);
}

void VoltCurrent_Callback(Voltage_Current_Typedef *config){
	config->voltage = (float)value[0]/4095*16.5;
	float rawVoltage = (float) value[1]*3.3*2*const_voltage/4095;
	config->current  = (rawVoltage - 2.5)/sensitivity;
	HAL_ADC_Start_DMA(&hadc, value, 2);
}

