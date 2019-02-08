#include "normal.h"
#include <iostream>
#include <unistd.h>


int NormalClock::tick() {
    seconds++;

    if(seconds > 59) {
        seconds = 0;
        minutes++;
    }
    if(minutes > 59) {
        minutes = 0;
        hours++;
    }
    if(hours > 23) {
        hours = 0;
    }

    return 0;
}
