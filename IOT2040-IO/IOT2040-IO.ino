/*
  Blink 
  Turns two LED on for one second, then off for one second, repeatedly.
  Using IOT2040 Shield
  
  Modified 19 Jun 2014  by Stephanus
*/

//Digital Input 
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
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(DQ0, HIGH);            // turn the LED on (HIGH is the voltage level)
  digitalWrite(DQ1, HIGH);            // turn the LED on (HIGH is the voltage level)
  digitalWrite(LED_BUILTIN, HIGH);    // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second

  digitalWrite(DQ0, LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(DQ1, LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(LED_BUILTIN, LOW);   // turn the LED on (HIGH is the voltage level)

  delay(1000);                       // wait for a second
}
