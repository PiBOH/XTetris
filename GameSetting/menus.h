#ifndef XTETRIS_MENUS_H
#define XTETRIS_MENUS_H

#ifndef XTETRIS_STDIO
#import <stdio.h>
#endif

#ifndef XTETRIS_STRING
#include "../Elements/mystring.h"
#endif

typedef
enum mode_t {
    SINGLEPLAYER = 1,
    MULTIPLAYER,
}
Mode_t;

/**
 * Metodo per stampare a terminale il titolo del gioco
 */
void print_titologioco();

/**
 * Metodo per stampare a terminale il menù principale del gioco
 */
Mode_t menu_gioco();

#endif //XTETRIS_MENUS_H
