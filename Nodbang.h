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
    bool switch_new;
    bool switch_old;
    void send_midi();
    void note_on(byte channel, byte pitch, byte velocity);
    void note_off(byte channel, byte pitch, byte velocity);
    int neopixel_ix;
    void flash_led();
    Adafruit_NeoPixel strand;
    uint16_t r;
    uint16_t g;
    uint16_t b;


  public:
    Button(int pin_number, byte note, Adafruit_NeoPixel strip, int pixel_ix);
    int pin;
    byte midi_note;
    void refresh();
    void set_color(uint16_t red, uint16_t green,uint16_t blue);
};

#endif
