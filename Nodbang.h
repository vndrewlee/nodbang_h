/*
   Nodbang.h - Library nodbang classes
   Created by Andrew Lee, 2017
   Don't be an asshole.
 */



#ifndef Classes_h
#define Classes_h

#include "Arduino.h"
#include "MIDIUSB.h"
#include "Adafruit_NeoPixel.h"


class Button {
  private:
    bool _switch_new;
    bool _switch_old;
    int _pixel_ix;
    Adafruit_NeoPixel _strand;
    uint16_t _red;
    uint16_t _green;
    uint16_t _blue;
    byte _note;
    void send_midi();
    void note_on(byte channel, byte pitch, byte velocity);
    void note_off(byte channel, byte pitch, byte velocity);
    void flash_led();

  public:
    Button(int pin_number, byte note);
    int pin;
    void refresh();
    void set_pixel(Adafruit_NeoPixel strand, int pixel_ix, uint16_t red, uint16_t green,uint16_t blue);
};

#endif
