cmake_minimum_required(VERSION 3.26)

project(consoleApp
        VERSION 1.0
        DESCRIPTION "Console app that works with sqlite3 and have 5 modes"
        LANGUAGES C CXX)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_FLAGS "-lm -ldl -lpthread -std=c17 -fPIC -O2 -Wno-return-local-addr")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-Wall -Wpedantic -Wextra")

add_executable(main include/sqlite-amalgamation-3071300/sqlite3.c src/person.cpp src/db_manip.cpp main.cpp)
