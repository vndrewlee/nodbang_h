/*
   Nodbang.cpp - Library nodbang classes
   Created by Andrew Lee, 2017
   Don't be an asshole.
 */

#include "Arduino.h"
#include "Nodbang.h"
#include "MIDIUSB.h"
#include "Adafruit_NeoPixel.h"

Button::Button(int pin_number, byte note, Adafruit_NeoPixel strip, int pixel_ix) {
  pin = pin_number;
  pinMode(pin, INPUT_PULLUP);
  switch_new = digitalRead(pin);
  switch_old = digitalRead(pin);
  midi_note = note;
  strand = strip;
  neopixel_ix = pixel_ix;
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
  if (switch_new == LOW && switch_old == HIGH) {
    note_on(0, midi_note, 127);  // Channel 0, middle C, normal velocity
    MidiUSB.flush();
  }
  if (switch_new == HIGH && switch_old == LOW) {
    note_off(0, midi_note, 127);   // Channel 0, middle C, normal velocity
    MidiUSB.flush();
  }
}

void Button::set_color(uint16_t red, uint16_t green,uint16_t blue) {
  r = red;
  g = green;
  b = blue;
}

void Button::flash_led() {
  if (switch_new == LOW) {
  strand.setPixelColor(neopixel_ix, strand.Color(r, g, b));
  strand.show();
} else {
  strand.setPixelColor(neopixel_ix, strand.Color(255, 255, 255));
  strand.show();
}
}

void Button::refresh() {
  switch_old = switch_new;
  switch_new = digitalRead(pin);
  send_midi();
  flash_led();
}

int smooth(int old_val, int new_val, float perc) {
        float new_smooth = float(old_val) * ( 1 - perc) + new_val * ( perc);
        return int(new_smooth);
}
