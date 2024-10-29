set -xe

yacc -d count.y
lex count.l
gcc -o count lex.yy.c y.tab.c -ll
./count