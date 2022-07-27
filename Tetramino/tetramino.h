#ifndef XTETRIS_TETRAMINO_H
#define XTETRIS_TETRAMINO_H

#ifndef XTETRIS_STDIO
#import <stdio.h>
#endif
#import "../Elements/colori.h"
#import "../Elements/mystring.h"
#import "../Elements/rotazioni.h"
#define DIM 4
#define PIECES 7

// TODO: Documentazione
typedef
struct tetramino_t {
    Colore_t colore;
    Rotazione_t rotazione;
    int ampiezze[4];
    int stato_BASIC  [DIM][DIM];
    int stato_ADD90  [DIM][DIM];
    int stato_ADD180 [DIM][DIM];
    int stato_ADD270 [DIM][DIM];
}
Tetramino_t;

/**
 * Struttura dati da utilizzare per gesitre la disponibilità dei tetramini da posizionare nel
 * piano di gioco.
 */
typedef
struct tetraminodigioco_t {
    int id;
    Tetramino_t t;
    int n_disponibili;
}
Tetraminodigioco_t;

/**
 * Metodo avente il compito di stampare ad ogni turno di gioco i tetramini sia dal punto di vista grafico che integrando
 * un'informazione relativa al numero di pezzi rimasti per ogni tipo.
 * @param t: array contenente le informazioni necessarie relative ai tetramini in un determinato momento di esecuzione.
 */
void print_tetramini(const Tetraminodigioco_t t[]);

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
 * Metodo avente il compito di stampare un tetramino passato come parametro in maniera basica (usando zeri e uni)
 * @param t: il tetramino da stampare passato come parametro costante
 */
void print_tetramino_basic(const Tetramino_t t);

/**
 * Metodo avente il compito di stampare, con una tecnica avanazata, un tetramino passato come parametro
 * @param t: il tetramino da stampare passato come parametro costante
 */
void print_tetramino(const Tetramino_t t);

/**
 * Metodo che stampa a video tutte le possibili rotazioni di un tetramino scelto dall'utente tramite id
 * @param id: id del tetramino da stampare (ovvero l'id del tetramino scelto dall'utente)
 */
void print_possibilirotazioni(int id);

// TODO: documentazione
int get_altezzatetramino(const Tetramino_t t);

#endif
