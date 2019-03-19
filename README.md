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
-  Make a driver interface

##Funtion complete

- User can increase and decrease the car speed by using the user interface
- User can change the car angle by using the user interface
- Change the car status between On/Off by using the user interface
- Filling up the cas when car is at Off state by using the user interface
- Randomly generate speed limit sign, and send warning when driver is overspeed
- Display Car status and information on user interface

##User interface:

![](/Users/you-jun/Desktop/EE590SW/Elma-AutomaticCar/螢幕快照 2019-03-18 下午6.05.25.png)

## Milestones 
- Complete the PID controller design and tuned Ki Kp Kd -- achieve before 13 Mar(have accomplished)
- Test controller according to the given value  -- achieve before 13 Mar (have accomplished)
- Add state change function and combine with controller -- achieve before 17 Mar (have accomplished)
- Test car can change the status when driver send the command -- achieve before 17 Mar (have accomplished)
- Plots the data from simulations for user-readable -- achieve before 20 Mar
- Record the track status and output it as json file (TBD)
- Make a driver interface (have accomplished)
- Calculate mileage distance

