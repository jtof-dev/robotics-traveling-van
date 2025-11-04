# robotics traveling van inverted pendulum robot

the code needed to power an inverted pendulum robot with four motors

# notes to self

- potentiometer will output values between 0 and 1023

## DRV8871 motor driver

- forward: IN1 = PWM signal, IN2 = LOW
- reverse: IN1 = LOW, IN2 = PWM signal
- brake (Stop): IN1 = LOW, IN2 = LOW

## pin configuration

- potentiometer: A0
- left motor 1: D3
- left motor 1: D5
- right motor 1: D6
- right motor 1: D9

# to-do

- [ ] write function that converts potentiometer values into what is needed for the PID controller
- [ ] implement the PID_V1.h PID controller function call
- [ ] write code that keeps robot from rolling too far in either direction
- [ ] implement touch screen and UI
