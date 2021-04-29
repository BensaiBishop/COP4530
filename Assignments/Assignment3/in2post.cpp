// Assignment 3
// Created on 16-Feb-21.
// Benjamin Bishop

#include <iostream>
#include <string>
#include "stack.h"
#include <cctype>
#include <sstream>

using namespace std;
using namespace cop4530;

//prototypes
int precedence(string);
int postfixEval();
int getInt(string);
int calculate(string, int, int);
bool isOperator(string, int);
bool isOperand(string, int);
bool checkExpression(string);
bool nextOp(string, int);
string getOperand(string, int &);
string getOperator(string, int &);
void convertResult();

string currVar;

cop4530::Stack<string> stack;
cop4530::Stack<string> results;
cop4530::Stack<int> postfix;
cop4530::Stack<string> operators;
cop4530::Stack<string> resStack;

int main() {

    bool killSwitch = true;

    do{

        string expression;
        cout << "Enter infix expression or 'quit': \n";
        getline(cin, expression);
        if (expression == "quit"){
            return 0;
        }

        int str = 0;

        if(isOperator(expression,str)){
            cout << "Error: Missing operands in the expression\n";
            return 1;
        }
        string temp;

        while (str < expression.length()){
            currVar = expression[str];
            if (isOperand(expression, str))
            {
                temp = getOperand(expression, str);
                results.push(temp);
            }
            if (expression[str] == '(')
            {
                if(isOperator(expression,str+2)){
                    cout << "Error: Missing operands in the expression\n";
                    break;
                }
                temp = getOperator(expression, str);
                stack.push(temp);
            }
            if (expression[str] == ')')
            {
                while ( !stack.empty() && stack.top() != "("){
                    results.push(stack.top());
                    stack.pop();
                }
                stack.pop();
            }
            if (isOperator(expression, str)){
                while(!stack.empty() && precedence(stack.top()) >= precedence(currVar))
                {
                    results.push(stack.top());
                    stack.pop();
                }
                stack.push(currVar);
            }
            str+=1;
        }
        while(!stack.empty())
        {
            results.push(stack.top());
            stack.pop();
        }

        cout << endl << "Postfix expression: " << results << endl;

        if (checkExpression(expression))
        {
            cout << "Postfix evaluation: " << results << endl;
            postfix.clear();
            resStack.clear();
            results.clear();
            stack.clear();
            operators.clear();
        }
        else
        {
            convertResult();
            int pf = postfixEval();
            postfix.clear();
            resStack.clear();
            results.clear();
            stack.clear();
            operators.clear();
        }

    }while(killSwitch == true);


    return 0;
}

bool isOperator(string expression, int str)
{
    if (expression[str] == '+' || expression[str] == '-' || expression[str] == '*' || expression[str] == '/'){
        return true;
    } 		return false;
}

bool isOperand(string expression, int str)
{
    if (isdigit(expression[str]) || isalpha(expression[str]) || expression[str] == '.' || expression[str] == '_'){
        return true;
    }
    return false;
}

string getOperand(string expression, int &str)
{
    string temp;
    while (isOperand(expression, str))
    {
        temp.push_back(expression[str]);
        str++;
    }
    return temp;
}

string getOperator(string expression, int &str)
{
    string temp;
    temp.push_back(expression[str]);
    return temp;
}

bool nextOp(string expression, int str)
{
    if (expression[str] == '*' || expression[str] == '/' )
    {
        return true;
    }
    return false;
}

int precedence(string expression)
{
    string temp;
    temp = expression;
    if(temp == "*" || temp == "/")
    {
        return 2;
    }
    if(temp == "+" || temp == "-")
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int postfixEval()
{
    string temp;
    int temp2;
    int val;
    int left;
    int right;
    int calc;
    while (!resStack.empty())
    {
        temp = resStack.top();
        val = getInt(temp);

        if (val != -1)
        {
            postfix.push(val);
            resStack.pop();
            //continue;
        }
        if (val == -1)
        {
            operators.push(temp);
            resStack.pop();
            right = postfix.top();
            postfix.pop();
            left = postfix.top();
            postfix.pop();
            calc = calculate(temp, left, right);
            postfix.push(calc);
        }
    }
    if (postfix.size() > 1){
        postfix.pop();
    }
    cout << "Postfix evaluation: " << postfix << endl;
    return 1;
}

int getInt(string str)
{
    string temp;
    int Result;
    if (isOperator(str, 0)){
        return -1;
    }
    stringstream convert(str);
    convert >> Result;
    return Result;
}

int calculate(string op, int left, int right)
{
    if (op == "+"){
        return left + right;
    } else if (op == "-"){
        return left - right;
    } else if (op == "*"){
        return left * right;
    } else if (op == "/"){
        return left / right;
    } else
        return -1;
}

void convertResult()
{
    string temp;
    while (!results.empty())
    {
        temp = results.top();
        resStack.push(temp);
        results.pop();
    }
}

bool checkExpression(string expression)
{
    for (int i = 0; i < expression.length(); i++)
    {
        if (isalpha(expression[i]) || expression[i] == '_')
        {
            return true;
        }
    }
    return false;
}
