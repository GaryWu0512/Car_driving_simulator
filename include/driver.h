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

        //! initialize the desired speed and angle
        //! initialize the watch command {speed up, speed down, right, left, turn on, turn off, gear up, gear down}
        void init();

        //! Nothing to do to start
        void start() {}

        //! Adjust the desired speed, heading angle and car state according to commands
        //! Adjust the speed limit and force according to gear state
        void update();
 
        

        //! Nothing to do to stop
        void stop() {}

        //! Return the Car state
        inline int getState(){ return state; }

        private:
        double desired_speed;
        double angle;
        int gear = 1;
        int state = 0;

    };
}
