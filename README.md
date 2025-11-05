# robotics traveling van inverted pendulum robot

the code needed to power an inverted pendulum robot with four motors

- this code is made much simpler thanks to [this PID controller library](https://github.com/br3ttb/Arduino-PID-Library)

# notes to self

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

- [x] implement the PID_V1.h PID controller function call
- [ ] take PID controller output and call motors
- [ ] write code that keeps robot from rolling too far in either direction
- [ ] implement touch screen and UI
