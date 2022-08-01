#include "PianoDiGioco/pianodigioco.h"
#include "GameSetting/menus.h"
#include "GameSetting/Player/player.h"

/**
 * Metodo avente il compito di impostare nelle condizioni iniziali, per iniziare la partita, l'insieme di tetramini a
 * disposizione contandone 20 per la modalità <code>SINGLEPLAYER</code> e 40 per la <code>MULTIPLAYER</code>
 * @param t_v: l'array di tetramini da inizializzare
 * @param mode: la modalità di gioco scelta dall'utente
 */
void set_tetraminiadisposizione(Tetraminodigioco_t* t_v, Mode_t mode)
{
    int i;
    for (i = 0; i < PIECES; ++i)
    {
        t_v[i].id = i + 1;
        t_v[i].n_disponibili = 20 * (int)mode;
    }

    // Allo stato iniziale imposto tutti i tetramini con un orientamento di 0° (ovvero allo stato di base)
    t_v[0].t = create_tetramino1();
    t_v[1].t = create_tetramino2();
    t_v[2].t = create_tetramino3();
    t_v[3].t = create_tetramino4();
    t_v[4].t = create_tetramino5();
    t_v[5].t = create_tetramino6();
    t_v[6].t = create_tetramino7();
}

/**
 * Metodo generico che consente di stampare a video una richiesta all'utente la cui risposta è un semplice <code>Boolean</code>
 * del tipo <code>true/false</code> oppure scelta1 / scelta2.
 * @param richiesta: stringa contenente il testo della richiesta da stampare a video
 * @return la scelta impostata dall'utente, rappresentata attraverso un <code>Bool_t</code>
 */
Bool_t do_richiesta(string_t richiesta)
{
    Bool_t scelta = FALSE;
    printf("%s\n  1- Si\n  0- No\n", richiesta);
    scanf("%d", &scelta);
    return scelta;
}

int main()
{
    Mode_t scelta_player = SINGLEPLAYER;
    PianoDiGioco_t pianoDiGioco;
    Tetraminodigioco_t tipologie_tetramini_disponibili[PIECES];
    set_tetraminiadisposizione(tipologie_tetramini_disponibili, scelta_player);
    pianoDiGioco = create_pianodigioco();

    Tetramino_t t = tipologie_tetramini_disponibili[1].t;
    Tetramino_t t1 = tipologie_tetramini_disponibili[0].t;
    t.rotazione = ADD270;
    t1.rotazione = ADD90;

    printf("%d\n", set_tetraminosupianodigioco(&pianoDiGioco, tipologie_tetramini_disponibili[3].t, 6));
    printf("%d\n", set_tetraminosupianodigioco(&pianoDiGioco, t, 6));
    printf("%d\n", set_tetraminosupianodigioco(&pianoDiGioco, tipologie_tetramini_disponibili[3].t, 6));
    printf("%d\n", set_tetraminosupianodigioco(&pianoDiGioco, t1, 6));
    printf("%d\n", set_tetraminosupianodigioco(&pianoDiGioco, t1, 6));
    printf("%d\n", set_tetraminosupianodigioco(&pianoDiGioco, tipologie_tetramini_disponibili[1].t, 6));
    //printf("%d\n", set_tetraminosupianodigioco(&pianoDiGioco, tipologie_tetramini_disponibili[0].t, 6));
    printf("%d\n", set_tetraminosupianodigioco(&pianoDiGioco, tipologie_tetramini_disponibili[5].t, 2));
    //printf("%d\n", set_tetraminosupianodigioco(&pianoDiGioco, tipologie_tetramini_disponibili[6].t, 9));
    print_pianodigioco(pianoDiGioco);
    //print_pianodigioco(pianoDiGioco);

    printf("%d\n", pianoDiGioco.is_limiteraggiunto);

    return 0;
}

int main_vero()
{
    Mode_t scelta_player;
    PianoDiGioco_t pianoDiGioco;
    Tetraminodigioco_t tipologie_tetramini_disponibili[PIECES];
    Player_t pl1, pl2;
    Tetramino_t t;
    int scelta;

    print_titologioco();
    menu_gioco();

    scanf("%d", &scelta);
    while(scelta != 1 && scelta != 2)
        scanf("%d", &scelta);

    if (scelta == 1) scelta_player = SINGLEPLAYER;
    else scelta_player = MULTIPLAYER;

    printf("\n");

    set_tetraminiadisposizione(tipologie_tetramini_disponibili, scelta_player);
    pianoDiGioco = create_pianodigioco();


    if (scelta_player == SINGLEPLAYER)
    {
        // printf("Inserisci il nome che vuoi avere durante questa partita (max 20 caratteri):\n");
        // TODO: Lettura del nome di un giocatore

        pl1 = get_nuovoplayer("Lollone Pellegrini\0");

        while (pianoDiGioco.is_limiteraggiunto == FALSE)
        {
            int id = -1, i, col, rotazione;
            print_pianodigioco(pianoDiGioco);
            printf("\n\n");
            printf("+ - - - - - - - - - +\n| Scegli  TETRAMINO |\n+ - - - - - - - - - +\n");

            if (do_richiesta("Vuoi vedere i tetramini a disposizione e i relativi codici identificativi?"))
                print_tetramini(tipologie_tetramini_disponibili);
        selezione_tetramino:
            printf("Scrivere il codice identificativo del tetramino che si vuole posizionare:\n");
            scanf("%d", &id);
            if(id < 1 || id > 7)
            {
                perror("Valore inserito non valido\n");
                goto selezione_tetramino;
            }

            for (i = 0; i < PIECES; ++i)
            {
                if(tipologie_tetramini_disponibili[i].id == id && tipologie_tetramini_disponibili->n_disponibili <= 0)
                {
                    perror("Numero di tetramini a disposizione terminato!!!\n");
                    printf("Inserisci un nuovo tetramino valido!\n");
                    goto selezione_tetramino;
                }
                else
                {
                    t = tipologie_tetramini_disponibili[i].t;
                    tipologie_tetramini_disponibili[i].n_disponibili--;
                    break;
                }
            }

        selezione_colonna:
            printf("+ - - - - - - - +\n| Scegli COLONNA |\n+ - - - - - - - +\n");
            printf("In quale COLONNA vuoi calare il tetramino selezionato (id = %d)?\n", id);
            scanf("%d", &col);
            if(col < 0 || col > 9)
            {
                perror("Valore della colonna non valido, re-inseriscine uno di corretto!!!\n");
                goto selezione_colonna;
            }

        selezione_rotazione:
            printf("\n+ - - - - - - - - +\n| Scegli ROTAZIONE |\n+ - - - - - - - - +\n");
            printf("Scegli con quale orientamento vuoi calare il tetramino nella colonna.\n");
            if (do_richiesta("Vuoi stampare tutte le possibili rotazioni a video per valutare quale scegliere?"))
                print_possibilirotazioni(id);

            printf("Inserisci l'id numerico fornito per la rotazione scelta:\n");
            scanf("%d", &rotazione);
            if (rotazione < 1 || rotazione > 4)
            {
                perror("Valore della rotazione non valido, re-inseriscine uno di corretto!!!\n");
                goto selezione_rotazione;
            }

            switch (rotazione)
            {
                case 1: t.rotazione = BASIC; break;
                case 2: t.rotazione = ADD90; break;
                case 3: t.rotazione = ADD180; break;
                default: t.rotazione = ADD270; break;
            }

            set_tetraminosupianodigioco(&pianoDiGioco, t, col);

            pianoDiGioco.is_limiteraggiunto = TRUE;
        }
    }
    else
    {
        /* Multiplayer */
    }

    return 0;
}