# laboite maker
laboite "maker edition" is a connected clock that displays a lot of information from the Internetz. This repository contains the ESP32/Arduino firmware that can connect to [lenuage.io](https://lenuage.io/) (a web app that collect data for you and send it back to your laboite device)!

![laboîte maker](https://raw.githubusercontent.com/laboiteproject/laboite-maker/master/images/labo%C3%AEte_usb.png)

This is the core library providing connectivity, parsing and debug. You will have to install the following libraries to get your laboîte device up and running:
* [Adafruit GFX Library](https://github.com/adafruit/Adafruit-GFX-Library): core graphics library
* [X Window System bitmap font](https://github.com/adafruit/Adafruit-GFX-Library): custom font that need to be placed in `/Fonts` directory in Adafruit GFX library
* [Max72xxPanel Library](https://github.com/markruys/arduino-Max72xxPanel): hardware-specific library for the dot matrix driven by Max7219 controllers

## Features
* Fetching data from [lenuage.io](https://lenuage.io/) web application
* Store, update and draw the tiles in real time
* Upcoming IFTTT enabled pushbutton

## User guide
This firmware can be uploaded using Arduino IDE after the ESP32 toolchain using Arduino IDE Boards Manager, here is a step-by-step guide:
1. Install ESP32 toolchain by following this [guide](https://github.com/espressif/arduino-esp32/blob/master/docs/arduino-ide/boards_manager.md)
2. Install the libraries mentionned before using [Library manager](https://www.arduino.cc/en/Guide/Libraries#toc3)
3. Download this repo as a [.zip](https://github.com/laboiteproject/laboite-maker/archive/master.zip)
4. Unzip the archive into your Arduino `/libraries` folder
5. Create a new Arduino sketch and copy-paste the code from lenuage.io that should look like this:

```c
/*
  laboîte ESP32 v0.1

  laboite "maker edition" is a connected clock that
  displays a lot of information from the Internetz!
  Please have a look at the user guide here:
  https://github.com/laboiteproject/lenuage/wiki/

  created 28 Oct 2018
  modified 11 Nov 2018
  by Baptiste Gaultier

  released under GPLv3
*/

#include <WiFi.h>
#include <WiFiMulti.h>
#include <LaBoite.h>

WiFiMulti wifiMulti;

Boite boite;

// wifi network params
char ssid[] = "";
char pass[] = "";

// lenuage params
char hostName[] = "lenuage.io";
char apikey[]   = "";

// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis = 0;        // will store last time LED was updated

// constants won't change:
const long interval = 3000;  

void setup() {
  Serial.begin(115200);
  Serial.print(F("laboîte ESP32 v0.1 booting"));

  boite.begin(hostName, apikey);

  wifiMulti.addAP(ssid, pass);

  boite.getTiles();
  boite.updateTiles();
}

void loop() {
  // here is where you'd put code that needs to be running all the time.
  boite.drawTiles();

  // check to see if it's time to connect again to lenuage server
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    // save the last time you were connected
    previousMillis = currentMillis;
    if(wifiMulti.run() == WL_CONNECTED) {
      boite.getTiles();
      boite.updateTiles();
    }
  }
}

```
