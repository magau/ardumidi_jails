/*
  This file is public domain. Use it as you like.
*/
#include <Arduino.h>
#include <ardumidi.h>

//int ledPin = 13;
int n_ctrl = 10;
bool notes_on[10] = {false, false, false, false, false,
                     false, false, false, false, false};
int notes[10] = {MIDI_C+MIDI_FLAT, MIDI_C,
                 MIDI_D+MIDI_FLAT, MIDI_D,
                 MIDI_E+MIDI_FLAT, MIDI_E,
                 MIDI_F, MIDI_G+MIDI_FLAT,
                 MIDI_G, MIDI_A+MIDI_OCTAVE+MIDI_FLAT}; 
int midi_ctrls[10] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
int iter_ctrl;

void setup()
{
  Serial.begin(115200);
  //pinMode(ledPin, OUTPUT);
  for (iter_ctrl=0; iter_ctrl < n_ctrl; ++iter_ctrl){
      pinMode(midi_ctrls[iter_ctrl], INPUT_PULLUP);
  }
}

void loop()
{
  for (iter_ctrl=0; iter_ctrl < n_ctrl; ++iter_ctrl){
      int ctrl_value = digitalRead(midi_ctrls[iter_ctrl]);
      if (!notes_on[iter_ctrl] && ctrl_value == LOW){
          midi_note_on(0, notes[iter_ctrl], 127);
          notes_on[iter_ctrl] = true;
          //digitalWrite(ledPin, HIGH);
      } else if (notes_on[iter_ctrl] && ctrl_value == HIGH){
          midi_note_off(0, notes[iter_ctrl], 127);
          notes_on[iter_ctrl] = false;
          //digitalWrite(ledPin, LOW);
      }
  }
}
