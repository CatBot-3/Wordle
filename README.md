# Wordle (C++ Terminal Edition)

A lightweight, terminal-based Wordle clone for 6-letter words, written in C++. Supports Easy and Hard modes with ANSI-colored feedback and dictionary validation.

## Features
- 6-letter Wordle with up to 6 guesses
- ANSI color feedback (Green = correct spot, Yellow = present elsewhere)
- Dictionary validation against `words.txt`
- Easy mode (default) and Hard mode (locks greens, require yellows, forbid grays)
- Duplicate-safe two-pass coloring algorithm

## Requirements
- C++20 compiler (GCC/Clang/MSVC)
- Terminal with ANSI color support
- `words.txt` placed next to the executable (one 6-letter word per line, case-sensitive)

## Build
```bash  
# Linux/macOS  
g++ -std=c++20 -O2 -Wall -Wextra -pedantic -o wordle wordle.cc

# Windows (MinGW)  
g++ -std=c++20 -O2 -Wall -Wextra -pedantic -o wordle.exe wordle.cc
```

## Usage
```bash
./wordle SECRET [MODE]
# SECRET: 6-letter word present in words.txt
# MODE: 0 = Easy (default), 1 = Hard
```
Examples:
```bash
./wordle orange           # Easy mode
./wordle orange 1         # Hard mode
```

## Exit Codes and Validation
#### Missing/invalid arguments and states return specific codes:
1: No secret word provided
2: Secret word not length 6
3: Mode is not an integer
4: Mode must be 0 or 1
5: Secret word not found in words.txt

#### Runtime input validation:
- Guess length must be 6
- Guess must exist in words.txt
- Hard mode violations produce an error and prompt again

#### words.txt
- Place words.txt in the same directory as the executable.
- One word per line, exactly 6 characters; comparisons are case-sensitive.
