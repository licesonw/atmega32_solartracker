# ATmega32 Solartracker

2-Axis Solartracker with the following components:
* ATmega32
* 2 9g Servos
* 4 LDRs
* HD44780 based 16x2 LCD driven with I2C PCF8574 backpack

LCD library by [Davide Gironi](http://davidegironi.blogspot.com/2013/06/an-avr-atmega-library-for-hd44780-based.html#.Wy-JMS3qigQ).

The project was entirely developed on MacOS 10.13 High Sierra and Xcode 9 with the [CrossPack](https://www.obdev.at/products/crosspack/index.html) environment and the Xcode plugin [xavr](https://github.com/jawher/xavr).

The solar tracking module consists of a two-axis pan-tilt kit with 2 servo motors and a 3D-printed solar panel mount with a light separator for the sensors. The module is shown in the images below.
![Solar Module Side View](/img/Panel_sideview.jpg)
![Solar Module Top View](/img/panel_topview.jpg)
