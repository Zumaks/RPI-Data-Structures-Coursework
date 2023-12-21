#include <iostream>
#include "time.h"
#include <algorithm>
#include <string>
Time::Time() { //default constructor
hour = 0;
minute = 0;
second = 0;
}

Time::Time(int aHour, int aMinute, int aSecond) { // construct from month, day, & year
hour = aHour;
minute = aMinute;
second = aSecond;
}

int Time::getHour() const {
    return hour;
}

int Time::getMinute() const {
    return minute;
}

int Time::getSecond() const {
    return second;
}
void Time::setHour(int aHour){
    hour = aHour;
}
void Time::setMinute(int aMinute){
    minute = aMinute;
}
void Time::setSecond(int aSecond){
    second = aSecond;
}
void Time::PrintAMPM(){
    std::string AMorPM;
    if (hour >= 12) {
        hour = hour - 12;
        AMorPM = "PM";
    }
    else {
        AMorPM = "AM";
    }

    if (hour == 0) {
        hour = 12;
    }
    std::string hours;
    std::string minutes;
    std::string seconds;
    if (hour < 10) {
       hours = "0" + std::to_string(hour);
    }
    else {
        hours = std::to_string(hour);
     }
    if (minute < 10) {
        minutes = "0" + std::to_string(minute);
     }
     else {
        minutes = std::to_string(minute);
     }
    if (second < 10) {
        seconds = "0" + std::to_string(second);
     }
    else {
        seconds = std::to_string(second);
     }
    std::cout << hours << ":" << minutes << ":" << seconds << " " << AMorPM << std::endl;
}
bool IsEarlierThan(const Time& t1, const Time& t2) {
    int hour1 = t1.getHour();
    int hour2 = t2.getHour();
    int minute1 = t1.getMinute();
    int minute2 = t2.getMinute();
    int second1 = t1.getSecond();
    int second2 = t2.getSecond();
    if (hour1 < hour2) { 
        return true;
    }
    else if (hour1 == hour2) { 
        if (minute1 < minute2) {
            return true;
        }
        else if (minute1 == minute2) {
            if (second1 < second2) {
                return true;
            }
            else if (second1 == second2) {
                return true;
            }
            else {
                return false;
            }
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}