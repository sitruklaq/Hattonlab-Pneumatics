

#define MEGA_VALVES.h

#include "Arduino.h"
#define OPEN 1 
#define CLOSE 0
const int positivepumppin= 6;
const int negativepumppin= 5;
const int invalve[3] = { 53, 52, 51};
const int ovalve[4] = {49, 48, 47, 46};
float p_pressure;
float n_pressure;
float o_pressure;
float p_pressure_avg = 0;
float n_pressure_avg = 0;
float o_pressure_avg = 0;
int dly = 25;
bool p_switch;
int pin;
unsigned long calltime;




void initializepins(){
  for (int i = 0; i < 3; i++) {
    pinMode(invalve[i], OUTPUT);
    digitalWrite(invalve[i], LOW);
  }

  for (int i = 0; i < 4; i++) {
    pinMode(ovalve[i], OUTPUT);
    digitalWrite(ovalve[i], LOW);

  }

}
  void setallinvalves(int position) {
    if (position == OPEN) {
      for (int i = 0; i < 3; i++) {
        digitalWrite(invalve[i], HIGH);
      }
    }

    if (position == CLOSE) {
      for (int i = 0; i < 3; i++) {
        digitalWrite(invalve[i], LOW);
      }
    }
  
  }

  void setinvalve(int number, int position) {
    if (position == OPEN) {
      digitalWrite(invalve[number], HIGH);
    }

    if (position == CLOSE) {
      digitalWrite(invalve[number], LOW);
    }
  }
void setalloutvalves(int position) {
      if (position == OPEN) {
        for (int i = 0; i < 4; i++) {
          digitalWrite(ovalve[i], HIGH);
        }
      }

      if (position == CLOSE) {
        for (int i = 0; i < 4; i++) {
          digitalWrite(ovalve[i], LOW);
        }
      }
    }

void setoutvalve(int number, int position) {
      if (position == OPEN) {
        digitalWrite(ovalve[number], HIGH);
      }

      if (position == CLOSE) {
        digitalWrite(ovalve[number], LOW);
      }

}
      
void pressurecontrol(int p_low, int p_high, int n_low, int n_high, int n_input, int p_input, int o_input, int power) {
    
    //sensor math to convert input voltage to pressure in KPa
    
    
    float  o_voltage= map(o_input, 0, 1023, 0, 5000);
    
    o_pressure= 50*(o_voltage/1000)-130.1;
    
    
    for (int i=0; i < 4; i++) {
        o_pressure_avg = o_pressure_avg + o_pressure;
    }
    o_pressure_avg = o_pressure_avg/5;
    
   
    
    
   float  n_voltage= map(n_input, 0, 1023, 0, 5000);
    
   n_pressure= 50*(n_voltage/1000)-130.6;
    
   
    for (int i=0; i < 9; i++) {
        n_pressure_avg = n_pressure_avg + n_pressure;
    }
    n_pressure_avg = n_pressure_avg/10;
    
    
   float  p_voltage= map(p_input, 0, 1023, 0, 5000);
    
   p_pressure= 50*(p_voltage/1000)-130.6;
    
    for (int i=0; i < 9; i++) {
        p_pressure_avg = p_pressure_avg + p_pressure;
    }
    p_pressure_avg = p_pressure_avg/10;
    
    //pressure regulation
    if(p_pressure_avg<p_low){
        analogWrite(positivepumppin,power);

    }
    
    if (abs(p_pressure_avg)>p_high){
        
        analogWrite(positivepumppin,0);
    }
    
    if(n_pressure_avg>n_high){
        analogWrite(negativepumppin,power);
       
    }
    if (n_pressure_avg<n_low){
       
        analogWrite(negativepumppin,0);
    }
    

}
//this is legacy code. These will switch the input valves to the desired position. The neutral valve is opened and closed in each case to first evacuate the buffer zone. This saves tank pressure when switching between positive and negative pressures. Using delays blocks the pump control from occuring so dont use this. Instead, use the pressure_switch function.

void negative_pressure (){
    setallinvalves (CLOSE);
    setinvalve(2, OPEN);
    delay(50);
    setinvalve(2, CLOSE);
    setinvalve(1,OPEN);
    delay(50);
}
void positive_pressure(){
setallinvalves (CLOSE);
setinvalve(2, OPEN);
delay(25);
setinvalve(2, CLOSE);
setinvalve(0,OPEN);
delay(25);
}

void neutral_pressure(){
setallinvalves (CLOSE);
delay(25);
setinvalve(2, OPEN);
delay(25);
}


void pressure_switch(int pin, int current, int when){
    setinvalve(2,OPEN);
    if ((unsigned long)(current - when) >= dly) {
        p_switch = false;
        setinvalve(2,CLOSE);
        setinvalve(pin,OPEN);
         }
}
