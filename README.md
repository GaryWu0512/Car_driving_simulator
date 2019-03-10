# Elma-AutomaticCar

## Project goals
- Simulation to use a more realistic simulation of a car's velocity and angle
    * Use PID controller to contol the Car speed and angle.
    * Set criteria to prevent the car from rotating too far or the acceleration is too fast.
- Add some changes in the state of the car by the instructions sent by the driver, like change gears, speed up, slow down, and stop.
    * Use StateMachine to change the car's driving status.
    * Use Watch to monitor the state of the car. Prompt or warning
- Export data taken from simulations and show with plots that the car's information and status(Speed, angle, time, the status of the car, oil quantity)
- (extra) Record the track status and output it as json file
- (extra) Make a driver interface

## Milestones 
- Complete the PID controller design and tuned Ki Kp Kd -- achieve before 13 Mar
- Test controller according to the given value  -- achieve before 13 Mar
- Add state change function and combine with controller -- achieve before 17 Mar
- Test car can change the status when driver send the command -- achieve before 17 Mar
- Plots the data from simulations for user-readable -- achieve before 20 Mar
- Record the track status and output it as json file (TBD)
- Make a driver interface (TBD)

