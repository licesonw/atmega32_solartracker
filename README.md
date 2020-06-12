# ATmega32 Solar Tracker

This 2-axis solar tracker automatically follows the varying postition of a lightsource to align the solar panel in a 90 degree angle to the light source. This is done by using an array of 4 light dependent resistors that are shielded from each other in a 3D printed chassis. 

The 2-Aaxis solar tracker includes the following components:
* ATmega32
* 2 servo motors (9g)
* 4 light dependent resistors (LDR)
* HD44780 based 16x2 LCD driven with I2C PCF8574 backpack

To present sensor data on the display, the LCD library by [Davide Gironi](http://davidegironi.blogspot.com/2013/06/an-avr-atmega-library-for-hd44780-based.html#.Wy-JMS3qigQ) was utilized.

The project was entirely developed on MacOS 10.13 High Sierra and Xcode 9 with the [CrossPack](https://www.obdev.at/products/crosspack/index.html) environment and the Xcode plugin [xavr](https://github.com/jawher/xavr).

The solar tracking module consists of a two-axis pan-tilt kit with 2 servo motors and a 3D-printed solar panel mount with a light separator for the sensors. The module is shown in the images below.

![Solar Module Side View](/img/Panel_sideview.jpg)
![Solar Module Top View](/img/panel_topview.jpg)
