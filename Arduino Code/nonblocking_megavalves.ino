#include <MEGA_VALVES.h>
//--pump control
//change these values to control how the pressure is controlled in the system.

// positive pressure control high/low values. Units are in KPa. Make sure High > Low

int p_low = 23;
int p_high = 25;
// Negative pressure control high/low values. Units are in KPa. Make sure High < Low, different than positive

int n_low = -55;
int n_high = -50;

//this is how hard the pumps work. 0= 0%, 255= 100% The pumps wont turn on if the value is too low.
int pumppower = 220;

//-----
char incomingByte;

float inputvalue;
float voltage;
float pressure;


void setup() {
  // put your setup code here, to run once:
  initializepins();
  Serial.begin(19200);

}

void loop() {
  int n_pres_sensor = analogRead(A14);
  int p_pres_sensor = analogRead(A13);
  int o_pres_sensor = analogRead(A15);
  pressurecontrol(p_low, p_high, n_low, n_high, n_pres_sensor, p_pres_sensor, o_pres_sensor, pumppower);
  unsigned long currentMillis = millis();
  if (Serial.available() > 0) {

  }
  incomingByte = Serial.read();

  switch (incomingByte) {
    case 'q':
      p_switch = true;
      pin = 0;
      setallinvalves(CLOSE);

      break;
    case 'w':
      p_switch = true;
      pin = 1;
      setallinvalves(CLOSE);
      break;
    case 'e':
      setallinvalves(CLOSE);
      setinvalve(2, OPEN);
      break;
    case '1':
      setinvalve(0, OPEN);
      break;
    case '2':
      setinvalve(1, OPEN);
      break;
    case '3':
      setinvalve(2, OPEN);
      break;
    case '4':
      setoutvalve(0, OPEN);
      break;
    case '5':
      setoutvalve(1, OPEN);
      break;
    case '6':
      setoutvalve(2, OPEN);
      break;
    case '7':
      setoutvalve(3, OPEN);
      break;
    case 'a':
      setallinvalves(CLOSE);
      setalloutvalves(CLOSE);
      break;

  }


  if (p_switch) {
    pressure_switch(pin, currentMillis, calltime);
  }

}
