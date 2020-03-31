#include <Bounce2.h>
#include <MIDI.h>
#include "config.h"

// MIDI 
MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI);

// expression pedal
byte jack_check_exp = LOW;      // HIGH when exp. pedal present
byte jack_check_sustain = LOW;  // HIGH when sus pedal present
int expression = 0;             // exp. pedal reading on pin 20 (A6)
int expression_last = 0;        // exp. pedal reading from previous loop
int expression_threshold = 10;  // threshold for detection of movement
int cc_mapped = 0;              // reading mapped to 0-127              

// debouncing
Bounce sw1 = Bounce(2, 5); // debounce pin 2, 5ms debounce time
Bounce sw2 = Bounce(3, 5); // debounce pin 3, 5ms debounce time
Bounce sw3 = Bounce(4, 5); // debounce pin 4, 5ms debounce time
Bounce sw4 = Bounce(5, 5); // debounce pin 5, 5ms debounce time

Bounce sus_pedal = Bounce(18, 10); // debounce pin 18, 10 ms debounce time
Bounce jack_check_sus = Bounce(17, 5); // debounce pin 17, 5 ms debounce time

void setup() {
 // switches
 pinMode(2, INPUT_PULLUP);  // SW1
 pinMode(3, INPUT_PULLUP);  // SW2
 pinMode(4, INPUT_PULLUP);  // SW3
 pinMode(5, INPUT_PULLUP);  // SW4
   
 // expression pedal
 pinMode(19, INPUT_PULLUP); // jack_check_exp, LOW when no jack
 pinMode(A6, INPUT); // read voltage on wiper pin

 // sustain pedal
 pinMode(17, INPUT_PULLUP); // jack_check_sus, LOW when no jack
 pinMode(18, INPUT_PULLUP); // LOW when pressed
}

void loop() {
  // switch reading
  sw1.update();
  sw2.update();
  sw3.update();
  sw4.update();

  // switch MIDI messages
  if (sw1.fallingEdge()) {
    usbMIDI.sendNoteOn(note1, 99, midi_out_channel);  
    MIDI.sendNoteOn(note1, 99, midi_out_channel);
  }
  if (sw1.risingEdge()) {
    usbMIDI.sendNoteOff(note1, 0, midi_out_channel);
    MIDI.sendNoteOff(note1, 0, midi_out_channel); 
  }
  if (sw2.fallingEdge()) {
    usbMIDI.sendNoteOn(note2, 99, midi_out_channel);  
    MIDI.sendNoteOn(note2, 99, midi_out_channel);
  }
  if (sw2.risingEdge()) {
    usbMIDI.sendNoteOff(note2, 0, midi_out_channel);
    MIDI.sendNoteOff(note2, 0, midi_out_channel); 
  }
  if (sw3.fallingEdge()) {
    usbMIDI.sendNoteOn(note3, 99, midi_out_channel);  
    MIDI.sendNoteOn(note3, 99, midi_out_channel);
  }
  if (sw3.risingEdge()) {
    usbMIDI.sendNoteOff(note3, 0, midi_out_channel);
    MIDI.sendNoteOff(note3, 0, midi_out_channel); 
  }
  if (sw4.fallingEdge()) {
    usbMIDI.sendNoteOn(note4, 99, midi_out_channel);  
    MIDI.sendNoteOn(note4, 99, midi_out_channel);
  }
  if (sw4.risingEdge()) {
    usbMIDI.sendNoteOff(note4, 0, midi_out_channel);
    MIDI.sendNoteOff(note4, 0, midi_out_channel); 
  }

  // SUSTAIN PEDAL: if pin 17 NOT LOW, check if pin 18 is LOW and if so send note.
  jack_check_sus.update();
  sus_pedal.update();
  jack_check_sustain = digitalRead(17);

  // first IF is for sending note_off when unplugging jack.
  if (jack_check_sus.fallingEdge()){
    usbMIDI.sendNoteOff(note_sus, 0, midi_out_channel);
    MIDI.sendNoteOff(note_sus, 0, midi_out_channel);     
  }
  // these IF statements might have to be reversed for a different pedal
  if (jack_check_sustain == HIGH) {
    if (sus_pedal.risingEdge()) {
      usbMIDI.sendNoteOn(note_sus, 99, midi_out_channel);  
      MIDI.sendNoteOn(note_sus, 99, midi_out_channel);
    }
    if (sus_pedal.fallingEdge()) {
      usbMIDI.sendNoteOff(note_sus, 0, midi_out_channel);
      MIDI.sendNoteOff(note_sus, 0, midi_out_channel); 
    }    
  }  
  
  // EXPRESSION PEDAL: if pin 19 NOT LOW, read pin 20 and map to midi CC
  jack_check_exp = digitalRead(19);
  if (jack_check_exp == HIGH) {
    expression = analogRead(A6);
    if (abs(expression - expression_last) > expression_threshold) {
      expression_last = expression;
      cc_mapped = map(expression, 0, 1023, 0, 128); // chose 128 upper bound because sometimes the max value will not be read
      if (cc_mapped == 128) {                       // correct for 0-127
        cc_mapped = 127;
      }
      usbMIDI.sendControlChange(midi_cc, cc_mapped, midi_out_channel);
      MIDI.sendControlChange(midi_cc, cc_mapped, midi_out_channel);
    }
  }
  while (usbMIDI.read()) {
  // ignore incoming messages
  }
}
