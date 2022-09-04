#include "pianodigioco.h"
#include "../Elements/color_codes.h"

const string_t terminal_colors[] = { "\033[0;36m", "\033[0;34m",
                                     "\033[0;37m", "\033[0;33m",
                                     "\033[0;31m", "\033[0;32m",
                                     "\033[0;35m" };

/**
 * [PRIVATE]\n
 * Metodo avente il compito di impostare tutta la <code>matrice_di_gioco</code> del piano di gioco con celle vuote (condizione
 * di partenza del gioco).
 * @param p - il piano di gioco contenente la matrice su cui svolgere l'operazione.
 */
void __set_cellevuote__(PianoDiGioco_t* p) {
    int i, j;
    for (i = 0; i < ROWS; ++i) {
        for (j = 0; j < COLS; ++j)
            p->matrice_di_gioco[i][j].is_vuota = TRUE;
    }
}

PianoDiGioco_t create_pianodigioco() {
    PianoDiGioco_t new_pdt;
    __set_cellevuote__(&new_pdt);
    new_pdt.is_limiteraggiunto = FALSE;
    return new_pdt;
}

void print_pianodigioco(PianoDiGioco_t p) {
    int i, j;
    printf("  -   -   -   -   -   -   -   -   -   -  \n");
    for (i = 0; i < ROWS; ++i) {
        printf("\n|");
        for (j = 0; j < COLS; ++j) {
            if(p.matrice_di_gioco[i][j].is_vuota) {
                printf("   ");
            } else {
                printf("%s", terminal_colors[p.matrice_di_gioco[i][j].tetramino_contenuto.colore]);
                printf(" # ");
                printf(DEFAULT);
            }
            if (j + 1 != COLS) {
                printf(NERO);
                printf(":");
            } else {
                printf(BIANCO);
                printf("|");
            }
            printf(DEFAULT);
        }
        printf(" \n");
    }
    printf("  -   -   -   -   -   -   -   -   -   -  \n  0   1   2   3   4   5   6   7   8   9  \n");
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

/**
 * [PRIVATE]\n
 * Il metodo ha il compito di verificare, scorrendo la matrice del piano di gioco fornita come parametro se
 * nell'intervallo definito dalla colonna di partenza (ovvero quella data dalla sottrazione tra la colonna selezionata
 * e l'ampiezza del tetramino scelto) e quella di fine (che quindi diventa la colonna scelta) esistono dei punti di
 * collisione tra un pezzo già settato nel piano di gioco e quello che si vuole calare. Se ciò accade significa che non
 * è possibile calare il tetramino in questa riga.
 * @param p il piano di gioco, contenente quindi la matrice di gioco
 * @param matrice_tetramino matrice di interi che rappresenta un tetramino (quello che si vuole posizionare)
 * @param row la riga in questione da verificare come libera
 * @param col la colonna di partenza (scelta sulla base di un posizionamento a partire dal lato in basso a dx
 * della matrice del tetramino
 * @param amp l'ampiezza orizzontale del tetramino selezionato
 * @param row_tetramino la riga della matrice_tetramino da verificare simultaneamente alla riga della <code>matrice_di_gioco</code>
 * @return <code>TRUE</code> - se la riga è valida per un inserimento\n
 *         <code>FALSE</code> - se nella riga non è possibile posizionare nulla
 */
Bool_t __check_rigavuota__(PianoDiGioco_t p, int matrice_tetramino[4][4], int row, int col, int amp, int row_tetramino)
{
    int j, k = 4 - amp;

    for (j = col - amp + 1; j <= col; ++j, ++k)
        if (!p.matrice_di_gioco[row][j].is_vuota && matrice_tetramino[row_tetramino][k]) // cerca collisioni
            return FALSE;

    return TRUE;
}

/**
 * [PRIVATE]\n
 * Metodo avente il compito di restituire il punteggio attribuito ad ogni giocatore in seguito all'eliminazione di un
 * certo numero di righe.\n
 * Le regole di assegnazione sono successivamente riportate.\n
 * 1 riga -> 1 punto\n
 * 2 righe -> 3 punti\n
 * 3 righe -> 6 punti\n
 * 4 righe -> 12 punti\n
 * @param righe - numero di righe eliminate con un singolo tetramino
 * @return punti ricevuti in formato intero (<code>int</code>).
 */
int __get_points__(int righe) {
    switch (righe) {
        case 1: return 1;
        case 2: return 3;
        case 3: return 6;
        case 4: return 12;
        default: return 0;
    }
}

Bool_t set_tetraminosupianodigioco(PianoDiGioco_t* p, Player_t* player, Tetramino_t t, int col)
{
    int i, j;
    Bool_t is_posizionabile = FALSE;
    int row;

    /* Prima di tutto verifico se il pezzo è posizionabile orizzontalmente */
    if ((col + 1) - t.ampiezze[t.rotazione] < 0)
        return FALSE;

    /* Scorrimento di tutte le righe dall'ultima alla prima per cercare di posizionare il tetramino */
    for (j = ROWS - 1; j >= 0; --j) {
        int row_t = 3; /* parto sempre dall'ultima riga del tetramino a verificare */
        is_posizionabile = TRUE;
        row = j;

        /* ciclo che mi permette di verificare se il tetramino è piazzabile a partire dalla riga dettata dal for esterno */
        for (i = j; i > j - get_altezzatetramino(t) && is_posizionabile; --i) {
            switch (t.rotazione) {
                case BASIC:
                    is_posizionabile = __check_rigavuota__(*p, t.stato_BASIC, i, col, t.ampiezze[t.rotazione], row_t--);
                    break;
                case ADD90:
                    is_posizionabile = __check_rigavuota__(*p, t.stato_ADD90, i, col, t.ampiezze[t.rotazione], row_t--);
                    break;
                case ADD180:
                    is_posizionabile = __check_rigavuota__(*p, t.stato_ADD180, i, col, t.ampiezze[t.rotazione], row_t--);
                    break;
                default:
                    is_posizionabile = __check_rigavuota__(*p, t.stato_ADD270, i, col, t.ampiezze[t.rotazione], row_t--);
                    break;
            }
        }

        /* Mi ri-posiziono nella riga da cui sono partito (quella dettata dal for esterno) */
        i = row;

        /*
         * Eseguo un'ulteriore verifica per vedere se il posizionamento mi vada a sforare verticalemente il piano
         * di gioco. In questo caso l'utente ha perso perchè ha raggiunto il limite superiore della matrice
         */
        if ((i - get_altezzatetramino(t) + 1) < 0) {
            p->is_limiteraggiunto = TRUE;
            return FALSE;
        }

        /*
         * Se la variabile is_posizionabile è settata a true vuol dire che ho controllato tutte le righe e colonne
         * interessate e non ho trovato collisioni, quindi posso diseganare sulla matrice di gioco
         */
        if (is_posizionabile) {
            int k, q, i1, j1;
            /* salvo il numero di righe che vado ad eliminare con una singola mossa */
            int eliminazioni = 0;

            /*
             * Cella per cella verifico se essa è settata ad 1 nella matrice del tetramino scelto e di pari passo vado
             * a settare come piene le celle del piano di gioco, salvando anche il tetramino che ci vado a posizionare
             * per poi in fase di stampa andare a colorare correttamente la cella in base al tetramino contenuto in
             * essa
             */
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

            /* controllo eliminazione righe per ricevere punteggio */
            for (i = ROWS - 1; i >= 0;) {
                int cont = 0;
                for (j = 0; j < COLS; ++j)
                    if (p->matrice_di_gioco[i][j].is_vuota == FALSE)
                        cont++;

                /* se la colonna è tutta piena la analizzo altrimenti posso salire in su di una riga */
                if (cont == COLS) {
                    ++eliminazioni;
                    for (j = 0; j < COLS; ++j) {
                        for (i1 = i; i1 > 0; --i1) {
                            /* se sono arrivato alla fine e non ho più righe da scalare le setto tutte vuote */
                            if (i1 - 1 < 0) p->matrice_di_gioco[i1][j].is_vuota = TRUE;
                            else {
                                p->matrice_di_gioco[i1][j].is_vuota = p->matrice_di_gioco[i1 - 1][j].is_vuota;
                                p->matrice_di_gioco[i1][j].tetramino_contenuto = p->matrice_di_gioco[i1 - 1][j].tetramino_contenuto;
                            }
                        }
                    }
                } else
                    --i;
            }

            /*
             * aggiorno il punteggio del giocatore passato come parametro alla funzione ovvero il giocatore che ha
             * comandato l'esecuzione della mossa specificata
             */

            if (eliminazioni) {
                printf("\n\n");
                printf("%sEliminazione di %d riga/righe con una sola mossa!%s", AZZURROB, eliminazioni, RESET);
                player->points += __get_points__(eliminazioni);
            }

            return TRUE;
        }
    }
    return FALSE;
}
