#!/bin/sh

set -xe

if [ $# -ne 1 ]; then
  echo "Usage: $0 <filename.l>"
  exit 1
fi

FILE="$1"

lex "$FILE"
gcc -o lexer lex.yy.c -lfl
./lexer
