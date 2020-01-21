# Pneumatics
Herein is described the pneumatic control system used in the HATTONLAB to control pneumatic smart surfaces.

# Overview
This system is designed to control multi-channel pneumatic smart surfaces using only small amounts of air.


![image of setup](https://github.com/sitruklaq/Pneumatics/blob/master/Images/Jan%2021%202020/bigpneumatics.png)

# Pneumatic Logic

The Pneumatic logic is as follows:

Two pumps (one for positive and one for negative pressure) pressurize two resevoirs. 

Valves
on the inlet side, there are three valves that control inlet flow.
1 to allow positive pressure
1 to allow negative pressure
1 to exhuast

On the outlet side, valves can be turned on to pressurize the channels.There are currently 8 output valves.

![image of logic](https://github.com/sitruklaq/Pneumatics/blob/master/Images/Jan%2021%202020/pressuresetup.png)

# Control

The Arduino microncontroller is responsible for opening and closing the pneumatic valves in addition to regulating pressure setpoints of the reservoirs. 

Setpoint control is currently only simple state monitoring. The pumps will turn on if the reservoirs are underpressurized below a threshold. For example, if the setpoint is +5kPa, the pump will turn on if < 4.7kPa... (a 0.3kPa threshold).

Communication to the microcontroller is accomplished through serial communication. Commands for valve control, setpoint, and pressure value requests are available in the X section.

A MATLAB GUI app uses these commands to visually control the pneumatics.

screenshot to be added later.




