#include <iostream>
#include <chrono>

#include "cruisecontrol.h"

using namespace std::chrono;
using std::vector;
using namespace elma;

namespace driving_example {

    void CruiseControl::init(){
        watch("desired speed", [this](Event& e) {
            desired_speed = e.value();
        });
        watch("angle", [this](Event& e) {
            angle = e.value();
        });
        watch("car state", [this](Event& e) {
            car_state = e.value();
        });
    }

    void CruiseControl::update(){
        if (car_state == 1){
            //std::cout<<"size = "<<channel("Velocity").size();
            if ( channel("Velocity").nonempty() ) {
                speed = channel("Velocity").latest();
                //std::cout<<"velo speed = "<<speed<<"\n";
            }
            channel("Throttle").send(-KP*(speed - desired_speed));
            channel("Angle").send(angle);
        }
    }
}