/*
 * communication_stm32.c
 *
 *  Created on: Feb 22, 2024
 *      Author: greatreyhan
 */


#include "communication_stm32.h"

static UART_HandleTypeDef* huart;
static uint8_t rxbuf[3];
static uint8_t rxbuf_get[16];

void komunikasi_init(UART_HandleTypeDef* uart_handler){
	huart = uart_handler;
}

uint8_t checksum_generator(uint8_t* arr, uint8_t size){
	uint8_t chksm = 0;
	for(uint8_t i = 0; i < size; i++) chksm += arr[i];
	return (chksm & 0xFF);
}

bool tx_ping(void){
	uint8_t ping[] = {0xA5, 0x5A, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	ping[15] = checksum_generator(ping, 16);

	if(HAL_UART_Transmit_IT(huart, ping, 16) == HAL_OK) return true;
	else return false;
}

// Send Roll Pitch & Yaw from BNO08X Sensor
bool tx_send_postion(BNO08X_Typedef BNO08x){
	uint8_t steady[] = {0xA5, 0x5A, 0x02, ((BNO08x.yaw >> 8) & 0XFF), ((BNO08x.yaw) & 0XFF), ((BNO08x.pitch >> 8) & 0XFF), ((BNO08x.pitch) & 0XFF), ((BNO08x.roll >> 8) & 0XFF), ((BNO08x.roll) & 0XFF), ((BNO08x.x_acceleration >> 8) & 0XFF), ((BNO08x.x_acceleration) & 0XFF), ((BNO08x.y_acceleration >> 8) & 0XFF), ((BNO08x.y_acceleration) & 0XFF), ((BNO08x.z_acceleration >> 8) & 0XFF), ((BNO08x.z_acceleration) & 0XFF), 0x00};
	steady[15] = checksum_generator(steady, 16);

	if(HAL_UART_Transmit_IT(huart, steady, 16) == HAL_OK) return true;
	else return false;
}

void rx_start(void){
	HAL_UART_Receive_DMA(huart,rxbuf, 3);
}

void rx_start_get(void){
	HAL_UART_Receive_DMA(huart,rxbuf_get, 16);
}

void rx_feedback(feedback_t* fed){
	if(rxbuf[0] == 0xA5 && rxbuf[1]  == 0x5A){
		if(rxbuf[2] == 0x01) fed->ping = true;
		else if(rxbuf[2] == 0x02) fed->standby = true;
		else if(rxbuf[2] == 0x03) fed->jalan = true;
		else if(rxbuf[2] == 0x04) fed->translasi = true;
		else if(rxbuf[2] == 0x05) fed->rotasi = true;
		else if(rxbuf[2] == 0x06) fed->req = true;
	}
	HAL_UART_Receive_DMA(huart,rxbuf, 3);
}

void rx_get(com_get_t* get){
	for(int i = 0; i < 16; i++){
		if((rxbuf_get[i] == 0xA5) && (rxbuf_get[i+1] == 0x5A)){

			// Check for ping
			if(rxbuf_get[i+2] == 0x01){
				get->cmd = 0x01;
				uint8_t txbuf[3] = {0xA5, 0x5A, 0x01};
				HAL_UART_Transmit(huart, txbuf, 3, 1);
			}

			// Check for Position
			else if(rxbuf_get[i+2] == 0x02){
				get->yaw = (rxbuf_get[i+3] << 8) | rxbuf_get[i+4];
				get->pitch = (rxbuf_get[i+5] << 8) | rxbuf_get[i+6];
				get->roll = (rxbuf_get[i+7] << 8) | rxbuf_get[i+8];
				get->x_acceleration = (rxbuf_get[i+9] << 8) | rxbuf_get[i+10];
				get->y_acceleration = (rxbuf_get[i+11] << 8) | rxbuf_get[i+12];
				get->z_acceleration = (rxbuf_get[i+13] << 8) | rxbuf_get[i+14];
				uint8_t txbuf[3] = {0xA5, 0x5A, 0x02};
				HAL_UART_Transmit(huart, txbuf, 3, 1);
				get->cmd = 0x02;
			}

		}
	}
	HAL_UART_Receive_DMA(huart, rxbuf_get, 16);
}
