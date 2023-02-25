#ifndef SENSOR_INTERFACE_HPP
#define SENSOR_INTERFACE_HPP

#include <vector>

class SensorInterface {
public:
void reset();
std::vector<double> read();
}


#endif