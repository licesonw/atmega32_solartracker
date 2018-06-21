# ATmega32 Solar Tracker

In this project, a light source following solar panel mount is developed on an ATmega32. The light source location is being detected by a LDR array. The 2-axis solar panel mount is actuated with two servomotors.

For driving the LCD, Davide Gironi's library was used which can be found [here](http://davidegironi.blogspot.com/2013/06/an-avr-atmega-library-for-hd44780-based.html#.WxxPVC_qigT).

The code was developed on MacOS 10.13 and written entirely in Xcode 9. The tools used for the toolchain are the xavr Xcode plugin and the CrossPack AVR environment.
