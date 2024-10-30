#include <stdio.h>
#include <string.h>
#include <ctype.h>

struct Rules {
    char left[2];
    char right[20];
};

struct FirstSet {
    char non_terminal;
    char first[10];
};

struct Rules Rule[10];
struct FirstSet FirstSets[10];

int rule_count;
int first_set_count = 0;

void print_first_set() {
    printf("\nFirst sets:\n");
    for (int i = 0; i < first_set_count; i++) {
        printf("FIRST(%c) = { ", FirstSets[i].non_terminal);
        for (int j = 0; FirstSets[i].first[j] != '\0'; j++) printf("%c ", FirstSets[i].first[j]);
        printf("}\n");
    }
}

void add_to_first(char non_terminal, char symbol) {
    int i, j;
    for (i = 0; i < first_set_count; i++) {
        if (FirstSets[i].non_terminal == non_terminal) {
            for (j = 0; FirstSets[i].first[j] != '\0'; j++) {
                if (FirstSets[i].first[j] == symbol) return; // exists
            }
            FirstSets[i].first[j] = symbol;  // not exists so add
            FirstSets[i].first[j + 1] = '\0';
            return;
        }
    }
    FirstSets[first_set_count].non_terminal = non_terminal;
    FirstSets[first_set_count].first[0] = symbol;
    FirstSets[first_set_count].first[1] = '\0';
    first_set_count++;
}

void add_first_set_of_reference(char non_terminal, char reference) {
    for (int i = 0; i < first_set_count; i++) {
        if (FirstSets[i].non_terminal == reference) {
            for (int j = 0; FirstSets[i].first[j] != '\0'; j++) {
                if (FirstSets[i].first[j] != '@') {
                    add_to_first(non_terminal, FirstSets[i].first[j]);
                }
            }
            return;
        }
    }
}

void find_first(char non_terminal) {
    for (int i = 0; i < rule_count; i++) {
        if (Rule[i].left[0] == non_terminal) {
            int j = 0;
            int all_epsilon = 1;
            while (Rule[i].right[j] != '\0' && all_epsilon) {
                char next_symbol = Rule[i].right[j];
                
                if (islower(next_symbol)) { // terminal
                    add_to_first(non_terminal, next_symbol);
                    all_epsilon = 0;
                } 
                else if (next_symbol == '@') { // epsilon directly in the production
                    add_to_first(non_terminal, '@');
                    all_epsilon = 0;
                } 
                else { // non-terminal
                    find_first(next_symbol);
                    add_first_set_of_reference(non_terminal, next_symbol);
                    
                    // check if the non-terminal's FIRST set contains epsilon
                    int has_epsilon = 0;
                    for (int k = 0; k < first_set_count; k++) {
                        if (FirstSets[k].non_terminal == next_symbol) {
                            for (int l = 0; FirstSets[k].first[l] != '\0'; l++) {
                                if (FirstSets[k].first[l] == '@') {
                                    has_epsilon = 1;
                                    break;
                                }
                            }
                            break;
                        }
                    }
                    
                    if (!has_epsilon) {
                        all_epsilon = 0;
                    }
                }
                j++;
            }
            if (all_epsilon) { // All symbols derived to epsilon
                add_to_first(non_terminal, '@');
            }
        }
    }
}

int main() {
    printf("\nEnter the number of rules: ");
    scanf("%d", &rule_count);

    char temp[40], *token1, *token2;

    printf("\nEnter the production rules (in the form 'left->right'): \n");
    printf("\nEpsilon is represented by '@'");
    for (int i = 0; i < rule_count; i++) {
        printf("\nEnter the rule %d: ", i);
        scanf("%s", temp);

        token1 = strtok(temp, "->");
        token2 = strtok(NULL, "->");

        strcpy(Rule[i].left, token1);
        strcpy(Rule[i].right, token2);

        printf("Left -> %s\nRight -> %s\n", Rule[i].left, Rule[i].right);
    }

    for (int i = 0; i < rule_count; i++) find_first(Rule[i].left[0]);

    print_first_set();

    return 0;
}