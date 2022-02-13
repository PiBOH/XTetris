#include "pianodigioco.h"

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
