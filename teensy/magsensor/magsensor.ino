#include <Adafruit_MMC56x3.h>
#include <SD.h>

/* Assign a unique ID to this sensor at the same time */
Adafruit_MMC5603 mmc = Adafruit_MMC5603(12345);

File myFile; // file to write to

void setup(void) {
  Serial.begin(115200);
  while (!Serial)
    delay(10); // will pause Zero, Leonardo, etc until serial console opens

  Serial.println("Adafruit_MMC5603 Magnetometer Test");
  Serial.println("");

  /* Initialise the sensor */
  if (!mmc.begin(MMC56X3_DEFAULT_ADDRESS, &Wire)) {  // I2C mode
    /* There was a problem detecting the MMC5603 ... check your connections */
    Serial.println("Ooops, no MMC5603 detected ... Check your wiring!");
    while (1) delay(10);
  }

  if (!SD.begin(BUILTIN_SDCARD)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");

  // open the file
  myFile = SD.open("test.txt", FILE_WRITE);

  /* Display some basic information on this sensor */
  mmc.printSensorDetails();
}

void loop(void) {
  // Get a new sensor event 
  sensors_event_t event;
  mmc.getEvent(&event);

  myFile = SD.open("test.txt", FILE_WRITE);

  // Display the results (magnetic vector values are in micro-Tesla (uT))
  // Serial.print("X: ");
  // Serial.print(event.magnetic.x);
  // Serial.print("  ");
  // Serial.print("Y: ");
  // Serial.print(event.magnetic.y);
  // Serial.print("  ");
  // Serial.print("Z: ");
  // Serial.print(event.magnetic.z);
  // Serial.print("  ");
  // Serial.println("uT");

  //if the file opened okay, write to it:
  if (myFile) {
    Serial.print("Writing to test.txt...");
    myFile.print("X: ");
    myFile.print(event.magnetic.x);
    myFile.print("  ");
    myFile.print("Y: ");
    myFile.print(event.magnetic.y);
    myFile.print("  ");
    myFile.print("Z: ");
    myFile.print(event.magnetic.z);
    myFile.print("  ");
    myFile.println("uT");

    // Read and display temperature
    float temp_c = mmc.readTemperature();
    myFile.print("Temp: "); myFile.print(temp_c); myFile.println(" *C");
    // Delay before the next sample
    delay(100);

	  // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }

  // // Read and display temperature
  // float temp_c = mmc.readTemperature();
  // Serial.print("Temp: "); Serial.print(temp_c); Serial.println(" *C");
  // // Delay before the next sample
  // delay(100);
}