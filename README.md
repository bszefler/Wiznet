Wiznet_Gateway project

1. Project description
	The device is reading temperature and relative humidity data from sensor. It is done via 1-Wire protocol. 
	In next step the data is gathered in appropiate form and sent to remote server via TCP/IP protocol. Communication with ethernet chip is done using SPI interface. 
	
2. Used devices:
	
	- STM32F103 Nucelo board
	- DHT11 - Temperature and humidity sensor
	- Wiznet W5500 - TCP/IP Ethernet controller

3. External Libraries

	To perform communication with Wiznet Ethernet chip I used parts of ioLibrary_Driver (https://github.com/Wiznet/ioLibrary_Driver).