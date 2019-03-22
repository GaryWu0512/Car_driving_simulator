#include <iostream>
#include <chrono>
#include <fstream>


#include "car.h"

using namespace std::chrono;
using std::vector;
using namespace elma;

using namespace std;


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
            if (gas<2){
                gas = 0;
                emit(Event("turn off"));
            }else{
                if ( channel("Throttle").nonempty() ) {
                    force = channel("Throttle").latest();
                }
                if ( channel("Angle_fore").nonempty() ) {
                    angle_force = channel("Angle_fore").latest();
                }
                if ( channel("Angle").nonempty() ) {
                    car_angle = channel("Angle").latest();
                }
                if (velocity > 1){
                    gas -=2;
                }else{
                    gas -=1;
                }
                //std::cout<<"send v1 = "<<velocity<<"\n";
                if (_gear == 1){
                    m = 250;
                }else if(_gear == 2){
                    m = 400;
                }else{
                    m = 600;
                }
                velocity += ( delta() / 1000 ) * ( - k * velocity + force ) / m;
                car_angle += ( delta() / 1000 ) * ( - k * car_angle + angle_force ) / g;
                //std::cout<<"send v2 = "<<velocity<<"\n";
                channel("Velocity").send(velocity);
                channel("Angle").send(car_angle);
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
            channel("Angle").send(car_angle);
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
        speed_record.push_back(velocity);
        angle_record.push_back(car_angle);
    }

    void Car::reporttpjson(){
        json j;

        j["speed"] = speed_record;
        j["angle"] = angle_record;
        std::ofstream file("key.json");
        file << j;
    }

}
