# ElectricToyCar

## ProtoV1

Code implemented with intent to test control with IR and on-board user controls of the vehicle

Encountered Issues:
* IR controls send different hex code stead FFFFFF when held in testing

## ProtoV1.1

Code implemented with intent to just the rider’s controls of the vehicle (speed & driving modes)

Encountered Issues:
* Motors shaking/jittery in fwd & bwd = lack of adequate power
* Motors run smoother independently
* When Arduino is reset, M2 is given power due to unallocated states of pins
* Multiple buttons touched should keep system idle but instead triggers one/a mix of the button’s functions

## ProtoV2

..


