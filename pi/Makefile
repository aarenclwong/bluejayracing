CC := g++
CONSERVATIVE_FLAGS = -std=c++20 -Wall -Wextra -pedantic
DEBUGGING_FLAGS = -g -Ofast -pg
IGNORE_FLAGS = -Wno-psabi -Wvla
LINKING_FLAGS = -lgps -lpigpiod_if2 -lrt -pthread -lm -lfmt
CFLAGS = $(CONSERVATIVE_FLAGS) $(DEBUGGING_FLAGS) $(IGNORE_FLAGS) $(LINKING_FLAGS)


all: main accel_test adc_test gps_test gyro_test gps_test spi_test imu_test multiple_adc_test linpot_test


accel_test: tests/accel_test.cpp accelerometer.o i2c_dev.o
	$(CXX) -o accel_test tests/accel_test.cpp accelerometer.o i2c_dev.o $(CFLAGS)

gyro_test: tests/gyro_test.cpp gyro.o i2c_dev.o
	$(CXX) -o gyro_test tests/gyro_test.cpp gyro.o i2c_dev.o $(CFLAGS)

multiple_adc_test: tests/multiple_adc_test.cpp adc.o i2c_dev.o adafruit_ads.o
	$(CXX) -o multiple_adc_test tests/multiple_adc_test.cpp adc.o i2c_dev.o adafruit_ads.o $(CFLAGS)

adc_test: tests/adc_test.cpp adc.o i2c_dev.o adafruit_ads.o
	$(CXX) -o adc_test tests/adc_test.cpp adc.o i2c_dev.o adafruit_ads.o $(CFLAGS)

gps_test: tests/gps_test.cpp gps.o
	$(CXX) -o gps_test tests/gps_test.cpp gps.o $(CFLAGS)

spi_test: tests/spi_test.cpp spi_pigpio.o
	$(CXX) -o spi_test tests/spi_test.cpp spi_pigpio.o $(CFLAGS)

imu_test: tests/imu_test.cpp imu.o spi_pigpio.o 
	$(CXX) -o imu_test tests/imu_test.cpp imu.o spi_pigpio.o $(CFLAGS)

vr_test: tests/vr_test.cpp adc.o i2c_dev.o adafruit_ads.o processing/fourier.hpp
	$(CXX) -o vr_test tests/vr_test.cpp adc.o i2c_dev.o adafruit_ads.o $(CFLAGS)

linpot_test: tests/linpot_test.cpp adc.o i2c_dev.o adafruit_ads.o
	$(CXX) -o linpot_test tests/linpot_test.cpp adc.o i2c_dev.o adafruit_ads.o $(CFLAGS)

lcd_test: tests/lcd_test.cpp lcd.o i2c_dev.o
	$(CXX) -o lcd_test tests/lcd_test.cpp lcd.o i2c_dev.o $(CFLAGS)

kevin_lcd_test: tests/kevin_lcd_test.cpp lcd.o i2c_dev.o
	$(CXX) -o kevin_lcd_test tests/kevin_lcd_test.cpp lcd.o i2c_dev.o $(CFLAGS)

dro_test: tests/dro_test.cpp adc.o i2c_dev.o adafruit_ads.o lcd.o
	$(CXX) -o dro_test tests/dro_test.cpp adc.o lcd.o i2c_dev.o adafruit_ads.o

dro_test2: tests/dro_test2.cpp adc.o i2c_dev.o adafruit_ads.o lcd.o
	$(CXX) -o dro_test2 tests/dro_test2.cpp adc.o lcd.o i2c_dev.o adafruit_ads.o

torque_test: tests/torque_test.cpp adc.o i2c_dev.o adafruit_ads.o
	$(CXX) -o torque_test tests/torque_test.cpp adc.o i2c_dev.o adafruit_ads.o $(CFLAGS)

main: main.cpp adc.o gps.o imu.o lcd.o i2c_dev.o adafruit_ads.o spi_pigpio.o realtime.o 
	$(CXX) -o main main.cpp adc.o gps.o imu.o lcd.o i2c_dev.o adafruit_ads.o spi_pigpio.o realtime.o $(CFLAGS)


accelerometer.o: sensors/ISM330DHCX/accelerometer.cpp sensors/ISM330DHCX/accelerometer.hpp sensors/ISM330DHCX/ISM330DHCX.hpp
	$(CXX) -c sensors/ISM330DHCX/accelerometer.cpp $(CFLAGS)

gyro.o: sensors/ISM330DHCX/gyro.cpp sensors/ISM330DHCX/gyro.hpp sensors/ISM330DHCX/ISM330DHCX.hpp
	$(CXX) -c sensors/ISM330DHCX/gyro.cpp $(CFLAGS)

adc.o: sensors/ADS1115/adc.cpp sensors/ADS1115/adc.hpp sensors/ADS1115/ADS1115.hpp
	$(CXX) -c sensors/ADS1115/adc.cpp $(CFLAGS)

gps.o: sensors/MTK3339/gps.cpp sensors/MTK3339/gps.hpp
	$(CXX) -c sensors/MTK3339/gps.cpp $(CFLAGS)

i2c_dev.o: communication/i2c_dev.hpp communication/i2c_dev.cpp
	$(CXX) -Wvla -c communication/i2c_dev.cpp $(CFLAGS) 

spi_pigpio.o: communication/spi_pigpio.hpp communication/spi_pigpio.cpp communication/spi_d.hpp
	$(CXX) -c communication/spi_pigpio.cpp $(CFLAGS)

adafruit_ads.o: sensors/ADS1115/adafruit_ads.hpp sensors/ADS1115/adafruit_ads.cpp
	$(CXX) -c sensors/ADS1115/adafruit_ads.cpp $(CFLAGS)

imu.o: sensors/ISM330DHCX/imu.cpp sensors/ISM330DHCX/imu.hpp sensors/ISM330DHCX/ISM330DHCX.hpp
	$(CXX) -c sensors/ISM330DHCX/imu.cpp $(CFLAGS)

lcd.o: ui/lcd2004/lcd.cpp ui/lcd2004/lcd.hpp
	$(CXX) -c ui/lcd2004/lcd.cpp $(CFLAGS)

realtime.o: concurrency/realtime.cpp concurrency/realtime.hpp
	$(CXX) -c concurrency/realtime.cpp $(CFLAGS)

clean:
	rm -rf *.o *.gch *out *~ accel_test gyro_test main adc_test spi_test gps_test imu_test multiple_adc_test linpot_test vr_test lcd_test torque_test
