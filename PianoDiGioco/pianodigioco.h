#ifndef XTETRIS_PIANODIGIOCO_H
#define XTETRIS_PIANODIGIOCO_H

#include "../Elements/boolType.h"
#include "../Tetramino/tetramino.h"

#define ROWS 15
#define COLS 10

typedef
struct cella_t {
    int riga;
    int colonna;
    Bool_t is_vuota;
    Tetramino_t* tetramino_contenuto;
}
Cella_t;

typedef
struct pianodigioco_t {
    Cella_t matrice_di_gioco[ROWS][COLS];
    Bool_t is_limiteraggiunto;
}
PianoDiGioco_t;

/**
 * Struttura dati da utilizzare per gesitre la disponibilità dei tetramini da posizionare nel
 * piano di gioco.
 */
typedef
struct tetraminodigioco_t {
    Tetramino_t t;
    int n_disponibili;
}
Tetraminodigioco_t;

/**
 * Metodo in grado di creare un nuovo piano di gioco
 * @return piano di gioco con settaggio di partenza per partita singleplayer
 */
PianoDiGioco_t create_pianodigioco_sp();

/**
 * Metodo che stampa il piano di gioco con una tecnica di stampa avanzata.
 * @param p: piano di gioco da stampare
 */
void print_pianodigioco(const PianoDiGioco_t p);

/**
 * Metodo che stampa il piano di gioco con una tecnica di stampa basilare (zeri e uni).
 * @param p: piano di gioco da stampare
 */
void print_pianodigioco_basic(const PianoDiGioco_t p);

#endif
