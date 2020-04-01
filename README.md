

# 1. Overview
This system is designed to control multi-channel pneumatic smart surfaces using only small amounts of air. The pneumatic system consists of 8 independent pneumatic channels that can access positive, negative, and neutral (exhaust) states. For a smaller, portable setup, please refer to this respository.

![image of setup](Images/Jan_21_2020/bigpneumatics.png)

<img src="Images/2020_08_19/topView.png" alt="topView" style="zoom:10%;" /> <img src="Images/2020_08_19/backView.png" alt="backView" style="zoom:10%;" />

## 1.1 Table of Contents

[TOC]

# 2. Components & Pneumatic Logic

The instrument is designed to provide 3 pressure 'input' states: positive (+∆P), negative, (-∆P), and neutral (0∆P). Postive and negative pressures are generated through pneumatic pumps and held in reservoirs. The pressure for each reservoir is defined by the user and monitored through in-line pressure sensors. Pneumatic valves can be toggled to open and enter a common pressure line which can be accessed by independent valves that lead to channels (N=8). 

The valves are rated for +-100kPa while the pumps are generally able to reach ~+-60kPa. Valve response time is <5ms.

![image of logic](Images/Jan_21_2020/pressuresetup.png)

# 3. Instrument Control

An Arduino microncontroller is responsible for opening and closing the pneumatic valves in addition to regulating pressure setpoints of the reservoirs. 



This instrument is controlled through a Serial Connection to a computer. 



Communication to the microcontroller is accomplished through serial communication. Commands for valve control, setpoint, and pressure value requests are available in the X section.

A MATLAB GUI app uses these commands to visually control the pneumatics.

screenshot to be added later.

## 3.1 Serial Command List

The Arduino is listening for serial commands in the following structure ‘< command, optional modifier, optional modifier>’.

### 3.1.1 Valve Control

| Command Syntax | Description                                                  | Example                                 |
| :------------: | ------------------------------------------------------------ | --------------------------------------- |
|     **VO**     | **VALVE OUTPUT** Changes the state of a single output valve. <command, valve # (0-7), valve state (0-closed 1-open)> | <VO, 4, 1> opens the fifth output valve |
|     **VI**     | **VALVE INPUT**Changes the state of a single input valve. <command, valve # (0-7), valve state (0-off 1-on)> | <VO, 4, 1> opens the fifth output valve |
|    **AIV**     | **ALL INPUT VALVES** Changes the state of all input valves <command, 0/1> | <AIV,1> opens all input valves          |
|    **AOV**     | **ALL OUTPUT VALVES** Changes the state of all outpu valves <command, 0/1> | <AOV, 0> turns off all output valves    |

### 3.1.2 Reservoir Setpoints

| Command Syntax | Description                                                  | Example    |
| :------------: | ------------------------------------------------------------ | ---------- |
|    **PSP**     | Changes setpoint of positive pressure reservoir              | <PSP, 15>  |
|    **NSP**     | Changes setpoint of negative pressure reservoir              | <NSP, -15> |
|    **PVN**     | **PRESSURE VALUE NEGATIVE** prints the pressure value of the negative pressure reservoir | <PVN>      |
|    **PVO**     | **PRESSURE VALUE OUTPUT** prints the pressure value of an output pressure channel | <PVO, 3>   |
|    **PVP**     | **PRESSURE VALUE POSITIVE** prints the pressure value of the positive pressure reservoir | <PVP>      |

### 3.1.3 Pressure Readings

| Command Syntax | Description                                                  | Example  |
| :------------: | ------------------------------------------------------------ | :------: |
|      PVP       | **PRESSURE VALUE POSITIVE** prints the pressure value of the positive pressure reservoir |  <PVP>   |
|      PVN       | **PRESSURE VALUE NEGATIVE** prints the pressure value of the negative pressure reservoir |  <PVN>   |
|      PVO       | **PRESSURE VALUE OUTPUT** prints the pressure value of an output pressure channel | <PVO, 3> |

# 4. Visual Control App

A visual control app was designed using Matlab App Designer. The app is basic in functionality but is able to control valves through sending serial commands. 

![VCA](Visual_Control_System/Pneumatics_App_Jan_24.png)

# 5. Setpoint Pressure Control

Reservoir pressure is controlled by simple state monitoring. The pressure sensors monitor the pressure and the pump is turned on if the pressure drops below the Setpoint (with a small threshold).

# 6. Electrical Circuitry

## 6.1 Electrical Components

Power is supplied by an off board 12V 5A brick-style switching power supply. The 12V power is then split and one side is stepped down to 5V. The valves run on the 5V rail and are toggled through npn transistors powered by an Arduino.

**12V**

- Pumps
- Motor Controller

**5V**

- Valves

**5V (Computer-> Arduino)**

- pressure sensors
- transistors
- leds

## 6.2 PCBs

### 6.2.2 Input Valve PCB

<img src="/Users/kurtislaqua/Documents/GitHub/Pneumatics/Images/3_valve_pcb.png" alt="3 valve pcb" style="zoom:50%;" />

### 6.2.3 Output Valve PCB

<img src="/Users/kurtislaqua/Documents/GitHub/Pneumatics/Images/4_valve_pcb.png" alt="4 valve pcb" style="zoom:50%;" />



### 6.2.4 2 Sensor Board

![sensor board](/Users/kurtislaqua/Documents/GitHub/Pneumatics/Images/sensor_board_image.png)



