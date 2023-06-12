/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/Blink
*/
#define DI0 12
#define DI1 11
#define DI2 10
#define DI3 9
#define DI4 4

#define DQ0 8
#define DQ1 7

int pin=DQ0;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(DQ0, OUTPUT);
  pinMode(DQ1, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);  
  
  pinMode(DI0, OUTPUT);
  pinMode(DI1, OUTPUT);
  pinMode(DI2, OUTPUT);
  pinMode(DI3, OUTPUT);
  pinMode(DI4, OUTPUT);
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);  
  pinMode(6, OUTPUT);  
  pinMode(7, OUTPUT);  
  pinMode(8, OUTPUT);  

}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(DQ0, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(DQ1, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(0, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(1, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(2, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(3, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(5, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(6, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(7, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(8, HIGH);   // turn the LED on (HIGH is the voltage level)

  delay(1000);                       // wait for a second

  digitalWrite(DQ0, HIGH);    // turn the LED off by making the voltage LOW
  digitalWrite(DQ1, HIGH);    // turn the LED off by making the voltage LOW
  digitalWrite(LED_BUILTIN, LOW);   // turn the LED on (HIGH is the voltage level)

  delay(1000);                       // wait for a second
}
