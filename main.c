#include "PianoDiGioco/pianodigioco.h"
#include "GameSetting/Player/player.h"
#include "Elements/color_codes.h"
#include "Elements/exit_modes.h"
#include<stdlib.h>

/**
 * Metodo utilizzato per generare un delay a terminale mediante l'utilizzo della tecnica del busy waiting (che però
 * consuma inutilmente tempo di CPU).
 * @param time - per quante volte ciclare a vuoto
 */
void delay(int time) {
    int i, j;
    for (i = 1; i <= time; i++)
        for (j = 1; j <= time; j++)
        {}
}

/**
 * Metodo generico che consente di stampare a video una richiesta all'utente la cui risposta è un semplice <code>Boolean</code>
 * del tipo <code>true/false</code> oppure scelta1 / scelta2.
 * @param richiesta: stringa contenente il testo della richiesta da stampare a video
 * @return la scelta impostata dall'utente, rappresentata attraverso un <code>Bool_t</code>
 */
Bool_t do_richiesta(const string_t richiesta)
{
    Bool_t scelta = FALSE;
    printf("%s\n\t1- Si\n\t0- No\n", richiesta);
    scanf("%d", &scelta);
    return scelta;
}

int main() {
    Mode_t mod_gioco;
    Tetraminodigioco_t* tetramini_set;
    int scelta_modgioco;

    menu_iniziale:
    print_titologioco();
    print_menugioco();


    /* scelta della modalità di gioco */
    seleziona_modalita:
    scanf("%d", &scelta_modgioco);
    if (scelta_modgioco < 1 || scelta_modgioco > 3)
        goto seleziona_modalita;

    if (scelta_modgioco == 3) return 0;

    mod_gioco = (scelta_modgioco == 1) ? SINGLEPLAYER : MULTIPLAYER;

    /* creazione del set di tetramini sulla base della modalià di gioco scelta */
    tetramini_set = create_tetraminiset(mod_gioco);

    if (mod_gioco == SINGLEPLAYER)
    {
        PianoDiGioco_t p;
        Player_t player;
        char nome[20];

        printf(" - Inserisci il tuo nome (non superiore ai 20 caratteri):\n");
        scanf("%s", nome);

        player = create_newplayer(nome);
        p = create_pianodigioco();

        while (!p.is_limiteraggiunto) {
            int id_tetramino, rotazione, colonna;
            Tetramino_t tetramino_scelto;
            Bool_t res; /* risultato del collocamento sul piano di gioco del tetramino */

            delay(20000);

            printf("\n\n");
            printf("Loading...");
            printf("\n\n");

            delay(15000);

            print_player(player);

            delay(30000);

            /* Stampa piano di gioco */
            print_pianodigioco(p);

            /* Chiedi tetramino */
            printf("\n+ - - - - - - - - - +\n| SCEGLI  TETRAMINO |\n+ - - - - - - - - - +\n");

            if (do_richiesta(" - Vuoi stampare tutto il set di tetramini con le relative disponibilità per una migliore scelta?"))
                print_settetramini(tetramini_set);

            seleziona_tetramino:
            printf(" - Quale tetramino hai scelto? (Scrivi il suo id)\n");
            scanf("%d", &id_tetramino);

            if (id_tetramino < 1 || id_tetramino > 7) {
                printf("%sCodice scorretto o disponibilità esaurita!!%s\n", ROSSO, NERO);
                goto seleziona_tetramino;
            }

            tetramino_scelto = tetramini_set[id_tetramino - 1].t;

            /* Chiedi rotazione */
            printf("\n+ - - - - - - - - - +\n| SCEGLI  ROTAZIONE |\n+ - - - - - - - - - +\n");
            if (do_richiesta(" - Vuoi stampare tutte le possibili rotazioni del tetramino scelto per una migliore scelta?"))
                print_possibilirotazioni(id_tetramino);

            selezione_rotazione:
            printf("- Quale rotazione hai scelto? (Scrivi il suo id)\n");
            scanf("%d", &rotazione);

            if (rotazione < 1 || rotazione > 4) {
                printf("%sValore rotazione non valido, inseriscine uno corretto!!%s\n", ROSSO, NERO);
                goto selezione_rotazione;
            }

            switch (rotazione) {
                case 1: tetramino_scelto.rotazione = BASIC; break;
                case 2: tetramino_scelto.rotazione = ADD90; break;
                case 3: tetramino_scelto.rotazione = ADD180; break;
                default: tetramino_scelto.rotazione = ADD270; break;
            }

            /* Chiedi colonna */
            printf("\n+ - - - - - - - - +\n| SCEGLI  COLONNA |\n+ - - - - - - - - +\n");

        selezione_colonna:
            printf(" - Scrivi il numero della colonna in cui vuoi calare il lato destro del tetramino.\n");
            scanf("%d", &colonna);

            if(colonna < 0 || colonna > 9) {
                printf("%sValore della colonna non valido, re-inseriscine uno di corretto!!%s\n", ROSSO, NERO);
                goto selezione_colonna;
            }

            /* posiziona sul piano di gioco e vedi se si possono eliminare righe */
            res = set_tetraminosupianodigioco(&p, &player, tetramino_scelto, colonna);

            if (res)
                tetramini_set[id_tetramino - 1].n_disponibili--;
            else if (!p.is_limiteraggiunto) {
                printf("%sNon è stato possibile piazzare il tetramino dove hai richiesto!!%s\n", ROSSO, NERO);
                goto selezione_colonna;
            }
        }

        print_losetitle(player);

        delay(40000);

        goto menu_iniziale;
    }
    else
    {
        PianoDiGioco_t p_pl1, p_pl2;
        Tetramino_t tetramino_scelto;
        Player_t player1, player2;
        ExitMode_t exitMode = NONE; /* modalità di terminazione della partita */
        Bool_t res; /* risultato del collocamento sul piano di gioco del tetramino */
        int id_tetramino, rotazione, colonna;
        char nome1[20];
        char nome2[20];
        int i;

        /* inizializzo giocatori e piani di gioco dei relativi */
        p_pl1 = create_pianodigioco();
        p_pl2 = create_pianodigioco();


        printf(" - Inserisci il nome del giocatore 1 (non superiore ai 20 caratteri):\n");
        scanf("%s", nome1);

        printf("\n");
        printf(" - Inserisci il nome del giocatore 2 (non superiore ai 20 caratteri):\n");
        scanf("%s", nome2);

        player1 = create_newplayer(nome1);
        player2 = create_newplayer(nome2);

        /* due giocatori */
        for (i = 1; !p_pl1.is_limiteraggiunto && !p_pl2.is_limiteraggiunto; ++i) {
            int j, cont = 0;

            /* Verifico se sono rimasti tetramini */
            for (j = 0; j < 7; ++j)
                if (tetramini_set[j].n_disponibili == 0) cont++;

            delay(20000);

            printf("\n\n");
            printf("Loading...");
            printf("\n\n");

            delay(15000);

            /* informazioni relative al turno in corso */
            print_turnoinfoplayer((i % 2) ? player1 : player2);


            if (cont == 7) { exitMode = NO_PIECES; break; }

            /* Stampa piano di gioco */
            print_pianodigioco((i % 2) ? p_pl1 : p_pl2);

            /* Chiedi tetramino */
            printf("\n+ - - - - - - - - - +\n| SCEGLI  TETRAMINO |\n+ - - - - - - - - - +\n");

            if (do_richiesta(" - Vuoi stampare tutto il set di tetramini con le relative disponibilità per una migliore scelta?"))
                print_settetramini(tetramini_set);

        seleziona_tetramino_mp:
            printf(" - Quale tetramino hai scelto? (Scrivi il suo id)\n");
            scanf("%d", &id_tetramino);

            if (id_tetramino < 1 || id_tetramino > 7) {
                printf("%sCodice scorretto o disponibilità esaurita!!%s\n", ROSSO, NERO);
                goto seleziona_tetramino_mp;
            }

            tetramino_scelto = tetramini_set[id_tetramino - 1].t;

            /* Chiedi rotazione */
            printf("\n+ - - - - - - - - - +\n| SCEGLI  ROTAZIONE |\n+ - - - - - - - - - +\n");
            if (do_richiesta(" - Vuoi stampare tutte le possibili rotazioni del tetramino scelto per una migliore scelta?"))
                print_possibilirotazioni(id_tetramino);

        selezione_rotazione_mp:
            printf("- Quale rotazione hai scelto? (Scrivi il suo id)\n");
            scanf("%d", &rotazione);

            if (rotazione < 1 || rotazione > 4) {
                printf("%sValore rotazione non valido, inseriscine uno corretto!%s\n", ROSSO, NERO);
                goto selezione_rotazione_mp;
            }

            switch (rotazione) {
                case 1: tetramino_scelto.rotazione = BASIC; break;
                case 2: tetramino_scelto.rotazione = ADD90; break;
                case 3: tetramino_scelto.rotazione = ADD180; break;
                default: tetramino_scelto.rotazione = ADD270; break;
            }

            /* Chiedi colonna */
            printf("\n+ - - - - - - - - +\n| SCEGLI  COLONNA |\n+ - - - - - - - - +\n");

        selezione_colonna_mp:
            printf(" - Scrivi il numero della colonna in cui vuoi calare il lato destro del tetramino.\n");
            scanf("%d", &colonna);

            if(colonna < 0 || colonna > 9) {
                printf("%sValore della colonna non valido, re-inseriscine uno di corretto!!%s\n", ROSSO, NERO);
                goto selezione_colonna_mp;
            }

            /* posiziona sul piano di gioco e vedi se si possono eliminare righe */
            res = set_tetraminosupianodigioco((i % 2) ? &p_pl1 : &p_pl2,
                                              (i % 2) ? &player1 : &player2,
                                              tetramino_scelto,
                                              colonna);

            if (res) {
                Player_t p = (i % 2) ? player1 : player2;
                printf("   Punti per %s totalizzati fino ad ora: %d\n\n", p.nome, p.points);
                tetramini_set[id_tetramino - 1].n_disponibili--;
                printf("\n\n");
                if (do_richiesta(" - Vuoi stampare il piano di gioco per vedere il risultato delle tue modifiche?"))
                    print_pianodigioco((i % 2) ? p_pl1 : p_pl2);
            } else if (!((i % 2) ? p_pl1 : p_pl2).is_limiteraggiunto) {
                printf("%sNon è stato possibile piazzare il tetramino dove hai richiesto!!%s\n", ROSSO, NERO);
                exitMode = OUT_OF_MATRIX;
                break;
            }
        }

        /*
         * Qualcuno ha perso:
         * Se i pezzi sono finiti valuto chi ha totalizzato il punteggio più alto
         * altrimenti
         * se si è sbagliato a posizionare un pezzo e si è andati out-of-matrix allora tale giocatore ha perso
         */
        if ((exitMode == NO_PIECES && player1.points > player2.points) ||
            (exitMode == OUT_OF_MATRIX && (i % 2))) {
            print_losetitle(player1);
            print_wintitle(player2);
        } else {
            print_losetitle(player2);
            print_wintitle(player1);
        }

        delay(40000);

        goto menu_iniziale;
    }
}
