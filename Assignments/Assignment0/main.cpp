//Provided by Dr. David A. Gaitros
//Modified by Benjamin Bishop on 9-Jan-2021
//The following is a copy of the output through the g++ terminal.

/*
bbishop@linprog6.cs.fsu.edu:~/COP4530/Assign_0>ls
main.cpp  makefile  stack.h
bbishop@linprog6.cs.fsu.edu:~/COP4530/Assign_0>make
g++ -std=c++11 -c main.cpp
g++ -std=c++11 -c stack.h
g++ -std=c++11 main.o -o exe
bbishop@linprog6.cs.fsu.edu:~/COP4530/Assign_0>exe
Assignment #0 Test Program
Stack overflow!
Size of Bool2 is: 2
The number of elements in Bool2 is: 2
Top element of Bool2 is: 0
Size on Double8 should be 8: 8
Test Pop on Char10, should produce a 'C': C
Test ostream overload on Char10, should be a 'C': C

Test ostream overload on Char10, should be a 'B': B

Test ostream overload on Char10, should be a 'A': A

Test ostream overload on Char10, should be an error: Empty Stack
*/

#include <iostream>
#include <string>
#include "stack.h"

using namespace std;

int main(void) {


    cout << "Assignment #0 Test Program" << endl;

    Stack<char> Char10;                                                                                          // Test Character Stack, Default constructor
    Stack<float> Float5(5);                                                                                     // Test Float Stack
    Stack<double> Double8(8);                                                                          // Test Double Stack
    Stack<bool> Bool2(2);                                                                                     // Test Bool Stack
    Bool2.Push(true);                                                                                               // Test Push on Bool
    Bool2.Push(false);                                                                                             // Test Push on Bool
    Bool2.Push(true);                                                                                             // Test error on Push
    cout << "Size of Bool2 is: "<< Bool2.Size()<<endl;
    cout << "The number of elements in Bool2 is: "<<Bool2.Number()<<endl;
    cout << "Top element of Bool2 is: " << Bool2.Top() <<endl;
    cout << "Size on Double8 should be 8: "<< Double8.Size()<<endl;
    Char10.Push('A');
    Char10.Push('B');
    Char10.Push('C');
    cout << "Test Pop on Char10, should produce a 'C': ";
    Char10.Pop();
    Char10.Push('C');
    cout << "Test ostream overload on Char10, should be a 'C': ";
    cout <<Char10<< endl;
    cout << "Test ostream overload on Char10, should be a 'B': ";
    cout <<Char10<< endl;
    cout << "Test ostream overload on Char10, should be a 'A': ";
    cout <<Char10<< endl;
    cout << "Test ostream overload on Char10, should be an error: ";
    cout <<Char10<< endl;
    return 0;
}
