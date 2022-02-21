#include "PianoDiGioco/pianodigioco.h"
#include "GameSetting/menus.h"
#include "GameSetting/Player/player.h"
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define PLAYERS_FILE "./GameSetting/Player/players.txt"

void set_tetraminiadisposizione(Tetraminodigioco_t* t, Scelta_t scelta) {
    int i;
    for (i = 0; i < PIECES; ++i) {
        t[i].id = i + 1;
        t[i].n_disponibili = 20 * (int)scelta;
    }

    t[0].t = create_tetramino1();
    t[1].t = create_tetramino2();
    t[2].t = create_tetramino3();
    t[3].t = create_tetramino4();
    t[4].t = create_tetramino5();
    t[5].t = create_tetramino6();
    t[6].t = create_tetramino7();
}

int main() {
    Scelta_t scelta_player;
    PianoDiGioco_t pianoDiGioco;
    Tetraminodigioco_t tetramini_a_disposizione[PIECES];
    Player_t pl1, pl2;

    print_titologioco();
 riapri_menu:
    scelta_player = menu_gioco();

    if (scelta_player == SETTINGS) {
        print_settingsmenu();
        goto riapri_menu;
    }

    set_tetraminiadisposizione(tetramini_a_disposizione, scelta_player);
    pianoDiGioco = create_pianodigioco_sp();
    char nome[20];
    if (scelta_player == SINGLEPLAYER) {
        printf("Inserisci il nome che vuoi avere durante questa partita (max 20 caratteri):\n");
        scanf("%s", nome);
        pl1 = get_nuovoplayer(nome);

        while (pianoDiGioco.is_limiteraggiunto == FALSE) {

            print_pezzirimanenti(tetramini_a_disposizione);
            pianoDiGioco.is_limiteraggiunto = TRUE;
        }
    } else {
        printf("Inserisci il nome che il PRIMO giocatore vuole avere durante questa partita (max 20 caratteri):\n");
        scanf("%s", nome);
        pl1 = get_nuovoplayer(nome);

        printf("Inserisci il nome che il SECONDO giocatore vuole avere durante questa partita (max 20 caratteri):\n");
        scanf("%s", nome);
        pl2 = get_nuovoplayer(nome);

        while (pianoDiGioco.is_limiteraggiunto == FALSE) {

            print_pezzirimanenti(tetramini_a_disposizione);
            pianoDiGioco.is_limiteraggiunto = TRUE;
        }
    }

    return 0;
}
