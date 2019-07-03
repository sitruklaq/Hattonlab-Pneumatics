#define Big_system.h

#include "Arduino.h"
#define OPEN 1 
#define CLOSE 0

//define output pins
const int invalve[3] = { 53, 52, 51};
//const int ovalve[8] = {28, 47, 29, 46,30,45,31,44};
const int ovalve[8] = {47, 46, 45, 44,31,30,29,28};
const int pump[2]= {6,5};
const int positivepumppin= 6;
const int negativepumppin= 5;

int pumpstatus[2]={0,0};
int invalvestatus[3];
int ovalvestatus[8];
int nsetpoint = 0;
int psetpoint= 0;
float p_pressure;
float n_pressure;
float o_pressure;
float p_pressure_avg = 0;
float n_pressure_avg = 0;
float o_pressure_avg = 0;
int dly = 25;
bool p_switch;
int pin;
int incomingByte;
unsigned long calltime;

const int numReadings = 30;

int readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int total = 0;                  // the running total
int average = 0;
bool wait;

const byte numChars = 32;
char receivedChars[numChars];
char tempChars[numChars];
char messageFromPC[numChars] = {0};
int integerFromPC = 0;
float floatFromPC = 0.0;
boolean newData = false;


char invalve_read[]="VI";
char ovalve_read[]="VO";
char psp[]="PSP";
char nsp[]="NSP";
char pvp[]="PVP";
char pvn[]="PVN";
char pvo[]="PVO";
char aov[]="AOV";
char aiv[]="AIV";

//----ARDUINO INITIALIZATION
void initializepins(){
  for (int i = 0; i < 3; i++) {
    pinMode(invalve[i], OUTPUT);
    digitalWrite(invalve[i], LOW);
  }

  for (int i = 0; i < 8; i++) {
    pinMode(ovalve[i], OUTPUT);
    digitalWrite(ovalve[i], LOW);

  }

}
//---------------

//---THIS FUNCTION TURNS ON/OFF ALL INPUT VALVES
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

//---------------------


//---THIS FUNCTION TURNS ON/OFF A SPECIFIC INPUT VALVE
  void setinvalve(int number, int position) {
    if (position == OPEN) {
      digitalWrite(invalve[number], HIGH);
        
    }

    if (position == CLOSE) {
      digitalWrite(invalve[number], LOW);
    }
  }
//---------------


//---THIS FUNCTION TURNS ON/OFF ALL OUTPUT VALVES
void setalloutvalves(int position) {
      if (position == OPEN) {
        for (int i = 0; i < 8; i++) {
          digitalWrite(ovalve[i], HIGH);
        }
      }

      if (position == CLOSE) {
        for (int i = 0; i < 8; i++) {
          digitalWrite(ovalve[i], LOW);
        }
      }
    }

//----------------------------

//---THIS FUNCTION TURNS ON/OFF A SPECIFIC OUTPUT VALVE
void setoutvalve(int number, int position) {
      if (position == OPEN) {
        digitalWrite(ovalve[number], HIGH);
      }
      if (position == CLOSE) {
        digitalWrite(ovalve[number], LOW);
      }
}
//-------


void pressurecontrol(int n_input, int p_input, int o_input, int power) {
    
    //sensor math to convert input voltage to pressure in KPa
    
    
    float  o_voltage= map(o_input, 0, 1023, 0, 5000);
    float  n_voltage= map(n_input, 0, 1023, 0, 5000);
    float  p_voltage= map(p_input, 0, 1023, 0, 5000);
    o_pressure= 50*(o_voltage/1000)-123.65;
    n_pressure= 50*(n_voltage/1000)-125.1;
    p_pressure= 50*(p_voltage/1000)-124.85;
    
    for (int i=0; i < 99; i++) {
        p_pressure_avg = p_pressure_avg + p_pressure;
        n_pressure_avg = n_pressure_avg + n_pressure;
       o_pressure_avg = o_pressure_avg + o_pressure;
    }
    
    p_pressure_avg = p_pressure_avg/100;
    n_pressure_avg = n_pressure_avg/100;
    o_pressure_avg = o_pressure_avg/100;

  
 // Serial.print("Positive Pressure is: ");
  // Serial.print(p_pressure_avg);
 // Serial.print(", Negative Pressure is: ");
 // Serial.println(n_pressure_avg);
 // Serial.println(",");
// Serial.print("Output Pressure is: ");
//Serial.println(o_pressure_avg);

    
    //pressure regulation
    if(p_pressure_avg<(psetpoint-.3)){
        analogWrite(positivepumppin,power);

    }
    
    if (abs(p_pressure_avg)>psetpoint){
        
        analogWrite(positivepumppin,0);
    }
    
    if(n_pressure_avg>(nsetpoint+.3)){
        analogWrite(negativepumppin,power);
       
    }
    if (n_pressure_avg<nsetpoint){
       
        analogWrite(negativepumppin,0);
    }
    

}
//-----------------------

//---THIS FUNCTION SWITCHES PRESSURE USING A QUICK NEUTRAL PRESSURE EVACUATION FIRST
void pressure_switch(int pin, int current, int when){
    setinvalve(2,OPEN);
    if ((unsigned long)(current - when) >= dly) {
        p_switch = false;
        setinvalve(2,CLOSE);
        setinvalve(pin,OPEN);
         }
}

//---THIS SECTION PULLS OUT VALUES FROM A SERIAL INPUT SO IT CAN BE READ AND EXECUTED ON
void parseData() {      // split the data into its parts
    
    char * strtokIndx; // this is used by strtok() as an index
    
    strtokIndx = strtok(tempChars,",");      // get the first part - the string
    strcpy(messageFromPC, strtokIndx); // copy it to messageFromPC
    
       strtokIndx = strtok(NULL, ","); // this continues where the previous call left off
       integerFromPC = atoi(strtokIndx);     // convert this part to an integer
    
    strtokIndx = strtok(NULL, ",");
    floatFromPC = atof(strtokIndx);     // convert this part to a float
    
}


void recvWithStartEndMarkers() {
    static boolean recvInProgress = false;
    static byte ndx = 0;
    char startMarker = '<';
    char endMarker = '>';
    char rc;
    
    while (Serial.available() > 0 && newData == false) {
        rc = Serial.read();
        
        if (recvInProgress == true) {
            if (rc != endMarker) {
                receivedChars[ndx] = rc;
                ndx++;
                if (ndx >= numChars) {
                    ndx = numChars - 1;
                }
            }
            else {
                receivedChars[ndx] = '\0'; // terminate the string
                recvInProgress = false;
                ndx = 0;
                newData = true;
            }
        }
        
        else if (rc == startMarker) {
            recvInProgress = true;
        }
    }
}
//============
void act_on_input(){
    if (strcmp(messageFromPC,invalve_read)==0){
        setinvalve(integerFromPC, floatFromPC);
    }
    if (strcmp(messageFromPC,ovalve_read)==0){
        setoutvalve(integerFromPC, floatFromPC);
    }
    if (strcmp(messageFromPC,nsp)==0){
        nsetpoint=integerFromPC;
    }
    if (strcmp(messageFromPC,psp)==0){
        psetpoint=integerFromPC;
    }
    if (strcmp(messageFromPC,pvp)==0){
      Serial.println(p_pressure_avg);
    }
    if (strcmp(messageFromPC,pvn)==0){
      Serial.println(n_pressure_avg);
    }
    
    if (strcmp(messageFromPC,pvo)==0){
      Serial.println(o_pressure_avg);
    }
    if (strcmp(messageFromPC,aov)==0){
        setalloutvalves(integerFromPC);
    }
    if (strcmp(messageFromPC,aiv)==0){
        setallinvalves(integerFromPC);
    }
}
