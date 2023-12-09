/*
 * TimeRTC.pde
 * example code illustrating Time library with Real Time Clock.
 * 
 */

#include <TimeLib.h>
#include <SD.h>
#include <SPI.h>

File myFile;

const int chipSelect = BUILTIN_SDCARD;

void setup()  {
  // set the Time library to use Teensy 3.0's RTC to keep time
  setSyncProvider(getTeensy3Time);
  setTime(0,0,0,25,11,2023);

  Serial.begin(9600);
  Serial.println(rtc_get());
  rtc_set(2698872972);
  Serial.println(rtc_get());
  
  while (!Serial);  // Wait for Arduino Serial Monitor to open
  delay(100);
  if (timeStatus()!= timeSet) {
    Serial.println("Unable to sync with the RTC");
  } else {
    Serial.println("RTC has set the system time");
    
    Serial.print("Initializing SD card...");

  if (!SD.begin(chipSelect)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");
  }
}

void loop() {
  myFile = SD.open("RTCTimeFile.txt", FILE_WRITE);

  if (Serial.available()) {
    time_t t = processSyncMessage();
    if (t != 0) {
      Teensy3Clock.set(t); // set the RTC
      setTime(t);
    }
  }
  digitalClockDisplay();  
  delay(1000);

  if (myFile) {
    fileClock();
  } else {
    Serial.println("error opening test.txt");
  }
  myFile.close();
  delay(10000000000);
}

void digitalClockDisplay() {
  // digital clock display of the time
  Serial.print(hour());
  printDigits(minute());
  printDigits(second());
  Serial.print(" ");
  Serial.print(day());
  Serial.print(" ");
  Serial.print(month());
  Serial.print(" ");
  Serial.print(year()); 
  Serial.println(); 
}

void fileClock() {
  myFile.print(hour());
  fileDigits(minute());
  fileDigits(second());
  myFile.print(" ");
  myFile.print(day());
  myFile.print(" ");
  myFile.print(month());
  myFile.print(" ");
  myFile.print(year()); 
  myFile.println(); 
}

time_t getTeensy3Time()
{
  return Teensy3Clock.get();
}

/*  code to process time sync messages from the serial port   */
#define TIME_HEADER  "T"   // Header tag for serial time sync message

unsigned long processSyncMessage() {
  unsigned long pctime = 0L;
  const unsigned long DEFAULT_TIME = 1357041600; // Jan 1 2013 

  if(Serial.find(TIME_HEADER)) {
     pctime = Serial.parseInt();
     return pctime;
     if( pctime < DEFAULT_TIME) { // check the value is a valid time (greater than Jan 1 2013)
       pctime = 0L; // return 0 to indicate that the time is not valid
     }
  }
  return pctime;
}

void printDigits(int digits){
  // utility function for digital clock display: prints preceding colon and leading 0
  Serial.print(":");
  if(digits < 10)
    Serial.print('0');
  Serial.print(digits);
}

void fileDigits(int digits) {
  myFile.print(":");
  if(digits < 10)
    myFile.print('0');
  myFile.print(digits);
}

