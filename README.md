# Wordle (C++ Terminal Edition)

A lightweight, terminal-based Wordle clone for 6-letter words, written in C++. Supports Easy and Hard modes with ANSI-colored feedback and dictionary validation.

## Features
- 6-letter Wordle with up to 6 guesses
- ANSI color feedback (Green = correct spot, Yellow = present elsewhere)
- Dictionary validation against `words.txt`
- Easy mode (default) and Hard mode (locks greens, require yellows, forbid grays)
- Duplicate-safe two-pass coloring algorithm

## Requirements
- C++17 compiler (GCC/Clang/MSVC)
- Terminal with ANSI color support
- `words.txt` placed next to the executable (one 6-letter word per line, case-sensitive)

## Build
```bash  
# Linux/macOS  
g++ -std=c++17 -O2 -Wall -Wextra -pedantic -o wordle wordle.cpp  

# Windows (MinGW)  
g++ -std=c++17 -O2 -Wall -Wextra -pedantic -o wordle.exe wordle.cpp  
