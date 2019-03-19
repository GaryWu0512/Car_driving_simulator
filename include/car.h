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
        void init();

        //! To start a new simulation, this process sets
        //! the car's velocity to zero kph.    
        void start() {}

        //! The update method gets the latest force from the 
        //! Throttle Channel, if any. Then it updates the 
        //! car's velocity, and sends it out on the Velocity
        //! Channel.     
        void update();

        inline double getSpeed(){ return velocity; }
        inline double getAngle(){ return car_angle; }
        inline int getGas(){ return gas; }
        inline int getCarState(){ return car_state; }
        inline int getGasState(){ return gas_state; }
        inline int getGearState(){ return _gear; }
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
        int _gear ;
        vector<double> speed_record;
        vector<double> angle_record;
        const double k = 0.02;
        double m = 300;
    };
}
