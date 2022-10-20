#ifndef IMU_H
#define IMU_H

#include <Adafruit_FXOS8700.h>
#include <Adafruit_FXAS21002C.h>


/* Wrapper class for the IMU to be used with Arduino */

class Imu {
private:
  Adafruit_FXOS8700 accelmag = Adafruit_FXOS8700(0x8700A, 0x8700B);
  Adafruit_FXAS21002C gyro = Adafruit_FXAS21002C(0x0021002C);
  sensors_event_t aevent;
  sensors_event_t mevent;
  sensors_event_t gevent;

public:

  void updateRaw() {
    aevent = sensors_event_t();
    mevent = sensors_event_t();
    gevent = sensors_event_t();
    accelmag.getEvent(&aevent, &mevent);
    gyro.getEvent(&gevent);
  }

  float getAx() {
    return aevent.acceleration.x;
  }

  float getAy() {
    return aevent.acceleration.y;
  }

  float getAz() {
    return aevent.acceleration.z;
  }

  float getGx() {
    return gevent.gyro.x;
  }

  float getGy() {
    return gevent.gyro.y;
  }

  float getGz() {
    return gevent.gyro.z;
  }

  float getMx() {
    return mevent.magnetic.x;
  }

  float getMy() {
    return mevent.magnetic.y;
  }

  float getMz() {
    return mevent.magnetic.z;
  }
};

#endif