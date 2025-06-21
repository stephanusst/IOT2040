#include <SPI.h>
#ifndef BINS
#define BINS
using namespace std;

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

//IOT2000 Extension Module
extern Bins portio;
#endif 
