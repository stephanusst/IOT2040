/*
  IOT2040-IO-PUSH-BUTTON with WebServer

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. 
  
  LED_BUILTIN is set to  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at: 
  https://www.arduino.cc/en/Main/Products

  The program is originated from Blink demo. However, we have added a class 
  to read a push button or a switch. The input can be a combinational logic
  as well.

  Current application uses 
  - a green push button attached to DI0 or pin 12.
  - a yellow pilot lamp attached to DQ0 or pin 7.

  The main class is Bins.
class
Bins::Bins()
  void Bins::Input()
  void Bins::Combinational()
  void Bins::LowToHighState()
  void Bins::Switch()
  void Bins::Output()
  Functions
  void webserver()
*/

#include <SPI.h>
#include <Ethernet.h>
#include <SD.h>

//Siemens IOT2000 Input Output Expansion Module
#define DI0 12
#define DI1 11
#define DI2 10
#define DI3 9
#define DI4 4

#define DQ0 8
#define DQ1 7

//////////////////// CLASS BINS/////////////////////////////////////////////////////////
class Bins {
  public: 
    byte buttonGreen;   //pin number
    byte lampYellow;    //pin number
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
////////////////////CLASS BINS/////////////////////////////////////////////////////////

///////////////////BINS::BINS/////////////////////////////////////////////////////////
Bins::Bins(){
  buttonGreen= DI0;
  lampYellow= DQ0;
  CurrentState=LOW;
  previousState=LOW;
  set=LOW;
  previousSet=LOW;  
};
///////////////////BINS::BINS/////////////////////////////////////////////////////////

///////////////////BINS::INPUT/////////////////////////////////////////////////////////
void Bins::Input(){
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonGreen); 
};
///////////////////BINS::INPUT/////////////////////////////////////////////////////////

///////////////////BINS::COMBINATIONAL////////////////////////////////////////////////
void Bins::Combinational(){
  CurrentState= (buttonState); 
};
///////////////////BINS::COMBINATIONAL////////////////////////////////////////////////

///////////////////BINS::LOWTOHIGHSTATE///////////////////////////////////////////////
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
///////////////////BINS::LOWTOHIGHSTATE/////////////////////////////////////////////////

///////////////////BINS::SWITCH/////////////////////////////////////////////////////////
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
///////////////////BINS::SWITCH /////////////////////////////////////////////////////////


///////////////////BINS::OUTPUT /////////////////////////////////////////////////////////
// output()
// Input:
// - outputPin
// - set
// - previousSet
// Considering only when the set changed
/////////////////////////////////////////////////////////////////////////////////////////
void Bins::Output(){
  //If Set is changed, then executes a function.
  if ((set==HIGH) & (previousSet==LOW)) { 
    digitalWrite(lampYellow, HIGH); 
//    report();
  } else if ((set==LOW) & (previousSet==HIGH)){
    digitalWrite(lampYellow, LOW); 
//    report();
  }  
  previousSet=set;
}
///////////////////BINS::OUTPUT ////////////////////////////////////////////////////////


///////// MAIN PROGRAM /////////////////////////////////////////////
//
////// GLOBAL VARIABLES ////////////////////////////////////////////
// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:

//X2P1LAN
//byte mac[] = { 0x8C, 0xF3, 0x19, 0x4E, 0x32, 0x2A };
//IPAddress ip(192,168,1,100);

//X1P1LAN
byte mac[] = { 0x8C, 0xF3, 0x19, 0x4E, 0x32, 0x29 };
IPAddress ip(192,168,1,100);

// Initialize the Ethernet server library
// with the IP address and port you want to use 
// (port 80 is default for HTTP):
EthernetServer server(80);
//IOT2000 Extension Module
Bins portio;
int pin;
//////////////////////////////////////////////////////////////////

/////////// WEBSERVER ////////////////////////////////////////////
void webserver() {
  float y,z;
  // listen for incoming clients
  EthernetClient client = server.available();
  if (client) {
    Serial.println("New client");
    
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
          client.println("<meta http-equiv=\"refresh\" content=\"1\">");

          char description[4][2]; 
          description[0][0]=' '; description[0][1]='V';
          description[1][0]='m'; description[1][1]='A';
          description[2][0]=' '; description[2][1]='V';
          description[3][0]='m'; description[3][1]='A';
           
          //Read and Display the four Analog Channel
          //Voltage 0
            int analogChannel=0;
            int sensorReading = analogRead(analogChannel);
            client.print("U0 ");
            client.print(analogChannel);
            client.print(" is ");
            client.print(sensorReading);
            client.println(" ");
            y=(float) sensorReading;
            client.print(y);
            client.print(description[analogChannel][0]);
            client.print(description[analogChannel][1]);
            client.println(" ");
            z=y/100;
            client.print(z);
            client.print("volt");
            client.println("<br />");  
            
          //Current 0
            analogChannel=1;
            sensorReading = analogRead(analogChannel);
            client.print("I0 ");
            client.print(analogChannel);
            client.print(" is ");
            client.print(sensorReading);
            client.println(" ");
            y=(float) sensorReading;
            //client.print(y);
            //client.print(description[analogChannel][0]);
            //client.print(description[analogChannel][1]);
            //client.println(" ");
            z=y/50;
            client.print(z);
            client.print("kg/cm2");
            client.println("<br />");  

          //Voltage 1
            analogChannel=2;
            sensorReading = analogRead(analogChannel);
            client.print("U1 ");
            client.print(analogChannel);
            client.print(" is ");
            client.print(sensorReading);
            client.println(" ");
            y=(float) sensorReading;
            client.print(y);
            client.print(description[analogChannel][0]);
            client.print(description[analogChannel][1]);
            client.println(" ");
            z=y/100;
            client.print(z);
            client.print("volt");
            client.println("<br />"); 
                        
            analogChannel=3;
            sensorReading = analogRead(analogChannel);
            client.print("I1 ");
            client.print(analogChannel);
            client.print(" is ");
            client.print(sensorReading);
            client.println(" ");
            y=(float) sensorReading;
            client.print(y);
            client.print(description[analogChannel][0]);
            client.print(description[analogChannel][1]);
            client.println(" ");
            z=y/50;
            client.print(z);
            client.print("kg/cm2");
            client.println("<br />");  
          //}
/*
        for (int analogChannel = 1; analogChannel < 4; analogChannel+1) {           
            int sensorReading = analogRead(analogChannel);
            client.print("Analog input ");
            client.print(analogChannel);
            client.print(" is ");
            client.print(sensorReading*16/20+240);
            client.print(description[analogChannel][0]);
            client.print(description[analogChannel][1]);
            client.println("<br />");  
          }
   */ 
          client.print("DQ0 (YELLOW LAMP): ");
          if (portio.set==HIGH)
            client.print("HIGH");
          else
            client.print("LOW");            
          client.println("<br />");  
                   
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
   // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);  
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
  
  // initialize digital pin LED_BUILTIN as an output.
  pin=LED_BUILTIN;
  //Initialize IOT2000 Extension Module
  pinMode(pin, OUTPUT);
  pinMode(DQ0, OUTPUT); 
  pinMode(portio.buttonGreen, INPUT);
 
  // Start the Ethernet connection and the server:
  Ethernet.begin(mac, ip);
  server.begin();
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
