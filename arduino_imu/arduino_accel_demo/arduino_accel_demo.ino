#include <Adafruit_FXOS8700.h>

/* working example of reading aceelerometer data */
Adafruit_FXOS8700 accelmag = Adafruit_FXOS8700(0x8700A, 0x8700B);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while (!Serial) {
    delay(1);
  }

    /* Initialise the sensor */
  if (!accelmag.begin()) {
    /* There was a problem detecting the FXOS8700 ... check your connections */
    Serial.println("Ooops, no FXOS8700 detected ... Check your wiring!");
    while (1)
      ;
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  sensors_event_t aevent, mevent;
  accelmag.getEvent(&aevent, &mevent);
  Serial.print("X:  ");
  Serial.print(aevent.acceleration.x, 4);
  Serial.print("   ");

  Serial.print("Y:  ");
  Serial.print(aevent.acceleration.y, 4);
  Serial.print("   ");

  Serial.print("Z:  ");
  Serial.print(aevent.acceleration.z, 4);
  Serial.print("   ");

  Serial.println("m/s^2");

  delay(500);
}