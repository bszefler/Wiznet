#include "dht_sensor.h"

uint8_t data[5] = {0, 0, 0, 0, 0};
int valid_data = 0;
int response = 0;
GPIO_InitTypeDef GPIO_InitStruct;

void DataPin_Output() {

	// GPIOC PIN8 definition as OUT (to initialize transmission)

	GPIO_InitStruct.Pin = DHT_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
}

void DataPin_Input() {

	// GPIOC PIN8 definition as IN (to read data from sensor)

	GPIO_InitStruct.Pin = DHT_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
}

void DHT11_Init() {

	DataPin_Output();
	HAL_GPIO_WritePin(GPIOC, DHT_PIN, GPIO_PIN_RESET);
	DWT_Delay_us(18000);
	DataPin_Input();

}

void check_response() {

	response = 0;
	DWT_Delay_us(40);

	if (HAL_GPIO_ReadPin(GPIOC, DHT_PIN) == GPIO_PIN_RESET) {
		DWT_Delay_us(80);
		if (HAL_GPIO_ReadPin(GPIOC, DHT_PIN) == GPIO_PIN_SET) response = 1;
	}

	while (!(HAL_GPIO_ReadPin(GPIOC, DHT_PIN))) ;

}

void read_data() {

	int i, j = 0;
	int checksum = 0;

	for(i=0; i<5; i++){
		for(j=7; j>-1; j--){

			while(!(HAL_GPIO_ReadPin(GPIOC, DHT_PIN))) ;

			DWT_Delay_us(40);

			if((HAL_GPIO_ReadPin(GPIOC, DHT_PIN)) == GPIO_PIN_RESET){
				data[i] &= ~(1 << j);
			}
			else {
				data[i] |= (1 << j);
				while ((HAL_GPIO_ReadPin(GPIOC, DHT_PIN))) ;
			}
		}
	}

	checksum = data[0] + data[1] + data[2] + data[3];

	if (checksum == data[4]) valid_data = 1;

}
