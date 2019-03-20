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

        //! initialize the velocity and angle
        //! initialize the watch command {car state, add gas, gear} from driver process
        void init();

        //! Nothing to do to start    
        void start() {}

        //! The update method gets the latest force from the 
        //! Throttle Channel, if any. Then it updates the 
        //! car's velocity, and sends it out on the Velocity
        //! Channel.
        //! Switch the car state according to the car_state command from driver
        //! When car state is off, driver can add car gas
        //! Restricted the force according to gear state
        void update();

        //! Return the current car speed to the driver
        inline double getSpeed(){ return velocity; }

        //! Return the current car heading angle to the driver
        inline double getAngle(){ return car_angle; }

        //! Return the current car gas to the driver
        inline int getGas(){ return gas; }

        //! Return the current car state to the driver
        inline int getCarState(){ return car_state; }

        //! Return the current gas state to the driver
        inline int getGasState(){ return gas_state; }

        //! Return the current cae gear state to the driver
        inline int getGearState(){ return _gear; }

        //! Set the current cae gas
        //! \param gas The desire gas
        inline double setGas( int gas ){ this->gas = gas; }

        //! Record the driving process and output it as json file
        json reporttpjson();

        //! Nothing to do to stop    
        void stop() {}

        private:
        double velocity;
        double force;
        double angle_force;
        double car_angle;
        int gas = 999;
        int car_state;
        int gas_state;
        int _gear ;
        vector<double> speed_record;
        vector<double> angle_record;
        const double k = 0.02;
        double m = 300;
        double g = 300;
    };
}
