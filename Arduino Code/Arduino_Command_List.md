# Command List

## Connecting To the Pneumatics


## Sending Commands

The Arduino is listening for commands in the following structure ‘< command, value1, optional value2>’

## Command List

| Command Syntax |                         Description                          |                           Example                            |
| :------------: | :----------------------------------------------------------: | :----------------------------------------------------------: |
|       **VI**       | Turns ON (1) or OFF (0) input valves. Negative = 0 Exhaust= 1 Positive = 2. | <VI, valve position, ON/OFF> <VI, 1, 1> opens the exhaust valve |
|     **VO**      | Turns ON (1) or OFF (0) input valves. Output valves are labelled 0-7. | <VO, valve number, ON/OFF> <VO,3,0> closes the fourth output valve |
|  **AIV**  |           Turns all input valves ON (1) or OFF (0)           |             <AIV,1> opens all three input valves             |
|      **AOV**       |           Turns all ouput valves ON (1) or OFF (0)           |               <AOV,0> closes all output valves               |
|      **PSP**       |       Changes setpoint of positive pressure reservoir*       | <PSP, desired pressure value> <PSP, 25> sets positive reservoir to 25kPa |
|      **NSP**       |       Changes setpoint of negative pressure reservoir*       | <NSP, desired pressure value> <NSP, -55> sets negative reservoir to -55kPa |
|      **PVO**       |         Returns value of output pressure sensors 0-N         | <PVO, output sensor> <PVO, 2> returns the third pressure sensor value |
|      **PVR**       |  **not setup. This will return the reservoir pressure value  |                                                              |
                                                         
*Reservoirs will not automatically exhaust if lowering setpoint. Pressure reduction  is completed by first lowering setpoint, then opening the desired input valve and exhaust valves until pumps turn on. 

