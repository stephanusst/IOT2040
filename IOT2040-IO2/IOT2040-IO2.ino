/*
  Blink
  Turns two LED on for one second, then off for one second, repeatedly.
  Testing Arduino shield PIN
  Size    83.771 bytes (0%) dari 
      10.000.000 bytes.
  
  Modified 19 Junn 2025 by Stephanus 
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
  
  pinMode(DI0, INPUT);
  pinMode(DI1, INPUT);
  pinMode(DI2, INPUT);
  pinMode(DI3, INPUT);
  pinMode(DI4, INPUT);
  
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
 
  pinMode(5, OUTPUT);  
  pinMode(6, OUTPUT);  
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

  delay(1000);                       // wait for a second

  digitalWrite(DQ0, LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(DQ1, LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(LED_BUILTIN, LOW);   // turn the LED on (HIGH is the voltage level)

  delay(1000);                       // wait for a second
}
