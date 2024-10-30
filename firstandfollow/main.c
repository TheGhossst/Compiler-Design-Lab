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

struct FollowSet {
    char non_terminal;
    char follow[20];
};

struct FollowSet FollowSets[10];
int follow_set_count = 0;

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
                if (FirstSets[i].first[j] == symbol) return;
            }
            FirstSets[i].first[j] = symbol;
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
    static char visited[26] = {0};

    if (visited[non_terminal - 'A']) return;
    visited[non_terminal - 'A'] = 1;

    for (int i = 0; i < rule_count; i++) {
        if (Rule[i].left[0] == non_terminal) {
            int j = 0;
            int all_epsilon = 1;
            while (Rule[i].right[j] != '\0' && all_epsilon) {
                char next_symbol = Rule[i].right[j];
                
                if (islower(next_symbol)) {
                    add_to_first(non_terminal, next_symbol);
                    all_epsilon = 0;
                } 
                else if (next_symbol == '@') {
                    add_to_first(non_terminal, '@');
                    all_epsilon = 0;
                } 
                else {
                    find_first(next_symbol);
                    add_first_set_of_reference(non_terminal, next_symbol);
                    
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
            if (all_epsilon) { 
                add_to_first(non_terminal, '@');
            }
        }
    }

    visited[non_terminal - 'A'] = 0;
}

void add_to_follow(char non_terminal, char symbol) {
    int i, j;
    for (i = 0; i < follow_set_count; i++) {
        if (FollowSets[i].non_terminal == non_terminal) {
            for (j = 0; FollowSets[i].follow[j] != '\0'; j++) {
                if (FollowSets[i].follow[j] == symbol) return;
            }
            FollowSets[i].follow[j] = symbol;
            FollowSets[i].follow[j + 1] = '\0';
            return;
        }
    }
    FollowSets[follow_set_count].non_terminal = non_terminal;
    FollowSets[follow_set_count].follow[0] = symbol;
    FollowSets[follow_set_count].follow[1] = '\0';
    follow_set_count++;
}

void add_follow_set(char target, char source) {
    for (int i = 0; i < follow_set_count; i++) {
        if (FollowSets[i].non_terminal == source) {
            for (int j = 0; FollowSets[i].follow[j] != '\0'; j++) {
                add_to_follow(target, FollowSets[i].follow[j]);
            }
            return;
        }
    }
}

void find_follow() {
    add_to_follow(Rule[0].left[0], '$');

    int changes;
    do {
        changes = 0;
        for (int i = 0; i < rule_count; i++) {
            char left = Rule[i].left[0];
            char *right = Rule[i].right;

            for (int j = 0; right[j] != '\0'; j++) {
                if (isupper(right[j])) {
                    if (right[j+1] == '\0') {
                        int old_count = strlen(FollowSets[follow_set_count-1].follow);
                        add_follow_set(right[j], left);
                        if (strlen(FollowSets[follow_set_count-1].follow) > old_count) {
                            changes = 1;
                        }
                    } else if (islower(right[j+1])) {
                        add_to_follow(right[j], right[j+1]);
                    } else if (isupper(right[j+1])) {
                        int has_epsilon = 0;
                        for (int k = 0; k < first_set_count; k++) {
                            if (FirstSets[k].non_terminal == right[j+1]) {
                                for (int l = 0; FirstSets[k].first[l] != '\0'; l++) {
                                    if (FirstSets[k].first[l] != '@') {
                                        add_to_follow(right[j], FirstSets[k].first[l]);
                                    } else {
                                        has_epsilon = 1;
                                    }
                                }
                                break;
                            }
                        }
                        if (has_epsilon) {
                            add_follow_set(right[j], left);
                        }
                    }
                }
            }
        }
    } while (changes);
}

void print_follow_set() {
    printf("\nFollow sets:\n");
    for (int i = 0; i < follow_set_count; i++) {
        printf("FOLLOW(%c) = { ", FollowSets[i].non_terminal);
        for (int j = 0; FollowSets[i].follow[j] != '\0'; j++) printf("%c ", FollowSets[i].follow[j]);
        printf("}\n");
    }
}

int main() {
    printf("\nEnter the number of rules: ");
    scanf("%d", &rule_count);

    char temp[40], *token1, *token2;

    printf("\nEnter the production rules (in the form 'left->right'): \n");
    printf("\nEpsilon is represented by '@'");
    for (int i = 0; i < rule_count; i++) {
        printf("\nEnter the rule %d: ", i + 1);
        scanf("%s", temp);

        token1 = strtok(temp, "->");
        token2 = strtok(NULL, "->");

        strcpy(Rule[i].left, token1);
        strcpy(Rule[i].right, token2);

        printf("Left -> %s\nRight -> %s\n", Rule[i].left, Rule[i].right);
    }

    for (int i = 0; i < rule_count; i++) find_first(Rule[i].left[0]);
    find_follow();

    print_first_set();
    print_follow_set();

    return 0;
}
/*
Enter the number of rules: 3

Enter the production rules (in the form 'left->right'):

Epsilon is represented by '@'
Enter the rule 1: S->AaBb
Left -> S
Right -> AaBb

Enter the rule 2: A->@
Left -> A
Right -> @

Enter the rule 3: B->@
Left -> B
Right -> @

First sets:
FIRST(A) = { @ }
FIRST(S) = { a }
FIRST(B) = { @ }

Follow sets:
FOLLOW(S) = { $ }
FOLLOW(A) = { a }
FOLLOW(B) = { b }*/