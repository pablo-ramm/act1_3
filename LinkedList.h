#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_

#include <iostream>
#include <stdexcept>
#include "Node.h"

template <class T>
class LinkedList
{
private:
  Node<T> *head;
  int numElements;

public:
  LinkedList();
  ~LinkedList();
  int getNumElements();
  void printList();
  void addFirst(T value);
  void addLast(T value);
  bool deleteData(T value);
  bool deleteAt(int position);
  T getData(int position);
  void updateData(T value, T newValue);
  int findData(T value);
  void updateAt(int posicion, T value);

  // overloading
  T &operator[](int position);
  void operator=(LinkedList<T> &list);
};

template <class T>
LinkedList<T>::LinkedList()
{

  head = nullptr;
  numElements = 0;
}

template <class T>
LinkedList<T>::~LinkedList()
{

  Node<T> *p, *q;
  p = head;
  while (p != nullptr)
  {
    q = p->next;
    delete p;
    p = q;
  }
  head = nullptr;
  numElements = 0;
}
template <class T>
int LinkedList<T>::getNumElements()
{
  return numElements;
}

template <class T>
void LinkedList<T>::printList()
{
  Node<T> *ptr = head;
  while (ptr != nullptr)
  {
    std::cout << ptr->data << " ";
    ptr = ptr->next;
  }
  std::cout << std::endl;
}

template <class T>
void LinkedList<T>::addFirst(T value)
{
  Node<T> *newNode = new Node<T>(value);
  newNode->next = head;
  head = newNode;
  numElements++;
}

template <class T>
void LinkedList<T>::addLast(T value)
{
  if (head == nullptr)
  {
    addFirst(value);
  }
  else
  {
    Node<T> *newNode = new Node<T>(value);
    Node<T> *p = head;
    while (p->next != nullptr)
    {
      p = p->next;
    }
    newNode->next = nullptr;
    p->next = newNode;
    numElements++;
  }
}

template <class T>
bool LinkedList<T>::deleteData(T value)
{
  Node<T> *p = head;
  Node<T> *prev = nullptr;
  // head existe y contiene a value
  if (p != nullptr && p->data == value)
  {
    head = p->next;
    delete p;
    numElements--;
    return true;
  }
  else
  {
    // buscar value en la lista
    while (p != nullptr && p->data != value)
    {
      prev = p;
      p = p->next;
    }
    // si no existe value en la lista
    if (p == nullptr)
      return false;
    prev->next = p->next;
    delete p;
    numElements--;
    return true;
  }
}

template <class T>
bool LinkedList<T>::deleteAt(int position)
{
  if (position < 0 || position >= numElements)
  {
    throw std::out_of_range("Indice fuera de rango");
  }
  else
  {
    Node<T> *p = head, *prev;
    // Si se debe borrar head
    if (position == 0)
    {
      head = p->next;
      delete p;
      numElements--;
      return true;
    }
    // Si se debe borrar algun otro nodo
    // Encontrar el nodo previo
    p = head;
    prev = nullptr;
    int index = 0;
    // buscar value en la lista
    while (index != position)
    {
      prev = p;
      p = p->next;
      index++;
    }
    prev->next = p->next;
    delete p;
    numElements--;
    return true;
  }
}

template <class T>
T LinkedList<T>::getData(int position)
{
  if (position < 0 || position >= numElements)
  {
    throw std::out_of_range("Indice fuera de rango");
  }
  else
  {
    if (position == 0)
      return head->data;
    Node<T> *p = head;
    int index = 0;
    while (p != nullptr)
    {
      if (index == position)
        return p->data;
      index++;
      p = p->next;
    }
    return -1;
  }
}

template <class T>
void LinkedList<T>::updateData(T value, T newValue)
{
  Node<T> *p = head;
  // buscar value en la lista
  while (p != nullptr)
  {
    if (p->data == value)
    {
      p->data = newValue;
      break;
    }
    p = p->next;
  }
  // Si value no existe en la lista
  if (p == nullptr)
    throw std::out_of_range("Valor no encontrado en la lista");
}

template <class T>
void LinkedList<T>::updateAt(int posicion, T value)
{
  int i = 0;
  Node<T> *ptr = head;
  while (ptr != nullptr && i != posicion)
  {
    ptr = ptr->next;
    i++;
  }
  if (ptr == nullptr)
  {
    throw std::out_of_range("Posicion no encontrado en la lista");
  }
  else
  {
    ptr->data = value;
  }
}

// encuentra un elemennto dado en la lista
// Entrada: El elemento a buscar
// Salida: El indice donde se encuentra el elemento, sino existe regresa -1
template <class T>
int LinkedList<T>::findData(T value)
{
  int posicion = 0;
  Node<T> *ptr = head;
  while ((ptr != nullptr) && (ptr->data != value))
  {
    ptr = ptr->next;
    posicion++;
  }
  if (ptr == nullptr)
  {
    return -1;
  }
  else
  {
    return posicion;
  }
}

// sobrecarga operador [], Leer y/o actualizar un elemento en la posicion indicada entre parentesis
// entrada: posición a la que quieres acceder en la lista ligada
// salida: referencia del elemento que se encuentra en la posicion de entrada
template <class T>
T &LinkedList<T>::operator[](int position)
{
  if (position < 0 || position >= numElements)
  {
    throw std::out_of_range("Indice fuera de rango");
  }
  else
  {
    if (position == 0)
      return head->data;
    Node<T> *ptr = head;
    int i = 0;
    while (ptr != nullptr && i != position)
    {
      ptr = ptr->next;
      i++;
    }
    return ptr->data;
  }
}

// Este operador copia la linkedlist del lado derecho de la igualdad en la linked list del lado izquierdo
// Entrada: una lista ligada
// salida: no regresa nada en si pero terminamos con una lista ligada
template <class T>
void LinkedList<T>::operator=(LinkedList<T> &list)
{
  // variable que representa diferencia en tamaños de ambas listas
  int sizeDiference = this->getNumElements() - list.getNumElements();

  // si la lista del lado izquierdo de la igualdad es igual o mas grande que la de la derecha
  if (sizeDiference >= 0)
  {
    // primero borramos algunos nodos para que queden del mismo tamaño
    for (int i = 1; i <= sizeDiference; i++)
    {
      this->deleteAt(0);
    }
    // finalmente copiamos cada valor del nodo en la lista derecha en los nodos de la lista la derecha de la igualdad
    for (int i = 0; i < list.getNumElements(); i++)
    {
      this->updateAt(i, list.getData(i));
    }
  }
  // si la lista del lado izquierdo de la igualdad es mas corta
  else
  {
    for (int i = 0; i < list.getNumElements(); i++)
    {
      // actualizamos en la lista los valores que se puedan con el tamaño actual
      if (i < this->getNumElements())
      {
        this->updateAt(i, list.getData(i));
      } // si ya hemos copiado todos los elementos posibles en la iquierda, agregamos los restantes
      else
      {
        this->addLast(list.getData(i));
      }
    }
  }
}

#endif // _LINKEDLIST_H_