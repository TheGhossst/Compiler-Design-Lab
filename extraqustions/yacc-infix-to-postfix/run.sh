#!/bin/sh

set -xe

yacc -d postfix.y
lex postfix.l

gcc -o postfix lex.yy.c y.tab.c -ll
./postfix