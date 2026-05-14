#include <stdio.h>
#include <stdlib.h>

/* * Project: Reverse Polish Calculator
 * Goal: Implement a postfix calculator using a stack data structure. [cite: 60]
 * Logic: Operands are pushed onto the stack; operations pop operands and
 * push results back. [cite: 52]
 */

#define MAX_STACK_SIZE 100

// Global Stack and Pointer
double calculationStack[MAX_STACK_SIZE];
int stackTopIndex = -1;

// Function to push an operand onto the stack [cite: 51]
void push(double value) {
    if (stackTopIndex < MAX_STACK_SIZE - 1) {
        calculationStack[++stackTopIndex] = value;
    } else {
        printf("Error: Stack Overflow\n");
    }
}

// Function to pop an operand from the stack [cite: 52]
double pop() {
    if (stackTopIndex >= 0) {
        return calculationStack[stackTopIndex--];
    } else {
        printf("Error: Stack Underflow\n");
        return 0.0;
    }
}

// Function to print the top of the stack without popping it
void peekAndPrint() {
    if (stackTopIndex >= 0) {
        printf("Top of Stack: %g\n", calculationStack[stackTopIndex]);
    } else {
        printf("Stack is empty.\n");
    }
}

int main() {
    char command;
    double operand, val1, val2;

    printf("--- Reverse Polish Calculator ---\n");
    printf("Instructions:\n");
    printf(" '?' <num> : Read and push number\n");
    printf(" '+', '-', '*', '/' : Perform operation\n");
    printf(" '=' : Print top value\n");
    printf(" 'q' : Quit program\n\n");

    while (1) {
        printf("Enter instruction: ");
        scanf(" %c", &command);

        switch (command) {
            // Read operand and push it onto the stack [cite: 53, 55]
            case '?':
                if (scanf("%lf", &operand) == 1) {
                    push(operand);
                }
                break;

            // Arithmetic Operations
            case '+':
                val2 = pop();
                val1 = pop();
                push(val1 + val2);
                break;

            case '-':
                val2 = pop();
                val1 = pop();
                push(val1 - val2);
                break;

            case '*':
                val2 = pop();
                val1 = pop();
                push(val1 * val2);
                break;

            case '/':
                val2 = pop();
                val1 = pop();
                if (val2 != 0) {
                    push(val1 / val2);
                } else {
                    printf("Error: Division by zero.\n");
                    push(val1); // Return val1 to stack
                }
                break;

            // Print top of stack without popping
            case '=':
                peekAndPrint();
                break;

            case 'q':
                printf("Exiting...\n");
                return 0;

            default:
                printf("Unknown command: %c\n", command);
        }
    }

    return 0;
}
