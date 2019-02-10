/*
  LaBoite.h - Library for laboite maker edition.
  Created by Baptiste Gaultier, November 2, 2018.
  Released under GPLv3
*/
#ifndef LaBoite_h
#define LaBoite_h

#include "Arduino.h"

#define TILES_ARRAY_SIZE 32
#define ITEMS_ARRAY_SIZE 16
// uncomment if you want to debug
//#define DEBUG

class Item
{
  public:
    Item();
    Item(
      byte type,
      int x,
      int y,
      String content
    );
    byte getType() {return _type;};
    void setType(const char * type);
    byte getWidth() {return _width;};
    void setWidth(byte width) {_width = width;};
    byte getHeight() {return _height;};
    void setHeight(byte height) {_height = height;};
    byte getX() {return _x;};
    void setX(byte x) {_x = x;};
    byte getY() {return _y;};
    void setY(byte y) {_y = y;};
    String getContent() {return _content;};
    void setContent(String content) {_content = content;};
    String asString();
  private:
    byte    _type;
    byte    _width;
    byte    _height;
    byte    _x;
    byte    _y;
    String  _content;
};


class Tile
{
  public:
    Tile();
    Tile(
      unsigned int id,
      unsigned long last_activity,
      unsigned int duration,
      byte brightness,
      byte transition
    );
    unsigned int getId() {return _id;};
    void setId(unsigned int id) {_id = id;};
    unsigned long getLastActivity() {return _last_activity;};
    void setLastActivity(unsigned long last_activity) {_last_activity = last_activity;};
    unsigned int getDuration() {return _duration;};
    void setDuration(unsigned int duration) {_duration = duration;};
    byte getBrightness() {return _brightness;};
    void setBrightness(byte brightness) {_brightness = brightness;};
    byte getTransition() {return _transition;};
    void setTransition(byte transition) {_transition = transition;};
    String asString();
    Item items[TILES_ARRAY_SIZE];
  private:
    unsigned int  _id;
    unsigned long _last_activity;
    unsigned int  _duration;
    byte          _brightness;
    byte          _transition;
};

class Boite
{
  public:
    Boite();
    void    begin(String server);
    boolean getTiles();
    boolean updateTiles();
    boolean updateTile(unsigned int id);
    boolean sendPushButtonRequest();
    void    drawTiles();
    void    drawTile(int id);
    void    drawTile(int id, int x, int y);
    void    getConfig();
    String  getSSID() {return _ssid;};
    String  getPass() {return _pass;};
    void    getApiKeyFromSerial();
  private:
    boolean _buttonPressed;
    boolean _intensityIncreases;
    int     _currentIntensity;
    String  _server;
    String  _apikey;
    String  _ssid;
    String  _pass;
    Tile    _tiles[TILES_ARRAY_SIZE];
    void    _interruptServiceRoutine();
    void    _updateSplashScreen();
    void    _drawTileTransition(int id);
    void    _fade(int id);
};

#endif
