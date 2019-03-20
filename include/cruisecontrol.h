#include <iostream>
#include <chrono>
#include "elma/elma.h"

//! \file

using namespace std::chrono;
using std::vector;
using namespace elma;

namespace driving_example {

    class CruiseControl : public Process {

        public:

        //! Wrap the base process class
        //! \param name The name of the controller      
        CruiseControl(std::string name) : Process(name) {}

        //! Watch for events that change the desired speed, car state, heading angle
        void init();

        //! Nothing to do to start    
        void start() {}

        //! Get the velocity from the Velocity Channel, compute
        //! a simple proportional control law, and send the result
        //! to the Throttle channel and Angle channel.    
        void update();

        //! Nothing to do to stop    
        void stop() {}

        private:
        double speed = 0;
        double desired_speed = 0.0;
        double desired_angle = 0.0;
        double angle = 0;
        int car_state;
        const double KP = 314.15;
                    vector<double> _v;
    };
}