/**
 * @file DoublyLinkedList.h
 * @author Christopher Liudahl-Rackley and Mohamed Elfergani
 * @brief DoublyLinkedList class
 * @version 4.0
 * @date 2021-11-07 
 */

#ifndef DOUBLY_LINKED_LIST
#define DOUBLY_LINKED_LIST

#include "Node.h"
#include <string>
#include <iostream>
using namespace std;

template <class T>
class DoublyLinkedList 
{
protected:      
    Node<T>* first;      //a pointer to the first of the linked list
    Node<T>* last;       //a pointer to the last node of the linked list
    Node<T>* iterator;   //an internal iterator for the linked list object
    int length;          //number of items in the linked list
public:
    //default no-argument constructor
    DoublyLinkedList();
    //destructor
    ~DoublyLinkedList();
    //copy constructor
    DoublyLinkedList(const DoublyLinkedList<T>&);
    //copy assignment operator
    DoublyLinkedList& operator=(const DoublyLinkedList<T>&);
    //initializes an empty list
    void init();
    //returns true if the list is empty, false otherwise
    bool isEmpty();
    //returns the number of items in the list
    int getLength();
    //inserts a new item to the beginning of the list
    void insertFirst(const T&);
    //inserts a new item at the beggining of the list
    void insertLast(const T&);
    //deletes the first item from the list
    void deleteFirst();
    //deletes the last item in the list
    void deleteLast();
    //destroys the list and makes it empty
    void clear();
    //iterator functions
    //sets the iterator to the beginning of the linked list
    void setIteratorFirst();
    //sets the iterator to the end of the linked list
    void setIteratorLast();
    //checks if the iterator has next
    bool hasNext();
    //checks if the iterator has prev
    bool hasPrev();
    //sets the iterator to the next node
    void next();
    //sets the iterator to the previous node
    void prev();
    //returns true if the iterator is null
    bool isIteratorNULL();
    //gets the data the iterator pointing at
    T getData();

    //friend functions
    template <class U>
    friend std::ostream& operator<<(std::ostream& out, const DoublyLinkedList<U>& dll) 
    {
        dll.setIteratorFirst();
        while (!dll.isIteratorNULL()) 
        {
            out << dll.getData();
            dll.next();
        }

        return out;
    }

    //overloading operator>>
    template <class U>
    friend istream& operator>>(istream& in, DoublyLinkedList<U>& dll) 
    {
        dll.setIteratorLast();
        while(!dll.isIteratorNULL()) 
        {
            in >> dll.getData();
            dll.prev();
        }

        return in;
    }

};

// constructors
template <class T>
DoublyLinkedList<T>::DoublyLinkedList():first(nullptr),last(nullptr),iterator(nullptr),length(0){}

template <class T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList<T>& other) 
{
    *this = other;
}

template <class T>
DoublyLinkedList<T>::~DoublyLinkedList() 
{ 
    clear();
    delete first;
    delete last;
    delete iterator;
    length = 0;
}

template <class T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(const DoublyLinkedList<T> &other) {
    if(this != &other)
    {
        clear();
        other.setIteratorLast();

        while(!isIteratorNULL())
        {
            insertLast(other.getData());
            if(hasPrev())
                prev();
            else    
                iterator = nullptr;
        }
        // assign other's length to this's length
        length = other.getLength();
    }
    // afterwards this will return the new (*this) DoublyLinkedList<T>;
    return *this;
}

//initializes an empty list
template <class T>
void DoublyLinkedList<T>::init() 
{
    first->data = NULL;
    first = nullptr;
    first = nullptr;
    last->data = NULL;
    last = nullptr;
    last = nullptr;
    iterator->data = NULL;
    iterator = nullptr;
    iterator = nullptr;
}

//returns true if the list is empty, false otherwise
template <class T>
bool DoublyLinkedList<T>::isEmpty() 
{
    return first == nullptr;
}

template <class T>
int DoublyLinkedList<T>::getLength() {
    return length;
}

template <class T>
void DoublyLinkedList<T>::insertFirst(const T& _item) 
{
    Node<T>* newItem;
    newItem = new Node<T>();
    if(first == nullptr)
    {
        first = newItem;
        newItem->prev = nullptr;
        newItem->data = _item;
        newItem->next = nullptr;
        last = newItem;
    }
    else
    {
        newItem->next = first;
        newItem->data = _item;
        newItem->prev = nullptr;
        first->prev = newItem;
        first = newItem;
    }
    length++;
}

//inserts a new item at the end of the list
template <class T>
void DoublyLinkedList<T>::insertLast(const T& _item) 
{
    Node<T>* newItem;
    newItem = new Node<T>();
    newItem->data = _item;

    if(first == nullptr)
    {
        first = newItem;
        newItem->prev=nullptr;
        newItem->next=nullptr;
        last=newItem;
    }
    else
    {
        newItem->prev=last;
        last->next=newItem;
        newItem->next=nullptr;
        last=newItem;
    }
    length++;
}

//deletes the first item from the list
template <class T>
void DoublyLinkedList<T>::deleteFirst() 
{
    if(first == nullptr){}
    if(first == last)///one element in the list
    {
        Node<T>* cur;
        cur=first;
        first=nullptr;
        last = nullptr;
        delete cur;
    }
    else
    {
        Node<T>* cur;
        cur=first;
        first=first->next;
        first->prev=NULL;
        delete cur;
    }
    length--;
}

//deletes the last item in the list
template <class T>
void DoublyLinkedList<T>::deleteLast() 
{
    if( first == last)
    {
        Node<T>* cur;
        cur = first;
        first = nullptr;
        last = nullptr;
        delete cur;
    }
    else
    {
        Node<T>* cur;
        cur = last;
        last = last->prev;
        last->next=nullptr;
        delete cur;
    }

    length--;
}

//destroys the list and makes it empty
template <class T>
void DoublyLinkedList<T>::clear() 
{
    setIteratorFirst();
    while(!isIteratorNULL()) 
    {
        deleteFirst();
        if(hasNext())
            next();
        else    
            iterator = nullptr;
    }
}

template <class T>
void DoublyLinkedList<T>::setIteratorFirst() 
{
    iterator = first;
}

//sets the iterator to the end of the linked list
template <class T>
void DoublyLinkedList<T>::setIteratorLast() 
{
    iterator = last;
}

//checks if the iterator has next
template <class T>
bool DoublyLinkedList<T>::hasNext() 
{
    return iterator->next != nullptr;
}

//checks if the iterator has prev
template <class T>
bool DoublyLinkedList<T>::hasPrev() 
{
    return iterator->prev != nullptr;
}

//sets the iterator to the next node
template <class T>
void DoublyLinkedList<T>::next() 
{
    if(isEmpty()) 
    {
        // throw new NoSuchElementException();
        return;
    }
    if (hasNext())
        iterator = iterator->next;
}

//sets the iterator to the previous node
template <class T>
void DoublyLinkedList<T>::prev() 
{
    if(isEmpty()) 
    {
        // throw new NoSuchElementException();
        return;
    }
    if (hasPrev())
        iterator = iterator->prev;
}

//returns true if the iterator is null
template <class T>
bool DoublyLinkedList<T>::isIteratorNULL() 
{
    return iterator == nullptr;
}

//gets the data the iterator pointing at
template <class T>
T DoublyLinkedList<T>::getData() 
{
    return iterator->data;
}

#endif

