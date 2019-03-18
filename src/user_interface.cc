#include <unistd.h>

#include "user_interface.h"

using namespace driving_example;

UserInterface::UserInterface(Car& carv) : Process("user input"), _car(carv) {
    initscr();   // Start ncurses
    timeout(1);  // Timeout for waiting for user input
    noecho();    // Do not echo user input to the screen
    curs_set(0); // Do not show the cursor
};

void UserInterface::show_time(int x, int y, high_resolution_clock::duration d) {

    // Print the time at the desired position.
    // mvprintw just calls sprintf
    mvprintw(x,y,"%d:%02d:%02d", 
        std::chrono::duration_cast<std::chrono::minutes>(d).count(),
        std::chrono::duration_cast<std::chrono::seconds>(d).count()%60,
        (std::chrono::duration_cast<std::chrono::milliseconds>(d).count()%1000)/10
    );
}

void UserInterface::update() {

    // USER INPUT
    // get a character from the user, if one is ready.
    // If no character is ready, getch() returns ERR (which is
    // ignored below since there is no condition in the switch statement)
    int c = getch();

    switch ( c ) {            
        case 'w':
            emit(Event("speed up"));
            break;
        case 's':
            emit(Event("speed down"));
            //clear(); // Clear the screen of old stuff
            break;
        case 'd':
            emit(Event("right"));
            break;
        case 'a':
            emit(Event("left"));
            break;
        case 'g':
            emit(Event("add gas"));
            break;
        case 'o':
            emit(Event("turn on"));
            break;
        case 'f':
            emit(Event("turn off"));
            break;
        case 'q':
            //std::cout << "halting\n";
            halt();
            break;
    }

    // OUTPUT
    //show_time(1,1,_stopwatch.value()); 
    mvprintw(1, 25, "Welcome to Elma Car simulator !!!");
    mvprintw(3, 1, "Instruction : ");
    mvprintw(4, 5, "speed up(w)");
    mvprintw(5, 5, "speed down(s)");
    mvprintw(6, 5, "turn right(d)");
    mvprintw(7, 5, "turn left(a)");
    mvprintw(4, 22, "turn on the car(o)");
    mvprintw(5, 22, "turn off the car(f)");
    mvprintw(6, 22, "filling up(g)");
    mvprintw(7, 22, "quit simulation(q)");
    mvprintw(10, 1, "Car Dashboard : ");
    mvprintw(12, 15, "Car speed: %.1f", _car.getSpeed());
    mvprintw(13, 15, "Car angle: %.1f", _car.getAngle());
    mvprintw(12, 31, "(Max speed 200)");
    mvprintw(14, 15, "Gas: %d", _car.getGas());
    mvprintw(14, 24, "/999 (Only can refuel in the off state.)");
    mvprintw(16, 1, "Car Status : ");
    mvprintw(18, 22, "Gas: ");
    mvprintw(18, 5, "Car: ");
    car_state = _car.getCarState();
    gas = _car.getGas();

    if (gas%150 == 0){
        int random_number = rand()%5;
        speed_lim = speed_limit[random_number];
    }
    mvprintw(16, 50, "Speed Limit: %d ", speed_lim);
    if (_car.getSpeed()>speed_lim){
        mvprintw(18, 50, "Overspeed !! Please slow down ");
    }else{
        mvprintw(18, 50, "                              ");
    }
    if (gas<150){
        mvprintw(18, 27, "low gas !!!");
    }else{
        mvprintw(18, 27, "gas  ok !!!");
    }
    if (car_state == 1){
        mvprintw(18, 10, "On ");
    }else{
        mvprintw(18, 10, "Off");
        mvprintw(12, 15, "Car speed: 0.0  ");
        mvprintw(13, 15, "Car angle: 0.0  ");
    }

    /*for ( int i=0; i<_stopwatch.laps().size(); i++ ) {
        mvprintw(5+i, 1, "Lap %d", _stopwatch.laps().size()-i);
        show_time(5+i, 10, _stopwatch.laps()[i]);
    }*/

    // NOTE: Since the stopwatch is running every 10 ms, we should sleep
    //       the ui to give processing time back to the OS. It is debatable
    //       whether this is the right place to put this. It could also become
    //       an Elma feature, or it could go in the StopWatch class, etc.
    //       The number 9999 should also be a parameter and not a constant.
    usleep(9999);

}