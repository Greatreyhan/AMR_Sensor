/*
 * Voltage_Current.h
 *
 *  Created on: Feb 12, 2024
 *      Author: greatreyhan
 */

#ifndef SRC_VOLTAGE_CURRENT_H_
#define SRC_VOLTAGE_CURRENT_H_

#include "main.h"

typedef struct{
	float voltage;
	float current;
}Voltage_Current_Typedef;

void VoltCurrent_Init(ADC_HandleTypeDef *hadc);
void VoltCurrent_Callback(Voltage_Current_Typedef *config);

#endif /* SRC_VOLTAGE_CURRENT_H_ */
