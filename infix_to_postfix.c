#include <stdio.h>
#include <string.h>

#define STACK_SIZE 50
#define DIGIT_LENGTH 11
#define HAS_SPACE 1

/**
 * Returns 1 if char is a digit [0-9] else 0
 */
int isDigit(char character) {
    return character >= '0' && character <= '9';
}

/**
 * Returns 1 if it is a single character operator such as '*', '+', etc
 *         2 if it is a double character operator such as '>=', '==', etc
 *         0 if it is not an operator
 */
int isOperator(char *str) {
    int i, result = 0;
    char singleCharacters[11] = {'+', '-', '*', '/', '%', '^', '!', '>', '<', '(', ')'};
    char doubleCharacters[6][3] = {">=", "<=", "!=", "==", "&&", "||"};

    for(i = 0; i < 11; i++) { // checks if it matches any of the single character-ed operators
        if(str[0] == singleCharacters[i]) {
            result = 1;
            break;
        }
    }

    for(i = 0; i < 6; i++) { // check if it matches any of the double character-ed operators
        if(strcmp(str, doubleCharacters[i]) == 0) {
            result = 2;
            break;
        }
    }

    // Note: Even if it is a single character-ed operator, if it is a double character-ed operator,
    //       it prioritizes it double character-ed operator
    //       Example: >=, > is valid for single character, but the overall operator is >= so it is a
    //                double character-ed operator
    
    return result;
}

/**
 * Returns the weight of the operator to allow 
 * operator comparison with other operators
 */
int getOperatorWeight(char *str) {
    int weight = 0;
    static int caretWeight = 0;
    if(strcmp(str, "!") == 0) {
        // highest weight 
        // (considers the caret weight and is always +1 weight than the caret's weight)
        weight = 8 + caretWeight; 
    } else if(strcmp(str, "^") == 0) {
        weight = 7 + caretWeight; 
        // since the caret is from right to left precedence
        // the logic basically is that the caret on the right
        // side is always bigger.
        caretWeight++; // increments the additional weight of the carret
    } else if(strcmp(str, "*") == 0 || strcmp(str, "/") == 0 || strcmp(str, "%") == 0) 
        weight = 6;
    else if(strcmp(str, "+") == 0 || strcmp(str, "-") == 0)
        weight = 5;
    else if(strcmp(str, "<") == 0 || strcmp(str, "<=") == 0 || strcmp(str, ">") == 0 || strcmp(str, ">=") == 0) 
        weight = 4;
    else if(strcmp(str, "!=") == 0 || strcmp(str, "==") == 0) 
        weight = 3;
    else if(strcmp(str, "&&") == 0)
        weight = 2;
    else if(strcmp(str, "||") == 0)
        weight = 1;
    
    return weight;
}

/**
 * Returns 1 if operator1 > operator2
 *         0 if equal
 *        -1 if operator 2 > operator1 
 */
int isOperatorGreater(char *operator1, char *operator2) {
    int operator1Weight = getOperatorWeight(operator1);
    int operator2Weight = getOperatorWeight(operator2);
    
    if(operator1Weight > operator2Weight) return 1;
    else if(operator2Weight > operator1Weight) return -1; 
    return 0;
}

void infixToPostfix(char* str, char* postfix) {
    struct Stack* operators = CREATE_STACK(STACK_SIZE);
    
    // loop the infix expression from left to right - 1 (since last char should always be a digit)
    for(int i = 0; i < strlen(str); i++) {
        char currDigit[DIGIT_LENGTH] = "\0"; // -> equivalent to {'\0', '\0', ..., '\0'}
        // checks all operands
        while(isDigit(str[i])) {
            currDigit[strlen(currDigit)] = str[i];
            i++;
        }
        
        char currOperator[3] = "\0";
        currOperator[0] = str[i];
        // only get the 2nd char if < string length - 1 (to avoid Out of Bounds error)
        if(i < strlen(str) - 1) currOperator[1] = str[i + 1];
        
        // if operator is a single character-ed operator, 
        // set the index 1 to null since we only need index 0
        if(isOperator(currOperator) == 1) currOperator[1] = '\0';
        // else if it is a double character-ed operator, increment it because if not, 
        // there will be 1 irrelevant iteration where nothing will be performed. 
        else if(isOperator(currOperator) == 2) i++;

        // printf("%s - [ %s ](%d) %d\n", currDigit, currOperator, isOperator(currOperator), i);

        // if currDigit has a value, 
        // this means the token is an operand, so just simply add it to the output 
        if(currDigit[0] != '\0') { 
            strcat(postfix, currDigit);
            if(HAS_SPACE) strcat(postfix, " "); // add a space at the end
        }
        
        // if currOperator has a value, 
        // this means the token is an operator
        if(currOperator[0] != '\0') {
            // if operator == ')' pop untill '(' is found
            // then discard both parenthesis
            if(strcmp(currOperator, ")") == 0) {
                while(!STACK_EMPTY(operators) && strcmp(TOP(operators), "(") != 0) {
                    if(strcmp(TOP(operators), "(") != 0) {
                        // printf("POPPED: %s\n", TOP(operators));
                        strcat(postfix, POP(operators));
                        if(HAS_SPACE) strcat(postfix, " ");
                    }
                }
                POP(operators);
            }
            // if the stack is empty ||
            // if the top of the stack == '(' ||
            // if operator precedence is greater than the top of the stack
            else if(STACK_EMPTY(operators)) 
                PUSH(operators, currOperator);
            else if(strcmp(TOP(operators), "(") == 0 || strcmp(currOperator, "(") == 0 || isOperatorGreater(currOperator, TOP(operators)) == 1) 
                PUSH(operators, currOperator);
            // else pop all the operators from the stack which are >= in precedence
            // than that of the scanned operator. Then push the scanned operator to the stack.
            else {
                while(!STACK_EMPTY(operators) && isOperatorGreater(TOP(operators), currOperator) >= 0) {
                    // printf("POPPED: %s\n", TOP(operators));
                    strcat(postfix, POP(operators));
                    if(HAS_SPACE) strcat(postfix, " ");
                }
                PUSH(operators, currOperator);
            }
        }
    }

    // empty the operators stack after looping the infix expression
    while(!STACK_EMPTY(operators)) {
        // char needs to be converted into a string to concatenate
        // printf("TOP: %s\n", TOP(operators));
        strcat(postfix, POP(operators));
        if(HAS_SPACE) strcat(postfix, " ");
    }
}