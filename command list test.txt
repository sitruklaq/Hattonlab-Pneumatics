# Command List
## How to send a command through serial

The Arduino is listening for commands in the following structure		‘< command, optional modifier, optional modifier >’

## Command List
Command Syntax  | Description | Example
  ------------- | ------------- | -------------
  VO  | Commands a Specific Output Valve  | 1
  VI  | Content Cell | 2
  AIV | Commands all input valves | <AIV,1>
  AOV | Commands all output valves to be on (1) or off (0) | <AOV, 0> turns off all output valves
  PSP | Changes setpoint of positive pressure reservoir | <PSP, 15>
  NSP | Changes setpoint of negative pressure reservoir | <NSP, -15>
  PVO | |

### Controlling Individual Valves

**VO**	Valve Output	Opens or closes output valves

The first numeric input defines which out valve you are addressing. There are currently 8 valves which can be addressed by 0-7.

The second numeric input defines state. 1= ON, 0=OFF.

<VO, 1 , 1> turns on the second output valve.

**VI**	Valve Input		Opens of closes an input valve

This works exactly like VO except there are only 3 input valves (0,1,2).

0-Negative pressure
1-Exhaust
2-Positive pressure

<VI, 0, 0> Turns off the negative input valve

### Controlling All Valves

**AOV**	

All out Valves

Opens of closes ALL output valves

This command takes one modifier 1=ALL ON,  0=ALL OFF

<AOV, 1> Opens all output valves


**AIV**	All Input Valves	Opens of closes ALL input valves
This command takes one modifier 1=ALL ON,  0=ALL OFF

<AOV, 0> closes all output valves
# Pressure Setpoints

**PSP**	Positive Pressure Setpoint		Assigns a setpoint pressure value for the positive pressure reservoir
<PSP, 25> assigns a Setpoint of +25KPa


**NSP**	Negative Pressure Setpoint  Assigns as Setpoint pressure value for the negative chamber

<NSP, -25> assigns a Setpoint of -25KPa

# Receiving data

**PVO**	Pressure Valve Output	returns the current pressure valve of the output pressure sensor

<PVO, 2> will send back the pressure value of sensor 3






