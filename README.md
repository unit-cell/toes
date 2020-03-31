# toes
A device that sends USB and DIN MIDI messages using four footswitches, a sustain pedal and an expression pedal as the interface. This project is a very easy DIY build that consists of very few through-hole components, recommended for beginners!


![alt text](https://github.com/unit-cell/toes/blob/master/Images/front.jpg "front")


![alt text](https://github.com/unit-cell/toes/blob/master/Images/pcb.jpg "pcb")

![alt text](https://github.com/unit-cell/toes/blob/master/Images/pedals.jpg "pedals")

## Software
Requirements: Bounce2 library, MIDI library (found in Arduino IDE library manager).

To set custom MIDI messages, change settings in config.h file and then compile.

## Foot switches 
They send a note on MIDI message when pressed, and a note off message when released.

## Sustain and expression pedals
The sustain pedal works the same as the foot switches. It is assumed that the sustain pedal will short the tip and sleeve of the jack while it is not pressed, and interrupt the connection when it is pressed. The code could be modified for the opposite situation.

The expression pedal sends a MIDI CC message. This design carries 5V on the tip, the wiper on the ring, and ground on the sleeve of the TRS jack.

## USB and DIN midi
The USB port on the teensy powers the unit and sends USB midi messages, and there is also a DIN MIDI out socket.

## Build guide
First solder R1, R2, the teensy pin sockets, MIDI DIN socket, and the stereo jack sockets for the pedals. All of them go on the top of the board, as shown in the picture below. **Do not solder the foot switches yet**.

![alt text](https://github.com/unit-cell/toes/blob/master/Images/board.png "toes board")

Then screw the foot switches to the top panel. Solder short cables or resistor legs to the foot switch legs that will be connected to the PCB. These are the legs that *become connected when the foot switch is pressed*. Mount the PCB to the top panel with the 22 mm spacers (I used a 20 mm spacer + a nut), and solder the wire/legs to the pads highlighted by the white mark on the silkscreen.

![alt text](https://github.com/unit-cell/toes/blob/master/Images/top_assemply.png "top assembly")

You can trim the long legs on the bottom of the board if you are using nuts as spacers for the bottom panel. Assemble these and you are done!

Note about foot switches: it is possible to use any momentary foot switch with enough clearance to fit between the top panel and the board. Just make sure to wire it to the holes marked with a white rectangle, so that these become connected when pressing the switch.


