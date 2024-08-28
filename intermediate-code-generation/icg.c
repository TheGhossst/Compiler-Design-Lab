#include <stdio.h>
#include <ctype.h>
#include <string.h>

int precedence(char op) {
    switch (op) {
        case '^':
            return 3;
        case '/':
        case '*':
            return 2;
        case '+':
        case '-':
            return 1;
        default:
            return -1;
    }
}

void convertToThreeAddress(char* expression) {
    char operandStack[20][10];
    char operatorStack[20];
    int operandTop = -1, operatorTop = -1;
    int tempCount = 1;
    char temp[10];

    for (int i = 0; i < strlen(expression); i++) {
        char current = expression[i];

        if (isalnum(current)) { 
            char operand[2] = {current, '\0'};
            strcpy(operandStack[++operandTop], operand);
        } else if (current == '(') {
            operatorStack[++operatorTop] = current;
        } else if (current == ')') {
            while (operatorTop != -1 && operatorStack[operatorTop] != '(') {
                sprintf(temp, "t%d", tempCount++);
                printf("%s = %s %c %s\n", temp, operandStack[operandTop - 1], operatorStack[operatorTop], operandStack[operandTop]);
                strcpy(operandStack[--operandTop], temp);
                operatorTop--;
            }
            operatorTop--;
        } else {
            while (operatorTop != -1 && precedence(operatorStack[operatorTop]) >= precedence(current)) {
                sprintf(temp, "t%d", tempCount++);
                printf("%s = %s %c %s\n", temp, operandStack[operandTop - 1], operatorStack[operatorTop], operandStack[operandTop]);
                strcpy(operandStack[--operandTop], temp);
                operatorTop--;
            }
            operatorStack[++operatorTop] = current;
        }
    }

    while (operatorTop != -1) {
        sprintf(temp, "t%d", tempCount++);
        printf("%s = %s %c %s\n", temp, operandStack[operandTop - 1], operatorStack[operatorTop], operandStack[operandTop]);
        strcpy(operandStack[--operandTop], temp);
        operatorTop--;
    }
}

char* convertToPostfix(char* expression) {
    static char postfix[20];
    char stack[20];
    int top = -1, k = 0;

    for (int i = 0; i < strlen(expression); i++) {
        char current = expression[i];

        if (isalnum(current)) {
            postfix[k++] = current;
        }

        else if (current == '(') {
            stack[++top] = current;
        }
        else if (current == ')') {
            while (top != -1 && stack[top] != '(') {
                postfix[k++] = stack[top--];
            }
            top--;
        }
        else {
            while (top != -1 && precedence(stack[top]) >= precedence(current)) postfix[k++] = stack[top--];
            
            stack[++top] = current;
        }
    }

    while (top != -1) postfix[k++] = stack[top--];
    

    postfix[k] = '\0';
    return postfix;
}

int main() {
    char expression[20];

    printf("\nEnter the expression: ");
    fgets(expression, sizeof(expression), stdin);
    expression[strcspn(expression, "\n")] = '\0';

    char* postfix_expression = convertToPostfix(expression);
    printf("Postfix expression: %s\n", postfix_expression);

    printf("\nThree Address Code:\n");
    convertToThreeAddress(expression);

    return 0;
}