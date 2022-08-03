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

/*
int main_()
{
    Mode_t scelta_player;
    PianoDiGioco_t pianoDiGioco;
    Tetraminodigioco_t tipologie_tetramini_disponibili[PIECES];
    Player_t pl1, pl2;
    Tetramino_t t;
    int scelta;

    set_tetraminiadisposizione(tipologie_tetramini_disponibili, scelta_player);
    pianoDiGioco = create_pianodigioco();


    if (scelta_player == SINGLEPLAYER)
    {
        pl1 = get_nuovoplayer("Player 1\0");
        print_pianodigioco(pianoDiGioco);

        while (pianoDiGioco.is_limiteraggiunto == FALSE)
        {
            int id = -1, col, rotazione;
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


            if(tipologie_tetramini_disponibili[id].n_disponibili <= 0)
            {
                perror("Numero di tetramini a disposizione terminato!!!\n");
                printf("Inserisci un nuovo tetramino valido!\n");
                goto selezione_tetramino;
            }
            else
                t = tipologie_tetramini_disponibili[id].t;

            print_tetramino(t);

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

            Bool_t res = set_tetraminosupianodigioco(&pianoDiGioco, t, col);

            if (!pianoDiGioco.is_limiteraggiunto && res) {
                print_pianodigioco(pianoDiGioco);
                tipologie_tetramini_disponibili[id].n_disponibili--;
            }

            if (!res)
            {
                printf("\e[4;31m\n");
                printf("Qualcosa è andato storto... non è stato possibile collocare il tuo tetramino.\n");
                printf("\e[0;37m");
            }

        }

        printf(" + - - - - - - +\n| Hai  PERSO |\n+ - - - - - - +\n");
    }
    else
    {

    }

    return 0;
}
*/

int main() {
    Mode_t mod_gioco;
    PianoDiGioco_t p;
    Tetraminodigioco_t* tetramini_set;
    int scelta_modgioco;
    print_titologioco();
    print_menugioco();

    /* scelta della modalità di gioco */
    scanf("%d", &scelta_modgioco);
    while(scelta_modgioco != 1 && scelta_modgioco != 2)
        scanf("%d", &scelta_modgioco);

    mod_gioco = (scelta_modgioco == 1) ? SINGLEPLAYER : MULTIPLAYER;

    /* inizializzazione dei supporti per il gioco */
    p = create_pianodigioco();
    tetramini_set = create_tetraminiset(mod_gioco);

    if (mod_gioco == SINGLEPLAYER)
    {
        Player_t player = create_newplayer("Player 1");
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

            switch (rotazione)
            {
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

            if(colonna < 0 || colonna > 9)
            {
                perror("Valore della colonna non valido, re-inseriscine uno di corretto!!!\n");
                goto selezione_colonna;
            }

            /* posiziona sul piano di gioco e vedi se si possono eliminare righe */
            res = set_tetraminosupianodigioco(&p, &player, tetramino_scelto, colonna);

            if (res)
                tetramini_set[id_tetramino - 1].n_disponibili--;
            else if (!p.is_limiteraggiunto){
                perror("Non è stato possibile piazzare il tetramino dove hai richiesto!");
                goto selezione_colonna;
            }
        }

        /* ha perso */
    }
    else
    {

    }

    return 0;
}