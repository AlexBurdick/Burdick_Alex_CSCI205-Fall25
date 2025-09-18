#include "Stack.hpp"
#include <unordered_map>
#include <string>
#include <vector>

using namespace std;

string infixToPostfix(string infixExpr) { // Code from Runestone
    unordered_map <char,int> prec;
    prec['*']=3;
    prec['/']=3;
    prec['+']=2;
    prec['-']=2;
    prec['(']=1;

    size_t length = infixExpr.length();
    Stack<char> opStack;
    string postfixExpr;
    string letsnums = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

    for (char token:infixExpr){ // For each character in infixExpr
        if (token == ' '){
            continue;
        }
        else if ( // If operand, add to postfixExpr
           ((token >= 'a' && token <= 'z') || 
            (token >= 'A' && token <= 'Z') || 
            (token >= '0' && token <= '9'))
        ) {  postfixExpr += token;
        } else if (token == '(') {
            opStack.push(token);
        } else if (token == ')') {
            char topToken;
            topToken = opStack.peak();
            opStack.pop();
            while (topToken != '(') {
                postfixExpr.emplace_back(topToken);
                topToken=opStack.peak();
                opStack.pop();
            }
        } else { //if the token is not inside of letsnums.
            while (!opStack.empty() && (prec[opStack.peak()]>=prec[token])) //while the stack is not empty and
                                                                           //the top item of the stack is on a
                                                                           //higher level of PEMDAS than token.
            {
                postfixExpr.emplace_back(opStack.peak());
                opStack.pop();
                }
            opStack.push(token);
        }
    }
    while (!opStack.empty()) {
        postfixExpr.emplace_back(opStack.peak());
        opStack.pop();
    }

    string s(postfixExpr.begin(),postfixExp.end());

    return s;
}