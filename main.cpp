//Este programa lee un archivo llama bitacora_ordenada txt el cual contiene fechas correspondientes a ciertos eventos en un formato 
//Ejemplo: Aug 4 03:18:56, se le preguntta al usuario fechas de inicio y fin para su busqueda, dichos resultados seran escritos en orden en el archivo bitacora_ordenada
//en caso de que las fechas inicio o fin del usuario no esten en el archivo, se le comunicaras
//Pablo Elias Ramirez Martinez A01702872
//Leonardo Gonzalez Guerra A01721434
//Realizada Miercoles 30 de Marzo

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


void merge(vector<Event> &events, int begin, int m, int end)
{
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

void ordenaMerge(vector<Event> &events, int begin, int end)
{
    if (begin < end)
    {
        int m = begin + (end - begin) / 2;
        ordenaMerge(events, begin, m);
        ordenaMerge(events, m + 1, end);
        merge(events, begin, m, end);
    }
}

int busquedaBinaria(vector<Event> &events, time_t k)
{
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

    return -1;
}

//Esta funcion regresa un tipo time_t, regresa el tiempo en segundos que han pasado desde el primero de Enero de 1970
//Es usada para conocer el time_ de la fecha de inicio y final ingresada por el usuario
time_t getDate(string month_, int day, string hour)
{

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

//Esta funcion escribe los datos de los "eventos" dentro del vector que se encuentran entre los indices inicio y final en el documento 
void printEvents(vector<Event> &events, int indexInicio, int indexFinal)
{
    ofstream outdata; // outdata es como cin

    outdata.open("bitacora_ordenada.txt"); // abre el archivo
    if (!outdata)
    { // por si el archivo no se puede abrir
        cerr << "Error: file could not be opened" << endl;
        exit(1);
    }

//Iteramos por todo el vector para escribirlos en el archivo
    for (int i = indexInicio; i < indexFinal + 1; i++)
    {
        outdata << events[i].getMonth() << " " << events[i].getDay() << " " << events[i].getHour() << " " << events[i].getIp() << " " << events[i].getMessage() << endl;
    }
}

int main()
{
    string month, hour, ip, message;
    int day, indexInicio, indexFinal;
    time_t inicio, final;
    vector<Event> events;

    // abrir documento bitacora
    ifstream file;
    file.open("bitacora.txt");

    // por si no se puede abrir el documento
    if (!file)
    {
        cerr << "Error while opening the file" << endl;
        return 1;
    }

   // ciclo para agregar las palabras restanttes del renglon a una sola variable string llamada message hasta encontrar el salto de linea que significa otro "Evento"
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

    ordenaMerge(events, 0, events.size() - 1); //Oordenamos por fecha el Vector

    cout << "_________________________________________Bienvenido____________________________________________" << endl;
    cout << "Favor ingresar la fecha de inicio para su busqueda en el siguiente formato:" << endl;
    cout << "Mes en formato de 3 letras(primera letra mayuscula), numero del dia y hora en formato hh:mm:ss" << endl;
    cout << "Ejemplo: Aug 4 03:18:56" << endl;
    cin >> month >> day >> hour;
    inicio = getDate(month, day, hour);
    indexInicio = busquedaBinaria(events, inicio);
    if(indexInicio == -1){
        cout << "Fecha no encontrada" << endl;
        return -1;
    }

    cout << "Favor ingresar la fecha de fin para su busqueda en el mismo formato:" << endl;
    cin >> month >> day >> hour;
    final = getDate(month, day, hour);
    indexFinal = busquedaBinaria(events, final);
    if(indexFinal == -1){
        cout << "Fecha no encontrada" << endl;
        return -1;
    }

    printEvents(events, indexInicio, indexFinal);
}
