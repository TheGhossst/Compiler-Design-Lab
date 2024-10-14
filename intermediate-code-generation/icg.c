#include <stdio.h>
#include <ctype.h>
#include <string.h>

struct ThreeAddressCode {
    char op[5];
    char arg1[10];
    char arg2[10];
    char result[10];
};

struct ThreeAddressCode tac[20];
int tacCount = 0;

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
                
                snprintf(tac[tacCount].op, sizeof(tac[tacCount].op), "%c", operatorStack[operatorTop]);
                strcpy(tac[tacCount].arg1, operandStack[operandTop - 1]);
                strcpy(tac[tacCount].arg2, operandStack[operandTop]);
                strcpy(tac[tacCount].result, temp);
                tacCount++;

                strcpy(operandStack[--operandTop], temp);
                operatorTop--;
            }
            operatorTop--;
        } else {
            while (operatorTop != -1 && precedence(operatorStack[operatorTop]) >= precedence(current)) {
                sprintf(temp, "t%d", tempCount++);
                printf("%s = %s %c %s\n", temp, operandStack[operandTop - 1], operatorStack[operatorTop], operandStack[operandTop]);
                
                snprintf(tac[tacCount].op, sizeof(tac[tacCount].op), "%c", operatorStack[operatorTop]);
                strcpy(tac[tacCount].arg1, operandStack[operandTop - 1]);
                strcpy(tac[tacCount].arg2, operandStack[operandTop]);
                strcpy(tac[tacCount].result, temp);
                tacCount++;

                strcpy(operandStack[--operandTop], temp);
                operatorTop--;
            }
            operatorStack[++operatorTop] = current;
        }
    }

    while (operatorTop != -1) {
        sprintf(temp, "t%d", tempCount++);
        printf("%s = %s %c %s\n", temp, operandStack[operandTop - 1], operatorStack[operatorTop], operandStack[operandTop]);

        snprintf(tac[tacCount].op, sizeof(tac[tacCount].op), "%c", operatorStack[operatorTop]);
        strcpy(tac[tacCount].arg1, operandStack[operandTop - 1]);
        strcpy(tac[tacCount].arg2, operandStack[operandTop]);
        strcpy(tac[tacCount].result, temp);
        tacCount++;

        strcpy(operandStack[--operandTop], temp);
        operatorTop--;
    }
}

void quadruple() {
    printf("\nQuadruple Table:\n");
    printf("Op\tArg1\tArg2\tResult\n");

    for (int i = 0; i < tacCount; i++) {
        printf("%s\t%s\t%s\t%s\n", tac[i].op, tac[i].arg1, tac[i].arg2, tac[i].result);
    }
}

void triple() {
    printf("\nTriple Table:\n");
    printf("Index\tOp\tArg1\tArg2\n");

    for (int i = 0; i < tacCount; i++) {
        printf("(%d)\t%s\t", i + 1, tac[i].op);
        if (tac[i].arg1[0] == 't')
            printf("(%c)\t", tac[i].arg1[1]);
        else
            printf(" %s\t", tac[i].arg1);

        if (tac[i].arg2[0] == 't')
            printf("(%c)\n", tac[i].arg2[1]);
        else
            printf(" %s\n", tac[i].arg2);

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

    quadruple();
    triple();    

    return 0;
}

/*Output
Enter the expression: ((a*b)+(b*e))
Postfix expression: ab*be*+

Three Address Code:
t1 = a * b
t2 = b * e
t3 = t1 + t2

Quadruple Table:
Op      Arg1    Arg2    Result
*       a       b       t1
*       b       e       t2
+       t1      t2      t3

Triple Table:
Index   Op      Arg1    Arg2
(1)     *        a       b
(2)     *        b       e
(3)     +       (1)     (2)
*/