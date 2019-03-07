#ifndef DHT_SENSOR_H_
#define DHT_SENSOR_H_

#include "stdio.h"
#include "stm32f1xx.h"
#include "dwt_stm32_delay.h"

#define DHT_PIN		GPIO_PIN_8

/**
 * Data from sensor is collected in order:
 * 		data[0] - integer part of temperature
 * 		data[1] - fractional part of temperature
 * 		data[2] - integer part of humidity
 * 		data[3] - fractional part of humidity
 * 		data[4] - checksum flag
 */
extern uint8_t data[5];

extern int valid_data;
extern int response;
extern GPIO_InitTypeDef GPIO_InitStruct;

void DataPin_Output();
void DataPin_Input();
void DHT11_Init();
void check_response();
void read_data();

#endif /* DHT_SENSOR_H_ */
