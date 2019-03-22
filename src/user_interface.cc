#include <unistd.h>

#include "user_interface.h"

using namespace driving_example;

UserInterface::UserInterface(Car& carv) : Process("user input"), _car(carv) {
    initscr();   // Start ncurses
    timeout(1);  // Timeout for waiting for user input
    noecho();    // Do not echo user input to the screen
    start_color();
    init_pair(1,COLOR_RED,COLOR_WHITE);
    init_pair(2,COLOR_RED,COLOR_BLACK);
    curs_set(0); // Do not show the cursor
};

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
            if (_car.getSpeed()>50){
                bad_score+=1;
            }
            break;
        case 'a':
            emit(Event("left"));
            if (_car.getSpeed()>50){
                bad_score+=1;
            }
            break;
        case 'g':
            emit(Event("add gas"));
            break;
        case 'o':
            emit(Event("turn on"));
            good_score = 0;
            bad_score = 0;
            break;
        case 'f':
            emit(Event("turn off"));
            break;
        case 'c':
            emit(Event("gear up"));
            break;
        case 'z':
            emit(Event("gear down"));
            break;
        case 'p':
            score_state = 1;
            break;
        case 'q':
            _car.reporttpjson();
            halt();
            break;
    }

    // OUTPUT
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
    mvprintw(13, 15, "Car heading: %.1f", _car.getAngle());
    mvprintw(12, 31, "(Max speed 200)");
    mvprintw(14, 15, "Gas: %03d", _car.getGas());
    mvprintw(14, 24, "/999 (Only can refuel in the off state.)");
    mvprintw(16, 1, "Car Status : ");
    mvprintw(18, 22, "Gas: ");
    mvprintw(18, 5, "Car: ");
    mvprintw(25, 1, "Score section:");
    mvprintw(25, 18, "See score(p)");

    mvprintw(7, 50, "Speed Limit");
    mvprintw(8, 53, "____");
   
    mvprintw(9, 52, "/");
    mvprintw(9, 57, "\\");
    
   
    mvprintw(10, 52, "|");
    mvprintw(10, 57, "|");

    mvprintw(11, 57, "/");
    mvprintw(11, 52, "\\");

    mvprintw(11, 53, "____");

    attron(COLOR_PAIR(2));
    mvprintw(10, 54, "%d  ",speed_lim);
    attroff(COLOR_PAIR(2));

    car_state = _car.getCarState();
    gas = _car.getGas();
    gear_state = _car.getGearState();

    if ((gas%200) == 1){ 
        speed_lim = speed_limit[index];
        index+=1;
        if (index == 5){
            index = 0;
        }
    }
    mvprintw(16, 50, "Speed Limit: %d ", speed_lim);
    mvprintw(17, 50, "Next Speed Limit: %d ", speed_limit[index+1]);
    if (_car.getSpeed()>speed_lim){
        attron(COLOR_PAIR(1));
        mvprintw(18, 50, "Overspeed !! Please slow down ");
        attroff(COLOR_PAIR(1));
        bad_score+=1;
    }else{
        mvprintw(18, 50, "                              ");
    }
    if (gas<200){
        attron(COLOR_PAIR(1));
        mvprintw(18, 27, "low gas !!!");
        attroff(COLOR_PAIR(1));
    }else{
        mvprintw(18, 27, "gas  ok !!!");
    }
    if (car_state == 1){
        mvprintw(18, 10, "On ");
        mvprintw(20, 1, "Gear Status : %d   ", gear_state);
        mvprintw(20, 21, "(Three stages) ");
        good_score += 1;
        score_state = 0;
        mvprintw(27, 1, "                              ");
        mvprintw(26, 1, "bad point: %f   ",bad_score);
    }else{
        mvprintw(18, 10, "Off");
        mvprintw(20, 1, "Gear Status : None");
        mvprintw(12, 15, "Car speed: 0.0  ");
        mvprintw(13, 15, "Car heading: 0.0  ");
        mvprintw(20, 21, "(Three stages) ");
        mvprintw(26, 1, "bad point: %f   ",bad_score);
        if (score_state == 1){
            score = ((good_score - bad_score)/good_score) *100;
            attron(COLOR_PAIR(1));
            mvprintw(27, 0, " Driving habit score : %.1f", score);
            attroff(COLOR_PAIR(1));
        }else{
            mvprintw(27, 0, "                              ");
        }
    }

    
    
    mvprintw(22, 3, "Gear down(z) ");
    mvprintw(22, 17, "Gear up(c) ");

    

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