#ifndef NODE_H
#define NODE_H

// |-------||-------||-------|
// | prev  || data  ||  next |
// |_______||_______||_______|


template <class T>
class Node{
public:
    T data;
    Node<T>* next;
    Node<T>* prev;
    
    Node();
    Node(const T&);
    Node(const T&, Node<T>*);
    Node(const T&, Node<T>*, Node<T>*);
};

template <class T>
Node<T>::Node():next(nullptr),prev(nullptr){}

template <class T>
Node<T>::Node(const T& _data):data(_data), next(nullptr), prev(nullptr){}

template <class T>
Node<T>::Node(const T& _data, Node<T>* _next):data(_data),next(_next){}


template <class T>
Node<T>::Node(const T& _data, Node<T>* _prev, Node<T>* _next):data(_data),prev(_prev),next(_next){}


#endif
