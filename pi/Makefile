CC := g++
CONSERVATIVE_FLAGS = -std=c++11 -Wall -Wextra -pedantic
DEBUGGING_FLAGS = -g -Ofast -pg
IGNORE_FLAGS = -Wno-psabi -Wvla
LINKING_FLAGS = 
CFLAGS = $(CONSERVATIVE_FLAGS) $(DEBUGGING_FLAGS) $(IGNORE_FLAGS)


all: main accel_test adc_test gps_test gyro_test gps_test


accel_test: tests/accel_test.cpp accelerometer.o i2c_dev.o
	$(CXX) -o accel_test tests/accel_test.cpp accelerometer.o i2c_dev.o $(CFLAGS)

gyro_test: tests/gyro_test.cpp gyro.o i2c_dev.o
	$(CXX) -o gyro_test tests/gyro_test.cpp gyro.o i2c_dev.o $(CFLAGS)

adc_test: tests/adc_test.cpp adc.o i2c_dev.o
	$(CXX) -o adc_test tests/adc_test.cpp adc.o i2c_dev.o $(CFLAGS)

gps_test: tests/gps_test.cpp gps.o i2c_dev.o
	$(CXX) -o accel_test tests/gps_test.cpp gps.o i2c_dev.o $(CFLAGS)

spi_test: tests/spi_test.cpp spi_pigpio.o
	$(CXX) -pthread -o spi_test tests/spi_test.cpp spi_pigpio.o $(CFLAGS) -lpigpio -lrt 


main: accelerometer.o gyro.o adc.o gps.o i2c_dev.o
	$(CXX) -o main main.cpp accelerometer.o gyro.o adc.o gps.o i2c_dev.o $(CFLAGS)	

accelerometer.o: sensors/ISM330DHCX/accelerometer.cpp sensors/ISM330DHCX/accelerometer.hpp sensors/ISM330DHCX/ISM330DHCX.hpp
	$(CXX) -c sensors/ISM330DHCX/accelerometer.cpp $(CFLAGS)

gyro.o: sensors/ISM330DHCX/gyro.cpp sensors/ISM330DHCX/gyro.hpp sensors/ISM330DHCX/ISM330DHCX.hpp
	$(CXX) -c sensors/ISM330DHCX/gyro.cpp $(CFLAGS)

adc.o: sensors/ADS1115/adc.cpp sensors/ADS1115/adc.hpp
	$(CXX) -c sensors/ADS1115/adc.cpp $(CFLAGS)

gps.o: sensors/MTK3339/gps.cpp sensors/MTK3339/gps.hpp
	$(CXX) -c sensors/MTK3339/gps.cpp $(CFLAGS)

i2c_dev.o: communication/i2c_dev.hpp communication/i2c_dev.cpp
	$(CXX) -c communication/i2c_dev.cpp $(CFLAGS)

spi_pigpio.o: communication/spi_pigpio.hpp communication/spi_pigpio.cpp communication/spi_d.hpp
	$(CXX) -c communication/spi_pigpio.cpp $(CFLAGS) 

clean:
	rm -rf *.o *.gch *out *~ accel_test gyro_test main adc_test spi_test 