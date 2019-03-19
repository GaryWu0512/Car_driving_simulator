#include <iostream>
#include <chrono>

#include "car.h"

using namespace std::chrono;
using std::vector;
using namespace elma;

namespace driving_example {
    void Car::init(){
        velocity = 0;
        car_angle = 0;
        _gear = 1;
        watch("car state", [this](Event& e) {
            car_state = e.value();
        });
        watch("add gas", [this](Event& e) {
            gas_state = 1;
        });
        watch("gear", [this](Event& e) {
            _gear = e.value();
        });
    }

    void Car::update(){
        if (car_state == 1){
            if (gas<1){
                car_state = 0;
            }else{
                if ( channel("Throttle").nonempty() ) {
                    force = channel("Throttle").latest();
                }
                if ( channel("Angle").nonempty() ) {
                    car_angle = channel("Angle").latest();
                }
                gas -=1;
                //std::cout<<"send v1 = "<<velocity<<"\n";
                if (_gear == 1){
                    m = 250;
                }else if(_gear == 2){
                    m = 400;
                }else{
                    m = 600;
                }
                velocity += ( delta() / 1000 ) * ( - k * velocity + force ) / m;
                //std::cout<<"send v2 = "<<velocity<<"\n";
                channel("Velocity").send(velocity);
                //std::cout << "speed = " << ","
                        // << velocity << " \n" <<"angle = "<< car_angle<<"\n"<<"gas="<<gas;
            }
        }else{
            channel("Velocity").flush();
            channel("Throttle").flush();
            channel("Angle").flush();
            velocity = 0;
            car_angle = 0;
            _gear = 1;
            channel("Velocity").send(velocity);
            if (gas_state == 1){
                if (gas<999){
                    if((gas+5)>999){
                        gas = 999;
                        gas_state = 0;
                    }else{
                        gas+=5;
                    }
                //std::cout<<"gas"<<gas<<"\n";
                }else{
                    //std::cout<<"gas is full"<<gas<<"\n";
                    gas = 999;
                    gas_state = 0;
                }
            }else{
                //std::cout<<"car is off"<<"\n";
                //std::cout<<"velocity = "<<velocity<<"\n";
            }
        }
    }

}
