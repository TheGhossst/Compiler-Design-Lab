#include <stdio.h>
#include <string.h>

struct ProductionRule {
    char left[10];
    char right[10];
};

void printTableRow(const char* stack, const char* input, const char* action) {
    printf("%-30s $%-29s %-30s\n", stack, input, action);
}

int canBeReduced(char stack[], int *stack_top, struct ProductionRule rules[], int rule_count) {
    char startingSymbol[20];
    sprintf(startingSymbol, "$%s", rules[0].left);

    if (strcmp(stack, startingSymbol) == 0) return 0;

    for (int i = 0; i < rule_count; i++) {
        int right_len = strlen(rules[i].right);
        int left_len = strlen(rules[i].left);

        if (*stack_top >= right_len &&
            strncmp(&stack[*stack_top - right_len], rules[i].right, right_len) == 0) {
            
            char action[40];
            sprintf(action, "Reduce %s -> %s", rules[i].left, rules[i].right);

            *stack_top -= right_len;
            strcpy(&stack[*stack_top], rules[i].left);
            *stack_top += left_len;
            stack[*stack_top] = '\0';

            printTableRow(stack, "", action);
            return 1;
        }
    }
    return 0;
}

int canBeParsed(char input[40], struct ProductionRule rules[], int rule_count) {
    char stack[40];
    stack[0] = '$';
    stack[1] = '\0';

    char startingSymbol[20];
    sprintf(startingSymbol, "$%s", rules[0].left);

    int stack_top = 1;

    printf("\n%-30s %-30s %-30s\n", "Stack", "Input", "Action");
    printf("%-30s %-30s %-30s\n", "-----", "-----", "------");

    for (int i = 0; i < strlen(input); i++) {
        stack[stack_top++] = input[i];
        stack[stack_top] = '\0';

        printTableRow(stack, &input[i+1], "Shift");

        while (canBeReduced(stack, &stack_top, rules, rule_count));
            

        if (strcmp(stack, startingSymbol) == 0 && i == strlen(input) - 1) {
            printTableRow(stack, &input[i+1], "Accept");
            return 1;
        }
    }
    return 0;
}

int main() {
    int rule_count, i;
    char temp[40], *token1, *token2, input[40];

    printf("\nEnter the number of production rules: ");
    scanf("%d", &rule_count);

    struct ProductionRule rules[rule_count];

    printf("\nEnter the production rules (in the form 'left->right'): \n");
    for (i = 0; i < rule_count; i++) {
        scanf("%s", temp);
        token1 = strtok(temp, "->");
        token2 = strtok(NULL, "->");
        strcpy(rules[i].left, token1);
        strcpy(rules[i].right, token2);
    }

    getchar();

    printf("\nEnter the input to be parsed: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0'; 

    if (canBeParsed(input, rules, rule_count)) {
        printf("\nThe input %s was parsed successfully\n", input);
    } else {
        printf("\nThe input %s cannot be parsed\n", input);
    }

    return 0;
}
/*Output
Enter the number of production rules: 4

Enter the production rules (in the form 'left->right'): 
S->(L)
S->a
L->L,S
L->S

Enter the input to be parsed: (a,(a,a))

Stack                          Input                          Action
-----                          -----                          ------
$(                             $a,(a,a))                      Shift
$(a                            $,(a,a))                       Shift
$(S                            $                              Reduce S -> a
$(L                            $                              Reduce L -> S
$(L,                           $(a,a))                        Shift
$(L,(                          $a,a))                         Shift
$(L,(a                         $,a))                          Shift
$(L,(S                         $                              Reduce S -> a 
$(L,(L                         $                              Reduce L -> S
$(L,(L,                        $a))                           Shift
$(L,(L,a                       $))                            Shift
$(L,(L,S                       $                              Reduce S -> a
$(L,(L                         $                              Reduce L -> L,S
$(L,(L)                        $)                             Shift
$(L,S                          $                              Reduce S -> (L)
$(L                            $                              Reduce L -> L,S
$(L)                           $                              Shift
$S                             $                              Reduce S -> (L)
$S                             $                              Accept

The input (a,(a,a)) was parsed successfully
*/
