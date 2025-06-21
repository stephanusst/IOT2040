/*
  IOT2040-IO-PUSH-BUTTON with WebServer

  1. Change yellow lamp state,  ON or OFF based on a push.
  Input   : a green push button attached to DI0 or pin 12.
  Ouutput : a yellow pilot lamp attached to DQ0 or pin 7.

  2. Blink Built In LED

  3. Webserver
     Reading Analog Input
*/

#include <SPI.h>
#include <Ethernet.h>
#include <SD.h>
#include "main.hpp"
#include "webserver.hpp"
#include "bins.hpp"

using namespace std;

int pin;
Bins portio;

// the setup function runs once when you press reset or power the board
void setup() {
  //1. Initialize serial communication at 9600 bits per second:
  Serial.begin(9600);  
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
  
  //2. Initialize digital pin LED_BUILTIN as an output.
  pin= LED_BUILTIN; 
  pinMode(pin, OUTPUT);
  
  //3. Initialize IOT2000 Extension Module
  pinMode(DQ0, OUTPUT); 
  pinMode(portio.buttonGreen, INPUT);
 
  // Start the Ethernet connection and the server:
  Ethernet.begin(mac, ip);
  server.begin();
}  

void blink(){
  digitalWrite(pin, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(100);                       // wait for a second
  digitalWrite(pin, LOW);    // turn the LED off by making the voltage LOW
  delay(100);                       // wait for a second 
}

// the loop function runs over and over again forever
void loop() {
  //1. Push Button
  portio.Input();             //Baca digital input
  portio.Combinational();     //Proses output dari input
  portio.LowToHighState();    //Proses hanya saat Low To High
  portio.Output();

  //2. Blink LED_BUILTIN
  blink();
  
  //3. Webserver
  webserver();  
}
