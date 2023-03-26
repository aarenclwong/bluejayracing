#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <cstring>
// #include <pigpio.h>

//Ioctls

// uint8_t spi_read(int spi_handle, uint8_t reg) {
//   int status;
//   struct spi_ioc_transfer xfer;

//     memset(&xfer, 0, sizeof(xfer));
//     uint8_t	inbuf[2], outbuf[2];

// 	memset(&inbuf, 0, sizeof(inbuf));
// 	memset(&outbuf, 0, sizeof(outbuf));

// 	outbuf[0] = reg | 0x80;

// 	xfer.tx_buf = (unsigned long)outbuf;
// 	xfer.rx_buf = (unsigned long)inbuf;
// 	xfer.len = 2;

// 	xfer.speed_hz = 10000000;
// 	xfer.delay_usecs = 5;
// 	xfer.bits_per_word = 8;
// 	xfer.cs_change = 0;
// 	status = ioctl(spi_handle, SPI_IOC_MESSAGE(1), &xfer);
// 	if (status < 0) {
// 	  perror("SPI_IOC_MESSAGE");
// 	}
//     cout << (int)inbuf[0] <<"."<< (int)inbuf[1] <<"."<< (int)outbuf[0] <<"."<< (int)outbuf[1] <<"."<< endl;
// 	return inbuf[1];
// }

// int spi_write(int spi_handle, uint8_t reg, uint8_t value) {
//   int status;
//   struct spi_ioc_transfer xfer;
// 	memset(&xfer, 0, sizeof(xfer));
//   uint8_t	outbuf[3];
	

// 	memset(&outbuf, 0, sizeof outbuf);

// 	outbuf[0] = reg;
// 	outbuf[1] = value;
// 	xfer.tx_buf = (unsigned long)outbuf;
// 	xfer.rx_buf = NULL;
// 	xfer.len = 2;

// 	xfer.speed_hz = 10000000;
// 	xfer.delay_usecs = 5;
// 	xfer.bits_per_word = 8;
// 	xfer.cs_change = 0;

// 	status = ioctl(spi_handle, SPI_IOC_MESSAGE(1), &xfer);
// 	if (status < 0) {
// 		perror("SPI_IOC_MESSAGE");
// 	}

//   return 0;
// }






//Synchronous

// uint8_t spi_read(int spi_handle, unsigned char reg)
// {
//     char tx_buf[2];
//     char rx_buf[2];
//     tx_buf[0] = reg | 0x80;
//     tx_buf[1] = 0x00;
//     spiXfer(spi_handle, tx_buf, rx_buf, 2);
//     return (uint8_t)rx_buf[1];
// }

// int spi_write(int spi_handle, unsigned char reg, unsigned char value)
// {
//     char tx_buf[2];
//     char rx_buf[2];
//     tx_buf[0] = reg & 0x7F;
//     tx_buf[1] = value;
//     cout << spiXfer(spi_handle, tx_buf, rx_buf, 1) << endl;
//     return 0;
// }