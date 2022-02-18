#ifndef XTETRIS_MENUS_H
#define XTETRIS_MENUS_H

#ifndef XTETRIS_STDIO
#import <stdio.h>
#endif

#ifndef XTETRIS_STRING
#include "../Elements/mystring.h"
#endif

typedef
enum scelta_t {
    SINGLEPLAYER = 1,
    MULTIPLAYER,
    SETTINGS
}
Scelta_t;

/**
 * Metodo per stampare a terminale il titolo del gioco
 */
void print_titologioco();

/**
 * Metodo per stampare a terminale il menù principale del gioco
 */
Scelta_t menu_gioco();

/**
 * Metodo per stampare il menu delle impostazioni
 */
void print_settingsmenu();

#endif //XTETRIS_MENUS_H
