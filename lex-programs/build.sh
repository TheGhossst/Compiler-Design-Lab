#!/bin/sh

set -xe


lex lex1.l
gcc -o lexer lex.yy.c
./lexer