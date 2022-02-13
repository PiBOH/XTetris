#ifndef XTETRIS_TETRAMINO_H
#define XTETRIS_TETRAMINO_H

#import <stdio.h>
#import "../Elements/colori.h"
#import "../Elements/rotazioni.h"
#define DIM 4

typedef
struct tetramino_t {
    Colore_t colore;
    Rotazione_t rotazione;
    int stato_BASIC  [DIM][DIM];
    int stato_ADD90  [DIM][DIM];
    int stato_ADD180 [DIM][DIM];
    int stato_ADD270 [DIM][DIM];
}
Tetramino_t;

/**
 * Metodo che costruisce un nuovo tatramino del 1° tipo in accordo con lo standard definito nella documentazione fornita
 * @return nuovo tetramino (Tetramino_t) avente le informazioni corrette per rappresentarlo
 */
Tetramino_t create_tetramino1();

/**
 * Metodo che costruisce un nuovo tatramino del 2° tipo in accordo con lo standard definito nella documentazione fornita
 * @return nuovo tetramino (Tetramino_t) avente le informazioni corrette per rappresentarlo
 */
Tetramino_t create_tetramino2();

/**
 * Metodo che costruisce un nuovo tatramino del 3° tipo in accordo con lo standard definito nella documentazione fornita
 * @return nuovo tetramino (Tetramino_t) avente le informazioni corrette per rappresentarlo
 */
Tetramino_t create_tetramino3();

/**
 * Metodo che costruisce un nuovo tatramino del 4° tipo in accordo con lo standard definito nella documentazione fornita
 * @return nuovo tetramino (Tetramino_t) avente le informazioni corrette per rappresentarlo
 */
Tetramino_t create_tetramino4();

/**
 * Metodo che costruisce un nuovo tatramino del 5° tipo in accordo con lo standard definito nella documentazione fornita
 * @return nuovo tetramino (Tetramino_t) avente le informazioni corrette per rappresentarlo
 */
Tetramino_t create_tetramino5();

/**
 * Metodo che costruisce un nuovo tatramino del 6° tipo in accordo con lo standard definito nella documentazione fornita
 * @return nuovo tetramino (Tetramino_t) avente le informazioni corrette per rappresentarlo
 */
Tetramino_t create_tetramino6();

/**
 * Metodo che costruisce un nuovo tatramino del 7° tipo in accordo con lo standard definito nella documentazione fornita
 * @return nuovo tetramino (Tetramino_t) avente le informazioni corrette per rappresentarlo
 */
Tetramino_t create_tetramino7();

/**
 * Metodo avente il compito di stampare un tetramino passato come parametro
 * @param t: il tetramino da stampare passato come parametro costante
 */
void print_tetramino(const Tetramino_t t);

/**
 * Metodo utilizzato per settare tutti i valori delle matrici interne al tetramino pari a 0
 * @param t: il tetramino su cui eseguire l'operazione specificata
 */
void __set_zero_tetramino(Tetramino_t* t);
#endif
