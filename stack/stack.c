#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "stack.h"

// creates a stack of size capacity, initializes top to index -1
struct Stack* CREATE_STACK(int capacity) {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    // 10 is the maximum length of the string, last index == '\0'
    stack->a = malloc(capacity * sizeof(char) * 11);
    
    return stack;
}

// check if the stack is full
int STACK_FULL(struct Stack* stack) {
    return stack->capacity - 1 == stack->top;
}

// check if the stack is empty
int STACK_EMPTY(struct Stack* stack) {
    return stack->top == -1;
}

// pushes an element to the top of a stack
void PUSH(struct Stack* stack, const char *str) {
    if (STACK_FULL(stack)) printf("Overflow error!\n");
    else {
        // printf("PUSHING: %s\n", str);
        // uses strdup to use a duplication of the string
        // and not allow to pass the address
        stack->a[++stack->top] = strdup(str);
    }
}

// pops the top element of a stack
char *POP(struct Stack* stack) {
    if (STACK_EMPTY(stack)) {
        printf("Underflow error!\n");
        return "";
    }
    // printf("%s %d\n", stack->a[stack->top], stack->top);
    return stack->a[stack->top--];
}

// returns the top element of the stack
char *TOP(struct Stack* stack) {
    if (STACK_EMPTY(stack)) {
        printf("Stack is empty!\n");
        return "";
    }
    else return stack->a[stack->top];
}