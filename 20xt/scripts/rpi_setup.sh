#!/bin/sh
sudo apt update -y
sudo apt upgrade -y
sudo apt autoremove -y
sudo apt install -y git emacs gpsd i2c-tools gpsd-clients pigpio
mkdir /home/pi/bin
curl -fsSL https://raw.githubusercontent.com/arduino/arduino-cli/95753fccb927e9730fac57f1039d5bb0af911321/install.sh | BINDIR=/home/pi/bin sh
sudo apt install libusb-dev -y
git clone https://github.com/PaulStoffregen/teensy_loader_cli.git /home/pi/teensy_loader_cli
wget https://www.pjrc.com/teensy/00-teensy.rules -P /home/pi/
sudo cp /home/pi/00-teensy.rules /etc/udev/rules.d/00-teensy.rules
curl -fsSL https://get.docker.com -o get-docker.sh
sudo sh ./get-docker.sh



