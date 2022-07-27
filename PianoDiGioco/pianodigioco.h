#ifndef XTETRIS_PIANODIGIOCO_H
#define XTETRIS_PIANODIGIOCO_H

#include "../Elements/boolType.h"
#include "../Tetramino/tetramino.h"

#define ROWS 15
#define COLS 10

// TODO: Documentazione
typedef
struct cella_t {
    int riga;
    int colonna;
    Bool_t is_vuota;
    Tetramino_t tetramino_contenuto;
}
Cella_t;

// TODO: Documentazione
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
 * Metodo avente il compito di posizionare effettivamente un tetramino nel piano di gioco andando a settare il limite
 * raggiunto nel caso in cui si fosse raggiunto l'apice della matrice di gioco.
 * @param t: tetramino da posizionare
 * @param col: colonna in cui calare il tetramino
 * @param p: piano di gioco sul quale applicare la modifica e l'inserimento del tetramino
 * @return <code>true</code> se e solo se il tetramino è stato posizionato correttamente, <code>false</code> altrimenti
 */
Bool_t set_tetraminosupianodigioco(PianoDiGioco_t* p, Tetramino_t t, int col);

#endif
