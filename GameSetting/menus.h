#ifndef XTETRIS_MENUS_H
#define XTETRIS_MENUS_H

#ifndef XTETRIS_STDIO
#import <stdio.h>
#endif

#ifndef XTETRIS_STRING
#include "../Elements/mystring.h"
#endif

// TODO: Documentazione
typedef
enum mode_t {
    SINGLEPLAYER = 1,
    MULTIPLAYER,
}
Mode_t;

/**
 * Metodo per stampare a terminale il titolo del gioco con grafica ASCII-Art
 */
void print_titologioco();

/**
 * Metodo utilizzato per stampare il menu iniziale di gioco
 */
void menu_gioco();

#endif //XTETRIS_MENUS_H
