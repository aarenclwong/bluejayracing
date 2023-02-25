CC := g++
CONSERVATIVE_FLAGS = -Wall -Wextra -pedantic
DEBUGGING_FLAGS = -g -Ofast -pg
IGNORE_FLAGS = -Wno-psabi
LINKING_FLAGS = #
CFLAGS = $(CONSERVATIVE_FLAGS) $(DEBUGGING_FLAGS) $(IGNORE_FLAGS)


all: main accel_test adc_test gps_test gyro_test gps_test


accel_test: tests/accel_test.cpp accelerometer.o
	$(CXX) -o accel_test tests/accel_test.cpp accelerometer.o $(CFLAGS)

gyro_test: tests/gyro_test.cpp gyro.o
	$(CXX) -o gyro_test tests/gyro_test.cpp gyro.o $(CFLAGS)

adc_test: tests/adc_test.cpp adc.o
	$(CXX) -o adc_test tests/adc_test.cpp adc.o $(CFLAGS)

gps_test: tests/gps_test.cpp gps.o
	$(CXX) -o accel_test tests/accel_test.cpp accelerometer.o $(CFLAGS)


main: accelerometer.o gyro.o adc.o
	$(CXX) -o main main.cpp accelerometer.o gyro.o adc.o gps.o $(CFLAGS)	


accelerometer.o: sensors/ISM330DHC/accelerometer.cpp sensors/ISM330DHC/accelerometer.hpp sensors/ISM330DHC/ISM330DHC.hpp
	$(CXX) -c sesnsors/ISM330DHC/accelerometer.cpp $(CFLAGS)

gyro.o: sensors/ISM330DHC/gyro.cpp sensors/ISM330DHC/gyro.hpp sensors/ISM330DHC/ISM330DHC.hpp
	$(CXX) -c sensors/ISM330DHC/accelerometer.cpp $(CFLAGS)

adc.o: sensors/ADS1115/adc.cpp sensors/ADS1115/adc.hpp
	$(CXX) -c sensors/ADS1115/adc.cpp $(CFLAGS)

gps.o: sensors/MTK3339/gps.cpp sensors/MTK3339/gps.hpp
	$(CXX) -c sensors/MTK3339/gps.cpp $(CFLAGS)
