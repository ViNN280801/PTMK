#!/bin/bash

# Compiling source code files of sqlite3 database to object files
# -fPIC - position independent code
# -O2 - optimize by speed
# https://www.sqlite.org/howtocompile.html
gcc -c include/sqlite-amalgamation-3071300/sqlite3.c -lm -ldl -lpthread -std=c17 -fPIC -O2 -Wno-return-local-addr -o sqlite3.o

# Compiling source code files of main project
gcc -c src/db_manip.cpp -lstdc++ -std=c++20 -Wall -Wpedantic -Wextra -o db_manip.o
gcc -c src/person.cpp -lstdc++ -std=c++20 -Wall -Wpedantic -Wextra -o person.o
gcc -c main.cpp -lstdc++ -std=c++20 -Wall -Wpedantic -Wextra -o main.o

# Building project from compiled object files
gcc sqlite3.o db_manip.o person.o main.o -lstdc++ -std=c++20 -Wall -Wpedantic -Wextra -o main

# Removing all object files as unnecessary
rm *.o
