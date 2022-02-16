#include "PianoDiGioco/pianodigioco.h"
#include "GameSetting/menus.h"

int main() {
    Scelta_t scelta_player;
    print_titologioco();
    scelta_player = menu_gioco();
    Tetraminodigioco_t tetramini_a_disposizione[PIECES] = {
            { .id = 1, .t = create_tetramino1(), .n_disponibili = 20 },
            { .id = 2, .t = create_tetramino2(), .n_disponibili = 20 },
            { .id = 3, .t = create_tetramino3(), .n_disponibili = 20 },
            { .id = 4, .t = create_tetramino4(), .n_disponibili = 20 },
            { .id = 5, .t = create_tetramino5(), .n_disponibili = 20 },
            { .id = 6, .t = create_tetramino6(), .n_disponibili = 20 },
            { .id = 7, .t = create_tetramino7(), .n_disponibili = 20 }
    };
    PianoDiGioco_t pianoDiGioco;
    pianoDiGioco = create_pianodigioco_sp();

    while (pianoDiGioco.is_limiteraggiunto == FALSE) {

        print_pezzirimanenti(tetramini_a_disposizione);
        pianoDiGioco.is_limiteraggiunto = TRUE;
    }
    return 0;
}
