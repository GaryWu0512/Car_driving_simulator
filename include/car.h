#include <iostream>
#include <chrono>
#include "elma/elma.h"

//! \file

using namespace std::chrono;
using std::vector;
using namespace elma;

namespace driving_example {

    class Car : public Process {
        public:

        //! Wrap the base process class
        //! \param name The name of the car    
        Car(std::string name) : Process(name) {}

        //! Nothing to do to initialize
        void init() {
            velocity = 0;
            car_angle = 0;
            watch("car state", [this](Event& e) {
                car_state = e.value();
            });
            watch("add gas", [this](Event& e) {
                gas_state = 1;
            });
        }

        //! To start a new simulation, this process sets
        //! the car's velocity to zero kph.    
        void start() {  
        }

        //! The update method gets the latest force from the 
        //! Throttle Channel, if any. Then it updates the 
        //! car's velocity, and sends it out on the Velocity
        //! Channel.     
        void update() {
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

        inline double getSpeed(){ return velocity; }
        inline double getAngle(){ return car_angle; }
        inline int getGas(){ return gas; }
        inline int getCarState(){ return car_state; }
        inline int getGasState(){ return gas_state; }
        inline double setGas( int gas ){ this->gas = gas; }

        //! Nothing to do to stop    
        void stop() {}

        private:
        double velocity;
        double force;
        double car_angle;
        int gas = 999;
        int car_state;
        int gas_state;
        const double k = 0.02;
        const double m = 300;
    };
}
