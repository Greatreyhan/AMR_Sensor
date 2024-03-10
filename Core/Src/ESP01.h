/*
 * ESP01.h
 *
 *  Created on: Feb 24, 2024
 *      Author: greatreyhan
 */

#ifndef SRC_ESP01_H_
#define SRC_ESP01_H_

#include "main.h"

typedef struct {
    uint16_t header;
    uint8_t type;
    uint8_t cmd;
    int16_t position_x;
    int16_t position_y;
    int16_t position_z;
    uint8_t checksum;
} ESP01RX_Typedef;

void ESPO1_Init(UART_HandleTypeDef *huart_instance, char *IP_Address);
void ESP01_Callback(ESP01RX_Typedef *data);

//////////////////////////////////////// RESPONSE /////////////////////////////////////////////////////

void Response_Reset(void);
void Response_Ready(void);
void Response_Waiting_IP(void);
void Response_Good_IP(void);
void Response_Bad_IP(void);
void Response_Wait_For_WiFi(void);
void Response_Connected_To_WiFi(void);
void Response_Wait_For_MQTT(void);
void Response_Connected_To_MQTT(void);
void Response_Failed_To_MQTT(void);
void Response_Get_Message(void);
void Response_Send_Message(void);

#endif /* SRC_ESP01_H_ */
