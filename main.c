#include "PianoDiGioco/pianodigioco.h"
#define PIECES 7

/**
 * Metodo avente il compito di stampare ad ogni turno di gioco i tetramini rimasti per giocare
 * @param t: array contenente le informazioni necessarie, array di tipo Tetraminodigioco_t.
 */
void print_pezzirimanenti(const Tetraminodigioco_t t[]) {
    int i;
    for (i = 0; i < PIECES; ++i) {
        printf("\n\n= = = = = = = = = = = = = = = = = = = = = = =\n");
        if (t[i].n_disponibili > 0) {
            printf("%sID tetramino: %d%s\n", "\e[1;97m", t[i].id, "\033[0m");
            print_tetramino(t[i].t);

            string_t val;
            if (t[i].n_disponibili < 5)
                val = "\e[0;93m";
            else
                val = "\e[0;92m";
            printf("A disposizione: %s%d%s", val, t[i].n_disponibili, "\033[0m");
        } else {
            printf("%sI PEZZI PER QUESTO TETRAMINO SONO TERMINATI !%s\n", "\e[1;91m", "\033[0m");
            print_tetramino(t[i].t);
        }
    }
    printf("\n\n= = = = = = = = = = = = = = = = = = = = = = =\n");
}

int main() {
    Tetraminodigioco_t tetramini_a_disposizione[PIECES] = {
            { .id = 1, .t = create_tetramino1(), .n_disponibili = 3 },
            { .id = 2, .t = create_tetramino2(), .n_disponibili = 12 },
            { .id = 3, .t = create_tetramino3(), .n_disponibili = 4 },
            { .id = 4, .t = create_tetramino4(), .n_disponibili = 20 },
            { .id = 5, .t = create_tetramino5(), .n_disponibili = 19 },
            { .id = 6, .t = create_tetramino6(), .n_disponibili = 0 },
            { .id = 7, .t = create_tetramino7(), .n_disponibili = 9 }
    };
    PianoDiGioco_t pianoDiGioco;
    pianoDiGioco = create_pianodigioco_sp();

    while (pianoDiGioco.is_limiteraggiunto == FALSE) {
        print_pezzirimanenti(tetramini_a_disposizione);
        pianoDiGioco.is_limiteraggiunto = TRUE;
    }
    return 0;
}
