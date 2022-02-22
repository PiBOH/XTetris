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
 * Metodo in grado di creare un nuovo piano di gioco
 * @return piano di gioco con settaggio di partenza per partita singleplayer
 */
PianoDiGioco_t create_pianodigioco();

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

/**
 * Metodo avente il compito di posizionare effettivamente un tetramino nel piano di gioco.
 * @param t: tetramino da posizionare
 * @param col: colonna in cui calare il tetramino
 * @return  true: se il tetramino è stato correttamente posizionato
 * @return  false: se si è verificata una situazione anomala
 */
Bool_t set_tetraminosupianodigioco(const Tetramino_t t, int col);

#endif
