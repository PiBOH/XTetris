#include "PianoDiGioco/pianodigioco.h"
#include "GameSetting/Player/player.h"

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

    print_titologioco();
    print_menugioco();

    /* scelta della modalità di gioco */
    scanf("%d", &scelta_modgioco);
    while(scelta_modgioco != 1 && scelta_modgioco != 2)
        scanf("%d", &scelta_modgioco);

    mod_gioco = (scelta_modgioco == 1) ? SINGLEPLAYER : MULTIPLAYER;

    tetramini_set = create_tetraminiset(mod_gioco);

    if (mod_gioco == SINGLEPLAYER)
    {
        PianoDiGioco_t p;
        Player_t player = create_newplayer("Player 1");

        p = create_pianodigioco();

        while (!p.is_limiteraggiunto) {
            int id_tetramino, rotazione, colonna;
            Tetramino_t tetramino_scelto;
            Bool_t res; /* risultato del collocamento sul piano di gioco del tetramino */

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
                perror("Codice scorretto o disponibilità esaurita!");
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
                perror("Valore rotazione non valido, inseriscine uno corretto!\n");
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
                perror("Valore della colonna non valido, re-inseriscine uno di corretto!!!\n");
                goto selezione_colonna;
            }

            /* posiziona sul piano di gioco e vedi se si possono eliminare righe */
            res = set_tetraminosupianodigioco(&p, &player, tetramino_scelto, colonna);

            if (res)
                tetramini_set[id_tetramino - 1].n_disponibili--;
            else if (!p.is_limiteraggiunto) {
                perror("Non è stato possibile piazzare il tetramino dove hai richiesto!");
                goto selezione_colonna;
            }
        }

        /* ha perso */
    }
    else
    {
        PianoDiGioco_t p_pl1, p_pl2;
        Tetramino_t tetramino_scelto;
        Player_t player1, player2;
        Bool_t res; /* risultato del collocamento sul piano di gioco del tetramino */
        int id_tetramino, rotazione, colonna;
        int i;

        p_pl1 = create_pianodigioco();
        p_pl2 = create_pianodigioco();
        player1 = create_newplayer("Player 1");
        player2 = create_newplayer("Player 2");

        /* due giocatori */
        for (i = 1; !p_pl1.is_limiteraggiunto && !p_pl2.is_limiteraggiunto; ++i) {
            print_titoloplayer((i % 2) ? player1 : player2);

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
                perror("Codice scorretto o disponibilità esaurita!");
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
                perror("Valore rotazione non valido, inseriscine uno corretto!\n");
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
                perror("Valore della colonna non valido, re-inseriscine uno di corretto!!!\n");
                goto selezione_colonna_mp;
            }

            /* posiziona sul piano di gioco e vedi se si possono eliminare righe */
            res = set_tetraminosupianodigioco((i % 2) ? &p_pl1 : &p_pl2,
                                              (i % 2) ? &player1 : &player2,
                                              tetramino_scelto,
                                              colonna);

            if (res) {
                tetramini_set[id_tetramino - 1].n_disponibili--;
                if (do_richiesta("Vuoi stampare il piano di gioco per vedere il risultato delle tue modifiche?"))
                    print_pianodigioco((i % 2) ? p_pl1 : p_pl2);
            } else if (!((i % 2) ? p_pl1 : p_pl2).is_limiteraggiunto) {
                perror("Non è stato possibile piazzare il tetramino dove hai richiesto!");
                goto selezione_colonna;
            }
        }

        /* qualcuno ha perso */

    }

    return 0;
}