# Small experiments with the Nordic Systems nRF24L01+ radio transceivers 

The files here are a test project that I built to help me get to grips with the RF24 library on Raspberry Pi and on the embedded Arduino ATTiny84 chip.

_multiColouredLedInterface.cpp_ is command line interface for the Raspberry Pi to set it up as a base node and then send a RGB colour code to the connected sensor node. 

_RGBLed.ino_ is an Arduino sketch that recieves the number, translates it into its respecting red, green and blue values then outputs these values (pwm) to the pins of an RGB led accordingly

### Example Usage

##### Set colour to white
```
$ ./multiColouredLedInterface -v 255255255
```
##### Set colour to green
``` 
$ ./multiColouredLedInterface -v 255000
```
This can also be called by other programs and I am aiming to write a webpage with a colour picker (in node.js) so that the colour of the LED will change as the user moves their mouse.

The addresses are currently fixed and assigned in the code but they could easily be passed as a command line argument to control multiple nodes individually. 


### Requirements
RF24 Library for Raspberry Pi and Arduino (incliding ATTiny) - https://github.com/TMRh20/RF24
