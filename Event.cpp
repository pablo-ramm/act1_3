

#include <iostream>
#include <time.h>
#include "Event.h"
#include <string>
#include <fstream>
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;
using std::time_t;

Event::Event()
{
}

Event::Event(string month_, int day_, string hour_, string ip_, string message_)
{
    stringMonth = month_;
//dependiendo el string que se ha ingresado se le asigna un valor numero para su mejor manejo al momento de regresar su time_t
    if (month_ == "Jan")
    {
        month = 0;
    }
    else if (month_ == "Feb")
        month = 1;
    else if (month_ == "Mar")
        month = 2;
    else if (month_ == "Apr")
        month = 3;
    else if (month_ == "May")
        month = 4;
    else if (month_ == "Jun")
        month = 5;
    else if (month_ == "Jul")
        month = 6;
    else if (month_ == "Aug")
        month = 7;
    else if (month_ == "Sep")
        month = 8;
    else if (month_ == "Oct")
        month = 9;
    else if (month_ == "Nov")
        month = 10;
    else
        month = 11;

    day = day_;
    hour = hour_;
    ip = ip_;
    message = message_;
}

//Esta funcion regresa un tipo time_t, regresa el tiempo en segundos que han pasado desde el primero de Enero de 1970 respecto al objeto event
time_t Event::getDate()
{
    time_t date;
    struct tm whenDate; //con ayuda de la structura tm y sus métodos, podemos crear el valor de la fecha de tipo time_t del objeto evento

    whenDate.tm_year = 2022;
    whenDate.tm_mon = month;
    whenDate.tm_mday = day;
    whenDate.tm_hour = stoi(string() + hour[0] + hour[1]);
    whenDate.tm_min = stoi(string() + hour[3] + hour[4]);
    whenDate.tm_sec = stoi(string() + hour[6] + hour[7]);
    whenDate.tm_isdst = -1;

    date = mktime(&whenDate);

    return date;
}


string Event::getMonth(){
    return stringMonth;
}

string Event::getHour(){
    return hour;
    
}

string Event::getIp(){
    return ip;
}

string Event::getMessage(){
    return message;
}

int Event::getDay(){
    return day;
}