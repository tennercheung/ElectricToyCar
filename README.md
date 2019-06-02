# ElectricToyCar

## Schematics

Motors
![Alt Text](https://github.com/tennercheung/ElectricToyCar/blob/master/Schematics/Motors.jpg)
![Alt Text](https://github.com/tennercheung/ElectricToyCar/blob/master/Schematics/Motor_close_up.jpg)
Dashboard PCB
![Alt Text](https://github.com/tennercheung/ElectricToyCar/blob/master/Schematics/Dash_zoomed.jpg)
![Alt Text](https://github.com/tennercheung/ElectricToyCar/blob/master/Schematics/Dash.jpg)
![Alt Text](https://github.com/tennercheung/ElectricToyCar/blob/master/Schematics/Dash2.jpg)

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

..

## Useful Links:
* 7A/160W L298 Motor Board (https://amzn.to/2WCc6RT)
* LM2596 DC-DC Step Down Buck Converter(https://bit.ly/2JCi5m3)


