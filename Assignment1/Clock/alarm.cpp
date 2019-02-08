#include "alarm.h"
#include <iostream>
#include <unistd.h>

int AlarmClock::tick() {

    NormalClock::tick();
    if(AlarmClock::checkAlarm()) {
        std::cout << "Alarm!" << std::endl ;
    }
    return 0;

}

bool AlarmClock::checkAlarm() {
    if(NormalClock::hours == alarmHrs && NormalClock::minutes == alarmMins && NormalClock::seconds == alarmSecs) {
          return true;
    }
    else {
        return false;
    }


}
