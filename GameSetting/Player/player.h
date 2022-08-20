#ifndef XTETRIS_PLAYER_H
#define XTETRIS_PLAYER_H

#ifndef XTETRIS_MALLOC_H
#include <stdio.h>
#include <stdlib.h>
#endif

#ifndef XTETRIS_STRING_H
#include <string.h>
#endif

#include "../../Elements/string.h"

/**
 * Tipo di dato strutturato che memorizza le informazioni essenziali relative ad un videogiocatore:\n
 *  - <b><code>nome</code></b>: il nome del giocatore\n
 *  - <b><code>points</code></b>: i punti accumulati durante la partita
 */
typedef
struct player_t
{
    string_t nome;
    int points;
}
Player_t;

/**
 * Metodo che, dato il nome di un giocatore, ne restituisce il rispettivo oggetto
 * @param nome: il nome del giocatore
 * @return oggetto di tipo Player_t avente nome uguale a quello fornito e punteggio massimo pari a 0
 */
Player_t create_newplayer(const string_t nome);

/**
 * Metodo avente il compito di stampare a video tramite pretty-printing le informazioni relative ad un giocatore.
 * @param p - il giocatore di cui visualizzare le informazioni
 */
void print_player(const Player_t p);

#endif
