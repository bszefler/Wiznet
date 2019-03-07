#ifndef INC_USER_CONFIG_H_
#define INC_USER_CONFIG_H_

#include "stdio.h"
#include "stm32f1xx.h"
#include "wizchip_conf.h"

/*
 	Server ip and port configuration
		remoteIP --> Server ip, which will collect data from mc
		remotePort --> Socket on which server is listening
 */

#define remotePort	5000
extern uint8_t remoteIP[4];

/*
 	 Wiznet configuration
 	 	 - mac address
 	 	 - ip address
 	 	 - subnet mask
 	 	 - gateway address

 */

#define	wiznet_mac		{0x00, 0x08, 0xdc, 0xab, 0xcd, 0xef}
#define wiznet_ip		{192, 168, 1, 57}
#define wiznet_sn		{255, 255, 255, 0}
#define wiznet_gw		{192, 168, 1, 1}

/*
 	SPI Configuration:
		PB12 ------> SPI_NSS
		PB13 ------> SPI_SCK
		PB14 ------> SPI_MISO
		PB15 ------> SPI_MOSI
 */

#define	SPI_NSS		GPIO_PIN_12
#define SPI_SCK		GPIO_PIN_13
#define SPI_MISO	GPIO_PIN_14
#define SPI_MOSI	GPIO_PIN_15
extern SPI_HandleTypeDef hspi2;			// SPI handler

/*
 * cs_sel() function is used to select wiznet (SPI_CS LOW)
 */
void cs_sel();

/*
 * cs_desel() function is used to deselct wiznet (SPI_CS HIGH)
 */
void cs_desel();

/*
 * spi_rb() function reads one byte via SPI
 */
uint8_t spi_rb(void);

/*
 * spi_wb() fucntion writes one byte via SPI
 */
void spi_wb(uint8_t );

/*
 * Wiznet_init() function initialize Wiznet chip
 * It configures its ip address, mac address, subnet mask and gateway address
 */
void Wiznet_init();


#endif /* INC_USER_CONFIG_H_ */
