#include <iostream>
#include "LinkedList.h"
using std::cout;
using std::endl;
using std::string;

int main()
{

    cout << "\nIniciamos la lista lista1 ligada de tipo int con los siguientes valores:" << endl;
    LinkedList<int> lista1;
    lista1.addFirst(3);
    lista1.addFirst(6);
    lista1.addFirst(14);
    lista1.addFirst(23);
    lista1.addFirst(8);
    lista1.addFirst(18);
    lista1.printList();
    cout << endl
         << endl;

    cout << "findData() Busca un elemento en la lista y regresa el indice en el que se encuentra el elemento" << endl;
    cout << "Elemento a buscar: 23" << endl;
    cout << "Indice: " << lista1.findData(23) << endl
         << endl
         << endl;

    cout << "Sobrecarga operador []. Leer y/o actualizar un elemento en una posición dada." << endl;
    cout << "Leeremos el elemento en la posicion 3: " << lista1[3] << endl;
    cout << "Asignaremos el valor 17 a la posición 3, para reemplazar al 14 e imprimir de nuevo la lista" << endl;
    lista1[3] = 17;
    lista1.printList();
    cout << endl
         << endl;

    cout << "Sobrecarga operador =. Actualiza la lista con base en otra lista." << endl;
    cout << "Creamos la nueva lista lista2: " << endl;
    LinkedList<int> lista2;
    lista2.addFirst(23);
    lista2.addFirst(6);
    lista2.addFirst(14);
    lista2.addFirst(35);
    lista2.printList();

    cout << "Igualamos lista2 a lista1" << endl;
    lista2 = lista1;

    cout << "Y volvemos a imprimir lista2 para observar la diferencia" << endl;

    lista2.printList();
}