#ifndef SENSOR_INTERFACE_HPP
#define SENSOR_INTERFACE_HPP

#include <vector>

class SensorInterface {
public:
    virtual void reset() = 0;
    virtual std::vector<double> read() = 0;
};


#endif
