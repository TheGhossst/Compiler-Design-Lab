#include <stdio.h>
#include <string.h>
#include <ctype.h>

int nop, m = 0;
char prod[10][10], res[10];

void FIRST(char c);
void FOLLOW(char c);
void result(char c);
void computeFirstFollow();

int main()
{
    int i;
    printf("Enter the number of productions: ");
    scanf("%d", &nop);
    puts("\nEnter the production string like \"E=E+T\" and epsilon as #");
    
    for (i = 0; i < nop; ++i)
    {
        printf("Enter production Number %d: ", i + 1);
        scanf("%s", prod[i]);
    }

    computeFirstFollow();
    
    return 0;
}

void computeFirstFollow()
{
    char nonTerminals[10];
    int ntCount = 0;

    for (int i = 0; i < nop; ++i)
    {
        if (strchr(nonTerminals, prod[i][0]) == NULL)
        {
            nonTerminals[ntCount++] = prod[i][0];
        }
    }

    printf("\nFIRST Sets:\n");
    for (int i = 0; i < ntCount; ++i)
    {
        m = 0;
        memset(res, '\0', sizeof(res));
        FIRST(nonTerminals[i]);
        printf("FIRST(%c) = { ", nonTerminals[i]);
        for (int j = 0; j < m; ++j)
            printf("%c ", res[j]);
        puts("}");
    }

    printf("\nFOLLOW Sets:\n");
    for (int i = 0; i < ntCount; ++i)
    {
        m = 0;
        memset(res, '\0', sizeof(res));
        FOLLOW(nonTerminals[i]);
        printf("FOLLOW(%c) = { ", nonTerminals[i]);
        for (int j = 0; j < m; ++j)
            printf("%c ", res[j]);
        puts("}");
    }
}

void FOLLOW(char c)
{
    int i, j;
    if (prod[0][0] == c)
        result('$');

    for (i = 0; i < nop; ++i)
    {
        for (j = 2; j < strlen(prod[i]); ++j)
        {
            if (prod[i][j] == c)
            {
                if (prod[i][j + 1] != '\0')
                    FIRST(prod[i][j + 1]);
                if (prod[i][j + 1] == '\0' && c != prod[i][0])
                    FOLLOW(prod[i][0]);
            }
        }
    }
}

void FIRST(char c)
{
    int k;
    if (!(isupper(c)))
        result(c);

    for (k = 0; k < nop; ++k)
    {
        if (prod[k][0] == c)
        {
            if (prod[k][2] == '#')
                FOLLOW(prod[k][0]);
            else if (prod[k][2] == c)
                return;
            else if (islower(prod[k][2]))
                result(prod[k][2]);
            else
                FIRST(prod[k][2]);
        }
    }
}

void result(char c)
{
    int i;
    for (i = 0; i < m; ++i)
        if (res[i] == c)
            return;
    res[m++] = c;
}