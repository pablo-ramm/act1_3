#ifndef _EVENT_H_
#define _EVENT_H_

#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
using std::string;
using std::time_t;

class Event
{
public:
    Event(string month_, int day_, string hour_, string ip_, string message_);
    Event();
    time_t getDate();
    string getMonth();
    int getDay();
    string getHour();
    string getIp();
    string getMessage();

public:
    int month;
    int day;
    string hour;
    string ip;
    string message;
    string stringMonth;
};

#endif