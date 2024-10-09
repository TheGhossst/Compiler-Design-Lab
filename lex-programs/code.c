#include <stdio.h>
#include <string.h>

int isPal(char *str){
    int left = 0;
    int right = strlen(str) - 1;
    int f = 1;

    while (left < right){
        if (str[left] == str[right]){
            left++;
            right--;
        }
        else{
            f = 0;
            break;
        }
    }

    return f;
}

void main(){
    char string[20];

    printf("\nEnter a string: ");
    fgets(string, sizeof(string), stdin);
    
    string[strcspn(string, "\n")] = '\0';

    if (isPal(string)) printf("Palindrome\n");
    else  printf("Not Palindrome\n");
}