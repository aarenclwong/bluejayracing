#include <TimeLib.h>
#include <SD.h>
#include <SPI.h>

File myFile;

const int chipSelect = BUILTIN_SDCARD;

void setup() {
  // put your setup code here, to run once:
  SD.begin(chipSelect);

  myFile = SD.open("rtcTime.txt", FILE_WRITE);

 if (myFile) {;
    myFile.print("Initial Time: ");
    myFile.println(rtc_get());
  } 
  
  if (rtc_get() < 2000000000) {
    rtc_set(2000000000);
  }

  
  
  myFile.close();
}

void loop() {
  // put your main code here, to run repeatedly:
  myFile = SD.open("rtcTime.txt", FILE_WRITE);
  if (myFile) {
    myFile.println(rtc_get());
    //rtc_set(2698872972);
    //myFile.println(rtc_get());
  } 
  myFile.close();
  delay(1000);
}
