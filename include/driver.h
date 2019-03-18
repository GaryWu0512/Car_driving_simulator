#include <iostream>
#include <chrono>
#include "elma/elma.h"

//! \file

using namespace std::chrono;
using std::vector;
using namespace elma;

namespace driving_example {

    class Driver : public Process {

        public: 

        //! Wrap the base process class
        //! \param name The name of the controller       
        Driver(std::string name) : Process(name) {}

        //! initialize the desired speed
        void init() {
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
            desired_speed = 0;
            angle = 0;
        }

        //! Nothing to do to start
        void start() {}

        //! If the desired speed is 50, change to 60,
        //! otherwise change to 50.
        void update() {
            /*if ( desired_speed == 50 ) {
                desired_speed = 60;
            } else {
                desired_speed = 50;
            }
            if ( angle == 50 ) {
                angle = 60;
            } else {
                angle = 50;
            }*/
            if (state == 1){
                if (desired_speed<1){
                    desired_speed = 0;
                }
                if (desired_speed>200){
                    desired_speed -=5;
                }
                emit(Event("desired speed", desired_speed));
                emit(Event("angle", angle));
                emit(Event("car state", state));
                //std::cout<<"desired speed"<<desired_speed;
                //std::cout<<"desired angle"<<angle;
            }else{
                emit(Event("car state", state));
            }
        }

        //! Nothing to do to stop
        void stop() {}

        inline int getState(){ return state; }

        private:
        double desired_speed;
        double angle;
        int state = 0;

    };
}
