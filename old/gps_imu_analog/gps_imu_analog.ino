#include <Adafruit_FXOS8700.h>
#include <Adafruit_FXAS21002C.h>
#include <NMEAGPS.h>
#include <SD.h>
#include <GPSport.h>
#include <Wire.h>



Adafruit_FXOS8700 accelmag = Adafruit_FXOS8700(0x8700A, 0x8700B);
Adafruit_FXAS21002C gyro = Adafruit_FXAS21002C(0x21002C);

NMEAGPS  gps; // This parses the GPS characters
gps_fix  fix; // This holds on to the latest values
//
#define gps_port 57600
#define debug_port 115200
//static const int32_t zone_hours    PROGMEM = -4L; // EST no daylight
//static const int32_t zone_minutes PROGMEM =  0L; // usually zero
//static const NeoGPS::clock_t zone_offset  PROGMEM = zone_hours   * NeoGPS::SECONDS_PER_HOUR + zone_minutes * NeoGPS::SECONDS_PER_MINUTE;
                                
// X Y coorelation
//const double R PROGMEM = 6.371E6;

// SD Card setting
const int chipSelect PROGMEM = 10;

// File logging
File logfile;
uint8_t file_num = 0;
uint16_t sub_log = 0;


void setup(void) {
  Wire.setClock(400000);
  
  Serial.begin(debug_port);
  while (!Serial);

  Serial.print(F("Initializing GPS..."));
  gpsPort.begin(9600); //default ultimate gps baud
  gpsPort.println(F("$PMTK251,57600*2C"));
  gpsPort.flush();
  gpsPort.end();
  gpsPort.begin(gps_port);
  gpsPort.println(F("$PMTK220,200*2C")); // speak rate
  gpsPort.println(F("$PMTK300,200,0,0,0,0*2F")); //fix rate 5hz
  gpsPort.flush();
  Serial.println(F("GPS initialized!"));
  
  Serial.print(F("Initializing SD card..."));
  pinMode(chipSelect, OUTPUT);
  if (!SD.begin(chipSelect)) {
    Serial.print(F("card initialization failed, or not present."));
    while (1);
  }
  Serial.println(F("Card initialized!"));

  Serial.print(F("Initializing IMU..."));
  if (!accelmag.begin()) {
    Serial.println(F("No FXOS8700 detected!"));
    while (1);
  }
  if (!gyro.begin()) {
    Serial.println(F("No FXAS21002C detected!"));
    while (1);
  }
  Serial.println(F("IMU Initilized!"));

  // create a new file
  
  char filename[] = "BUT00000.CSV";
  for (uint8_t i = 0; i < 100; i++) {
    filename[3] = i / 10 + '0';
    filename[4] = i % 10 + '0';
    if (!SD.exists(filename)) {
      // Only open a new file if it doesn't exist
      file_num = i;
      sub_log=1;
      logfile = SD.open(filename, FILE_WRITE);
      break; // leave the loop!
    }
  }

  if (!logfile) {
    Serial.println(filename);
    Serial.println(F("broke"));
    while (1);
  }
  Serial.print(F("Logging to: "));
  Serial.println(filename);
  file_header();
  

}

#define SYNC_INTERVAL 5000
#define LOG_INTERVAL 25
#define RESET_INTERVAL 120000
uint32_t sync = millis();
uint32_t timer = millis();
uint32_t reset = millis();

void loop(void) {
  
  delay((LOG_INTERVAL - 1) - (millis() % LOG_INTERVAL));
  logfile.print(millis());
  logfile.print(F(", "));

//  Serial.print(F("g "));
  bool gotFix = false;
  if (gps.available( gpsPort )) {
    fix = gps.read();
    gotFix = true;
  }

  //Serial.print(F("i "));
  sensors_event_t aevent, mevent, gevent;
  accelmag.getEvent(&aevent, &mevent);
  gyro.getEvent(&gevent);

  //Serial.print(F("iw "));
  //m/s^2
  logfile.print(aevent.acceleration.x, 6);
  logfile.print(F(", "));
  logfile.print(aevent.acceleration.y, 6);
  logfile.print(F(", "));
  logfile.print(aevent.acceleration.z, 6);
  logfile.print(F(", "));
  //uT
  logfile.print(mevent.magnetic.x, 6);
  logfile.print(F(", "));
  logfile.print(mevent.magnetic.y, 6);
  logfile.print(F(", "));
  logfile.print(mevent.magnetic.z, 6);
  logfile.print(F(", "));
  //rad/s
  logfile.print(gevent.gyro.x, 6);
  logfile.print(F(", "));
  logfile.print(gevent.gyro.y, 6);
  logfile.print(F(", "));
  logfile.print(gevent.gyro.z, 6);


//  Serial.print(F("gw "));
  if(gotFix) {
    if (fix.valid.location) {//degrees
      Serial.print(fix.latitudeL(), 10);
      Serial.print(F(", "));
      Serial.print(fix.longitudeL(), 10);
      logfile.print(F( ", "));
      logfile.print(fix.latitudeL(), 10);
      logfile.print(F(", "));
      logfile.print(fix.longitudeL(), 10);
    } else {
      logfile.print(F(", 0, 0"));
    }
//    if (fix.valid.altitude) {//m
//      logfile.print(F(", "));
//      logfile.print(fix.altitude(), 6);
//    } else {
//      logfile.print(F(", 0"));
//    }
//    if (fix.valid.speed) {//mph
//      logfile.print(F(", "));
//      logfile.print(fix.speed_mph(), 6);
//    } else {
//      logfile.print(F(", 0"));
//    }
//    if (fix.valid.lat_err) {//m
//      logfile.print(F(", "));
//      logfile.print(fix.lat_err(), 6);
//    } else {
//      logfile.print(F(", 0"));
//    }
//    if (fix.valid.lon_err) {//m
//      logfile.print(F(", "));
//      logfile.print(fix.lon_err(), 6);
//    } else {
//      logfile.print(F(", 0"));
//    }
  }

  
  logfile.println();
  if ((millis() - timer) < SYNC_INTERVAL)
    return;
  timer = millis();
  if ((millis() - reset) > RESET_INTERVAL) {

    logfile.flush();
    
    file_gen();
    reset = millis();
  } else {
    logfile.flush();
    Serial.println(F("write"));
  }
  
}


void file_header() {
//  while(!gps.available(gpsPort));
//  fix = gps.read();
//  if (fix.valid.time && fix.valid.date) {
//      adjustTime( fix.dateTime );
//      logfile.print(F("#"));
//      logfile << fix.dateTime;
//      logfile.println(F(""));
//  }
  logfile.println(F("# ms, m/s^2, m/s^2, m/s^2, uT, uT, uT, deg/sec, deg/sec, deg/sec, deg*10^7, deg*10^7, m, mph, m, m"));
}




void file_gen() {
  logfile.close();
  Serial.println(F("reset"));
  char filename[] = "BUT00000.CSV";
  filename[3] = file_num / 10 + '0';
  filename[4] = file_num % 10 + '0';
  filename[5] = sub_log / 100 + '0';
  filename[6] = (sub_log / 10) % 10 + '0';
  filename[7] = sub_log % 10 + '0';
  if (!SD.exists(filename)) {
    logfile = SD.open(filename, FILE_WRITE);
    sub_log++;
  } 
  
  if (!logfile) {
    Serial.println(filename);
    Serial.println(F("broke"));
    logfile = SD.open(filename, FILE_WRITE);
    if (!logfile) Serial.println(F("broke 2nd"));
  }
  Serial.print(F("Logging to: "));
  Serial.println(filename); 
}


//void adjustTime( NeoGPS::time_t & dt )
//{
//  NeoGPS::clock_t seconds = dt; // convert date/time structure to seconds
//  seconds += zone_offset; //  Offset from UTC to the local timezone
//  dt = seconds; // convert seconds back to a date/time structure
//}
