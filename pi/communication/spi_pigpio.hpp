#ifndef SPI_PIGPIO_HPP
#define SPI_PIGPIO_HPP

#include <vector>
#include "spi_d.hpp"
#include <cstdint>
#include <linux/spi/spidev.h>


int spi_write(/*spi_d sd*/int spi_handle, std::uint8_t reg, std::uint8_t data);

std::uint8_t spi_read(/*spi_d sd*/int spi_handle, std::uint8_t reg);


#endif