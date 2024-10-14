# Compiler Design Lab Experiments

This repository contains various lab experiments for the **Compiler Design** course. The experiments involve implementing different phases of a compiler, including lexical analysis, syntax analysis, and intermediate code generation.

## Lab Experiment Cycle

### 1. Lexical Analysis
- **Description**: This experiment focuses on lexical analysis, where the source code is scanned to extract meaningful tokens.
- **Files**: `lexical-analysis/`

### 2. Recursive Descent Parser
- **Description**: This experiment implements a **Recursive Descent Parser**, which is a top-down parser for analyzing the structure of the given source code.
- **Files**: `Recursive-decent Parser/`

### 3. Shift-Reduce (SR) Parser
- **Description**: The **SR Parser** experiment involves implementing a **Shift-Reduce Parser**, which is a bottom-up parsing technique used in syntax analysis.
- **Files**: `SR Parser/`

### 4. Intermediate Code Generation
- **Description**: This experiment focuses on generating intermediate code, which is an abstract representation of the source code that can be optimized and converted to target code.
- **Files**: `intermediate-code-generation/`

### Lex Programs

1. **Lex Program to Count Words and Lines**
   - **Description**: A Lex program (`lex1.l`) to count the number of words and lines in a given input.
   - **Files**: `lex-programs/lex1.l`

2. **Lex Program to Count Vowels and Consonants**
   - **Description**: A Lex program (`lex2.l`) to count the number of vowels and consonants in a given input.
   - **Files**: `lex-programs/lex2.l`

3. **Lex Program to Convert 'abc' to 'ABC'**
   - **Description**: A Lex program (`lex3.l`) to convert lowercase letters (`abc`) to uppercase letters (`ABC`).
   - **Files**: `lex-programs/lex3.l`

4. **Lexical Analysis Using Lex**
   - **Description**: This Lex program (`lexusinglex.l`) performs lexical analysis to identify and extract tokens from the input source code.
   - **Files**: `lex-programs/lexusinglex.l`

## YACC Programs

### 1. YACC Program to Recognize Valid Arithmetic Expressions
- **Description**: This YACC program parses and recognizes valid arithmetic expressions. It performs syntax analysis to ensure that the input is a correctly structured arithmetic expression.
- **Files**: `yacc/validExpression`

### 2. YACC Program to Recognize a Pattern of Any Characters Followed by Letters and Digits
- **Description**: This YACC program parses a pattern where the input consists of any characters followed by letters and digits. It demonstrates how to recognize and validate specific patterns using YACC.
- **Files**: `yacc/char`

