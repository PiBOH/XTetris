#ifndef XTETRIS_PLAYER_H
#define XTETRIS_PLAYER_H

#ifndef XTETRIS_MALLOC_H
#include <malloc.h>
#endif

#ifndef XTETRIS_STRING_H
#include <string.h>
#endif

#include "../../Elements/mystring.h"

typedef
struct player_t
{
    string_t nome;
    int max_points;
}
Player_t;

/**
 * Metodo che memorizza all'interno di un file un nuovo giocatore
 * @param nome: il nome del giocatore da memorizzare
 */
void save_player(string_t nome);

/**
 * Metodo che, dato il nome di un giocatore, ne restituisce il rispettivo oggetto
 * @param nome: il nome del giocatore
 * @return oggetto di tipo Player_t avente nome uguale a quello fornito e punteggio massimo pari a 0
 */
Player_t get_nuovoplayer(string_t nome);

#endif //XTETRIS_PLAYER_H
