cmake_minimum_required(VERSION 3.16)
project(XTetris C)

set(CMAKE_C_STANDARD 90)

add_executable(XTetris main.c Tetramino/tetramino.h Elements/colori.h Elements/rotazioni.h Tetramino/tetramino.c PianoDiGioco/pianodigioco.c PianoDiGioco/pianodigioco.h Elements/boolType.h GameSetting/menus.c GameSetting/menus.h Elements/mystring.h GameSetting/Player/player.c GameSetting/Player/player.h)
