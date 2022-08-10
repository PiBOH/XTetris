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

/* TODO: Documentazione */
Bool_t __check_rigavuota__(PianoDiGioco_t p, int matricetetrmaino[4][4], int row, int col, int amp, int row_tetramino)
{
    int j, k = 4 - amp;

    for (j = col - amp + 1; j <= col; ++j, ++k)
        if (!p.matrice_di_gioco[row][j].is_vuota && matricetetrmaino[row_tetramino][k]) // cerca collisioni
            return FALSE;

    return TRUE;
}

/* TODO: Implementare */
/* TODO: Documentazione */
Bool_t set_tetraminosupianodigioco(PianoDiGioco_t* p, Player_t* player, Tetramino_t t, int col)
{
    int i, j;
    Bool_t empty_r = FALSE;
    int row;

    for (j = ROWS - 1; j >= 0 && empty_r == FALSE; --j) {
        int row_t = 3; // riga tetramino
        empty_r = TRUE;
        row = j;

        for (i = j; i > j - get_altezzatetramino(t) && empty_r; --i) {
            switch (t.rotazione) {
                case BASIC:
                    empty_r = __check_rigavuota__(*p, t.stato_BASIC, i, col, t.ampiezze[t.rotazione], row_t--) && empty_r;
                    break;
                case ADD90:
                    empty_r = __check_rigavuota__(*p, t.stato_ADD90, i, col, t.ampiezze[t.rotazione], row_t--) && empty_r;
                    break;
                case ADD180:
                    empty_r = __check_rigavuota__(*p, t.stato_ADD180, i, col, t.ampiezze[t.rotazione], row_t--) && empty_r;
                    break;
                default:
                    empty_r = __check_rigavuota__(*p, t.stato_ADD270, i, col, t.ampiezze[t.rotazione], row_t--) && empty_r;
                    break;
            }
        }

        i = row;

        if ((col + 1) - t.ampiezze[t.rotazione] < 0) {
            return FALSE;  // sfondo in ampiezza
        }



        if (empty_r) {
            int k, q, i1, j1;
            if ((i - get_altezzatetramino(t) + 1) < 0) {
                p->is_limiteraggiunto = TRUE;
                return FALSE;
            }
            for (k = i, i1 = 3; k > i - get_altezzatetramino(t); --k, i1--) {
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
