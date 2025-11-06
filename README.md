# robotics traveling van inverted pendulum robot

the code needed to power an inverted pendulum robot with four motors

- this code is made much simpler thanks to [this PID controller library](https://github.com/br3ttb/Arduino-PID-Library)
- I referenced [Ian Carey's inverted pendulum code](https://gist.github.com/careyi3/d087f707b33c665915bd611e5514a355) for help with organizing the code, thank you!!

# notes to self

## DRV8871 motor driver

- forward: IN1 = PWM signal, IN2 = LOW
- reverse: IN1 = LOW, IN2 = PWM signal
- brake (Stop): IN1 = LOW, IN2 = LOW

## pin configuration

- potentiometer: A0
- left motor 1: D3 (PWM)
- left motor 1: D5 (PWM)
- right motor 1: D6 (PWM)
- right motor 1: D9 (PWM)

# to-do

- [x] implement the PID_V1.h PID controller function call
- [x] take PID controller output and call motors
- [ ] write code that keeps robot from rolling too far in either direction
- [ ] implement touch screen and UI
