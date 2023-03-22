#ifndef MTK3339_GPS_HPP
#define MTK3339_GPS_HPP

// Unsure why this header was included
//#include "../../communication/uart.hpp"

#include "../interfaces/sensor_interface.hpp"
#include "MTK3339.hpp"

class GPS: public SensorInterface {
public:
  GPS();
  ~GPS();
  
  void reset() override;
  std::vector<double> read() override;
private:
};

#endif