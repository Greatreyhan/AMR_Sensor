/*
 * communication_stm32.h
 *
 *  Created on: Feb 22, 2024
 *      Author: greatreyhan
 */

#ifndef SRC_COMMUNICATION_STM32_H_
#define SRC_COMMUNICATION_STM32_H_

#include "main.h"
#include "BNO08X.h"
#include <stdbool.h>

typedef struct{
	bool ping;
	bool standby;
	bool jalan;
	bool translasi;
	bool rotasi;
	bool req;
}feedback_t;

typedef struct{
	uint16_t x_acceleration;
	uint16_t y_acceleration;
	uint16_t z_acceleration;
	uint16_t roll;
	uint16_t pitch;
	uint16_t yaw;
	uint8_t cmd;
}com_get_t;

void komunikasi_init(UART_HandleTypeDef* uart_handler);
bool tx_ping(void);
uint8_t checksum_generator(uint8_t* arr, uint8_t size);
bool tx_send_postion(BNO08X_Typedef BNO08x);
void rx_start(void);
void rx_feedback(feedback_t* fed);
void rx_start_get(void);
void rx_get(com_get_t* get);

#endif /* SRC_COMMUNICATION_STM32_H_ */
