#include <time.h>
#include "PianoDiGioco/pianodigioco.h"
#include "GameSetting/Player/player.h"
#include "Elements/color_codes.h"
#include "Elements/exit_modes.h"

#define NTETRAMINI 7

Tetraminodigioco_t* tetramini_set;

/**
 * Metodo utilizzato per generare un delay a terminale mediante l'utilizzo della tecnica del busy waiting (che però
 * consuma inutilmente tempo di CPU).
 * @param time - durata del ciclo a vuoto
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
    int scelta;
    printf("%s\n\t1- Si\n\t0- No\n", richiesta);
    scanf("%d", &scelta);
    if (scelta) return TRUE;
    return FALSE;
}

/**
 * Metodo avente il compito di richiedere all'utente le informazioni essenziali per poter stabilire che tipo di tetramino
 * lui voglia calare in una determinata mossa
 * @param id puntatore utilizzato per memorizzare al suo interno il valore intero identificativo del tetramino scelto
 * @return il tipo di dato strutturato rappresentante il tetramino scelto dall'utente
 */
Tetramino_t ask_tetramino(int* id) {
    Tetramino_t tetramino_scelto;
    int id_tetramino;
    int rotazione;
    printf("\n+ - - - - - - - - - +\n| SCEGLI  TETRAMINO |\n+ - - - - - - - - - +\n");

    if (do_richiesta(" - Vuoi stampare tutto il set di tetramini con le relative disponibilità per una migliore scelta?"))
        print_settetramini(tetramini_set);

    seleziona_tetramino:
    printf(" - Quale tetramino hai scelto? (Scrivi il suo id)\n");
    scanf("%d", &id_tetramino);

    if (id_tetramino < 1 || id_tetramino > NTETRAMINI || tetramini_set[id_tetramino - 1].n_disponibili == 0) {
        printf("%sCodice scorretto o disponibilità esaurita!!%s\n", ROSSO, DEFAULT);
        goto seleziona_tetramino;
    }

    tetramino_scelto = tetramini_set[id_tetramino - 1].t;

    /* Chiedi rotazione */
    printf("\n+ - - - - - - - - - +\n| SCEGLI  ROTAZIONE |\n+ - - - - - - - - - +\n");
    if (do_richiesta(" - Vuoi stampare tutte le possibili rotazioni del tetramino per una migliore scelta?"))
        print_possibilirotazioni(id_tetramino);

    selezione_rotazione:
    printf("- Quale rotazione hai scelto? (Scrivi il suo id)\n");
    scanf("%d", &rotazione);

    if (rotazione < 1 || rotazione > 4) {
        printf("%sValore rotazione non valido, inseriscine uno corretto!!%s\n", ROSSO, DEFAULT);
        goto selezione_rotazione;
    }

    switch (rotazione) {
        case 1: tetramino_scelto.rotazione = BASIC; break;
        case 2: tetramino_scelto.rotazione = ADD90; break;
        case 3: tetramino_scelto.rotazione = ADD180; break;
        default: tetramino_scelto.rotazione = ADD270; break;
    }

    *id = id_tetramino;
    return tetramino_scelto;
}

/**
 * Metodo che chiede all'utente di selezionare la colonna in cui desidera calare il tetramino che ha appena selezionato
 * o che la tricky mode ha stabilito
 * @return il codice identificativo della colonna
 */
int ask_colonna() {
    int colonna;

    codice_colonna:
    printf(" - Scrivi il numero della colonna in cui vuoi calare il lato destro del tetramino.\n");
    scanf("%d", &colonna);

    if(colonna < 0 || colonna > 9) {
        printf("%sValore della colonna non valido, re-inseriscine uno di corretto!!%s\n", ROSSO, DEFAULT);
        goto codice_colonna;
    }

    return colonna;
}

/**
 * Metodo che verifica se sono ancora presenti tetramini nel set creato ad inizio partita
 * @return <code>TRUE</code> - se esistono ancora tetramini di qualsiasi tipo\n\n
 *<code>FALSE</code> - se sono completamente terminati ( in questo caso la partita deve concludersi )
 */
Bool_t thereis_tetramini() {
    int j, cont = 0;

    for (j = 0; j < NTETRAMINI; ++j)
        if (tetramini_set[j].n_disponibili == 0) cont++;

    if (cont == NTETRAMINI) return FALSE;
    return TRUE;
}

int main() {
    Mode_t mod_gioco;
    int scelta_modgioco;
    Bool_t trickymode = FALSE;
    char c;
    srand(time(NULL));

    menu_iniziale:
    print_titologioco();
    print_menugioco();

    /* scelta della modalità di gioco */
    seleziona_modalita:
    scanf("%d", &scelta_modgioco);
    if (scelta_modgioco < 1 || scelta_modgioco > 4)
        goto seleziona_modalita;

    if (scelta_modgioco == 4) return 0;

    switch (scelta_modgioco) {
        case 1:
            mod_gioco = SINGLEPLAYER; break;
        case 2:
            mod_gioco = MULTIPLAYER_PL; break;
        case 3:
            mod_gioco = MULTIPLAYER_PC; break;
        default:
            return 0;
    }

    /* creazione del set di tetramini sulla base della modalità di gioco scelta */
    if (mod_gioco == SINGLEPLAYER || mod_gioco == MULTIPLAYER_PL)
        tetramini_set = create_tetraminiset(mod_gioco);
    else tetramini_set = create_tetraminiset(MULTIPLAYER_PL);

    printf("\n");
    if (do_richiesta(" - Vuoi entrare nella tricky mode?"))
        trickymode = TRUE;
    else trickymode = FALSE;

    if (mod_gioco == SINGLEPLAYER) {
        PianoDiGioco_t p;
        Player_t player;
        char nome[20];

        printf("\n");
        scanf("%c", &c);
        printf(" - Inserisci il tuo nome (non superiore ai 20 caratteri):\n");
        scanf("%[^\n]", nome);

        player = create_newplayer(nome);
        p = create_pianodigioco();

        delay(15000);

        printf("\n\n");
        printf("Loading...");
        printf("\n\n");

        delay(10000);

        printf("\n");
        print_player(player);
        printf("\n");

        while (!p.is_limiteraggiunto) {
            int id_tetramino, colonna, old_points;
            Tetramino_t tetramino_scelto;
            Bool_t res;

            old_points = player.points;

            if (!thereis_tetramini()) break;

            delay(20000);

            print_pianodigioco(&p);

            if (!trickymode)
                tetramino_scelto = ask_tetramino(&id_tetramino);
            else {
                int rotazione = rand() % 4 + 1;
                genera_nuovo_tetramino:
                id_tetramino = rand() % NTETRAMINI + 1;

                if (tetramini_set[id_tetramino - 1].n_disponibili)
                    tetramino_scelto = tetramini_set[id_tetramino - 1].t;
                else
                    goto genera_nuovo_tetramino;

                switch (rotazione) {
                    case 1:
                        tetramino_scelto.rotazione = BASIC;
                        break;
                    case 2:
                        tetramino_scelto.rotazione = ADD90;
                        break;
                    case 3:
                        tetramino_scelto.rotazione = ADD180;
                        break;
                    default:
                        tetramino_scelto.rotazione = ADD270;
                        break;
                }

                printf("\n\n");
                printf("Tetramino randomico:\n");
                print_tetramino(tetramino_scelto);
            }

            printf("\n+ - - - - - - - - +\n| SCEGLI  COLONNA |\n+ - - - - - - - - +\n");
            selezione_colonna:
            colonna = ask_colonna();

            res = set_tetraminosupianodigioco_sp(&p, &player, tetramino_scelto, colonna, NULL);

            if (res) {
                if (old_points < player.points) {
                    printf("\n");
                    print_player(player);
                    printf("\n");
                    delay(30000);
                }

                tetramini_set[id_tetramino - 1].n_disponibili--;
            } else if (!p.is_limiteraggiunto) {
                printf("%sNon è stato possibile piazzare il tetramino dove hai richiesto!!%s\n", ROSSO, DEFAULT);
                goto selezione_colonna;
            }
        }

        print_finishtitle();
        print_player(player);

        if (!thereis_tetramini()) printf("%sI tetramini sono finiti!!!%s\n", ROSSO, DEFAULT);

        delay(50000);
        goto menu_iniziale;
    }
    else
    {
        PianoDiGioco_t p_pl1, p_pl2;
        Tetramino_t tetramino_scelto;
        Player_t player1, player2;
        ExitMode_t exitMode = NONE;
        Bool_t res;
        int id_tetramino, colonna;
        char nome1[20];
        char nome2[20] = "PC\0";
        char c;
        int i;

        p_pl1 = create_pianodigioco();
        p_pl2 = create_pianodigioco();

        scanf("%c", &c);
        printf(" - Inserisci il nome del giocatore 1 (non superiore ai 20 caratteri):\n");
        scanf("%[^\n]", nome1);
        player1 = create_newplayer(nome1);

        /* filtro tra modalità vs persona e vs pc */
        if (mod_gioco == MULTIPLAYER_PL) {
            scanf("%c", &c);
            printf(" - Inserisci il nome del giocatore 2 senza spazi (non superiore ai 20 caratteri):\n");
            scanf("%[^\n]", nome2);
        }

        player2 = create_newplayer(nome2);

        delay(20000);

        printf("\n\n");
        printf("Loading...");
        printf("\n\n");

        for (i = 1; !p_pl1.is_limiteraggiunto && !p_pl2.is_limiteraggiunto; ++i) {
            /* Verifico se sono rimasti tetramini */
            if (!thereis_tetramini()) {
                exitMode = NO_PIECES;
                break;
            }

            if (mod_gioco == MULTIPLAYER_PL)
                delay(15000);

            print_turnoinfoplayer((i % 2) ? player1 : player2);

            /* Stampa piano di gioco di entrambi se i giocatori sono veri, altrimenti il pc non ha bisogno di vedere
             * prima la situazione */
            if (mod_gioco == MULTIPLAYER_PL) print_pianodigioco((i % 2) ? &p_pl1 : &p_pl2);
            else if (i % 2) print_pianodigioco(&p_pl1);

            if (!trickymode && mod_gioco == MULTIPLAYER_PL || mod_gioco == MULTIPLAYER_PC && (i % 2) && !trickymode)
                tetramino_scelto = ask_tetramino(&id_tetramino);
            else {
                int rotazione;
                genera:
                rotazione = rand() % 4 + 1;
                id_tetramino = rand() % NTETRAMINI + 1;
                if (tetramini_set[id_tetramino - 1].n_disponibili == 0) goto genera;

                tetramino_scelto = tetramini_set[id_tetramino - 1].t;
                switch (rotazione) {
                    case 1:
                        tetramino_scelto.rotazione = BASIC;
                        break;
                    case 2:
                        tetramino_scelto.rotazione = ADD90;
                        break;
                    case 3:
                        tetramino_scelto.rotazione = ADD180;
                        break;
                    default:
                        tetramino_scelto.rotazione = ADD270;
                        break;
                }

                /* Se è la modalità vs PC ed è il suo turno non serve che mostro il tetramino altrimenti si */
                if (mod_gioco == MULTIPLAYER_PC && (i % 2) || mod_gioco == MULTIPLAYER_PL) {
                    printf("\n\n");
                    printf("Tetramino randomico:\n");
                    print_tetramino(tetramino_scelto);
                }
            }

            if (i % 2 && mod_gioco == MULTIPLAYER_PC || mod_gioco == MULTIPLAYER_PL) {
                printf("\n+ - - - - - - - - +\n| SCEGLI  COLONNA |\n+ - - - - - - - - +\n");
                selezione_colonna_mp:
                colonna = ask_colonna();
            } else {
                genera_colonna:
                colonna = (rand()%1000) % 9;
            }

            /* posiziona sul piano di gioco e vedi se si possono eliminare righe */
            res = set_tetraminosupianodigioco_mp((i % 2) ? &p_pl1 : &p_pl2, (i + 1 % 2) ? &p_pl2 : &p_pl1,
                                                 (i % 2) ? &player1 : &player2,
                                                 tetramino_scelto,
                                                 colonna);

            if (res) {
                tetramini_set[id_tetramino - 1].n_disponibili--;
                printf("\n");
                print_pianodigioco((i % 2) ? &p_pl1 : &p_pl2);
                delay(30000);
            } else if (!((i % 2) ? p_pl1 : p_pl2).is_limiteraggiunto) {
                if (i % 2 && mod_gioco == MULTIPLAYER_PC || mod_gioco == MULTIPLAYER_PL) {
                    printf("%sNon è stato possibile piazzare il tetramino dove hai richiesto!!%s\n", ROSSO,
                           DEFAULT);
                    goto selezione_colonna_mp;
                } else goto genera_colonna;
            } else
                exitMode = OUT_OF_MATRIX;
        }

        if (exitMode == OUT_OF_MATRIX) {
            if (!(i % 2)) {
                print_losetitle(player1);
                print_wintitle(player2);
            } else {
                print_losetitle(player2);
                print_wintitle(player1);
            }
        } else {
            if (player1.points > player2.points) {
                print_wintitle(player1);
                print_losetitle(player2);
            } else if (player2.points > player1.points) {
                print_wintitle(player2);
                print_losetitle(player1);
            } else {
                print_finishtitle();
                print_player(player1);
                print_player(player2);
            }
        }

        delay(40000);
        goto menu_iniziale;
    }
}