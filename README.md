# laboite maker
laboite "maker edition" is a connected clock that displays a lot of information from the Internetz. This repository contains the ESP32/Arduino firmware that can connect to [lenuage.io](https://lenuage.io/)!

![laboîte maker](images/laboîte_usb.png)

This is the core library providing connectivity, parsing and debug. You will have to install the following libraries to get your laboîte device up and running:
* [Adafruit GFX Library](https://github.com/adafruit/Adafruit-GFX-Library): core graphics library
* [X Window System bitmap font](https://github.com/adafruit/Adafruit-GFX-Library): custom font that need to be placed in `/Fonts` directory in Adafruit GFX library
* [Max72xxPanel Library](https://github.com/markruys/arduino-Max72xxPanel): hardware-specific library for the dot matrix driven by Max7219 controllers

## Features
* Fetching data from [lenuage.io](https://lenuage.io/) web application
* Store, update and draw the tiles in real time
* Upcoming IFTTT enabled pushbutton

## User guide
This firmware can be uploaded using
