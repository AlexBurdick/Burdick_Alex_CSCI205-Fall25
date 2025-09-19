#include "Stack.hpp"
#include <unordered_map>
#include <string>
#include <stdexcept>

// Function prototypes
std::string infixToPostfix(std::string);
int postfixEvaluator(std::string);
int infixEvaluator(std::string);
bool parChecker(std::string);

/**
 * @brief Evaluates an infix expression by converting it to postfix notation first.
 * 
 * @param expr infix expression to be evaluated
 * @return int result of the evalutaion
 */
int infixEvaluator(std::string expr){
    return postfixEvaluator( infixToPostfix(expr) );
}

/**
 * @brief Converts an infix expression to postfix notation.
 * 
 * @param infixExpr infix expression
 * @return string postfix expression
 */
std::string infixToPostfix(std::string infixExpr) { // Code from Runestone, edited by Alex Burdick
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
    std::string postfixExpr;

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
            topToken = opStack.peek();
            opStack.pop();
            while (topToken != '(') { // Pop and add to the string until reaching '('
                postfixExpr += topToken;
                topToken = opStack.pop();
            }
        } else { // If token is not an operand
            while ( !opStack.empty() && (prec[opStack.peek()] >= prec[token]) ) {
                postfixExpr += opStack.pop();
            }
            opStack.push(token);
        }
    }
    while (!opStack.empty()) {
        postfixExpr += opStack.pop();
    }

    return postfixExpr;
}

/**
 * @brief Evaluates an expression in postfix notation
 * 
 * @param expr expression to be evaluated
 * @return int result of the calculation
 */
int postfixEvaluator(std::string expr){
    size_t length = expr.length();
    Stack<char> operands;
    int n;

    for (char token:expr){
        if ( isdigit(token) ){
            operands.push(token - '0');;
        } else {
            int lhs = operands.pop();
            int rhs = operands.pop();
            int r;
            switch (token){ // Switch statement from LeChat 09/19/2025
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

// Returns whether the parentheses in the input are balanced
// From Runestone, edited by Alex Burdick
/**
 * @brief 
 * 
 * @param symbolString 
 * @return true 
 * @return false 
 */
bool parChecker(std::string symbolString){
    Stack<std::string> s;
    bool balanced = true;
    int index = 0;
    int str_len = symbolString.length();

    while (index < str_len && balanced){
        std::string symbol;
        symbol = symbolString[index];
        if (symbol == "(") {
            s.push(symbol); //pushes the open parentheses to the stack.
        } else {
            if (s.empty())  { balanced = false; } 
            else            { s.pop(); }
        }
    index = index + 1;
    }

    if (balanced && s.empty())  { return true; } 
    else                        { return false; }
}