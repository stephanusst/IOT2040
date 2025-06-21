#ifndef WEBSERVER
#define WEBSERVER

//X1P1LAN
//extern byte mac[] = { 0x8C, 0xF3, 0x19, 0x4E, 0x32, 0x29 };
extern byte mac[];

//extern IPAddress ip(192,168,1,100);
extern IPAddress ip;

// Initialize the Ethernet server library
// with the IP address and port you want to use 
// (port 80 is default for HTTP):
extern EthernetServer server;

//IOT2000 Extension Module
//extern Bins portio;
//extern int pin;

void webserver();
#endif
////////////////////CLASS BINS/////////////////////////////////////////////////////////
