cmake_minimum_required(VERSION 3.16)
project(XTetris C)

set(CMAKE_C_STANDARD 90)

add_executable(XTetris main.c Tetramino/tetramino.h Tetramino/colori.h Tetramino/rotazioni.h)
