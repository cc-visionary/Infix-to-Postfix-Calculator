#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "stack/stack.c"
#include "queue/queue.c"
#include "infix_to_postfix.c"
#include "postfix_evaluation.c"

#define MAX_INPUT_SIZE 256
#define MAX_OUTPUT_SIZE 512

// To run the code:
//     clear && gcc -o main main.c -Wall -lm && ./main < TESTCASE.txt > RESULT.txt
//     clear && gcc -o main main.c -Wall  -lm && ./main < TESTCASE.txt

int main() {
    // struct Stack* stack = CREATE_STACK(20);
    // printf("%d\n", stack->capacity);
    // char a[11] = "a";
    // PUSH(stack, a);
    // PUSH(stack, "+");
    // PUSH(stack, "=>");
    // printf("%s\n", POP(stack));
    // printf("%s\n", POP(stack));
    // printf("%s\n", POP(stack));
    // printf("%d\n", STACK_FULL(stack));
    // printf("%d\n", STACK_EMPTY(stack));

    // Queue* queue = createQueue(10);
    // printf("capacity: %d\n", queue->capacity);
    // printf("head: %d\n", queue_head(queue));
    // printf("tail: %d\n", queue_tail(queue));
    // enqueue(queue, 1);
    // enqueue(queue, 2);
    // printf("head: %d\n", queue_head(queue));
    // printf("tail: %d\n", queue_tail(queue));
    // printf("%d\n", dequeue(queue));
    // printf("%d\n", dequeue(queue));
    // printf("head: %d\n", queue_head(queue));
    // printf("tail: %d\n", queue_tail(queue));
    // enqueue(queue, 3);
    // printf("tail: %d\n", dequeue(queue));

    char infix[MAX_INPUT_SIZE];    // input: infix
    char postfix[MAX_OUTPUT_SIZE]; // output: postfix
    int i, isStopped = 0, ctr = 1, evaluated;

    do {
        // make sures the infix and postfix variables are empty strings 
        for(i = 0; i < MAX_INPUT_SIZE; i++) infix[i] = '\0';
        for(i = 0; i < MAX_OUTPUT_SIZE; i++) postfix[i] = '\0';
        evaluated = 0;
        scanf("%s", infix);
        if(strcmp(infix, "QUIT") != 0) {
            printf("|| Number: %d ||\n", ctr);
            printf("INFIX: %s\n", infix);
            infixToPostfix(infix, postfix);
            printf("POSTFIX: %s\n", postfix);
            evaluated = evaluatePostfix(postfix);
            if(evaluated == 99999999) printf("EVALUATED: Division by zero error!\n\n");
            else printf("EVALUATED: %d\n\n", evaluated);
        } else isStopped = 1;
        ctr++;
    } while(!isStopped);

    return 0;
}
