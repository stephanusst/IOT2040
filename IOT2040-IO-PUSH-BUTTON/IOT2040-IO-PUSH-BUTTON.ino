/*
  IOT2040-IO-PUSH-BUTTON

  Turns an LED on for one hundred milli second, then off for one hundred milli second, repeatedly.

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

#include <SPI.h>
#include <Ethernet.h>

//Siemens IOT2000 Input Output Module
#define DI0 12
#define DI1 11
#define DI2 10
#define DI3 9
#define DI4 4

#define DQ0 8
#define DQ1 7


///////////BINS/////////////////////////////////////////////////////////
class Bins {
  public: 
    byte buttonPin;     //pin number
    byte buttonState;
  public: 
    Bins();
    void Input();
    void Combinational();
    void LowToHighState();
    void Output();
    void Switch();
  public:
    int previousState;
    int CurrentState;
    int set;
    int previousSet;          // The previous output condition    
};

Bins::Bins(){
  buttonPin= DI0;
  CurrentState=LOW;
  previousState=LOW;
  set=LOW;
  previousSet=LOW;  
};

void Bins::Input(){
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin); 
};

void Bins::Combinational(){
  CurrentState= (buttonState); 
};

// Function: pushbutton
// Considering the state Low to High only.
// Input: 
// - changedState
// - previousChangedState
// Output:
// - set
void Bins::LowToHighState(){
  if ((CurrentState == HIGH) & ( previousState== LOW) )
  {
    if (set==HIGH)  {    
      set= LOW;
    } else if (set==LOW)
      set= HIGH;
  };
  previousState=CurrentState;
};

//The Switch is on PushButton, don't use this if you use PushButton mode
void Bins::Switch(){
  CurrentState=buttonState;
  delay(1);
  if (CurrentState == HIGH)
  //{
      set= LOW;
   else
      set= HIGH;
}

// output()
// Input:
// - outputPin
// - set
// - previousSet
// Considering only when the set changed
void Bins::Output(){
  //If Set is changed, then executes a function.
  if ((set==HIGH) & (previousSet==LOW)) { 
    digitalWrite(DQ0, HIGH); 
//    report();
  } else if ((set==LOW) & (previousSet==HIGH)){
    digitalWrite(DQ0, LOW); 
//    report();
  }  
  previousSet=set;
}
///////// BINS /////////////////////////////////////




///////// MAIN PROGRAM /////////////////////////////////////////////
//
////// GLOBAL VARIABLES ///////////////
// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:

byte mac[] = { 
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192,168,1,249);

// Initialize the Ethernet server library
// with the IP address and port you want to use 
// (port 80 is default for HTTP):
EthernetServer server(80);

//IOT2000 Extension Module
Bins portio;
int pin;
/////////////////////////////////////////////////////////

/////////// WEBSERVER /////////////////////////////
void webserver() {
  // listen for incoming clients
  EthernetClient client = server.available();
  if (client) {
    Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html;charset=UTF-8");
          client.println("Connection: close");
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html lang=""en-US"">");          
          client.println("<head>");
          client.println("     <meta charset=""UTF-8"">");
          client.println("     <title> IOT2040 Analog Input</title>");
          client.println("</head>");
          client.println("<html>");
          
          // add a meta refresh tag, so the browser pulls again every 5 seconds:
          client.println("<meta http-equiv=\"refresh\" content=\"5\">");
          
          // output the value of each analog input pin //0
          for (int analogChannel = 0; analogChannel < 1; analogChannel++) {           
            int sensorReading = analogRead(analogChannel);
            client.print("Analog input ");
            client.print(analogChannel);
            client.print(" is ");
            client.print(sensorReading);
            client.println("<br />");  

            client.print("Digital Output");
            client.print(portio.set);
            client.println("<br />");  
          }
          client.println("</html>");
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } 
        else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);
    
    // close the connection:
    client.stop();
    //Serial.println("client disonnected");
  }
}
/////////// WEBSERVER /////////////////////////////

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pin=LED_BUILTIN;
  //Initialize IOT2000 Extension Module
  pinMode(pin, OUTPUT);
  pinMode(portio.buttonPin, INPUT);
  pinMode(DQ0, OUTPUT); 

  // Start the Ethernet connection and the server:
  Ethernet.begin(mac, ip);
  server.begin();
  //Serial.print("server is at ");
  //Serial.println(Ethernet.localIP());
}  

// the loop function runs over and over again forever
void loop() {
  portio.Input();
  portio.Combinational();
  portio.LowToHighState();
//  portio.Switch();
  portio.Output();
  webserver();
  
  digitalWrite(pin, HIGH);   // turn the LED on (HIGH is the voltage level)
  //digitalWrite(DQ0, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(100);                       // wait for a second

  digitalWrite(pin, LOW);    // turn the LED off by making the voltage LOW
  //digitalWrite(DQ0, LOW);    // turn the LED off by making the voltage LOW

  delay(100);                       // wait for a second
}
/////////////// MAIN PROGRAM //////////////////////////////////////
