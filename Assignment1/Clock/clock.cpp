#include "clock.h"
#include <iostream>

void Clock::print() {
    std::cout << hours << ":" << minutes << ":"
              << seconds << std::endl;
}

void Clock::setTime(int secs, int mins, int hrs) {
    hours = hrs;
    minutes = mins;
    seconds = secs;
}

