//
// Created by bensa on 07-Jan-21.
//

#ifndef UNTITLED_STACK_H
#define UNTITLED_STACK_H
// Created by David A Gaitros on 10/15/19.
// ********************************************************************
// * Name: Stack Class                                                                                               *
// * Description: A template Stack class designed to be used with *
// * any simple C++ type to include floating point, double                   *
// * floating point, character, and Boolean.                                                    *
// * The stack pointer, as is the convention, points to the last            *
// * or highest element in the array. So if you allocate 100                  *
// * elements of type "T" then the first empty element will be 99. *
// * Author: Dr. David A. Gaitros                                                                         *
// * Date: January 19, 2019 *
// ********************************************************************
#include <iostream>
using namespace std;

const int DEFAULTSIZE=100;
template <class T>
class Stack {
public:
    Stack();                                              // Default Constructor, stack is size 100.
    Stack(const int size);                // Constructor, creates stack of size "size"
    Stack(const Stack & Obj);     // Copy constructor
    bool Full();                                     // Return true if the stack is full
    bool Empty();                               // Return true if the stack is empty
    int Size();                                        // Return the size of the stack
    int Number();                              // Return the number of elements stored
    T Top();                                           // Returns the top element, does not pop it
    bool Push (const T item);    // Put an item on the stack
    bool Pop();                                   // Pop an item off and display to std out
    friend ostream &operator <<(ostream & os, Stack<T> &s)  //overloaded "<<" representing pop op to standard output
    {s.Pop();return os;};
    //virtual ~Stack();           //destructor

private:
    T * _stack;                                   // The "stack"
    int _size;                                      // The number of elements the stack can hold
    int _top;                                      // Points to the first empty node
    int _number;                            // The number of elements in the stack.
};

template<class T>           //default stack
Stack<T>::Stack() {
    _top = 0;
    _size = DEFAULTSIZE;
    _stack = new T[_size];
    _number = 0;
}

template<class T>           //constructor of size
Stack<T>::Stack(const int size) {
    _top = 0;
    _size = size;
    _stack = new T[_size];
    _number = size;
}

template<class T>           // copy constructor
Stack<T>::Stack(const Stack & Obj) {
    _top = Obj._top;
    _size = Obj._size;
    _stack = new T[_size];
    _number = Obj._size;

    for (int i = 0; i <= _top; i++) {
        _stack[i] = Obj._stack[i];
    }
}
/*
template <class T>          // destructor
Stack<T>::~Stack() {
    T next;
    while (!Empty())
        next = Pop();
}
*/
template<class T>           //check the top for size
bool Stack<T>::Full() {
    return _top == _size;
}

template<class T>           //check if empty
bool Stack<T>::Empty() {
    return _top == 0;
}

template<class T>           //return size
int Stack<T>::Size() {
    return _size;
}

template<class T>           //return the number of elements
int Stack<T>::Number() {
    return _number;
}

template<class T>           //return top element of stack
T Stack<T>::Top() {
    return _stack[_top];
}

template<class T>           //push function
bool Stack<T>::Push(const T item) {
    if (Full()){     //check if full
        cout<<"Stack overflow!\n";
        return 0;
    }
    _stack[++_top] = item; //redefine the top, and increment stack
}

template<class T>
bool Stack<T>::Pop() {
    if (Empty()){
        cout<<"Empty Stack\n";
        exit(1);
    }
    cout<<Top()<<endl;
    --_top;
}

#endif //UNTITLED_STACK_H
