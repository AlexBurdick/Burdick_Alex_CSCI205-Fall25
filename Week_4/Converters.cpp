#include "Stack.hpp"
#include <unordered_map>
#include <string>
#include <vector>

using namespace std;

string infixToPostfix(string infixExpr) { // Code from Runestone, edited by Alex Burdick
    unordered_map <char,int> prec;
    prec['*']=3;
    prec['/']=3;
    prec['+']=2;
    prec['-']=2;
    prec['(']=1;

    size_t length = infixExpr.length();
    Stack<char> opStack;
    string postfixExpr;

    for (char token:infixExpr){ // For each character in infixExpr
        if (token == ' '){
            continue;
        }
        else if ( // If operand, add to postfixExpr
           ((token >= 'a' && token <= 'z') || // Logic structure from GeeksForGeeks
            (token >= 'A' && token <= 'Z') || // https://www.geeksforgeeks.org/dsa/convert-infix-expression-to-postfix-expression/
            (token >= '0' && token <= '9'))
        ) {  postfixExpr += token;
        } else if (token == '(') {
            opStack.push(token);
        } else if (token == ')') {
            char topToken;
            topToken = opStack.peak();
            opStack.pop();
            while (topToken != '(') { // Pop and add to the string until reaching '('
                postfixExpr += topToken;
                topToken = opStack.peak();
                opStack.pop();
            }
        } else { // If token is not an operand
            while ( !opStack.empty() && (prec[opStack.peak()] >= prec[token]) ) {
                postfixExpr += opStack.peak();
                opStack.pop();
            }
            opStack.push(token);
        }
    }
    while (!opStack.empty()) {
        postfixExpr += opStack.peak();
        opStack.pop();
    }

    return postfixExpr;
}