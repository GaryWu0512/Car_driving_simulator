#include <iostream>
#include <chrono>
#include "driver.h"

using namespace std::chrono;
using std::vector;
using namespace elma;

namespace driving_example {

    void Driver::init() {
        watch("speed up", [this](Event& e) {
            desired_speed +=5;
        });
        watch("speed down", [this](Event& e) {
            desired_speed -=5;
        });
        watch("right", [this](Event& e) {
            if (angle>359){
                angle = 0+5;
            }else{
                angle += 5;
            }
        });
        watch("left", [this](Event& e) {
            if (angle<1){
                angle = 360-5;
            }else{
                angle -= 5;
            }
        });
        watch("turn on", [this](Event& e) {
            state = 1;
        });
        watch("turn off", [this](Event& e) {
            state = 0;
            desired_speed = 0;
        });
        watch("gear up", [this](Event& e) {
            if (gear <3){
                gear += 1;
            }else{
                gear = 3;
            }
        });
        watch("gear down", [this](Event& e) {
            if (gear >1){
                gear -= 1;
            }else{
                gear = 1;
            }
        });
        desired_speed = 0;
        angle = 0;
    }

    void Driver::update(){
        if (state == 1){
            if (gear == 1){
                if (desired_speed<1){
                    desired_speed = 0;
                }
                if (desired_speed>50){
                    desired_speed -=5;
                }
            }else if (gear == 2){
                if (desired_speed<1){
                    desired_speed = 0;
                }
                if (desired_speed>100){
                    desired_speed -=5;
                }
            }else if (gear == 3){
                if (desired_speed<1){
                    desired_speed = 0;
                }
                if (desired_speed>200){
                    desired_speed -=5;
                }
            }
            emit(Event("desired speed", desired_speed));
            emit(Event("desired angle", angle));
            emit(Event("car state", state));
            emit(Event("gear", gear));
            //std::cout<<"desired speed"<<desired_speed;
            //std::cout<<"desired angle"<<angle;
        }else{
            gear = 1;
            emit(Event("gear", gear));
            emit(Event("car state", state));
        }
    }
}
