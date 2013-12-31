Quadrotor Fake Signal
=====================
##Prerequisite

-St-Link 

-Sourcery CodeBench toolchain

##Setup

Install Sourcery CodeBench toolchain for ARM processor

Please read NCKU embedded course lab:19 

http://wiki.csie.ncku.edu.tw/embedded/Lab19

Install st-link firmware

`sudo apt-get install automake* libtool libusb-1.0-0-dev`

`git clone http://github.com/texane/stlink.git`

`cd stlink`

`./autogen.sh`

`./configure --prefix=/usr`

`make`

`sudo make install`

`sudo cp 49-stlinkv2.rules /etc/udev/rules.d/`

##Quick Start

Make sure your st-link is correctly connected. 

`make`

`make flash`

If you see the message that confirm flash successful, you can reset the MCU and receive the message from it. If you want to change the format of message, you will find the function `void test_serial_plot()`. This function actually is the task which do tansmit message.

##Glossary

Roll, Pitch, Yaw: the attitude measure from AHRS
CH1, CH2, CH3, CH4, CH5: the radio control signal measure by PWM input capturing
MOTOR 1~4: the PWM CCR
Acc x,y,z: the acceleration measure from accelerometer
Gyo x,y,z: the angular velocity meausre from gyroscope
