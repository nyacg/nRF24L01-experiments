# Small experiments with the Nordic Semiconductor nRF24L01+ radio transceivers 

The files here are a test project that I built to help me get to grips with the RF24 library on Raspberry Pi and on the embedded Arduino ATTiny84 chip.

_multiColouredLedInterface.cpp_ is command line interface for the Raspberry Pi to set it up as a base node and then send a RGB colour code to the connected sensor node. 

_RGBLed.ino_ is an Arduino sketch that recieves the number, translates it into its respecting red, green and blue values then outputs these values (pwm) to the pins of an RGB led accordingly

_webaccess.js_ is a node.js script that provides api-like ability to set the led colour 

_lightapp_ is a folder containing an node/express/socketio project that provies a web-inteface colour picker to set the colour

### Example Usage

##### Set colour to white
```
$ ./multiColouredLedInterface -v 255255255
```
##### Set colour to green
``` 
$ ./multiColouredLedInterface -v 255000
```
This can also be called by other programs ~~and I am aiming to write a webpage with a colour picker (in node.js) so that the colour of the LED will change as the user moves their mouse.~~

I have now written both an api-like webpage to set the colour and a webapp to change the colour using a colour picker. _webaccess.js_ should be placed in the same directory as _multiColouredLedInterface_

#### Launch the api like so...
```
$ sudo node webaccess.js 3000
```
Where 3000 is the port number that you wish to start the server on

#### Set the colour to green
```
http://ip-address:portno/api/setcol?v=255000
```
This will return a JSON object in the form `{ 'color': colorcode }` and set the led colour to the code specified 

#### To launch the lightapp webapp 
```
sudo npm start
```
This requires all the depenancies to have been downloaded first and will currently launch using nodemon as this tracks file changes and restarts the server when one occours as this is useful for development. Once launched going to http://ip-address:3000 will start a web inteface with a colour picker that will set the colour as the user moves the dot or slider. 
![Image of Colourpicker Interface](https://lh5.googleusercontent.com/nyAYx2R0I9-Czs5ehg4DxoFDCO3Iu4OU9xNPBgxjz1AxhZaS47fBDH28CuzdhIRm16hnDyit5_9QB-I=w1896-h859)


The addresses are currently fixed and assigned in the code but they could easily be passed as a command line argument to control multiple nodes individually. 

### Requirements
RF24 Library for Raspberry Pi and Arduino (incliding ATTiny) - https://github.com/TMRh20/RF24
