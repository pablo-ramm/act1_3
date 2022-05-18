#ifndef _BITACORA_H_
#define _BITACORA_H_

#include <iostream>
#include <vector>
#include <time.h>
#include <fstream>
#include "Event.h"
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;
using std::time_t;
using std::ofstream;
using std::ifstream;
using std::cerr;
#include <cstdlib>

class Bitacora{
    public:
    void merge(vector<Event> &events, int begin, int m, int end);
    void ordenaMerge(vector<Event> &events, int begin, int end);
    int busquedaBinaria(vector<Event> &events, time_t k);
    time_t getDate(string month_, int day, string hour);
    void printEvents(vector<Event> &events, int indexInicio, int indexFinal);
    void writeEvents(vector<Event> &events);
    void openFile(vector<Event> &events);

    private:
    

};

void Bitacora::merge(vector<Event> &events, int begin, int m, int end){
    int i = 0, j = 0, k = 0;
    int n1 = m - begin + 1;
    int n2 = end - m;
    vector<Event> L(n1);
    vector<Event> R(n2);
    // copiar datos en dos arreglos
    for (int i = 0; i < n1; i++)
    {
        L[i] = events[begin + i];
    }
    for (int j = 0; j < n2; j++)
    {
        R[j] = events[m + 1 + j];
    }
    // fusionar los subarreglos
    i = j = 0;
    k = begin;

    while (i < n1 && j < n2)
    {
        if (L[i].getDate() <= R[j].getDate())
        {
            events[k] = L[i];
            i++;
        }
        else
        {
            events[k] = R[j];
            j++;
        }
        k++;
    }

    // en caso que se terminen los elementos de un lado copiar los demás
    while (i < n1)
    {
        events[k] = L[i];
        k++;
        i++;
    }

    while (j < n2)
    {
        events[k] = R[j];
        k++;
        j++;
    }

}

void Bitacora::ordenaMerge(vector<Event> &events, int begin, int end){
     if (begin < end)
    {
        int m = begin + (end - begin) / 2;
        ordenaMerge(events, begin, m);
        ordenaMerge(events, m + 1, end);
        merge(events, begin, m, end);
    }
}

int Bitacora::busquedaBinaria(vector<Event> &events, time_t k){
    int l = 0;
    int r = events.size() - 1;

    while (l <= r)
    {
        int m = l + (r - l) / 2;
        if (k == events[m].getDate())
            return m;
        else if (k < events[m].getDate())
            r = m - 1;
        else
            l = m + 1;
    }

    throw std::invalid_argument("Fecha no encontrada");
    return -1;
}

//Esta funcion regresa un tipo time_t, regresa el tiempo en segundos que han pasado desde el primero de Enero de 1970
//Es usada para conocer el time_ de la fecha de inicio y final ingresada por el usuario
time_t Bitacora::getDate(string month_, int day, string hour){
     int month;
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

    time_t date;
    struct tm whenDate;

//con ayuda de la structura tm y sus métodos, podemos crear el valor de la fecha de tipo time_t

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


//Esta funcion escribe los datos de los "eventos" dentro del vector en el documento 
void Bitacora::writeEvents(vector<Event> &events){
    try{
        ofstream outdata; // outdata es como cin

        outdata.open("bitacora_ordenada.txt"); // abre el archivo
        if (!outdata)
        { // por si el archivo no se puede abrir
           throw "no se pudo abrir el archivo";
        }

    //Iteramos por todo el vector para escribirlos en el archivo
        for (int i = 0; i < events.size(); i++)
        {
            outdata << events[i].getMonth() << " " << events[i].getDay() << " " << events[i].getHour() << " " << events[i].getIp() << " " << events[i].getMessage() << endl;
        }
    }catch(string e){
        cout << "una excepción ha ocurrido" << e << endl;
    }
}

//Esta funcion imprime en pantalla los resultados de la busqueda hecha por el usuario
void Bitacora::printEvents(vector<Event> &events, int indexInicio, int indexFinal){
    
       
//Iteramos por todo el vector para imprimirlos en la terminal
        for (int i = indexInicio; i < indexFinal + 1; i++)
        {
            cout << events[i].getMonth() << " " << events[i].getDay() << " " << events[i].getHour() << " " << events[i].getIp() << " " << events[i].getMessage() << endl;
        }
   
}


//este metodo abre y lee un documento para guardar estos eventos en un vector
void Bitacora::openFile(vector<Event> &events){

    string month, hour, ip, message;
    int day;
    try{
        // abrir documento bitacora
        ifstream file;
        file.open("bitacora.txt");
        // por si no se puede abrir el documento
        if (!file)
        {
             throw "Error al abrir el archivo";
        }

        // ciclo para agregar las palabras restantes del renglon a una sola variable string llamada message hasta encontrar el salto de linea que significa otro "Evento"
        while (!file.eof())
        {
            file >> month >> day >> hour >> ip;

            // ciclo para agregar las palabras restantes del renglon a una sola variable string llamada message
            while (file.peek() != '\n' && file.peek() != EOF)
            {
                string part;
                file >> part;
                message += part + " ";
            }

            // le pase los argumentos traidos del documento al constructor de la clase Event para una instancia y agregarla a un vector de tipo Event
            Event event(month, day, hour, ip, message);
            events.push_back(event);
            message = "";
        }

        events.pop_back();
    }
    catch(string e){
        cout << "Una excepcion ocurrio: " << e << endl;
    }
}



#endif