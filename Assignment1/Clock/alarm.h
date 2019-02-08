#ifndef ALARM_H
#define ALARM_H

#include "clock.h"
#include "normal.h"

class AlarmClock:public NormalClock
{
public:
    int tick();
    bool checkAlarm();

protected:
    int alarmSecs, alarmMins, alarmHrs;
};


#endif // ALARM_H

