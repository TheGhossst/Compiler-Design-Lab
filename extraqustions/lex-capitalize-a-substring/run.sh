#!/bin/sh

set -xe

lex capitalize.l

gcc -o capital lex.yy.c -lfl
./capital