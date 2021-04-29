//
// provide by class lectures
//

#ifndef IN2POST_CPP_NODE_H
#define IN2POST_CPP_NODE_H
template<class T> class Stack;
template<class T> class StackIterator;
template<class T>

class Node{



    friend class Stack<T>;
    friend class StackIterator<T>;
public:
    Node();//constructor
    Node(const T& d);//copy
    Node(T && d);//move
    Node<T> * next;
private:
    T data;
    Node<T> *prev;
};

template<class T>
Node<T>::Node() {
    prev= nullptr;
    next= nullptr;
}

template<class T>
Node<T>::Node(const T &d) {
    data=d;
    prev=next= nullptr;
}

template<class T>
Node<T>::Node(T &&d) {
    data=std::move(d);
    prev=next= nullptr;
}

#endif //IN2POST_CPP_NODE_H
