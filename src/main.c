#include "stm32f1xx.h"
#include "stdio.h"
#include "string.h"
#include "user_config.h"
#include "socket.h"
#include "dht_sensor.h"

#define DATA_MSG		"%d.%d %d.%d\r\n"
char msg[18] = {'0'};

void SPI2_Init(void);

int main(void)
{
	SystemCoreClock = 8000000;
	HAL_Init();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();

	SPI2_Init();

	DWT_Delay_Init();
	HAL_Delay(1000);

	Wiznet_init();

	while(socket(0, Sn_MR_TCP, 5000, 0) == -1);

	while(connect(0, remoteIP, remotePort) == -1);

	while(1){

		DHT11_Init();				// Init communication with sensor
		check_response();			// Waiting for valid response after init
		read_data();				// Read data from sensor

		sprintf(msg, DATA_MSG, data[0], data[1], data[2], data[3]);

		if(valid_data)
			send(0, (uint8_t *)msg, (uint16_t)strlen(msg));
		else

		HAL_Delay(200);
	}
}

void SPI2_Init(void)
{

    hspi2.Instance = SPI2;
    hspi2.Init.Mode = SPI_MODE_MASTER;
    hspi2.Init.Direction = SPI_DIRECTION_2LINES;
    hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
    hspi2.Init.CLKPolarity = SPI_POLARITY_LOW;
    hspi2.Init.CLKPhase = SPI_PHASE_1EDGE;
    hspi2.Init.NSS = SPI_NSS_SOFT;
    hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
    hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
    hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
    hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
    hspi2.Init.CRCPolynomial = 7;

    __HAL_RCC_SPI2_CLK_ENABLE();


    GPIO_InitStruct.Pin = SPI_SCK|SPI_MISO|SPI_MOSI;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = SPI_NSS;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	HAL_SPI_Init(&hspi2);
	__HAL_SPI_ENABLE(&hspi2);
}


