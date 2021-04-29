// Assignment 3
// Created on 16-Feb-21.
// Benjamin Bishop

#ifndef STACK_H
#define STACK_H
#include <iostream>
#include <utility>
#include <initializer_list>
#include "node.h"
namespace cop4530{

    template<class T> class iterator;

    template<class T>
class Stack{
    friend class iterator<T>;
    /*
private:
    // nested Node class
    struct Node {
        T data;// maybe unused
        Node *next;

        Node(const T &d = T{},  Node *n = nullptr)
                : data{d}, next{n} {}

        Node(T &&d, Node *n = nullptr)
                : data{std::move(d)}, next{n} {}
    };
*/
    //code sourced from lectures
    public:
        Stack(); //zero-argument constructor.
        ~Stack (); //destructor.
        Stack (const Stack&); //copy constructor.
        Stack(Stack &&); //move constructor.
        Stack& operator= (const Stack &); //copy assignment operator=.
        Stack & operator=(Stack &&); //move assignment operator=
        bool empty() const; //returns true if the Stack contains no elements, and false otherwise.
        void clear(); //all elements from the stack.
        void push(const T& x); //adds x to the Stack. copy version.
        void push(T && x); //adds x to the Stack. move version.
        void pop(); //removes and discards the most recently added element of the Stack.
        T& top(); //returns a reference to the most recently added element of the Stack (as a modifiable L-value).
        const T& top() const; //accessor that returns the most recently added element of the Stack (as a const reference)
        int size() const; //returns the number of elements stored in the Stack.
        void print(std::ostream& os, char ofc = ' ')const;

        iterator<T>*begin() {return head;};

        friend std::ostream& operator<< (std::ostream& os, const Stack<T>& a){//invokes the print() method
            a.print(os);
            return os;
        };
        friend bool operator == (const Stack<T>& a, const Stack<T> & b){//returns true if the two compared Stacks have the same elements, in the same order, and false otherwise
            if (a.size() == b.size()){
                Stack<T> lhs = a, rhs=b;
                while (!lhs.empty() && !rhs.empty()){
                    if (lhs.top() != rhs.top())
                        return false;
                    lhs.pop();
                    rhs.pop();
                }
                return true;
            }
            else
                return false;
        };
        friend bool operator!= (const Stack<T>& a, const Stack<T> & b){//opposite of operator==().
            return(!(a==b));
        };
        friend bool operator<= (const Stack<T>& a, const Stack<T> & b){//returns true if every element in Stack a is smaller than or equal to the corresponding element of Stack b
            if (a==b)
                return true;
            Stack<T> lhs=a, rhs=b;
            while (!lhs.empty()){
                if (rhs.empty())
                    return true;
                if (lhs.top() > rhs.top())
                    return false;
                lhs.pop();
                rhs.pop();
            }
            return true;
        };
    private:

        int theSize;
        Node<T> *head;
        void init();
};

    template<class T>
    class iterator{
        friend class Stack<T>;
    public:
        iterator(){current=nullptr;};
        iterator(const Stack<T>&s){current=s.head;};
        bool hasNext()const;
        bool hasPrev()const;
        void getNext();
        void getPrev();
        T& getData();

    private:
        Node<T> *current;
    };

#include "stack.hpp"
}//end of cop4530 namespace
#endif //STACK_H
