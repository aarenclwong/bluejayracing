#include "spi_pigpio.hpp"
#include <pigpiod_if2.h>
#include <cstdlib>

using std::uint8_t;
using std::vector;

#include <iostream>



using std::cout;
using std::endl;

uint8_t spi_read(spi_d sd, uint8_t reg) {
  char tx_buf[2];
  char rx_buf[2];
  tx_buf[0] = reg | 0x80;
  tx_buf[1] = 0x00;
  spi_xfer(sd.pi, sd.spi_handle, tx_buf, rx_buf, 2);
  return static_cast<uint8_t>(rx_buf[1]);
}

int spi_write(spi_d sd, uint8_t reg, uint8_t value) {
  char tx_buf[2];
  char rx_buf[2];
  tx_buf[0] = reg & 0x7F;
  tx_buf[1] = value;
  spi_xfer(sd.pi, sd.spi_handle, tx_buf, rx_buf, 2);
  return 0;
}

#include <cstring>

vector<uint8_t> spi_bulk_read(spi_d sd, uint8_t reg, int len) {
  char *tx_buf = (char*)malloc((len+1)*sizeof(char));
  char *rx_buf = (char*)malloc((len+1)*sizeof(char));
  memset(rx_buf, 0, sizeof(*rx_buf));
  memset(tx_buf, 0, sizeof(*tx_buf));
  // char tx_buf[len];
  // char rx_buf[len];
  tx_buf[0] = reg | 0x80;
  spi_xfer(sd.pi, sd.spi_handle, tx_buf, rx_buf, len+1);
  vector<uint8_t> ret;
  for (int i = 0; i < len; i++) {
    ret.push_back(static_cast<uint8_t>(rx_buf[i+1]));
  }
  return ret;
}

