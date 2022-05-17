#ifndef _NODE_H_
#define _NODE_H_

template <class T>
class Node
{
public:
    T data;
    Node<T> *next;
    Node();
    Node(T val);
};

template <class T>
Node<T>::Node()
{
    data = 0;
    next = nullptr;
}
template <class T>
Node<T>::Node(T val)
{
    data = val;
    next = nullptr;
}

#endif // _NODE_H_