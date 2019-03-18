#include <iostream>
#include <chrono>
#include <vector>
#include <ncurses.h>

#include "driver.h"
#include "car.h"
#include "cruisecontrol.h"

namespace driving_example {

    using namespace std::chrono;
    using namespace elma;
    using namespace driving_example;

    
    class UserInterface : public Process {

        public:

        UserInterface(Car& carv);

        void init() {}
        void start() {}

        //! Display the time at the given x,y position on the screen
        void show_time(int x, int y, high_resolution_clock::duration d);

        //! Update the user interface by (a) reading keyboard input and (b) writing to the screen
        void update();
        void stop() {}

        private:
        Car& _car;
        int gas;
        int car_state;
        double desire_speed;
        int speed_limit[5] = {20,100,80,180,60};
        int speed_lim = 80;

    };

}