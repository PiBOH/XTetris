#include "pianodigioco.h"

const string_t terminal_colors[] = { "\033[0;36m", "\033[0;34m",
                                     "\033[0;37m", "\033[0;33m",
                                     "\033[0;31m", "\033[0;32m",
                                     "\033[0;35m" };

void __set_celle__(PianoDiGioco_t* p) {
    int i, j;
    for (i = 0; i < ROWS; ++i) {
        for (j = 0; j < COLS; ++j) {
            p->matrice_di_gioco[i][j].is_vuota = TRUE;
            p->matrice_di_gioco[i][j].riga = i;
            p->matrice_di_gioco[i][j].colonna = j;
        }
    }
}

PianoDiGioco_t create_pianodigioco() {
    PianoDiGioco_t new_pdt;
    __set_celle__(&new_pdt);
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
                printf("%s", terminal_colors[p.matrice_di_gioco[i][j].tetramino_contenuto.colore]);
                printf(" #");
                printf("\033[0m");
            }
        }
        printf(" |\n");
    }
    printf("+ - - - - - - - - - - +\n  0 1 2 3 4 5 6 7 8 9  \n");
}

void print_pianodigioco_basic(const PianoDiGioco_t p)
{
    int i, j;
    for (i = 0; i < ROWS; ++i) {
        for (j = 0; j < COLS; ++j) {
            if (p.matrice_di_gioco[i][j].is_vuota) {
                printf("\033[0;30m");
                printf("%d ", !p.matrice_di_gioco[i][j].is_vuota);
                printf("\033[0m");
            } else
                printf("%d ", !p.matrice_di_gioco[i][j].is_vuota);
        }
        printf("\n");
    }
    printf("- - - - - - - - - -\n0 1 2 3 4 5 6 7 8 9\n");
}

// TODO: documentazione
Bool_t __check_rigavuota__(PianoDiGioco_t p, int row, int col, int amp)
{
    int j;

    for (j = col - amp + 1; j <= col; ++j)
        if (!p.matrice_di_gioco[row][j].is_vuota)
            return FALSE;

    return TRUE;
}



// TODO: Implementare
// TODO: Documentazione
Bool_t set_tetraminosupianodigioco(PianoDiGioco_t* p, Tetramino_t t, int col)
{
    int i;
    for (i = 0; i < ROWS; ++i) {
        Bool_t empty_r = __check_rigavuota__(*p, i, col, t.ampiezze[t.rotazione]);
        int riga_wh_insert = i - 1;
        if (i == ROWS - 1 && empty_r) riga_wh_insert = ROWS - 1;

        if (!empty_r || i == ROWS - 1) {
            if ((riga_wh_insert - get_altezzatetramino(t) + 1) < 0) {
                p->is_limiteraggiunto = TRUE;
                return FALSE;
            }

            int k, q, i1, j1;
            for (k = riga_wh_insert, i1 = 3; k > riga_wh_insert - get_altezzatetramino(t); --k, i1--) {
                for (q = col, j1 = 3; q > col - t.ampiezze[t.rotazione]; --q, j1--) {
                    if (t.stato_BASIC[i1][j1] && t.rotazione == BASIC ||
                        t.stato_ADD90[i1][j1] && t.rotazione == ADD90 ||
                        t.stato_ADD180[i1][j1] && t.rotazione == ADD180 ||
                        t.stato_ADD270[i1][j1] && t.rotazione == ADD270 )
                    {
                        p->matrice_di_gioco[k][q].is_vuota = FALSE;
                        p->matrice_di_gioco[k][q].tetramino_contenuto = t;
                    }
                }
            }
            return TRUE;
        }
    }
    return FALSE;
}
