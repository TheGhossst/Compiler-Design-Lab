#!/bin/sh

set -xe

yacc -d calulator.y
lex calculator.l

gcc -o code lex.yy.c y.tab.c -lfl
./code