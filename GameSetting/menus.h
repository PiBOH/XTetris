#ifndef XTETRIS_MENUS_H
#define XTETRIS_MENUS_H

#ifndef XTETRIS_STDIO
#import <stdio.h>
#endif

#ifndef XTETRIS_STRING
#include "../Elements/mystring.h"
#include "Player/player.h"

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
 * Metodo utilizzato per stampare il menu iniziale di gioco
 */
void print_menugioco();

/**
 * Metodo avente il compito di eseguire un pretty printing delle informazioni contenute all'interno della variabile
 * passata come argomento. Esso comunica in primo luogo il turno della mossa e in seguito stampa le informazioni relative
 * al giocatore
 * @param p - il giocatore proprietario del turno corrente
 */
void print_turnoinfoplayer(Player_t p);

/* TODO: documentazione */
void print_losetitle(Player_t p);

/* TODO: Documentazione */
void print_wintitle(Player_t p);

#endif
