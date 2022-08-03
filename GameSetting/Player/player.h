#ifndef XTETRIS_PLAYER_H
#define XTETRIS_PLAYER_H

#ifndef XTETRIS_MALLOC_H
#include <malloc.h>
#endif

#ifndef XTETRIS_STRING_H
#include <string.h>
#endif

#include "../../Elements/mystring.h"

/* TODO: Documentazione */
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

void print_player(const Player_t p);

#endif //XTETRIS_PLAYER_H
