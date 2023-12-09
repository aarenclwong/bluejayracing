#include <TimeLib.h>
#include <Wire.h>
#include <Adafruit_INA219.h>
#include <SD.h>
#include <SPI.h>

File myFile;

Adafruit_INA219 ina219;

const int chipSelect = BUILTIN_SDCARD;

void setup(void)
{
  SD.begin(chipSelect); // set chip to SD card

  // Serial.begin(115200);
  // while (!Serial) {
  //     // will pause Zero, Leonardo, etc until serial console opens
  //     delay(1);
  // }
    
  // Serial.print("Initializing SD card...");

  if (!SD.begin(chipSelect)) {
    // Serial.println("initialization failed!");
    return;
  }
  // Serial.println("initialization done.");

  if (rtc_get() < 2000000000){
    // Serial.println("ITS BEING RESET");
    rtc_set(2000000000); // set base time (starts counting number of seconds starting at 2 billion)
  }
  
  // Initialize the INA219.
  // By default the initialization will use the largest range (32V, 2A).  However
  // you can call a setCalibration function to change this range (see comments).
  if (! ina219.begin()) {
    // Serial.println("Failed to find INA219 chip");
    while (1) { delay(10); }
  }
  // To use a slightly lower 32V, 1A range (higher precision on amps):
  //ina219.setCalibration_32V_1A();
  // Or to use a lower 16V, 400mA range (higher precision on volts and amps):
  ina219.setCalibration_16V_400mA();

  Wire.begin();

  // Serial.println("Measuring voltage and current with INA219 ...");
}

void loop(void) 
{
  // open the file. 
  myFile = SD.open("test1.txt", FILE_WRITE);
  
  // if the file opened okay, write to it:
  if (myFile) {
    time_elapsed(myFile, 0, 0, 0); // SET START TIME HERE
    write_volts(myFile);
	// close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    myFile.println("error opening test.txt");
  }

  delay(1000);
}

void write_volts(File myFile){
  float shuntvoltage = 0;
  float busvoltage = 0;
  float current_mA = 0;
  float loadvoltage = 0;
  float power_mW = 0;

  shuntvoltage = ina219.getShuntVoltage_mV();
  busvoltage = ina219.getBusVoltage_V();
  current_mA = ina219.getCurrent_mA();
  power_mW = ina219.getPower_mW();
  loadvoltage = busvoltage + (shuntvoltage / 1000);

  myFile.println("");
  myFile.print("Bus Voltage:   "); myFile.print(busvoltage); myFile.println(" V");
  myFile.print("Shunt Voltage: "); myFile.print(shuntvoltage); myFile.println(" mV");
  myFile.print("Load Voltage:  "); myFile.print(loadvoltage); myFile.println(" V");
  myFile.print("Current:       "); myFile.print(current_mA); myFile.println(" mA");
  myFile.print("Power:         "); myFile.print(power_mW); myFile.println(" mW");
  myFile.println("");
}

void time_elapsed(File myFile, int hour, int min, int sec){
  int total = rtc_get() - 2000000000;
  hour += total / 3600;
  total %= 3600;
  min += total / 60;
  total %= 60;
  sec += total;

  myFile.println("");
  myFile.print(hour);
  myFile.print(":");
  myFile.print(min);
  myFile.print(":");
  myFile.print(sec);

  // Serial.println(rtc_get());
  // Serial.println("");
  // Serial.print(hour);
  // Serial.print(":");
  // Serial.print(min);
  // Serial.print(":");
  // Serial.print(sec);
}
