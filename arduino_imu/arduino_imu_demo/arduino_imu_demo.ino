#include <Adafruit_FXOS8700.h>
#include <Adafruit_FXAS21002C.h>

/* Outputs odd values */

/* Assign a unique ID to this sensor at the same time */
Adafruit_FXOS8700 accelmag = Adafruit_FXOS8700(0x8700A, 0x8700B);

/* Assign a unique ID to this sensor at the same time */
Adafruit_FXAS21002C gyro = Adafruit_FXAS21002C(0x0021002C);

typedef struct Data {
  float ax;
  float ay;
  float az;
  float gx;
  float gy;
  float gz;
  float mx;
  float my;
  float mz;
} Data;

Data data;

void updateImu() {
  sensors_event_t aevent;
  sensors_event_t mevent;
  sensors_event_t gevent;
  accelmag.getEvent(&aevent, &mevent);
  gyro.getEvent(&gevent);
  
  data.ax = aevent.acceleration.x;
  data.ay = aevent.acceleration.y;
  data.az = aevent.acceleration.z;
}

void setup(void) {
  Serial.begin(9600);
  delay(100);
}

void loop(void) {
  updateImu();

  /* Display the accel results (acceleration is measured in m/s^2) */
  Serial.print("A ");
  Serial.print("X: ");
  Serial.print(data.ax, 4);
  Serial.print("  ");
  Serial.print("Y: ");
  Serial.print(data.ay, 4);
  Serial.print("  ");
  Serial.print("Z: ");
  Serial.print(data.az, 4);
  Serial.print("  ");
  Serial.println("m/s^2");

  /* Display the mag results (mag data is in uTesla) */
  Serial.print("M ");
  Serial.print("X: ");
  Serial.print(mevent.magnetic.x, 1);
  Serial.print("  ");
  Serial.print("Y: ");
  Serial.print(mevent.magnetic.y, 1);
  Serial.print("  ");
  Serial.print("Z: ");
  Serial.print(mevent.magnetic.z, 1);
  Serial.print("  ");
  Serial.println("uT");

  Serial.println("");

  delay(500);
}
