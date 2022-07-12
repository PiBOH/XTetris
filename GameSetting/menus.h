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
 * Metodo per stampare a terminale il titolo del gioco con grafica ASCII-Art
 */
void print_titologioco();

/**
 * Metodo avente il compito di stampare a video il menu di gioco e di attendere la selezione della modalità
 * <code>SINGLEPLAYER</code> o <code>MULTIPLAYER</code> da parte dell'utente
 * @return la modalità di gioco scelta dall'utente
 */
Mode_t menu_gioco();

#endif //XTETRIS_MENUS_H
