#include "gps.hpp"
#include <iostream>


using std::cout;
using std::endl;
using std::cerr;
using std::vector;
using std::vector;


GPS::GPS(): gps_rec{"localhost", DEFAULT_GPSD_PORT} {
  if (gps_rec.stream(WATCH_ENABLE|WATCH_JSON) == NULL) {
    cerr << "No GPSD running.\n";
    return;
  }
}


GPS::~GPS() {
}

void GPS::reset() {
  if (gps_rec.stream(WATCH_ENABLE|WATCH_JSON) == NULL) {
    cerr << "No GPSD running.\n";
    return;
  }
}

vector<double> GPS::read() {
  vector<double> ret;
  struct gps_data_t* data;

  for(;;) {
    if (gps_rec.waiting(50)) break;
  }
  

  if ((data = gps_rec.read()) == NULL) {
	  cerr << "Gps read error." << endl;
	} else {
	  ret.push_back(data->fix.latitude);
    ret.push_back(data->fix.longitude);
    ret.push_back(data->fix.altitude);
  }
  return ret;
}



