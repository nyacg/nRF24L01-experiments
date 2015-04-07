/*
ATtiny24/44/84 Pin map with CE_PIN 8 and CSN_PIN 7
	Schematic provided and successfully tested by Carmine Pastore (https://github.com/Carminepz)
                                  +-\/-+
    nRF24L01  VCC, pin2 --- VCC  1|o   |14 GND --- nRF24L01  GND, pin1
                            PB0  2|    |13 AREF
                            PB1  3|    |12 PA1
                            PB3  4|    |11 PA2 --- nRF24L01   CE, pin3
                            PB2  5|    |10 PA3 --- nRF24L01  CSN, pin4
                            PA7  6|    |9  PA4 --- nRF24L01  SCK, pin5
    nRF24L01 MOSI, pin7 --- PA6  7|    |8  PA5 --- nRF24L01 MISO, pin6
                                  +----+
*/

// CE and CSN are configurable, specified values for ATtiny85 as connected above
#define CE_PIN 9
#define CSN_PIN 8

#include "RF24.h"

// define pin connections 
int redPin = 0;
int greenPin = 1;
int bluePin = 2;

RF24 radio(CE_PIN, CSN_PIN);

byte addresses[][6] = {"1Node","2Node"};
unsigned long payload = 0;

void setup() {
	pinMode(redPin, OUTPUT);
	pinMode(greenPin, OUTPUT);
	pinMode(bluePin, OUTPUT);
	
	analogWrite(redPin, 255);
	analogWrite(greenPin, 255);
	analogWrite(bluePin, 0);
	
	// Setup and configure rf radio
	radio.begin(); // Start up the radio
	radio.setAutoAck(0); // Ensure autoACK is not enabled
	radio.setRetries(5,15); // Max delay between retries & number of retries
	radio.openReadingPipe(1,addresses[0]); // Read on pipe 1 for device address '1Node'
	radio.startListening(); // Start listening
}

void loop(void){
	
	 // if there is data ready
	if (radio.available()){
		unsigned long message;	 // variable to recieve message
		 
		while (radio.available()){
			// get available data
			radio.read( &message, sizeof(unsigned long) ); 

			// Delay just a little bit to let the other unit make the transition to receiver
			delay(20);
		}			

		// convert the revieved data into its red green and blue componets
		long int num = (long int) message;	// cast the recieved data as a long int
		int col = 2;	// start with the last column (the blue component)
		int placeValue = 1;
		int values[3] = {0, 0, 0};	// array to hold the RGB values
			
		while(num > 0) {
			long int digit = num % 10;	// get last digit in number
			num = num / 10;	 // divide the number by 10, ignoring the decimal
				
			// add the (last digit * its weighting) to the values array for the current colour
			values[col] = values[col] + placeValue * digit;	
			placeValue = placeValue * 10;	 // increase the weighting 10 fold
				
			// if we have done the hundreds, tens and units for the current colour
			// change to the next colour and reset the weighting to unit 
			if(placeValue > 100) {
				placeValue = 1;
				col = col - 1;
			}
		}
			
		// write the RGB values to their respective pins
		analogWrite(redPin, values[0]);
		analogWrite(greenPin, values[1]);
		analogWrite(bluePin, values[2]);		
	}
}
