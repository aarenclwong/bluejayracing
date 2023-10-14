#include <SPI.h>
#include "SdFat.h"
#define PIN_CS 10
#define SD_SPI_SPEED 50
SdFat sd //the sd card
SdFile file; //file

void setup() {
  Serial.begin(115200)
  //sd.begin will initialize the sd card
  if (!sd.begin(PIN_CS, SD_SCK_MHZ(SD_SPI_SPEED))) {
  }
  }

}

void loop() {
  // put your main code here, to run repeatedly:

}
