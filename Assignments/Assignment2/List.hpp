// Assignment 2
// Created by Benjamin Bishop on 02-Feb-21.
// Most code sourced from book and lecture hints

#ifndef ASSIGNENT2REDO_LIST_HPP
#define ASSIGNENT2REDO_LIST_HPP
template<typename T>
List<T>::const_iterator::const_iterator() {
    current=nullptr;
}

template<typename T>
const T &List<T>::const_iterator::operator*() const {
    return retrieve();
}

template<typename T>
typename List<T>::const_iterator &List<T>::const_iterator::operator++() {   //pre
    if(current->next != nullptr){
        current = current->next;
        return *this;
    }
    else
        return *this;
}

template<typename T>
typename List<T>::const_iterator List<T>::const_iterator::operator++(int) { //post
    const_iterator temp=*this;
    if(current->next != nullptr){
        ++(*this);
        return temp;
    }
    else
        return *this;
}

template<typename T>
typename List<T>::const_iterator &List<T>::const_iterator::operator--() { //pre
    if(current->prev != nullptr){
        current = current->prev;
        return *this;
    }
    else
        return *this;
}

template<typename T>
typename List<T>::const_iterator List<T>::const_iterator::operator--(int) { //post
    const_iterator temp=*this;
    if(current->next != nullptr){
        --(*this);
        return temp;
    }
    else
        return *this;
}

template<typename T>
bool cop4530::List<T>::const_iterator::operator==(const List::const_iterator &rhs) const {
    return current==rhs.current;
}

template<typename T>
bool cop4530::List<T>::const_iterator::operator!=(const List::const_iterator &rhs) const {
    return current!=rhs.current;
}

template<typename T>
T &cop4530::List<T>::const_iterator::retrieve() const {
    return this->current->data;
}

template<typename T>
cop4530::List<T>::const_iterator::const_iterator(List::Node *p) {
    current=p;
}
//
//
//
template<typename T>
cop4530::List<T>::iterator::iterator() {
    init();
}

template<typename T>
T &cop4530::List<T>::iterator::operator*() {
    return const_iterator::retrieve();
}

template<typename T>
const T &cop4530::List<T>::iterator::operator*() const {
    return const_iterator::operator*();
}

template<typename T>
typename cop4530::List<T>::iterator &cop4530::List<T>::iterator::operator++() {
    this->current = this->current->next;
    return *this;
}

template<typename T>
typename cop4530::List<T>::iterator cop4530::List<T>::iterator::operator++(int) {
    iterator temp=*this;
    ++(*this);
    return temp;
}

template<typename T>
typename cop4530::List<T>::iterator &cop4530::List<T>::iterator::operator--() {
    this->current = this->current->prev;
    return *this;
}

template<typename T>
typename cop4530::List<T>::iterator cop4530::List<T>::iterator::operator--(int) {
    iterator temp=*this;
    --(*this);
    return temp;
}

template<typename T>
cop4530::List<T>::iterator::iterator(List::Node *p):List<T>::const_iterator::const_iterator(p) {
    this->current=p;
}
//
//
/////////////////////////////////////////////////////////
template<typename T>
cop4530::List<T>::List() {
    init();
}

template<typename T>
cop4530::List<T>::List(const List &rhs) {
    init();
    for (auto itr=rhs.begin();itr!=rhs.end();++itr)
        push_back(*itr);
}

template<typename T>
cop4530::List<T>::List(List &&rhs) {
    theSize = rhs.theSize;
    head = rhs.head;
    tail = rhs.tail;
    rhs.theSize=0;
    rhs.head=nullptr;
    rhs.tail=nullptr;
}

template<typename T>
cop4530::List<T>::List(int num, const T &val) {
    init();
    for (int i = 0; i < num; ++i) {     //add the 'val', 'num' number of times
        push_back(val);
    }
}

template<typename T>
cop4530::List<T>::List(List::const_iterator start, List::const_iterator end) {
    init();
    for (auto itr=start; itr != end; ++itr) {
        push_back(*itr);
    }
}

template<typename T>
cop4530::List<T>::List(std::initializer_list<T> iList) {
    init();
    for(T val : iList)
        push_back(val);
}

template<typename T>
cop4530::List<T>::~List() {
    clear();
    delete head;
    delete tail;
}

template<typename T>
const cop4530::List<T> &cop4530::List<T>::operator=(const List &rhs) {
    clear();
    for(auto itr = rhs.begin; itr != end(); ++itr){
        push_back(*itr);
    }
    return *this;
}

template<typename T>
cop4530::List<T> &cop4530::List<T>::operator=(List &&rhs) {
    std::swap( theSize, rhs.theSize );
    std::swap( head, rhs.head );
    std::swap( tail, rhs.tail );
    return *this;
}

template<typename T>
cop4530::List<T> &cop4530::List<T>::operator=(std::initializer_list<T> iList) {
    init();
    for (T val:iList)
        push_back(val);
}

template<typename T>
int cop4530::List<T>::size() const {
    return theSize;
}

template<typename T>
bool cop4530::List<T>::empty() const {
    if (theSize==0){
        return true;
    }
    else
        return false;
}

template<typename T>
void cop4530::List<T>::clear() {
    while( !empty( ) )
        pop_front( );
}

template<typename T>
void cop4530::List<T>::reverse() {
    if (empty())                    //confusing but it works, I wonder if I could use the swap function? maybe even push back?
        return;
    Node* temp=head;
    head=tail;
    tail=temp;
    Node* tempH=head;
    while (tempH != nullptr){
        temp=tempH->prev;
        tempH->prev=tempH->next;
        tempH->next=temp;
        tempH=tempH->next;
    }
}

template<typename T>
T &cop4530::List<T>::front() {
    return *begin();
}

template<typename T>
const T &cop4530::List<T>::front() const {
    return *begin();
}

template<typename T>
T &cop4530::List<T>::back() {
    return *(--end());
}

template<typename T>
const T &cop4530::List<T>::back() const {
    return *(--end());
}

template<typename T>
void cop4530::List<T>::push_front(const T &val) {   //somehow this doesn't assign a next or prev leading to segmentation fault
    insert(begin(),val);
    /* this doesn't work either, leads to a segmentation fault in the increment operator
    if (!empty()){
        head = new Node(val);
        head->next->prev=head;
    }
    else{
        head=tail= new Node(val);
    }
     */
}

template<typename T>
void cop4530::List<T>::push_front(T &&val) {
    insert(begin(),std::move(val));
/*
    if (!empty()){
        head = new Node(val);
        head->next->prev=head;
    }
    else{
        head=tail= new Node(std::move(val));
    }
    */
}

template<typename T>
void cop4530::List<T>::push_back(const T &val) {
    insert(end(),val);
/*
    if (!empty()){
        tail = new Node(val);
        tail->prev->next=tail;
    }
    else{
        head=tail= new Node(val);
    }
    */
}

template<typename T>
void cop4530::List<T>::push_back(T &&val) {
    insert(end(),std::move(val));
/*
    if (!empty()){
        tail = new Node(std::move(val));
        tail->prev->next=tail;
    }
    else{
        head=tail= new Node(std::move(val));
    }
    */
}

template<typename T>
void cop4530::List<T>::pop_front() {
    erase(begin());
}

template<typename T>
void cop4530::List<T>::pop_back() {
    erase(--end());
}

template<typename T>
void cop4530::List<T>::remove(const T &val) {
    for (auto itr=begin(); itr !=end() ; ++itr) {      //unable to create variable object... I suspect it isn't linked properly
        if(itr.retrieve() == val)                                //it is capable of removing 4 but nothing between, it should be a linking error
            erase(itr);
    }
}

template<typename T>
template<typename PREDICATE>
void cop4530::List<T>::remove_if(PREDICATE pred) {
    for (auto itr=begin(); itr !=end() ; ++itr) {
        if (pred(*itr)==true)
            erase(itr);
    }
}

template<typename T>
void cop4530::List<T>::print(std::ostream &os, char ofc) const {
    for(auto itr = begin(); itr != end(); ++itr){
        os << itr.retrieve() << ofc;
    }
    const_iterator itr=begin();
    os << itr.retrieve();
}

template<typename T>
typename cop4530::List<T>::iterator cop4530::List<T>::begin() {
    return iterator(head->next);
}

template<typename T>
typename cop4530::List<T>::const_iterator cop4530::List<T>::begin() const {
    return const_iterator(head->next);
}

template<typename T>
typename cop4530::List<T>::iterator cop4530::List<T>::end() {
    return iterator(tail);
}

template<typename T>
typename cop4530::List<T>::const_iterator cop4530::List<T>::end() const {
    return const_iterator(tail);
}

template<typename T>
typename cop4530::List<T>::iterator cop4530::List<T>::insert(List::iterator itr, const T &val) { //inserts ahead of itr, at least it's supposed to
    Node *ptr = itr.current;
    ++theSize;
    return {ptr->prev = ptr->prev->next = new Node{val,ptr->prev,ptr}};

    /*
    auto *ptr = itr.current;
    ++theSize;
    auto *ptr2=new List<T>::Node{val,ptr->prev,ptr};
    ptr->prev->next=ptr2;
    ptr->prev=ptr2;
    List<T>::iterator iter{ptr2};
    return iter;
     */
}

template<typename T>
typename cop4530::List<T>::iterator cop4530::List<T>::insert(List::iterator itr, T &&val) {
    Node *ptr = itr.current;
    ++theSize;
    return {ptr->prev = ptr->prev->next = new Node{std::move(val),ptr->prev,ptr}};

    /*
    auto *ptr = itr.current;  //the same thing but rewritten of course no difference
    ++theSize;
    auto *ptr2=new List<T>::Node{std::move(val),ptr->prev,ptr};
    ptr->prev->next=ptr2;
    ptr->prev=ptr2;
    List<T>::iterator iter{ptr2};
    return iter;
     */
}

template<typename T>
typename cop4530::List<T>::iterator cop4530::List<T>::erase(List::iterator itr) {
    List<T>::Node *p = itr.current;
    List<T>::iterator retval(p->next);
    p->prev->next = p->next;
    p->next->prev = p->prev;
    delete p;
    --theSize;
    return retval;
}

template<typename T>
typename cop4530::List<T>::iterator cop4530::List<T>::erase(List::iterator start, List::iterator end) {
    for( iterator itr = start; itr != end; )
        itr = erase(itr);
    return end;
}

template<typename T>
void cop4530::List<T>::init() {
    theSize=0;
    head=new List::Node;
    tail=new List::Node;
    //head->next=nullptr;     //with current code fails to create a variable object, segmentation fault
    //tail->prev=nullptr;     //with current code fails to create a variable object, segmentation fault
    head->next=tail;
    tail->prev=head;
    head->prev=nullptr;
    tail->next=nullptr;
}

template<typename T>
bool operator==(const List<T> &lhs, const List<T> &rhs){    //compares left and right hand side
    if(lhs.size()==rhs.size()){
        for(auto & itr:lhs){                //check lhs
            for(auto &itr2:rhs){            //check rhs
                if(itr!=itr2)
                    return false; //if not equal
            }
        }
        return true; //equal
    }
    else //if not same size
        return false;
}

template<typename T>
bool operator!=(const List<T> &lhs, const List<T> &rhs){    //just the negation of the == operator
    return(!(lhs==rhs));
}

// overloading output operator
template<typename T>
std::ostream &operator<<(std::ostream &os, const List<T> &l){
    l.print(os);
    return os;
}
#endif //ASSIGNENT2REDO_LIST_HPP
