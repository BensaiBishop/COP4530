//  Assignment 4 Project
//  Benjamin Bishop
//  7 Mar. 2021

#ifndef PROJ4_BET_H
#define PROJ4_BET_H
#include <iostream>
#include <sstream>
#include <stack>

using namespace std;
class BET{
    struct BinaryNode{ //struct BinaryNode contains all node relevant information.

        BinaryNode *left;  // pointer to the left
        BinaryNode *right; // pointer to the right
        string data;

        BinaryNode(const string & d = string{}, BinaryNode *l = nullptr, BinaryNode *r = nullptr)
            : data{d}, left{l},  right{r} {}
    };

public:
    BET(); //default constructor
    BET(const string& postfix); //one-parameter constructor
    BET(const BET&);
    ~BET();
    bool buildFromPostfix(const string& postfix);
    const BET & operator= (const BET &);
    void printInfixExpression();
    void printPostfixExpression();
    size_t size();
    size_t leaf_nodes();
    bool empty();
private:
    BinaryNode *beginning; //pointer to the beginning of the tree
    void printInfixExpression(BinaryNode *n);
    void makeEmpty(BinaryNode* &t);
    BinaryNode * clone(BinaryNode *t) const;
    void printPostfixExpression(BinaryNode *n);
    size_t size(BinaryNode *t);
    size_t leaf_nodes(BinaryNode *t);
};
// end of BET class
#include "bet.hpp"
#endif //PROJ4_BET_H
