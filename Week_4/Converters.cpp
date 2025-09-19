#include "Stack.hpp"
#include <unordered_map>
#include <string>
#include <vector>

// Function prototypes
string infixToPostfix(string);
int postfixEvaluator(string);
int infixEvaluator(string);
bool parChecker(string);

string infixToPostfix(string infixExpr) { // Code from Runestone, edited by Alex Burdick
    // Make sure the expression is valid
    if ( !parChecker(infixExpr) ){ 
        throw std::invalid_argument("Invalid expression: unbalanced parentheses");
    }
    
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

int postfixEvaluator(string expr){
    size_t length = expr.length();
    Stack<char> operands;
    int n;

    for (char token:expr){
        if ( isdigit(token) ) {
            operands.push(token - '0');;
        } else {
            int lhs = operands.pop();
            int rhs = operands.pop();
            int r;
            switch (token) { // Switch statement from LeChat 09/19/2025
                case '+': r = lhs + rhs; break;
                case '-': r = lhs - rhs; break;
                case '*': r = lhs * rhs; break;
                case '/': r = lhs / rhs; break;
                default: throw invalid_argument("Invalid operator");
            }
            operands.push(r); // Push the result onto the stack
        }
    }

    return operands.pop();
}

int infixEvaluator(string expr){
    return postfixEvaluator( infixToPostfix(expr) );
}

// Returns whether the parentheses in the input are balanced
// From Runestone, edited by Alex Burdick
bool parChecker(string symbolString) {
    Stack<string> opStack;
    bool balanced = true;
    int index = 0;
    int str_len = symbolString.length();

    while (index < str_len && balanced) {
              string symbol;
              symbol = symbolString[index];
              if (symbol == "(") {
                  opStack.push(symbol); //pushes the open parentheses to the stack.
              } else {
                  if (opStack.empty()) { //if there is no open parentheses in the stack,
                                   //the closing parentheses just found makes the string unbalanced.
                        balanced = false;
                  } else { //if there is an open parentheses in the stack,
                           //the closing parentheses just found has a matching open parentheses.
                       opStack.pop();
                  }
              }
    index = index + 1;
    }

    if (balanced && opStack.empty()) { //if the string is balanced and there are no
                                 //remaining open parentheses.
        return true;
    } else {
        return false;
    }
}