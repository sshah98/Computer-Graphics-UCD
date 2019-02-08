#include "timer.h"
#include <iostream>
#include <unistd.h>

int TimerClock::tick() {
    seconds--;

    if(seconds < 0) {
        seconds = 59;
        minutes--;
    }
    if(minutes < 0) {
        minutes = 59;
        hours--;
    }
    if(hours < 0) {
        hours = 23;
    }

    return 0;
}
