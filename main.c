#include "PianoDiGioco/pianodigioco.h"

int main() {
    Tetraminodigioco_t tetramini_a_disposizione[7] = {
            { .t = create_tetramino1(), .n_disponibili = 20 },
            { .t = create_tetramino2(), .n_disponibili = 20 },
            { .t = create_tetramino3(), .n_disponibili = 20 },
            { .t = create_tetramino4(), .n_disponibili = 20 },
            { .t = create_tetramino5(), .n_disponibili = 20 },
            { .t = create_tetramino6(), .n_disponibili = 20 },
            { .t = create_tetramino7(), .n_disponibili = 20 }
    };

    PianoDiGioco_t pianoDiGioco;
    pianoDiGioco = create_pianodigioco_sp();

    int i;
    for (i = 0; i < 7; ++i) {
        print_tetramino(tetramini_a_disposizione[i].t);
        printf("A disposizione: %d\n", tetramini_a_disposizione[i].n_disponibili);
    }
    return 0;
}
