#ifndef CLOCK_H
#define CLOCK_H

class Clock
{

public:
    void print(); //print function
    void setTime(int secs, int mins, int hrs); //sets the times
    virtual int tick() = 0;

protected:
    int seconds, minutes, hours;
};



#endif // CLOCK_H
