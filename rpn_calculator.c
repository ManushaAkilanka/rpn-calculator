/*
 * ============================================================
 *  Reverse Polish Notation (RPN) Calculator
 *  Course  : IC 2306 - Programming II
 *  Group   : Student 2023T01892 & Student 2023T01859
 * ============================================================
 *
 *  HOW IT WORKS:
 *  -------------
 *  This program implements a Reverse Polish (Postfix) Calculator
 *  using a Stack data structure.
 *
 *  Supported Instructions:
 *    ?   -> Read a number from the user and push it onto the stack
 *    +   -> Pop two numbers, add them, push the result
 *    -   -> Pop two numbers, subtract (second - top), push result
 *    *   -> Pop two numbers, multiply them, push the result
 *    /   -> Pop two numbers, divide (second / top), push result
 *    =   -> Print the top of the stack (without removing it)
 *    q   -> Quit the program
 *
 *  Example:
 *    Input sequence: ? ? + =
 *    Enter operand: 3
 *    Enter operand: 5
 *    Result: 8.00
 * ============================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/* ---- Constants ---- */
#define STACK_MAX_SIZE 100   /* Maximum number of elements the stack can hold */

/* ============================================================
 *  STACK DATA STRUCTURE
 * ============================================================ */

/* Stack structure:
 *   - data[]  : array that stores the stack elements (double for decimal support)
 *   - top     : index of the current top element (-1 means empty)
 */
typedef struct {
    double data[STACK_MAX_SIZE];
    int top;
} Stack;


/* ------------------------------------------------------------
 *  initStack
 *  Purpose : Initialise a new stack by setting top to -1 (empty)
 *  Param   : stack - pointer to the Stack to initialise
 * ------------------------------------------------------------ */
void initStack(Stack *stack) {
    stack->top = -1;
}


/* ------------------------------------------------------------
 *  isEmpty
 *  Purpose : Check whether the stack has no elements
 *  Returns : 1 (true) if empty, 0 (false) otherwise
 * ------------------------------------------------------------ */
int isEmpty(Stack *stack) {
    return stack->top == -1;
}


/* ------------------------------------------------------------
 *  isFull
 *  Purpose : Check whether the stack has reached its capacity
 *  Returns : 1 (true) if full, 0 (false) otherwise
 * ------------------------------------------------------------ */
int isFull(Stack *stack) {
    return stack->top == STACK_MAX_SIZE - 1;
}


/* ------------------------------------------------------------
 *  push
 *  Purpose : Add a new value on top of the stack
 *  Param   : stack - pointer to the Stack
 *            value - the double value to push
 * ------------------------------------------------------------ */
void push(Stack *stack, double value) {
    if (isFull(stack)) {
        printf("  [ERROR] Stack overflow! Cannot push %.2f\n", value);
        return;
    }
    /* Increment top first, then store the value */
    stack->top++;
    stack->data[stack->top] = value;
}


/* ------------------------------------------------------------
 *  pop
 *  Purpose : Remove and return the top value from the stack
 *  Returns : The top value, or 0.0 with an error message if empty
 * ------------------------------------------------------------ */
double pop(Stack *stack) {
    if (isEmpty(stack)) {
        printf("  [ERROR] Stack underflow! Not enough operands.\n");
        return 0.0;
    }
    /* Retrieve top value, then decrement top */
    double topValue = stack->data[stack->top];
    stack->top--;
    return topValue;
}


/* ------------------------------------------------------------
 *  peek
 *  Purpose : Return the top value WITHOUT removing it
 *  Returns : The top value, or 0.0 with an error message if empty
 * ------------------------------------------------------------ */
double peek(Stack *stack) {
    if (isEmpty(stack)) {
        printf("  [ERROR] Stack is empty! Nothing to display.\n");
        return 0.0;
    }
    return stack->data[stack->top];
}


/* ============================================================
 *  HELPER: Print the current stack contents (for debugging)
 * ============================================================ */
void printStack(Stack *stack) {
    if (isEmpty(stack)) {
        printf("  [Stack: EMPTY]\n");
        return;
    }
    printf("  [Stack bottom -> top]: ");
    for (int i = 0; i <= stack->top; i++) {
        printf("%.2f ", stack->data[i]);
    }
    printf("\n");
}


/* ============================================================
 *  MAIN PROGRAM
 * ============================================================ */
int main() {

    Stack calculatorStack;   /* The one stack used by the RPN calculator */
    initStack(&calculatorStack);

    char instruction;        /* Stores the instruction character read from the user */
    double operandValue;     /* Stores a numeric operand entered by the user */
    double operandA, operandB, result;  /* Temporary variables for arithmetic */

    /* ---- Welcome Banner ---- */
    printf("============================================\n");
    printf("   Reverse Polish Notation (RPN) Calculator \n");
    printf("   IC 2306 - Programming II Group Project   \n");
    printf("============================================\n");
    printf("Instructions:\n");
    printf("  ?  -> Enter a number (push onto stack)\n");
    printf("  +  -> Add top two numbers\n");
    printf("  -  -> Subtract (second - top)\n");
    printf("  *  -> Multiply top two numbers\n");
    printf("  /  -> Divide (second / top)\n");
    printf("  =  -> Print top of stack\n");
    printf("  q  -> Quit\n");
    printf("============================================\n\n");

    /* ---- Main Instruction Loop ---- */
    while (1) {

        printf("Enter instruction (?, +, -, *, /, =, q): ");
        scanf(" %c", &instruction);   /* Space before %c skips whitespace/newlines */

        /* ---- Process each instruction ---- */
        switch (instruction) {

            /* ? : Read an operand from the user and push it onto the stack */
            case '?':
                printf("  Enter operand value: ");
                scanf("%lf", &operandValue);
                push(&calculatorStack, operandValue);
                printf("  Pushed: %.2f\n", operandValue);
                printStack(&calculatorStack);
                break;

            /* + : Pop two operands, add them, push the result */
            case '+':
                if (calculatorStack.top < 1) {
                    printf("  [ERROR] Need at least 2 operands for addition.\n");
                    break;
                }
                operandB = pop(&calculatorStack);   /* top element */
                operandA = pop(&calculatorStack);   /* second element */
                result   = operandA + operandB;
                push(&calculatorStack, result);
                printf("  %.2f + %.2f = %.2f\n", operandA, operandB, result);
                printStack(&calculatorStack);
                break;

            /* - : Pop two operands, subtract (A - B), push the result */
            case '-':
                if (calculatorStack.top < 1) {
                    printf("  [ERROR] Need at least 2 operands for subtraction.\n");
                    break;
                }
                operandB = pop(&calculatorStack);   /* top element */
                operandA = pop(&calculatorStack);   /* second element */
                result   = operandA - operandB;
                push(&calculatorStack, result);
                printf("  %.2f - %.2f = %.2f\n", operandA, operandB, result);
                printStack(&calculatorStack);
                break;

            /* * : Pop two operands, multiply them, push the result */
            case '*':
                if (calculatorStack.top < 1) {
                    printf("  [ERROR] Need at least 2 operands for multiplication.\n");
                    break;
                }
                operandB = pop(&calculatorStack);
                operandA = pop(&calculatorStack);
                result   = operandA * operandB;
                push(&calculatorStack, result);
                printf("  %.2f * %.2f = %.2f\n", operandA, operandB, result);
                printStack(&calculatorStack);
                break;

            /* / : Pop two operands, divide (A / B), push the result */
            case '/':
                if (calculatorStack.top < 1) {
                    printf("  [ERROR] Need at least 2 operands for division.\n");
                    break;
                }
                operandB = pop(&calculatorStack);
                /* Guard against division by zero */
                if (operandB == 0.0) {
                    printf("  [ERROR] Division by zero is not allowed!\n");
                    push(&calculatorStack, operandB); /* put it back */
                    break;
                }
                operandA = pop(&calculatorStack);
                result   = operandA / operandB;
                push(&calculatorStack, result);
                printf("  %.2f / %.2f = %.2f\n", operandA, operandB, result);
                printStack(&calculatorStack);
                break;

            /* = : Print the top of the stack WITHOUT removing it */
            case '=':
                if (isEmpty(&calculatorStack)) {
                    printf("  [ERROR] Stack is empty. Nothing to display.\n");
                } else {
                    printf("  >>> Result = %.2f\n", peek(&calculatorStack));
                    printStack(&calculatorStack);
                }
                break;

            /* q : Quit the program */
            case 'q':
            case 'Q':
                printf("\nExiting RPN Calculator. Goodbye!\n");
                return 0;

            /* Any other character is invalid */
            default:
                printf("  [ERROR] Unknown instruction '%c'. Use ?, +, -, *, /, =, or q.\n",
                       instruction);
                break;
        }

        printf("\n"); /* Blank line between instructions for readability */
    }

    return 0;
}
