#!/bin/sh

set -xe

if [ $# -ne 2 ]; then
  echo "Usage: $0 <filename.y> <filename.l>"
  exit 1
fi

YFILE="$1"
LFILE="$2"

YFILENAME=$(basename "$YFILE" .y)

bison -d "$YFILE"
flex "$LFILE"

gcc -o parser "$YFILENAME.tab.c" lex.yy.c -lfl
./parser
