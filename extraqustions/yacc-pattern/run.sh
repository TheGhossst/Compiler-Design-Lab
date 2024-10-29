#!/bin/sh

set -xe

yacc -d pattern.y
lex pattern.l

gcc -o pattern lex.yy.c y.tab.c -ll
./pattern