#include <QCoreApplication>
#include "clock.h"
#include "clock.h"
#include "normal.h"
#include "alarm.h"
#include "timer.h"
#include <fstream>
#include <iostream>
using namespace std;


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    NormalClock normal;
    AlarmClock alarm;
    TimerClock timer;

    int secs, mins, hrs;
    int alarmSecs, alarmMins, alarmHrs;

    // open a file in read mode.
    ifstream infile;
    infile.open("clock.dat");
    cout << "Reading from the file" << endl;
    infile >> secs;
    infile >> mins;
    infile >> hrs;

    infile >> alarmSecs;
    infile >> alarmMins;
    infile >> alarmHrs;

    normal.setTime(secs, mins, hrs);

    cout << "Clock: ";
    normal.print();

    //invocate tick according to specs
    for(int i=0; i <= 100000; i++) {
        normal.tick();
    }

    cout << "Normal Clock: ";
    normal.print(); //print normal object after tick


    alarm.setTime(alarmSecs, alarmMins, alarmHrs);
    for(int i=0; i <= 100000; i++) {
        alarm.tick();
    }
    cout << "Alarm Clock: ";
    alarm.print();

    timer.setTime(secs, mins, hrs);
    for(int i=0; i <= 100000; i++) {
        timer.tick();
    }
    cout << "Timer Clock: ";
    timer.print();


    return a.exec();
}

