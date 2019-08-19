# ElectricToyCar

# (Car 1)
## ProtoV1

Code implemented with intent to test control with IR and on-board user controls of the vehicle


Encountered Issues:
* IR controls send different hex code stead FFFFFF when held in testing

## ProtoV1.1

Code implemented with intent to just the rider’s controls of the vehicle (speed & driving modes)

Encountered Issues:
* Motors shaking/jittery in fwd & bwd = PWM given to motor needs to start from low value so motors have time to speed up
* Motors run smoother independently -> since they are lower speeds there is less time needed to speed up
* When Arduino is reset, M2 is given power due to unallocated states of pins = since connected to LED takes a high during reset, reallocated pin 13 to pin 7

* Multiple buttons touched should keep system idle but instead triggers one/a mix of the button’s functions

## ProtoV2

Encountered Issues:
* Arduino must be off to send serial output to battery
* Battery has automatic shut off when pedal switch has not been pressed for longer than ~10 minutes
* When starting up the car, pedal switch is to be pressed first while the switch for power to the Arduino and H-Bridge (Red Switch on the back of the car) is off.
* 60kg servo does not function with the Arduino library, but works if it connects to the RC receiver
* Small servo jitters when RC is shut off
* Small detail, hidden speed control switch can be implemented as a small feature incase client wants to increase the speed of the car

# (Car 2)
## ProtoV1 
Encountered Issues: N/A

## Pedal Signal Analysis
Oscilloscope
![Alt Text](https://github.com/tennercheung/ElectricToyCar/blob/master/Car_2/Pedal_Signal/on_oscillo.jpg)

Serial Plotter
![Alt Text](https://github.com/tennercheung/ElectricToyCar/blob/master/Car_2/Pedal_Signal/pedsig_start.jpg)
![Alt Text](https://github.com/tennercheung/ElectricToyCar/blob/master/Car_2/Pedal_Signal/pedsig_end.jpg)

## Schematics

Motors
![Alt Text](https://github.com/tennercheung/ElectricToyCar/blob/master/Schematics/Motors.jpg)
![Alt Text](https://github.com/tennercheung/ElectricToyCar/blob/master/Schematics/Motor_close_up.jpg)
Dashboard PCB
![Alt Text](https://github.com/tennercheung/ElectricToyCar/blob/master/Schematics/Dash_zoomed.jpg)
![Alt Text](https://github.com/tennercheung/ElectricToyCar/blob/master/Schematics/Dash.jpg)
![Alt Text](https://github.com/tennercheung/ElectricToyCar/blob/master/Schematics/Dash2.jpg)


## Useful Links:
* 7A/160W L298 Motor Board (https://amzn.to/2WCc6RT)
* Tesla Club Forum (https://bit.ly/2KY1rN8)


