#ifndef TIMER_H
#define TIMER_H
#include "clock.h"

class TimerClock:public Clock
{

public:
    int tick();

};


#endif // TIMER_H

