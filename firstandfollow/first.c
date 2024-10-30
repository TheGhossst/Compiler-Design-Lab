#include <stdio.h>
#include <string.h>
#include <ctype.h>

struct Rules {
    char left[2];
    char right[20];
};

struct First{
    char NT;
    char first_set[100];
    int index;
    int isComputed;
};

struct Rules Rule[100];
struct First FirstSet[10];
int rule_count;
int first_count = 0;

void find_first(char non_terminal){
    for (int i = 0; i < rule_count;i++){
        if (Rule[i].left[0] == non_terminal){
            if (islower(Rule[i].right[0])){ //terminal
                FirstSet[first_count].first_set[FirstSet[first_count].index++] = Rule[i].right[0];
            }   
        }
    }
}

int main(){
    for (int i = 0; i < 10; i++){
         FirstSet[i].isComputed = 0;
         FirstSet[i].index = 0;
    }
    
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

        //printf("Left -> %s\nRight -> %s\n", Rule[i].left, Rule[i].right);
    }
    
    for (int i = 0; i < rule_count; i++) find_first(Rule[i].left[0]);
    displayFirstSet();
}