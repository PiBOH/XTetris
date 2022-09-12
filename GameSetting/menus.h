#ifndef XTETRIS_MENUS_H
#define XTETRIS_MENUS_H
#import <stdio.h>
#include "Player/player.h"

/**
 * Tipo di dati enumerativo avente il compito di rappresentare la modalità di gioco scelta dall'utente per la partita
 * corrente.
 */
typedef
enum mode_t {
    SINGLEPLAYER = 1,
    MULTIPLAYER_PL,
    MULTIPLAYER_PC
}
Mode_t;

/**
 * Metodo per stampare a terminale il titolo del gioco (X-Tetris) con grafica ASCII-Art a colori
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
void print_turnoinfoplayer(const Player_t p);

/**
 * Metodo avente il compito di stampare in ASCII-Art la parola "<i>Lose</i>" e successivamente stampare le informazioni del
 * giocatore perdente (tramite invocazione del metodo di pretty-printing <code>print_player</code>).
 * @param p - il giocatore sconfitto
 */
void print_losetitle(const Player_t p);

/**
 * Metodo avente il compito di stampare in ASCII-Art la parola "<i>Winner</i>" e successivamente stampare le informazioni del
 * giocatore vincitore (tramite invocazione del metodo di pretty-printing <code>print_player</code>).
 * @param p - il giocatore vincitore
 */
void print_wintitle(const Player_t p);

/**
 * Metodo avente il compito di stampare in ASCII-Art la parola "<i>Finish</i>"
 */
void print_finishtitle();

#endif
