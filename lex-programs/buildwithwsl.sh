#!/bin/sh

set -xe


if ! command -v dos2unix > /dev/null; then
  echo "dos2unix is not installed. Please install it and try again."
  exit 1
fi

dos2unix "$0"

if [ $# -ne 1 ]; then
  echo "Usage: $0 <filename.l>"
  exit 1
fi

FILE="$1"
dos2unix "$FILE"

lex "$FILE"
gcc -o lexer lex.yy.c -lfl
./lexer