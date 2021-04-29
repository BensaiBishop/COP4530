//
// Created by bensa on 21-Jan-21.
//

#ifndef UNTITLED2_TLIST_HPP
#define UNTITLED2_TLIST_HPP
#include <iostream>
#include <utility>
#include <string>
#include "tlist.h"

using namespace std;
//************************************
//*        TList definitions         *
//************************************
template<typename T>
TList<T>::TList(){                  //create empty linked list
    size=0;
    first= nullptr;
    last=nullptr;
}

template<typename T>
TList<T>::TList(T val, int num){    //create list with num copies of val
    size=0;
    first=nullptr;
    last=nullptr;
    for (int i=0;i<num;i++){
        InsertBack(val);
    }
}

template<typename T>
TList<T>::~TList(){                 //deconstructor
    Clear();
    delete last;
    delete first;
}

template<typename T>
TList<T>::TList(const TList &L) {   //copy constructor
    if (L.first == nullptr) {
        first = last = nullptr;
        size=0;
    }
    else{
        first=new Node<T>(L.first);
        Node<T>* tempL =L.first->next;
        Node<T>* temp =first;
        while (tempL != nullptr){
            temp->next = new Node<T>(tempL, nullptr, temp);
            temp=temp->next;
            tempL=tempL->next;
            ++size;
        }
        last=temp;
    }
}

template<typename T>
TList<T> &TList<T>::operator=(const TList &L) {       //copy assignment operator
    if (this==&L)
    return *this;
    while (L.first->next!=nullptr){
        Node<T>* temp = L.first->next;
        InsertBack(temp->data);
        L.first->next=temp->next;
    }
    return* this;
}

template<typename T>
TList<T>::TList(TList &&L) {            //move constructor
    first=L.first;
    L.first= nullptr;
    last=L.last;
    L.last= nullptr;
    size=L.size;
    L.size=0;
}

template<typename T>
TList<T> &TList<T>::operator=(TList &&L) {     //move assignment operator
    return *this;
}

template<typename T>
bool TList<T>::IsEmpty() const {    //checks to see whether list is empty
    return first == nullptr;
}

template<typename T>
void TList<T>::Clear() {            //clear list
    Node<T>* temp =first;
    while (temp != nullptr){
        Node<T>* discard = temp;
        delete discard;
    }
    first = last= nullptr;
}

template<typename T>
int TList<T>::GetSize() const {     //return size
    return size;
}

template<typename T>
void TList<T>::InsertFront(const T &d) {    //insert data d as first element
    if (first != nullptr){
        first = new Node<T>(d);
        first->next->prev=first;
    }
    else
        first=last=new Node<T>(d);      //if empty
}

template<typename T>
void TList<T>::InsertBack(const T &d) {     //insert data d as last element
    if (last != nullptr){
        last=new Node<T>(d);
        last->prev->next=last;
    }
    else
        first=last= new Node<T>(d);     //if empty
}

template<typename T>
void TList<T>::RemoveFront() {      //remove first element from the list
    if (first==last){               //if empty
        delete first;
        first=last= nullptr;
    }
    else {
        first=first->next;
        delete first->prev;
        first->prev= nullptr;
    }
}

template<typename T>
void TList<T>::RemoveBack() {       //remove last element from the list
    if (first==last){               //if empty
        delete first;
        first=last= nullptr;
    }
    else{
        last=last->prev;
        delete last->next;
        last->next= nullptr;
    }
}

template<typename T>
T &TList<T>::GetFirst() const {     //return data from first
    return first->data;
}

template<typename T>
T &TList<T>::GetLast() const {      //return data from last
    return last->data;
}
template<typename T>
TListIterator<T> TList<T>::GetIterator() const {    //return iterator to first item my 'begin()' function
    return TListIterator<T>(first);
}
template<typename T>
TListIterator<T> TList<T>::GetIteratorEnd() const {     //return iterator to the last item  my 'end() function'
    return TListIterator<T>(last);
}

template<typename T>
void TList<T>::Insert(TListIterator<T> pos, const T &d) {   //insert data d at pos
    Node<T>* newNode = new Node<T>(d,pos.ptr->next);
    if (pos.ptr==last) last = newNode;
    pos.ptr->next=newNode;
}

template<typename T>
TListIterator<T> TList<T>::Remove(TListIterator<T> pos) {      //remove data d at pos
    Node<T>* discard=pos.ptr->next;
    pos.ptr->next=pos.ptr->next->next;
    if (discard == last) last=pos.ptr;
    delete discard;
    return pos;
}

//************************************
//*   TListIterator definitions      *
//************************************

template<typename T>
TListIterator<T>::TListIterator():ptr(nullptr){}    //default constructor for iterator

template<typename T>
bool TListIterator<T>::HasNext() const {    //return true if the next item isn't nullptr
    if (ptr->next!= nullptr){return true;}
    else{return false;}
}

template<typename T>
bool TListIterator<T>::HasPrevious() const {      //return true if prev item isn't nullptr.
    if (ptr->prev!= nullptr){return true;}
    else{return false;}
}

template<typename T>
TListIterator<T> TListIterator<T>::Next() {     //advance to next item
    if (HasNext()){
        ptr=ptr->next;
    }
    else{
        cout<<"Error: No item to advance to";
        exit(1);
    }
}

template<typename T>
TListIterator<T> TListIterator<T>::Previous() {     //regress to previous item
    if (HasPrevious()){
        ptr=ptr->prev;
    }
    else{
        cout<<"Error: No item to recede to";
        exit(1);
    }
}

template<typename T>
T &TListIterator<T>::GetData() const {              // return data
    return ptr->data;
}
//***************************************
//*      definition of ostream          *
//***************************************
template<typename T>
void TList<T>::Print(ostream &os, char delim) const {       //prints the list in order
    for (auto ptr= GetIterator(); ptr != GetIteratorEnd() ; ptr++) {
        os<<*ptr<<delim;
    }
}
#endif //UNTITLED2_TLIST_HPP
