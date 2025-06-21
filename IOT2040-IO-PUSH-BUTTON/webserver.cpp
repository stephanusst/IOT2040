#include <Ethernet.h>
#include "webserver.hpp"
#include "bins.hpp"

//X2P1LAN
//byte mac[] = { 0x8C, 0xF3, 0x19, 0x4E, 0x32, 0x2A };
//IPAddress ip(192,168,1,100);

byte mac[] = { 0x8C, 0xF3, 0x19, 0x4E, 0x32, 0x29 };
IPAddress ip(192,168,1,100);

// Initialize the Ethernet server library
// with the IP address and port you want to use 
// (port 80 is default for HTTP):
EthernetServer server(80);
extern Bins portio;

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
