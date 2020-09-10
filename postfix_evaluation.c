#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define QUEUE_SIZE 50
#define DIGIT_LENGTH 11

int evaluate(int a, int b, char* op) {
  if (!strcmp(op, "+")) return a + b;
  else if (!strcmp(op, "-")) return a - b; 
  else if (!strcmp(op, "*")) return a * b;
  else if (!strcmp(op, "/")) return a / b;
  else if (!strcmp(op, "%")) return a % b;
  else if (!strcmp(op, "^")) return ((int) pow(a, b));
  else if (!strcmp(op, ">")) return a > b;
  else if (!strcmp(op, "<")) return a < b;
  else if (!strcmp(op, ">=")) return a >= b;
  else if (!strcmp(op, "<=")) return a <= b;
  else if (!strcmp(op, "==")) return a == b;
  else if (!strcmp(op, "!=")) return a != b;
  else if (!strcmp(op, "!")) return !b;
  else if (!strcmp(op, "&&")) return a && b;
  else if (!strcmp(op, "||")) return a || b;
}

int evaluatePostfix(char *postfix) { //   char postfix[]
  Queue* operands = createQueue(QUEUE_SIZE);
  char currStr[DIGIT_LENGTH] = "\0";
  int i, j, temp, a, b, operated, num, ogTail;

  for (i = 0; i < strlen(postfix); i++) {
    // printf("digit: %c\n", postfix[i]);
    // printf("i = %d\n", i);
    if (postfix[i] == ' ') {
        // printf("CURR: %s, IS OPERATOR: %d\n", currStr, isOperator(currStr));
        // put the postfix evaluation algorithm here :)
        switch(isOperator(currStr)) {
            case 0:
                // convert string to int
                num = atoi(currStr);
                //enqueue to queue
                enqueue(operands, num);
                
                break;
            case 1:
            case 2:
                // in order to find the two operands that are going to be used, we need to find the original tail of the queue and compare it to the head, if their difference is 2, then those are the operands. Else, we have to move the current head to the tail of the queue and compare the current head with the original tail.
                
                //copies the intial tail of the queue (will need to check on the original index of the tail)
                ogTail = queue_tail(operands); 
                
                operated = 0; // checks if there was an operation done
                do {
                  // check first if the operator is not (!)
                  if (!strcmp(currStr, "!")) {
                    a = dequeue(operands);
                    enqueue(operands, !a);
                    operated = 1;
                  }
                  // checks if the head and the tail have a difference of 2
                  // these are the two numbers to be used on the operator
                  if (operated == 0 && abs(ogTail - queue_head(operands)) == 2) {
                    a = dequeue(operands);
                    b = dequeue(operands);
                    // printf("a = %d\nb = %d\n", a, b);

                    // zero division error
                    if((!strcmp(currStr, "/") || !strcmp(currStr, "%")) && b == 0) {
                        return 99999999;
                    }
                    enqueue(operands, evaluate(a, b, currStr));
                    operated = 1; // operation was done
                  }
                  // if the difference is not 2, puts the number to the back of the queue
                  else {
                    temp = dequeue(operands);
                    enqueue(operands, temp);
                  }
                } while (!operated); // loop while there has not been an operation done
                break;
        }
        for (j = 0; j < DIGIT_LENGTH; j++) currStr[j] = '\0'; // empties the string
    } else 
        currStr[strlen(currStr)] = postfix[i];
  }
  return dequeue(operands);
}

