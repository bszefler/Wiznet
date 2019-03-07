#include "user_config.h"

uint8_t remoteIP[4]	= {192, 168, 1, 192};
SPI_HandleTypeDef hspi2;

void cs_sel() {
	HAL_GPIO_WritePin(GPIOB, SPI_NSS, GPIO_PIN_RESET); //CS LOW
}

void cs_desel() {
	HAL_GPIO_WritePin(GPIOB, SPI_NSS, GPIO_PIN_SET); //CS HIGH
}

uint8_t spi_rb(void) {
	uint8_t rbuf;
	HAL_SPI_Receive(&hspi2, &rbuf, 1, 0xFFFFFFFF);
	return rbuf;
}

void spi_wb(uint8_t b) {
	HAL_SPI_Transmit(&hspi2, &b, 1, 0xFFFFFFFF);
}

void Wiznet_init(){

	reg_wizchip_cs_cbfunc(cs_sel, cs_desel);
	reg_wizchip_spi_cbfunc(spi_rb, spi_wb);

	wiz_NetInfo netInfo = { .mac =  wiznet_mac,
							.ip = wiznet_ip,
							.sn = wiznet_sn,
							.gw = wiznet_gw};

	wizchip_setnetinfo(&netInfo);
}
