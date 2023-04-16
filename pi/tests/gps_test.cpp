#include "../sensors/MTK3339/gps.hpp"
#include <iostream>

// #include "libgpsmm.h"

using std::cout;
using std::endl;
using std::cerr;
using std::vector;


int main(/*int argc, char* argv[]*/) {
  /* TODO */
  gpsmm gps_rec("localhost", DEFAULT_GPSD_PORT);

  if (gps_rec.stream(WATCH_ENABLE|WATCH_JSON) == NULL) {
    cerr << "No GPSD running.\n";
    return 1;
  }

  GPS gps = GPS();
  
  gps.read();

  
	  
  return 0;

}