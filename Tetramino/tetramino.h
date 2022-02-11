#ifndef XTETRIS_TETRAMINO_H
#define XTETRIS_TETRAMINO_H

#import "colori.h"
#import "rotazioni.h"
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
Tetramino_t create_tetramino1() {
    int i, j;
    Tetramino_t new_t;
    new_t.colore = AZZURRO;
    new_t.rotazione = BASIC;

    for (i = 0; i < DIM; ++i) {
        for (j = 0; j < DIM; ++j) {
            new_t.stato_BASIC [i][j] = 0;
            new_t.stato_ADD90 [i][j] = 0;
            new_t.stato_ADD180[i][j] = 0;
            new_t.stato_ADD270[i][j] = 0;
        }
    }

    /* imposto blocco orizzontale */
    for (j = 0; j < DIM; ++j) {
        new_t.stato_BASIC  [DIM - 1][j] = 1;
        new_t.stato_ADD180 [DIM - 1][j] = 1;
    }

    /* imposto blocco verticale */
    for (i = 0; i < DIM; ++i) {
        new_t.stato_ADD90  [i][DIM - 1] = 1;
        new_t.stato_ADD270 [i][DIM - 1] = 1;
    }

    return new_t;
}

/**
 * Metodo che costruisce un nuovo tatramino del 2° tipo in accordo con lo standard definito nella documentazione fornita
 * @return nuovo tetramino (Tetramino_t) avente le informazioni corrette per rappresentarlo
 */
Tetramino_t create_tetramino2() {
    int i, j;
    Tetramino_t new_t;
    new_t.colore = BLU;
    new_t.rotazione = BASIC;

    for (i = 0; i < DIM; ++i) {
        for (j = 0; j < DIM; ++j) {
            new_t.stato_BASIC [i][j] = 0;
            new_t.stato_ADD90 [i][j] = 0;
            new_t.stato_ADD180[i][j] = 0;
            new_t.stato_ADD270[i][j] = 0;
        }
    }

    new_t.stato_BASIC[2][1] = 1;
    new_t.stato_BASIC[3][1] = 1;
    new_t.stato_BASIC[3][2] = 1;
    new_t.stato_BASIC[3][3] = 1;

    new_t.stato_ADD90[1][3] = 1;
    new_t.stato_ADD90[1][2] = 1;
    new_t.stato_ADD90[2][2] = 1;
    new_t.stato_ADD90[3][2] = 1;

    new_t.stato_ADD180[2][1] = 1;
    new_t.stato_ADD180[2][2] = 1;
    new_t.stato_ADD180[2][3] = 1;
    new_t.stato_ADD180[3][3] = 1;

    new_t.stato_ADD270[1][3] = 1;
    new_t.stato_ADD270[2][3] = 1;
    new_t.stato_ADD270[3][3] = 1;
    new_t.stato_ADD270[3][2] = 1;
    return new_t;
}

/**
 * Metodo che costruisce un nuovo tatramino del 3° tipo in accordo con lo standard definito nella documentazione fornita
 * @return nuovo tetramino (Tetramino_t) avente le informazioni corrette per rappresentarlo
 */
Tetramino_t create_tetramino3() {
    int i, j;
    Tetramino_t new_t;
    new_t.colore = ARANCIONE;
    new_t.rotazione = BASIC;

    for (i = 0; i < DIM; ++i) {
        for (j = 0; j < DIM; ++j) {
            new_t.stato_BASIC [i][j] = 0;
            new_t.stato_ADD90 [i][j] = 0;
            new_t.stato_ADD180[i][j] = 0;
            new_t.stato_ADD270[i][j] = 0;
        }
    }

    new_t.stato_BASIC[2][3] = 1;
    new_t.stato_BASIC[3][3] = 1;
    new_t.stato_BASIC[3][2] = 1;
    new_t.stato_BASIC[3][1] = 1;

    new_t.stato_ADD90[1][2] = 1;
    new_t.stato_ADD90[2][2] = 1;
    new_t.stato_ADD90[3][2] = 1;
    new_t.stato_ADD90[3][3] = 1;

    new_t.stato_ADD180[3][1] = 1;
    new_t.stato_ADD180[2][1] = 1;
    new_t.stato_ADD180[2][2] = 1;
    new_t.stato_ADD180[2][3] = 1;

    new_t.stato_ADD270[1][2] = 1;
    new_t.stato_ADD270[1][3] = 1;
    new_t.stato_ADD270[2][3] = 1;
    new_t.stato_ADD270[3][3] = 1;

    return new_t;
}

/**
 * Metodo che costruisce un nuovo tatramino del 4° tipo in accordo con lo standard definito nella documentazione fornita
 * @return nuovo tetramino (Tetramino_t) avente le informazioni corrette per rappresentarlo
 */
Tetramino_t create_tetramino4() {
    int i, j;
    Tetramino_t new_t;
    new_t.colore = GIALLO;
    new_t.rotazione = BASIC;

    for (i = 0; i < DIM; ++i) {
        for (j = 0; j < DIM; ++j) {
            new_t.stato_BASIC [i][j] = 0;
            new_t.stato_ADD90 [i][j] = 0;
            new_t.stato_ADD180[i][j] = 0;
            new_t.stato_ADD270[i][j] = 0;
        }
    }

    new_t.stato_BASIC[2][2] = 1;
    new_t.stato_BASIC[2][3] = 1;
    new_t.stato_BASIC[3][2] = 1;
    new_t.stato_BASIC[3][3] = 1;

    for (i = 0; i < DIM; ++i)
        for (j = 0; j < DIM; ++j)
            new_t.stato_ADD90[i][j] = new_t.stato_ADD180[i][j] = new_t.stato_ADD270[i][j] = new_t.stato_BASIC[i][j];

    return new_t;
}

/**
 * Metodo che costruisce un nuovo tatramino del 5° tipo in accordo con lo standard definito nella documentazione fornita
 * @return nuovo tetramino (Tetramino_t) avente le informazioni corrette per rappresentarlo
 */
Tetramino_t create_tetramino5() {
    int i, j;
    Tetramino_t new_t;
    new_t.colore = VERDE;
    new_t.rotazione = BASIC;

    for (i = 0; i < DIM; ++i) {
        for (j = 0; j < DIM; ++j) {
            new_t.stato_BASIC [i][j] = 0;
            new_t.stato_ADD90 [i][j] = 0;
            new_t.stato_ADD180[i][j] = 0;
            new_t.stato_ADD270[i][j] = 0;
        }
    }

    new_t.stato_BASIC[2][3] = 1;
    new_t.stato_BASIC[2][2] = 1;
    new_t.stato_BASIC[3][2] = 1;
    new_t.stato_BASIC[3][1] = 1;

    new_t.stato_ADD90[1][2] = 1;
    new_t.stato_ADD90[2][2] = 1;
    new_t.stato_ADD90[2][3] = 1;
    new_t.stato_ADD90[3][3] = 1;

    for (i = 0; i < DIM; ++i) {
        for (j = 0; j < DIM; ++j) {
            new_t.stato_ADD180[i][j] = new_t.stato_BASIC[i][j];
            new_t.stato_ADD270[i][j] = new_t.stato_ADD90[i][j];
        }
    }

    return new_t;
}

/**
 * Metodo che costruisce un nuovo tatramino del 6° tipo in accordo con lo standard definito nella documentazione fornita
 * @return nuovo tetramino (Tetramino_t) avente le informazioni corrette per rappresentarlo
 */
Tetramino_t create_tetramino6() {
    int i, j;
    Tetramino_t new_t;
    new_t.colore = VIOLA;
    new_t.rotazione = BASIC;

    for (i = 0; i < DIM; ++i) {
        for (j = 0; j < DIM; ++j) {
            new_t.stato_BASIC [i][j] = 0;
            new_t.stato_ADD90 [i][j] = 0;
            new_t.stato_ADD180[i][j] = 0;
            new_t.stato_ADD270[i][j] = 0;
        }
    }

    new_t.stato_BASIC [2][2] = 1;
    new_t.stato_BASIC [3][1] = 1;
    new_t.stato_BASIC [3][2] = 1;
    new_t.stato_BASIC [3][3] = 1;

    new_t.stato_ADD90 [1][2] = 1;
    new_t.stato_ADD90 [2][2] = 1;
    new_t.stato_ADD90 [2][3] = 1;
    new_t.stato_ADD90 [3][2] = 1;

    new_t.stato_ADD180 [2][1] = 1;
    new_t.stato_ADD180 [2][2] = 1;
    new_t.stato_ADD180 [2][3] = 1;
    new_t.stato_ADD180 [3][2] = 1;

    new_t.stato_ADD270 [1][3] = 1;
    new_t.stato_ADD270 [2][3] = 1;
    new_t.stato_ADD270 [2][2] = 1;
    new_t.stato_ADD270 [3][3] = 1;

    return new_t;
}

/**
 * Metodo che costruisce un nuovo tatramino del 7° tipo in accordo con lo standard definito nella documentazione fornita
 * @return nuovo tetramino (Tetramino_t) avente le informazioni corrette per rappresentarlo
 */
Tetramino_t create_tetramino7() {
    int i, j;
    Tetramino_t new_t;
    new_t.colore = ROSSO;
    new_t.rotazione = BASIC;

    for (i = 0; i < DIM; ++i) {
        for (j = 0; j < DIM; ++j) {
            new_t.stato_BASIC [i][j] = 0;
            new_t.stato_ADD90 [i][j] = 0;
            new_t.stato_ADD180[i][j] = 0;
            new_t.stato_ADD270[i][j] = 0;
        }
    }

    new_t.stato_BASIC [2][1] = 1;
    new_t.stato_BASIC [2][2] = 1;
    new_t.stato_BASIC [3][2] = 1;
    new_t.stato_BASIC [3][3] = 1;

    new_t.stato_ADD90 [1][3] = 1;
    new_t.stato_ADD90 [2][3] = 1;
    new_t.stato_ADD90 [2][2] = 1;
    new_t.stato_ADD90 [3][2] = 1;

    for (i = 0; i < DIM; ++i) {
        for (j = 0; j < DIM; ++j) {
            new_t.stato_ADD180[i][j] = new_t.stato_BASIC[i][j];
            new_t.stato_ADD270[i][j] = new_t.stato_ADD90[i][j];
        }
    }

    return new_t;
}

/**
 * Metodo avente il compito di stampare un tetramino passato come parametro
 * @param t il tetramino da stampare passato come parametro costante
 */
void print_tetramino(const Tetramino_t t) {
    int i, j;
    for (i = 0; i < DIM; ++i) {
        for (j = 0; j < DIM; ++j) {
            if(t.rotazione == BASIC) {
                if (t.stato_BASIC[i][j] == 1) printf("# ");
                else printf("_ ");
            } else if(t.rotazione == ADD90) {
                if (t.stato_ADD90[i][j] == 1) printf("# ");
                else printf("_ ");
            } else if(t.rotazione == ADD180) {
                if (t.stato_ADD180[i][j] == 1) printf("# ");
                else printf("_ ");
            } else if(t.rotazione == ADD270) {
                if (t.stato_ADD270[i][j] == 1) printf("# ");
                else printf("_ ");
            }
        }

        printf("\n");
    }
}
#endif
