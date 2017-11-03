/*
   Nodbang.cpp - Library nodbang classes
   Created by Andrew Lee, 2017
   Don't be an asshole.
 */

#include "Arduino.h"
#include "Nodbang.h"
#include "MIDIUSB.h"
#include "Adafruit_NeoPixel.h"

Button::Button(int pin_number, byte note) {
  pin = pin_number;
  pinMode(pin, INPUT_PULLUP);
  _switch_new = digitalRead(pin);
  _switch_old = digitalRead(pin);
  _note = note;
}

void Button::note_on(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOn = {0x09, 0x90 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOn);
}

void Button::note_off(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOff = {0x08, 0x80 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOff);
}

void Button::send_midi() {
  if (_switch_new == LOW && _switch_old == HIGH) {
    note_on(0, _note, 127);  // Channel 0, middle C, normal velocity
    MidiUSB.flush();
  }
  if (_switch_new == HIGH && _switch_old == LOW) {
    note_off(0, _note, 127);   // Channel 0, middle C, normal velocity
    MidiUSB.flush();
  }
}

void Button::set_pixel(Adafruit_NeoPixel strand, int pixel_ix, uint16_t red, uint16_t green,uint16_t blue) {
  _strand = strand;
  _pixel_ix = pixel_ix;
  _red = red;
  _green = green;
  _blue = blue;
}

void Button::flash_led() {
  if (_switch_new == LOW) {
  _strand.setPixelColor(_pixel_ix, _strand.Color(_red, _green, _blue));
  _strand.show();
} else {
  _strand.setPixelColor(_pixel_ix, _strand.Color(255, 255, 255));
  _strand.show();
}
}

void Button::refresh() {
  _switch_old = _switch_new;
  _switch_new = digitalRead(pin);
  send_midi();
  flash_led();
}

int smooth(int old_val, int new_val, float perc) {
        float new_smooth = float(old_val) * ( 1 - perc) + new_val * ( perc);
        return int(new_smooth);
}
