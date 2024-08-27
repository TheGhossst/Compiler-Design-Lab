#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

char *input;
int pos = 0;

int E();
int T();
int F();

char peek() {
    return input[pos];
}

void consume() {
    pos++;
}

int digit() {
    int result = 0;
    while (isdigit(peek())) {
        result = result * 10 + (peek() - '0');
        consume();
    }
    return result;
}

// F -> (E) | digit
int F() {
    if (peek() == '(') {
        consume();  
        int result = E();
        if (peek() == ')') {
            consume();
            return result;
        } else {
            printf("\nParsing Error\nError: Expected closing parenthesis\n");
            exit(1);
        }
    } else if (isdigit(peek())) {
        return digit();
    } else {
        printf("\nParsing Error\nError: Unexpected character %c\n", peek());
        exit(1);
    }
}

// T -> F * T | F
int T() {
    int result = F();
    if (peek() == '*') {
        consume(); 
        result *= F();
    }
    return result;
}

// E -> T + E | T
int E() {
    int result = T();
    if (peek() == '+') {
        consume();
        result += T();
    }
    return result;
}

int main() {
    printf("Recursive Decent Parser\n");
    printf("----------------------------------\n");
    printf("\nGrammer used in the parser:\n");
    
    printf("E -> T + E | T\nT -> F * T | F\nF -> (E) | digit\ndigit -> 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9\n\n");
    char expression[100];
    printf("Enter an arithmetic expression: ");
    fgets(expression, sizeof(expression), stdin);
    input = expression;
    
    int result = E();
    
    if (peek() != '\n' && peek() != '\0') {
        printf("\nParsing Error\nError: Unexpected character %c\n", peek());
    } else {
        printf("\nParsed Successfully\n");
        printf("Result: %d\n", result);
    }
    
    return 0;
}
/*Output
Recursive Decent Parser
----------------------------------
Grammer used in the parser:
E -> T + E | T
T -> F * T | F
F -> (E) | digit
digit -> 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9
Enter an arithmetic expression: 2+3
Parsed Successfully
Result: 5

Recursive Decent Parser
----------------------------------
Grammer used in the parser:
E -> T + E | T
T -> F * T | F
F -> (E) | digit
digit -> 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9
Enter an arithmetic expression: 2-3
Parsing Error
Error: Unexpected character -
*/