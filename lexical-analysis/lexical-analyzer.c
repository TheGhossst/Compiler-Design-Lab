#include <stdio.h>
#include <string.h>

struct identifier{
    int slno;
    char name[30];
};
struct identifier ID[40];
int idcount = 0;

//keywords : if int void main else printf
//operators + - += -= = ==

void displaysymtab(){
    printf("\n\nSymbol Table:\n");
    printf("Sl.no\t\tIdentifier\n.................................");
    for(int i = 0; i < idcount; i++){
        printf("\n%d\t\t%s", ID[i].slno, ID[i].name);
    }
}

int isthereDuplicate(char * str){
    for(int i = 0; i < idcount; i++){
        if (strcmp(str, ID[i].name) == 0)    return 1;
    }
    return 0;
}
int isIdentifier(char c){
    if (c >= 'a' && c <= 'z' || c  >= 'A' && c <= 'Z' || c >= '0' && c <= '9')
        return 1;
    return 0;
}

void startlexical(char  *file_stream){
    int b = 0;
    int f = 0;
q0:
    //printf("\nCurrent in q0 -> %c", file_stream[f]);
    if (file_stream[f] == '\0'){
        f++;
        goto end;
    }

    if (file_stream[f] == 'i'){
        f++;
        goto q1;
    }

    else if (file_stream[f] == 'v'){
        f++;
        goto q5;
    }

    else if (file_stream[f] == 'm'){
        f++;
        goto q9;
    }

    else if (file_stream[f] == 'e'){
        f++;
        goto q13;
    }

    else if (file_stream[f] == 'p'){
        f++;
        goto q17;
    }
    
    else if ((file_stream[f] >= 'a' && file_stream[f] <= 'z')||(file_stream[f] >= 'A' && file_stream[f] <= 'Z')||(file_stream[f] == '_')){
        f++;
        goto identifier;
    }
    else if (file_stream[f] == '+'){
        f++;
        goto q23;
    }

    else if (file_stream[f] == '-'){
        f++;
        goto q26;
    }

    else if (file_stream[f] == '='){
        f++;
        goto q29;
    }

    else if (file_stream[f] == '(' || file_stream[f] == ')' || file_stream[f] == '{' || file_stream[f] == '}'){
        printf("\n< Bracket, %c >", file_stream[f]);
        f++;
        b = f;
        goto q0;
    }
    else if (file_stream[f] == '\'' || file_stream[f] == '"') {
        char opening_quote = file_stream[f];
        printf("\n< String Literal, \"");
        f++;
        while (file_stream[f] != opening_quote && file_stream[f] != '\0') {
            printf("%c", file_stream[f]);
            f++;
        }

        if (file_stream[f] == opening_quote) {
            printf(" \" >");
            f++;
        } else {
            printf(" [Error: Unterminated string literal] ");
        }

        b = f;
        goto q0;
    }

    else if (file_stream[f] >= '0' && file_stream[f] <= '9'){
        printf("\n< DIGIT, ");
        while(file_stream[f] >= '0' && file_stream[f] <= '9'){
            printf("%c", file_stream[f]);
            f++;
        }
        printf(" >");
        b = f;
        goto q0;
    }

    else if(file_stream[f] == '.' || file_stream[f] == ',' || file_stream[f] == ';', file_stream[f] == ':'){
        printf("\n< PUNCTUATION, %c >", file_stream[f]);
        f++;
        b = f;
        goto q0;
    }

    else{
        f++;
        goto q0;
    }

q1:
    if (file_stream[f] == 'n'){
        f++;
        goto q2;
    }
    else if (file_stream[f] == 'f'){
        f++;
        goto q3;
    }
    else if (isIdentifier(file_stream[f])){
        f++;
        goto identifier;
    }

q2:
    if (file_stream[f] == 't'){
        f++;
        goto q4;
    }
q3:
    if (isIdentifier(file_stream[f])){
        f++;
        goto identifier;
    }
    else{
        f++;
        printf("\n< Keyword, if >");
        b = f;
        goto q0;
    }


q4:
    if (isIdentifier(file_stream[f])){
        f++;
        goto identifier;
    }
    else{
        f++;
        printf("\n< Keyword, int >");
        b = f;
        goto q0;
    }

q5:
    if (file_stream[f] == 'o'){
        f++;
        goto q6;
    }
    else if (isIdentifier(file_stream[f])){
        f++;
        goto identifier;
    }
q6:
    if (file_stream[f] == 'i'){
        f++;
        goto q7;
    }
    else if (isIdentifier(file_stream[f])){
        f++;
        goto identifier;
    }
q7:
    if (file_stream[f] == 'd'){
        f++;
        goto q8;
    }
    else if (isIdentifier(file_stream[f])){
        f++;
        goto identifier;
    }
q8:
    if (isIdentifier(file_stream[f])){
        f++;
        goto identifier;
    }
    else{
        f++;
        printf("\n< Keyword, void >");
        b = f;
        goto q0;
    }
q9:
    if (file_stream[f] == 'a'){
        f++;
        goto q10;
    }
    else if (isIdentifier(file_stream[f])){
        f++;
        goto identifier;
    }
q10:
    if (file_stream[f] == 'i'){
        f++;
        goto q11;
    }
    else if (isIdentifier(file_stream[f])){
        f++;
        goto identifier;
    }
q11:
    if (file_stream[f] == 'n'){
        f++;
        goto q12;
    }
    else if (isIdentifier(file_stream[f])){
        f++;
        goto identifier;
    }
q12:
    //printf("\nCurrent -> %c", file_stream[f]);
    if (isIdentifier(file_stream[f])){
        f++;
        goto identifier;
    }
    else{
        printf("\n< Keyword, main >");
        b = f;
        goto q0;
    }
q13:
    if (file_stream[f] == 'l'){
        f++;
        goto q14;
    }
    else if (isIdentifier(file_stream[f])){
        f++;
        goto identifier;
    }
q14:
    if (file_stream[f] == 's'){
        f++;
        goto q15;
    }
    else if (isIdentifier(file_stream[f])){
        f++;
        goto identifier;
    }
q15:
    if (file_stream[f] == 'e'){
        f++;
        goto q16;
    }
    else if (isIdentifier(file_stream[f])){
        f++;
        goto identifier;
    }
q16:
    if (file_stream[f] == ' '){
        f++;
        printf("\n< Keyword, else >");
        b = f;
        goto q0;
    }
    else if (isIdentifier(file_stream[f])){
        f++;
        goto identifier;
    }
q17:
    if (file_stream[f] == 'r'){
        f++;
        goto q18;
    }
    else if (isIdentifier(file_stream[f])){
        f++;
        goto identifier;
    }
q18:
    if (file_stream[f] == 'i'){
        f++;
        goto q19;
    }
    else if (isIdentifier(file_stream[f])){
        f++;
        goto identifier;
    }
q19:
    if (file_stream[f] == 'n'){
        f++;
        goto q20;
    }
    else if (isIdentifier(file_stream[f])){
        f++;
        goto identifier;
    }
q20:
    if (file_stream[f] == 't'){
        f++;
        goto q21;
    }
    else if (isIdentifier(file_stream[f])){
        f++;
        goto identifier;
    }
q21:
    if (file_stream[f] == 'f'){
        f++;
        goto q22;
    }
    else if (isIdentifier(file_stream[f])){
        f++;
        goto identifier;
    }
q22:
    if (isIdentifier(file_stream[f])){
        f++;
        goto identifier;
    }
    else{
        printf("\n< Keyword, printf >");
        b = f;
        goto q0;
    }
q23:
    if (file_stream[f] == '=') {
        f++;
        goto q24;
    } 
    else if (file_stream[f] == '+') {
        f++;
        goto q25;
    } 
    else {
        printf("\n< Operator, + >");
        b = f;
        goto q0;
    }

q24:
    if (isIdentifier(file_stream[f])) {
        f++;
        printf("\n< Operator, += >");
        b = f;
        goto q0;
    }

q25:
    if (isIdentifier(file_stream[f])) {
        f++;
        printf("\n< Operator, ++ >");
        b = f;
        goto q0;
    }
q26:
    if (file_stream[f] == '=') {
        f++;
        goto q24;
    } 
    else if (file_stream[f] == '-') {
        f++;
        goto q27;
    } 
    else {
        printf("\n< Operator, - >");
        b = f;
        goto q0;
    }

q27:
    if (isIdentifier(file_stream[f])) {
        f++;
        printf("\n< Operator, -= >");
        b = f;
        goto q0;
    }

q28:
    if (isIdentifier(file_stream[f])) {
        f++;
        printf("\n< Operator, -- >");
        b = f;
        goto q0;
    }

q29:
    if (file_stream[f] == '='){
        f++;
        goto q30;
    }
    else if (isIdentifier(file_stream[f]) || file_stream[f] == ' '){
        f++;
        printf("\n< Operator, = >");
        b = f;
        goto q0;
    }
q30:
    if (isIdentifier(file_stream[f]) || file_stream[f] == ' '){
        f++;
        printf("\n< Operator, == >");
        b = f;
        goto q0;
    }

identifier:
    //printf("\ncurrent in identifier -> %c", file_stream[f]);
    if (isIdentifier(file_stream[f])){
        f++;
        goto identifier;
    }
    else{
        printf("\n< Identifier, ");
        char temp[30];
        int j = 0;

        for (int i = b; i < f && j < sizeof(temp) - 1; i++) {
            temp[j++] = file_stream[i];
            printf("%c", file_stream[i]);
        }
        temp[j] = '\0';

        printf(" >");
        b = f;
        printf("\nGoing for dup check -> %s", temp);
        if (!isthereDuplicate(temp)){
            strcpy(ID[idcount].name, temp);
            ID[idcount].slno =  idcount;
            idcount++;
        } 
        goto q0;
    }
end:
    printf("\nComplete");
    return;
}
int main(){
    FILE *in = fopen("input.c", "r");
    if (in == NULL) {
        perror("Error opening file");
        return 1;
    }

    char file_stream[100];
    char c;
    int i = 0;

    while ((c = fgetc(in)) != EOF && i < sizeof(file_stream) - 1) {
        if (c == '#') {
            while (c != '\n' && c != EOF) {
                c = fgetc(in);
            }
        } else {
            file_stream[i++] = c;
        }
    }
    file_stream[i] = '\0'; 

    fclose(in);

    printf("%s", file_stream);

    startlexical(file_stream);
    displaysymtab();
    return 0;
}