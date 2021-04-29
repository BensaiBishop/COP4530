//  Assignment 4 Project
//  Benjamin Bishop
//  7 Mar. 2021

#ifndef PROJ4_BET_HPP
#define PROJ4_BET_HPP


int precedence(const string& expression);
bool isOperand(const string& expression);

BET::BET() { //default constructor
    beginning = new BinaryNode;
}

BET::BET(const string& postfix) { //constructor that takes postfix and builds tree
    beginning = new BinaryNode;
    buildFromPostfix(postfix);
}

BET::BET(const BET &n) { //copy constructor
    beginning = clone(n.beginning);
}

BET::~BET() { //deconstructor
    makeEmpty(beginning);
}

bool BET::buildFromPostfix(const string &postfix) { // build a tree based on postfix expression
    stack<BinaryNode*> stack;
    stringstream sstr(postfix);
    string temp;
    string temp1;
    int operands = 0;
    int operators = 0;

    if (postfix.empty()){
        cout << "Bad postfix expression\n";
        beginning = nullptr;
        return false;
    }
    if (!empty())
        makeEmpty(beginning);// clear for a new tree

    while (sstr >> temp){

        BinaryNode *node = new BinaryNode(temp);

        if (isOperand(temp)){// push operands to the stack
            operands++;
            stack.push(node);
        }
        else if (precedence(temp) > 0){ // operator has precedence greater than zero
            operators++;
            if (operands <= operators){ // if operators ever overtakes operands, we are done, bad postfix
                cout<<"Bad postfix expression\n";
                beginning = nullptr;
                return false;
            }
            else{
                node->left = stack.top();
                stack.pop();
                node->right = stack.top();
                stack.pop();
                stack.push(node);
            }
        }
    }
    if (operands - operators != 1){ // if the difference between operands and operators is ever greater than 1
        cout<<"Bad postfix expression\n";
        beginning = nullptr;
        return false;
    }
    else if (stack.empty()){
        cout<< "Bad postfix expression \n";
        beginning = nullptr;
        return false;
    }
    else if (operands != operators)
        beginning = stack.top();
    return true;
}


const BET &BET::operator=(const BET & n) { // assignment operator
    beginning = clone(n.beginning);
    return *this;
}

void BET::printInfixExpression() { // print infix utilizing the recursive
    printInfixExpression(beginning);
}

void BET::printPostfixExpression() {    // print postfix utilizing the recursive
    printPostfixExpression(beginning);
}

size_t BET::size() { // return number of nodes in the tree
    return (size(beginning));
}

size_t BET::leaf_nodes() { // returns number of leaves(external nodes) in the tree
    return (leaf_nodes(beginning));
}

bool BET::empty() {
    if (beginning == nullptr)
        return true;
    else
        return false;
}

void BET::printInfixExpression(BET::BinaryNode *n) {
    bool openParen = false;
    if (n != nullptr){
        if (n->left == nullptr && n->right == nullptr)// valid beginning node but no children
            cout << n->data << " ";
        else{
            if (precedence(n->data) != 0 && precedence(n->right->data) != 0){ // looking for operators, print the right side first
                if (precedence(n->data) >= precedence(n->right->data)){
                    if (precedence(n->data) == 2){ // multiplication or division, prepare parentheses
                        cout << "( ";
                        openParen = true;
                    }
                }
            }
            printInfixExpression(n->right);

            if (openParen)
                cout << ") ";
            openParen = false; //resetting the bool
            cout << n->data << " ";

            if (precedence(n->data) != 0 && precedence(n->left->data) != 0){ // looking for operators, print the left side
                if (precedence(n->data) >= precedence(n->left->data)){
                    cout<<"( ";
                    openParen = true;
                }
            }
            printInfixExpression(n->left);

            if (openParen)
                cout<< ") ";
            openParen = false;
        }
    }
}

void BET::makeEmpty(BET::BinaryNode *&t) { //deletes all nodes in subtree pointed to by t
    if (t != nullptr){
        if (t->left != nullptr)
            makeEmpty(t->left);
        if (t->left != nullptr)
            makeEmpty(t->right);
        delete t;
    }
    t = nullptr;
}

BET::BinaryNode *BET::clone(BET::BinaryNode *t) const { // clone all nodes in subtree pointed to by t
    if (t == nullptr)
        return nullptr;
    else
        return new BinaryNode{t->data, clone(t->left),clone(t->right)};
}

void BET::printPostfixExpression(BET::BinaryNode *n) { //print the post fix expression
    if(n != nullptr){
        printPostfixExpression(n->left);
        printPostfixExpression(n->right);
        std::cout << n->data << " ";
    }
}

size_t BET::size(BET::BinaryNode *t) { // returns number of nodes pointed to by t
    if (t == nullptr)
        return 0;
    else
        return(size(t->left)+size(t->right)+1);
}

size_t BET::leaf_nodes(BET::BinaryNode *t) { //return number of leaf nodes in the subtree pointed to by t
    if (t == nullptr)
        return 0;
    // if node has no children it is leaf
    else if ((t->left == nullptr) && (t->right == nullptr))
        return 1;
    else
        return (leaf_nodes(t->left)+leaf_nodes(t->right));
}

int precedence(const string& exp){ // check precedence of string
    if (exp == "(" || exp == ")")
        return (3);
    else if (exp == "*" || exp == "/")
        return (2);
    else if (exp == "+" || exp == "-")
        return (1);
    else //white space or anything else really
        return (0);
}

bool isOperand(const string& exp){ // check to see if is operand within string
    if(exp.length() == 1){
        char c = exp[0];
        return((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || (c == '_'));
    }
    else return true;
}
#endif //PROJ4_BET_HPP
