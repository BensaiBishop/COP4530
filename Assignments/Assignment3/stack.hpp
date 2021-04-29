

// Assignment 3
// Created on 16-Feb-21.
// Benjamin Bishop

#ifndef UNTITLED3_STACK_HPP
#define UNTITLED3_STACK_HPP
template<class T>
Stack<T>::Stack() { //default constructor
    init();
}

template<class T>
Stack<T>::~Stack() {//deconstructor
    clear();
    delete head;
}

template<class T>
Stack<T>::Stack(const cop4530::Stack<T> & rhs) {//copy constructor
  *this=rhs;
}

template<class T>
Stack<T>::Stack(Stack &&rhs) {
    *this=rhs;
}

template<class T>
Stack<T> &Stack<T>::operator=(const Stack &rhs) {
   Stack<T> copy =rhs;
   std::swap(*this,copy);
   return *this;
}

template<class T>
Stack<T> &Stack<T>::operator=(Stack &&rhs) {
    Stack<T> s;
    std::swap(head,rhs.head);
    std::swap(s,rhs);
    return *this;
}

template<class T>
bool Stack<T>::empty() const {
    if (theSize==0){
        return true;
    }
    else
        return false;
}

template<class T>
void Stack<T>::clear() {
    while (!empty()){
        pop();
    }
}

template<class T>
void Stack<T>::push(const T &x) {
    Node<T> *element = new Node<T>(x);
    element->next=head;
    head=element;
    ++theSize;
}

template<class T>
void Stack<T>::push(T &&x) {
    Node<T> *element = new Node<T>(x);
    element->next=head;
    head=element;
    ++theSize;
}

template<class T>
void Stack<T>::pop() {
    if (empty()){
        std::cout<<"empty stack;";
        return;
    }
    Node<T> *temp = head->next; //get the next in line element
    delete head;    //delete prev head
    head=temp;  //assign new head
    --theSize;
}

template<class T>
T& cop4530::Stack<T>::top(){
    //return head; //this thing I don't get it.
}

template<class T>
const T &Stack<T>::top() const {
    return head;
}

template<class T>
int Stack<T>::size() const {
    return theSize;
}

template<class T>
void Stack<T>::print(std::ostream &os, char ofc) const {

    for(auto itr = 0;itr<theSize; ++itr)
        os << itr << ofc;
}

template<class T>
void Stack<T>::init() {
    theSize=0;
    head= nullptr;
}


template<class T>
bool iterator<T>::hasNext() const {
    if (current->next!= nullptr)
        return true;
    else
        return false;
}

template<class T>
bool iterator<T>::hasPrev() const {
    if (current->prev!= nullptr)
        return true;
    else
        return false;
}

template<class T>
void iterator<T>::getNext() {
    if (hasNext()!= false)
        return(current->next);
}

template<class T>
void iterator<T>::getPrev() {
    if (hasPrev()!= false)
        return(current->prev);
}

template<class T>
T &iterator<T>::getData() {
    return *current;
}
#endif //UNTITLED3_STACK_HPP
