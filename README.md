# toes
A device that sends USB and DIN MIDI messages using four footswitches, a sustain pedal and an expression pedal as the interface. This project is a very easy DIY build that consists of very few through-hole components, recommended for beginners!

## Foot switches 
They send a note on MIDI message when pressed, and a note off message when released.

## Sustain and expression pedals
The sustain pedal works the same as the foot switches. It is assumed that the sustain pedal will short the tip and sleeve of the jack while it is not pressed, and interrupt the connection when it is pressed. The code could be modified for the opposite situation.

The expression pedal sends a MIDI CC message. This design carries 5V on the tip, the wiper on the ring, and ground on the sleeve of the TRS jack.

## USB and DIN midi
The USB port on the teensy powers the unit and sends USB midi messages, and there is also a DIN MIDI out socket.
