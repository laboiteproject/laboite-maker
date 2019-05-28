# laboite maker
laboite "maker edition" is a connected clock that displays a lot of information from the Internetz. This repository contains the ESP32/Arduino firmware that can connect to [lenuage.io](https://lenuage.io/) (a web app that collect data for you and send it back to your laboite device)!

<img src="https://raw.githubusercontent.com/laboiteproject/laboite-maker/master/images/labo%C3%AEte_usb.png" width="512">

This is the core library providing connectivity, parsing and debug. You will have to install the following libraries to get your laboîte device up and running:
* [ArduinoJson Library v5](https://github.com/bblanchon/ArduinoJson/tree/5.x): json parsing library
* [Adafruit GFX Library](https://github.com/adafruit/Adafruit-GFX-Library): core graphics library
* [X Window System bitmap font](https://github.com/adafruit/Adafruit-GFX-Library): custom font that need to be placed in `/Fonts` directory in Adafruit GFX library
* [Max72xxPanel Library](https://github.com/markruys/arduino-Max72xxPanel): hardware-specific library for the dot matrix driven by Max7219 controllers

## Features
* Fetching data from [lenuage.io](https://lenuage.io/) web application
* Store, update and draw the tiles in real time
* IFTTT enabled pushbutton

## Installation guide
This firmware can be uploaded using Arduino IDE, here is a step-by-step guide:
1. Install ESP32 toolchain by following this [guide](https://github.com/espressif/arduino-esp32/blob/master/docs/arduino-ide/boards_manager.md)
2. Install the libraries mentionned before using [Library manager](https://www.arduino.cc/en/Guide/Libraries#toc3)
3. Download this repo as a [.zip](https://github.com/laboiteproject/laboite-maker/archive/master.zip)
4. Unzip the archive into your Arduino `/libraries` folder
5. Upload the [laboiteMaker.ino](https://github.com/laboiteproject/laboite-maker/blob/master/examples/laboiteMaker/laboiteMaker.ino) example
6. Follow the [guide](https://github.com/laboiteproject/laboite-maker/wiki) to configure your laboite device!
