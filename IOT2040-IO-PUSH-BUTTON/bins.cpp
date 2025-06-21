/*
 * Class BINS
 * Menerima input Pushbutton  
 *  
 * Input: DI0
 * Output: DQ0
 */
#include "bins.hpp"

/*
 * Constructor
 */
Bins::Bins(){
  buttonGreen= DI0;
  lampYellow= DQ0;
  CurrentState=LOW;
  previousState=LOW;
  set=LOW;
  previousSet=LOW;  
};

/* 
 * INPUT
 * Read the state of the pushbutton value
 */
void Bins::Input(){
  buttonState = digitalRead(buttonGreen); 
};

void Bins::Combinational(){
  CurrentState= (buttonState); 
};

/* 
 * LOWTOHIGHSTATE
 * Function: pushbutton 
 * Considering the state Low to High only. 
 * Input: changedState, previousChangedState 
 * Output: set
 */
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

/*
 * SWITCH
 * Change State High to Low or Low to High
 * Don't use this if you use PushButton mode
 */
void Bins::Switch(){
  CurrentState=buttonState;
  delay(1);
  if (CurrentState == HIGH)
    set= LOW;
  else
    set= HIGH;
}

/*
 * OUTPUT
 * Input:outputPin, set, previousSet
 * Considering only when the set changed.
 */
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
