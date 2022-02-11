#include <stdio.h>
#include "Tetramino/tetramino.h"

int main() {
    int i, j;
    Tetramino_t t;
    t = create_tetramino3();
    t.rotazione = ADD180;

    print_tetramino(t);
/*
    printf("basic:\n");
    for (i = 0; i < DIM; ++i) {
        for (j = 0; j < DIM; ++j) {
            printf("%d  ", t.stato_BASIC[i][j]);
        }
        printf("\n");
    }

    printf("add90:\n");
    for (i = 0; i < DIM; ++i) {
        for (j = 0; j < DIM; ++j) {
            printf("%d  ", t.stato_ADD90[i][j]);
        }
        printf("\n");
    }

    printf("add180:\n");
    for (i = 0; i < DIM; ++i) {
        for (j = 0; j < DIM; ++j) {
            printf("%d  ", t.stato_ADD180[i][j]);
        }
        printf("\n");
    }

    printf("add270:\n");
    for (i = 0; i < DIM; ++i) {
        for (j = 0; j < DIM; ++j) {
            printf("%d  ", t.stato_ADD270[i][j]);
        }
        printf("\n");
    }
*/
    return 0;
}
