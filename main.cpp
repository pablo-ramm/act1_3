// Este programa lee un archivo llama bitacora_ordenada txt el cual contiene fechas correspondientes a ciertos eventos en un formato
// Ejemplo: Aug 4 03:18:56, se le preguntta al usuario fechas de inicio y fin para su busqueda, dichos resultados seran escritos en orden en el archivo bitacora_ordenada
// en caso de que las fechas inicio o fin del usuario no esten en el archivo, se le comunicaras
// Pablo Elias Ramirez Martinez A01702872
// Leonardo Gonzalez Guerra A01721434
// Realizada Miercoles 30 de Marzo

#include <iostream>
#include <vector>
#include <time.h>
#include <fstream>
#include "Event.h"
#include "Bitacora.h"
using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::string;
using std::time_t;
using std::vector;
#include <cstdlib>

int main()
{
    string month, hour, ip, message;
    int day, indexInicio, indexFinal;
    time_t inicio, final;
    vector<Event> events;
    Bitacora bitacora;

    // este metodo abre y lee un documento para guardar estos eventos en el vector pasado como argumento
    bitacora.openFile(events);

    bitacora.ordenaMerge(events, 0, events.size() - 1); // Oordenamos por fecha el Vector
    bitacora.writeEvents(events);

    cout << "_________________________________________Bienvenido____________________________________________" << endl;
    cout << "Favor ingresar la fecha de inicio para su busqueda en el siguiente formato:" << endl;
    cout << "Mes en formato de 3 letras(primera letra mayuscula), numero del dia y hora en formato hh:mm:ss" << endl;
    cout << "Ejemplo: Aug 4 03:18:56" << endl
         << "Fecha 1: ";
    cin >> month >> day >> hour;
    inicio = bitacora.getDate(month, day, hour);
    indexInicio = bitacora.busquedaBinaria(events, inicio);

    cout << "Favor ingresar la fecha de fin para su busqueda en el mismo formato:" << endl
         << "Fecha 2: ";
    cin >> month >> day >> hour;
    final = bitacora.getDate(month, day, hour);
    indexFinal = bitacora.busquedaBinaria(events, final);

    cout << "\n\nResultado: " << indexFinal - indexInicio + 1 << " registros" << endl;
    bitacora.printEvents(events, indexInicio, indexFinal);
}
