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

        //! Watch for events that change the desired speed.
        void init() {
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

        //! Nothing to do to initialize    
        void start() {}

        //! Get the velocity from the Velocity Channel, compute
        //! a simple proportional control law, and send the result
        //! to the Throttle channel.    
        void update() {
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

        //! Nothing to do to stop    
        void stop() {}

        private:
        double speed = 0;
        double desired_speed = 0.0;
        double angle = 0.0;
        int car_state;
        const double KP = 314.15;
                    vector<double> _v;
    };
}