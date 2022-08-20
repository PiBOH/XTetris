#include "tetramino.h"

/**
 * [PRIVATE]\n
 * Metodo creato per permettere di settare tutti i valori delle matrici interne al tetramino pari a 0
 * @param t: il tetramino su cui eseguire l'operazione specificata
 */
void __set_zero_tetramino__(Tetramino_t* t)
{
    int i, j;
    for (i = 0; i < DIM; ++i) {
        for (j = 0; j < DIM; ++j) {
            (*t).stato_BASIC [i][j] = 0;
            (*t).stato_ADD90 [i][j] = 0;
            (*t).stato_ADD180[i][j] = 0;
            (*t).stato_ADD270[i][j] = 0;
        }
    }
}

Tetramino_t create_tetramino1()
{
    int i, j;
    Tetramino_t new_t;
    new_t.colore = AZZURRO;
    new_t.rotazione = BASIC;
    new_t.ampiezze[0] = new_t.ampiezze[2] = 4;
    new_t.ampiezze[1] = new_t.ampiezze[3] = 1;

    __set_zero_tetramino__(&new_t);

    for (j = 0; j < DIM; ++j) {
        new_t.stato_BASIC  [DIM - 1][j] = 1;
        new_t.stato_ADD180 [DIM - 1][j] = 1;
    }


    for (i = 0; i < DIM; ++i) {
        new_t.stato_ADD90  [i][DIM - 1] = 1;
        new_t.stato_ADD270 [i][DIM - 1] = 1;
    }

    return new_t;
}


Tetramino_t create_tetramino2()
{
    Tetramino_t new_t;
    new_t.colore = BLU;
    new_t.rotazione = BASIC;
    new_t.ampiezze[0] = new_t.ampiezze[2] = 3;
    new_t.ampiezze[1] = new_t.ampiezze[3] = 2;

    __set_zero_tetramino__(&new_t);

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


Tetramino_t create_tetramino3()
{
    Tetramino_t new_t;
    new_t.colore = ARANCIONE;
    new_t.rotazione = BASIC;
    new_t.ampiezze[0] = new_t.ampiezze[2] = 3;
    new_t.ampiezze[1] = new_t.ampiezze[3] = 2;

    __set_zero_tetramino__(&new_t);

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


Tetramino_t create_tetramino4()
{
    int i, j;
    Tetramino_t new_t;
    new_t.colore = GIALLO;
    new_t.rotazione = BASIC;
    new_t.ampiezze[0] = new_t.ampiezze[1] = new_t.ampiezze[2] = new_t.ampiezze[3] = 2;

    __set_zero_tetramino__(&new_t);

    new_t.stato_BASIC[2][2] = 1;
    new_t.stato_BASIC[2][3] = 1;
    new_t.stato_BASIC[3][2] = 1;
    new_t.stato_BASIC[3][3] = 1;

    for (i = 0; i < DIM; ++i)
        for (j = 0; j < DIM; ++j)
            new_t.stato_ADD90[i][j] = new_t.stato_ADD180[i][j] = new_t.stato_ADD270[i][j] = new_t.stato_BASIC[i][j];

    return new_t;
}


Tetramino_t create_tetramino5()
{
    int i, j;
    Tetramino_t new_t;
    new_t.colore = VERDE;
    new_t.rotazione = BASIC;
    new_t.ampiezze[0] = new_t.ampiezze[2] = 3;
    new_t.ampiezze[1] = new_t.ampiezze[3] = 2;

    __set_zero_tetramino__(&new_t);

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


Tetramino_t create_tetramino6()
{
    Tetramino_t new_t;
    new_t.colore = VIOLA;
    new_t.rotazione = BASIC;
    new_t.ampiezze[0] = new_t.ampiezze[2] = 3;
    new_t.ampiezze[1] = new_t.ampiezze[3] = 2;

    __set_zero_tetramino__(&new_t);

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


Tetramino_t create_tetramino7()
{
    int i, j;
    Tetramino_t new_t;
    new_t.colore = ROSSO;
    new_t.rotazione = BASIC;
    new_t.ampiezze[0] = new_t.ampiezze[2] = 4;
    new_t.ampiezze[1] = new_t.ampiezze[3] = 2;

    __set_zero_tetramino__(&new_t);

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


void print_tetramino(const Tetramino_t t)
{
    const string_t terminal_colors[] = { "\033[0;36m", "\033[0;34m",
                                         "", "\033[0;33m",
                                         "\033[0;31m", "\033[0;32m",
                                         "\033[0;35m" };
    int i, j;
    printf(" _________ \n");
    for (i = 0; i < DIM; ++i) {
        printf("| ");
        for (j = 0; j < DIM; ++j) {
            printf("%s", terminal_colors[t.colore]);
            if(t.rotazione == BASIC) {
                if (t.stato_BASIC[i][j] == 1) printf("# ");
                else printf("  ");
            } else if(t.rotazione == ADD90) {
                if (t.stato_ADD90[i][j] == 1) printf("# ");
                else printf("  ");
            } else if(t.rotazione == ADD180) {
                if (t.stato_ADD180[i][j] == 1) printf("# ");
                else printf("  ");
            } else if(t.rotazione == ADD270) {
                if (t.stato_ADD270[i][j] == 1) printf("# ");
                else printf("  ");
            }
            printf("\033[0m");
        }
        printf("|\n");
    }
    printf(" --------- \n");
}


void print_tetramino_basic(const Tetramino_t t)
{
    int i, j;
    for (i = 0; i < DIM; ++i) {
        for (j = 0; j < DIM; ++j) {
            if(t.rotazione == BASIC) {
                printf("%d ", t.stato_BASIC[i][j]);
            } else if(t.rotazione == ADD90) {
                printf("%d ", t.stato_ADD90[i][j]);
            } else if(t.rotazione == ADD180) {
                printf("%d ", t.stato_ADD180[i][j]);
            } else if(t.rotazione == ADD270) {
                printf("%d ", t.stato_ADD270[i][j]);
            }
        }

        printf("\n");
    }
}


void print_settetramini(const Tetraminodigioco_t t[])
{
    int i;
    for (i = 0; i < PIECES; ++i) {
        printf("\n\n= = = = = = = = = = = = = =\n");
        if (t[i].n_disponibili > 0) {
            string_t val;

            printf("%sID tetramino: %d%s\n", "\e[1;97m", t[i].id, "\033[0m");
            print_tetramino(t[i].t);

            if (t[i].n_disponibili < 10) val = "\e[0;93m";
            else val = "\e[0;92m";

            printf("Disponibili: %s%d%s", val, t[i].n_disponibili, "\033[0m");
        } else {
            printf("%sI PEZZI PER QUESTO TETRAMINO SONO TERMINATI !%s    ", "\e[1;91m", "\033[0m");
            print_tetramino(t[i].t);
        }
    }
    printf("\n\n= = = = = = = = = = = = = = = =\n");
}


void print_possibilirotazioni(int id)
{
    Tetramino_t t;
    switch (id) {
        case 1: t = create_tetramino1(); break;
        case 2: t = create_tetramino2(); break;
        case 3: t = create_tetramino3(); break;
        case 4: t = create_tetramino4(); break;
        case 5: t = create_tetramino5(); break;
        case 6: t = create_tetramino6(); break;
        default: t = create_tetramino7(); break;
    }
    printf("1:\n");
    print_tetramino(t);
    printf("2:\n");
    t.rotazione = ADD90;
    print_tetramino(t);
    printf("3:\n");
    t.rotazione = ADD180;
    print_tetramino(t);
    printf("4:\n");
    t.rotazione = ADD270;
    print_tetramino(t);
}

/**
 * [PRIVATE]\n
 * Metodo avente il compito di restituire l'altezza reale di un tetramino (definito all'interno di una matrice di interi
 * 4x4.
 * @param m - la matrice contenente il tetramino
 * @return valore intero indicante l'altezza reale, o effettiva, del tetramino.
 */
int __get_altezzatetramino__(const int m[4][4]) {
    int i, j, cont = 0;
    for (i = 3; i >= 0; --i)
        for (j = 0; j < 4; ++j)
            if (m[i][j]) {
                ++cont;
                break;
            }

    return cont;
}

int get_altezzatetramino(const Tetramino_t t)
{
    if (t.rotazione == BASIC)
        return __get_altezzatetramino__(t.stato_BASIC);
    else if (t.rotazione == ADD90)
        return __get_altezzatetramino__(t.stato_ADD90);
    else if (t.rotazione == ADD180)
        return __get_altezzatetramino__(t.stato_ADD180);
    else
        return __get_altezzatetramino__(t.stato_ADD270);
}

Tetraminodigioco_t* create_tetraminiset(Mode_t mode)
{
    int i;
    Tetraminodigioco_t* t_v = (Tetraminodigioco_t*) malloc(sizeof(Tetraminodigioco_t) * PIECES);
    for (i = 0; i < PIECES; ++i)
    {
        t_v[i].id = i + 1;
        t_v[i].n_disponibili = 20 * (int)mode;
    }

    /* Allo stato iniziale imposto tutti i tetramini con un orientamento di 0° (ovvero allo stato di base) */
    t_v[0].t = create_tetramino1();
    t_v[1].t = create_tetramino2();
    t_v[2].t = create_tetramino3();
    t_v[3].t = create_tetramino4();
    t_v[4].t = create_tetramino5();
    t_v[5].t = create_tetramino6();
    t_v[6].t = create_tetramino7();
    return t_v;
}