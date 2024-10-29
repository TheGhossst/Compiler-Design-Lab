set -xe

lex lex.l
gcc -o lex lex.yy.c -ll
./lex