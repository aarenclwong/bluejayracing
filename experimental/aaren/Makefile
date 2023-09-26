CC := g++
CONSERVATIVE_FLAGS = -std=c++20 -Wall -Wextra -pedantic
DEBUGGING_FLAGS = -g -Ofast -pg
IGNORE_FLAGS = -Wno-psabi -Wvla
LINKING_FLAGS = -lgps -lpigpiod_if2 -lrt -pthread -lm -lfmt
CFLAGS = $(CONSERVATIVE_FLAGS) $(DEBUGGING_FLAGS) $(IGNORE_FLAGS) $(LINKING_FLAGS)

all: main

main: main.cpp i2c_dev.o
	$(CXX) -o main main.cpp i2c_dev.o $(CFLAGS)

i2c_dev.o: i2c_dev.hpp i2c_dev.cpp
	$(CXX) -c i2c_dev.cpp $(CFLAGS) 

clean:
	rm -rf *.o *.gch *out *~ accel_test gyro_test main adc_test spi_test gps_test imu_test multiple_adc_test linpot_test vr_test lcd_test torque_test
