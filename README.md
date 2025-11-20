# robotics traveling van inverted pendulum robot

the code needed to power an inverted pendulum robot with four (or two) motors

- this code is made much simpler thanks to [this PID controller library](https://github.com/br3ttb/Arduino-PID-Library)
- I referenced [Ian Carey's inverted pendulum code](https://gist.github.com/careyi3/d087f707b33c665915bd611e5514a355) for help with organizing the code, thank you!!

# notes to self

## DRV8871 motor driver

| IN1 | IN2 |  OUT1  |  OUT2  | DESCRIPTION                                                   |
| :-: | :-: | :----: | :----: | :------------------------------------------------------------ |
|  0  |  0  | High-Z | High-Z | Coast; H-bridge disabled to High-Z (sleep entered after 1 ms) |
|  0  |  1  |   L    |   H    | Reverse (Current OUT2 --> OUT1)                               |
|  1  |  0  |   H    |   L    | Forward (Current OUT1 --> OUT2)                               |
|  1  |  1  |   L    |   L    | Brake; low-side slow decay                                    |

## GM3865-520 dc motor encoder

- outputs two data signals phased 100deg apart

## pin configuration

- potentiometer: A0
- encoder output A: A1
- encoder output B: A2

- left motor 1: D3 (PWM)
- left motor 1: D5 (PWM)
- right motor 1: D6 (PWM)
- right motor 1: D9 (PWM)

# to-do

- [x] implement the PID_V1.h PID controller function call
- [x] take PID controller output and call motors
- [x] bugfix for initial hardware test
- [x] implement initial encoder software
- [x] implement code that keeps robot from rolling too far in either direction
- [ ] implement function to prevent robot from going too far in either direction

## future to-do

- [ ] implement touch screen and UI
