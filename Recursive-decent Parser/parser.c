#include <stdio.h>
#include <string.h>

char input[100];
int pos = 0;
int backtrack = 0;

int E();
int T();
int F();

// F -> ( E ) | i
int F() {
    if (input[pos] == '(') {
        pos++;
        int result = E();
        if (input[pos] == ')') {
            pos++;
            return result;
        } else {
            printf("Error: missing closing parenthesis\n");
            return 0;
        }
    } else if (input[pos] == 'i') {
        backtrack++;
        pos++;
        return 1;
    } else {
        printf("Error: invalid input\n");
        return 0;
    }
}

// T -> F * T | F
int T() {
    int result = F();
    while (input[pos] == '*') {
        pos++;
        result *= F();
    }
    return result;
}

// E -> T + E | T
int E() {
    int result = T();
    while (input[pos] == '+') {
        pos++;
        result += T();
    }
    return result;
}

int main() {
    printf("\nEnter the expression: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';

     E();

    if (input[pos] != '\0') {
        printf("\nError: invalid expression\n");
    } else {
        printf("\nValid");
        printf("\nBacktrack = %d", backtrack);
    }

    return 0;
}