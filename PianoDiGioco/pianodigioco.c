#include "pianodigioco.h"

const string_t terminal_colors[] = { "\033[0;36m", "\033[0;34m",
                                     "", "\033[0;33m",
                                     "\033[0;31m", "\033[0;32m",
                                     "\033[0;35m" };

void set_celle(PianoDiGioco_t* p) {
    int i, j;
    for (i = 0; i < ROWS; ++i) {
        for (j = 0; j < COLS; ++j) {
            p->matrice_di_gioco[i][j].is_vuota = TRUE;
            p->matrice_di_gioco[i][j].riga = i;
            p->matrice_di_gioco[i][j].colonna = j;
            p->matrice_di_gioco[i][j].tetramino_contenuto = NULL;
        }
    }
}

PianoDiGioco_t create_pianodigioco_sp() {
    PianoDiGioco_t new_pdt;
    set_celle(&new_pdt);
    new_pdt.is_limiteraggiunto = FALSE;
    return new_pdt;
}

void print_pianodigioco(PianoDiGioco_t p) {
    int i, j;
    printf("+ - - - - - - - - - - +\n");
    for (i = 0; i < ROWS; ++i) {
        printf("|");
        for (j = 0; j < COLS; ++j) {
            if(p.matrice_di_gioco[i][j].is_vuota) printf("  ");
            else {
                printf("%s", terminal_colors[p.matrice_di_gioco[i][j].tetramino_contenuto->colore]);
                printf("# ");
                printf("\033[0m");
            }
        }
        printf(" |\n");
    }
    printf("+ - - - - - - - - - - +\n");
}

void print_pianodigioco_basic(const PianoDiGioco_t p) {
    int i, j;
    for (i = 0; i < ROWS; ++i) {
        for (j = 0; j < COLS; ++j) {
            printf("%d ", !p.matrice_di_gioco[i][j].is_vuota);
        }
        printf("\n");
    }
}
