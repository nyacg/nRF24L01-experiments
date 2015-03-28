#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <RF24/RF24.h>
#include <stdlib.h> 

using namespace std;

RF24 radio(RPI_V2_GPIO_P1_15, RPI_V2_GPIO_P1_24, BCM2835_SPI_SPEED_8MHZ);					// Setup for GPIO 22 CE and CE0 CSN with SPI Speed @ 8Mhz

const uint8_t pipes[][6] = {"1Node","2Node"};												// Radio pipe addresses for the 2 nodes to communicate.

void setup(){
	radio.begin();
	radio.setRetries(15,15);
	radio.printDetails();																	// Dump the configuration of the rf unit for debugging
	radio.openWritingPipe(pipes[0]);
	radio.openReadingPipe(1,pipes[1]);	
}


bool sendColour(char *colour){
	//This function send a message, the 'action', to the arduino and wait for answer
	//Returns true if ACK package is received

	radio.stopListening();
	unsigned long message = strtoul(colour, NULL, 10);
	printf("Now sending %lu...", message);
	
	bool ok = radio.write(&message, sizeof(unsigned long));									//Send the message
	
	if(ok){
		printf("ok...");
	}else{
		printf("failed.\n\r");
	}
	
	radio.startListening();																	//Listen for ACK
	unsigned long started_waiting_at = millis();
	bool timeout = false;
	while (!radio.available() && !timeout) {
		delay(10);
		if (millis() - started_waiting_at > 50){
			timeout = true;
		}
	}

	if(timeout){
		printf("Failed, response timed out.\n\r");
		return false;
	}else{
		// If we received the reply in time, let's read it and print it along with the time taken
		unsigned long got_time;
		radio.read(&got_time, sizeof(unsigned long));
		printf("Got response %lu, round-trip delay: %lu\n\r",got_time,millis()-got_time);
		return true;
	}
}


int main(int argc, char **argv){
	setup();	// run the radio setup 

	int c;
	char *colour = {0}; // initialise colour variable

	// get the RGB value from the 
	while((c = getopt(argc, argv, "v:")) != -1){
		colour = optarg;
	}

	cout << colour << "\n\r";	// print this to confirm read correctly

	sendColour(colour); 		// send RBG value to sensor node

	return 0;					// exit when complete
}