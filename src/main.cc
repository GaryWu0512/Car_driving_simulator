#include <iostream>
#include <chrono>
#include <vector>
#include <ncurses.h>


#include "user_interface.h"

using namespace std::chrono;
using namespace elma;
using namespace driving_example;

int main() {

    Manager m;

    driving_example::Car car("Car");
    driving_example::CruiseControl cc("Control");
    driving_example::Driver driver("Steve");
    UserInterface ui(car);

    Channel throttle("Throttle");
    Channel angle_force("Angle_fore");
    Channel velocity("Velocity");
    Channel angle("Angle");

    m.schedule(car, 100_ms)
    .schedule(cc, 100_ms)
    .schedule(driver, 100_ms)
    .schedule(ui, 200_ms)
    .add_channel(throttle)
    .add_channel(angle_force)
    .add_channel(angle)
    .add_channel(velocity)
    .init()
    .run();
    endwin();  
    /*.emit(Event("turn on"))
    .emit(Event("speed up"));
    m.run(10_s);
    std::cout<<"speed down"<<"\n";
    m.emit(Event("speed down"));
    m.run(10_s);
    std::cout<<"right"<<"\n";
    m.emit(Event("right"))
    .run(2_s);
    std::cout<<"left"<<"\n";
    m.emit(Event("left"))
    .run(2_s);
    std::cout<<"turn off"<<"\n";
    m.emit(Event("turn off"))
    .run(2_s);
    std::cout<<"add gas"<<"\n";
    m.emit(Event("add gas"));
    m.run(5_s);*/
     
}