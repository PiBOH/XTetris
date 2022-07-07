#include "PianoDiGioco/pianodigioco.h"
#include "GameSetting/menus.h"
#include "GameSetting/Player/player.h"

void set_tetraminiadisposizione(Tetraminodigioco_t* t, Mode_t scelta) {
    int i;
    for (i = 0; i < PIECES; ++i) {
        t[i].id = i + 1;
        t[i].n_disponibili = 20 * (int)scelta;
    }

    // Allo stato iniziale imposto tutti i tetramini con un orientamento di 0° (ovvero allo stato di base)
    t[0].t = create_tetramino1();
    t[1].t = create_tetramino2();
    t[2].t = create_tetramino3();
    t[3].t = create_tetramino4();
    t[4].t = create_tetramino5();
    t[5].t = create_tetramino6();
    t[6].t = create_tetramino7();
}

Bool_t do_richiesta(const string_t richiesta) {
    Bool_t scelta = FALSE;
    printf("%s\n  1- Si\n  0- No\n", richiesta);
    scanf("%d", &scelta);
    return scelta;
}

int main() {
    Mode_t scelta_player;
    PianoDiGioco_t pianoDiGioco;
    Tetraminodigioco_t tipologie_tetramini_disponibili[PIECES];
    Player_t pl1, pl2;
    Tetramino_t t;

    print_titologioco();
 riapri_menu:
    scelta_player = menu_gioco();

    set_tetraminiadisposizione(tipologie_tetramini_disponibili, scelta_player);
    pianoDiGioco = create_pianodigioco();
    char nome[20];
    if (scelta_player == SINGLEPLAYER) {
        printf("Inserisci il nome che vuoi avere durante questa partita (max 20 caratteri):\n");
        scanf("%s", nome);
        pl1 = get_nuovoplayer(nome);

        while (pianoDiGioco.is_limiteraggiunto == FALSE) {
            int id = -1, i, col, rotazione;


            printf("\e[1;1H\e[2J"); // clean terminal
            if (do_richiesta("Vuoi vedere i tetramini a disposizione e i relativi codici identificativi?"))
                print_pezzirimanenti(tetramini_a_disposizione);
        selezione_tetramino:
            printf("Scrivere il codice identificativo del tetramino che si vuole posizionare:\n");
            scanf("%d", &id);
            if(id < 1 || id > 7) {
                perror("Valore inserito non valido\n");
                goto selezione_tetramino;
            }

            for (i = 0; i < PIECES; ++i) {
                if(tetramini_a_disposizione[i].id == id && tetramini_a_disposizione->n_disponibili <= 0) {
                    perror("Numero di tetramini a disposizione terminato!!!\n");
                    printf("Inserisci un nuovo tetramino valido!");
                    goto selezione_tetramino;
                } else {
                    t = tetramini_a_disposizione[i].t;
                    tetramini_a_disposizione[i].n_disponibili--;
                    break;
                }
            }

        selezione_colonna:
            printf("In quale COLONNA vuoi calare il lato in basso a dx del tetramino selezionato (id = %d)?\n", id);
            scanf("%d", &col);
            if(col < 0 || col > 9) {
                perror("Valore della colonna non valido, re-inseriscine uno di corretto!!!\n");
                goto selezione_colonna;
            }

            /* selezione dell'orientamento */
            printf("Scegli con quale orientamento vuoi calare il tetramino nella colonna.\n");
            if (do_richiesta("Vuoi stampare tutte le possibili rotazioni a video per valutare quale scegliere?"))
                print_possibilirotazioni(id);

        selezione_rotazione:
            printf("Inserisci l'id numerico fornito per la rotazione scelta:\n");
            scanf("%d", &rotazione);
            if (rotazione < 1 || rotazione > 4) {
                perror("Valore della rotazione non valido, re-inseriscine uno di corretto!!!\n");
                goto selezione_rotazione;
            }

            switch (rotazione) {
                case 1: t.rotazione = BASIC; break;
                case 2: t.rotazione = ADD90; break;
                case 3: t.rotazione = ADD180; break;
                default: t.rotazione = ADD270; break;
            }

            set_tetraminosupianodigioco(t, col);

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