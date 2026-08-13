#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

// Stack for characters (operators)
char operatorStack[MAX];
int top = -1;

// Stack for integers (evaluation)
int valueStack[MAX];
int valueTop = -1;

// Push character onto operator stack
void pushOperator(char ch) {
    operatorStack[++top] = ch;
}

// Pop character from operator stack
char popOperator() {

    return operatorStack[top--];
}

// Peek top operator
char peekOperator() {
    return operatorStack[top];
}

// Push integer onto value stack
void pushValue(int value) {
    valueStack[++valueTop] = value;
}

// Pop integer from value stack
int popValue() {
    return valueStack[valueTop--];
}

// Return precedence of operator
int precedence(char op) {
    if (op == '+' || op == '-')
        return 1;

    if (op == '*' || op == '/')
        return 2;

    if (op == '^')
        return 3;

    return 0;
}

// Check whether character is an operator
int isOperator(char ch) {
    return (ch == '+' || ch == '-' ||
            ch == '*' || ch == '/' || ch == '^');
}

// Apply arithmetic operation
int applyOperation(int a, int b, char op) {
    switch (op) {
        case '+':
            return a + b;

        case '-':
            return a - b;

        case '*':
            return a * b;

        case '/':
            return a / b;

        case '^': {
            int result = 1;
            for (int i = 0; i < b; i++)
                result *= a;
            return result;
        }
    }

    return 0;
}

// Convert infix expression to postfix
void infixToPostfix(char infix[], char postfix[]) {
    int i = 0, j = 0;
    char ch;

    top = -1;

    while ((ch = infix[i++]) != '\0') {

        // Ignore spaces
        if (ch == ' ')
            continue;

        // If operand, add directly to postfix
        if (isdigit(ch)) {
            postfix[j++] = ch;
        }

        // If '(' push onto stack
        else if (ch == '(') {
            pushOperator(ch);
        }

        // If ')' pop until '('
        else if (ch == ')') {
            while (top != -1 && peekOperator() != '(') {
                postfix[j++] = popOperator();
            }

            if (top != -1)
                popOperator();   // Remove '('
        }

        // If operator
        else if (isOperator(ch)) {

            while (top != -1 &&
                   peekOperator() != '(' &&
                   precedence(peekOperator()) >= precedence(ch)) {
                postfix[j++] = popOperator();
            }

            pushOperator(ch);
        }
    }

    // Pop remaining operators
    while (top != -1) {
        postfix[j++] = popOperator();
    }

    postfix[j] = '\0';
}

// Evaluate postfix expression
int evaluatePostfix(char postfix[]) {
    int i = 0;
    char ch;

    valueTop = -1;

    while ((ch = postfix[i++]) != '\0') {

        // If operand
        if (isdigit(ch)) {
            pushValue(ch - '0');
        }

        // If operator
        else if (isOperator(ch)) {
            int b = popValue();
            int a = popValue();

            int result = applyOperation(a, b, ch);

            pushValue(result);
        }
    }

    return popValue();
}

int main() {
    char infix[MAX];
    char postfix[MAX];

    printf("Enter infix expression: ");
    fgets(infix, MAX, stdin);

    // Remove newline
    infix[strcspn(infix, "\n")] = '\0';

    infixToPostfix(infix, postfix);

    printf("Postfix expression: %s\n", postfix);

    printf("Result: %d\n", evaluatePostfix(postfix));

    return 0;
}