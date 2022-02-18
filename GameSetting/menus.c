#include "menus.h"

void print_titologioco() {
    printf("\n\n");
    printf("██╗  ██╗      ████████╗███████╗████████╗██████╗ ██╗███████╗\n");
    printf("╚██╗██╔╝      ╚══██╔══╝██╔════╝╚══██╔══╝██╔══██╗██║██╔════╝\n");
    printf(" ╚███╔╝ █████╗   ██║   █████╗     ██║   ██████╔╝██║███████╗\n");
    printf(" ██╔██╗ ╚════╝   ██║   ██╔══╝     ██║   ██╔══██╗██║╚════██║\n");
    printf("██╔╝ ██╗         ██║   ███████╗   ██║   ██║  ██║██║███████║\n");
    printf("╚═╝  ╚═╝         ╚═╝   ╚══════╝   ╚═╝   ╚═╝  ╚═╝╚═╝╚══════╝\n");
    printf("Berton Alex Giulio - 884378\n");
    printf("\n\n");
}


Scelta_t menu_gioco() {
    int scelta = 0;
    printf("Benvenuto! Cosa vuoi fare?\n   1) Gioca da solo\n   2) Gioca con un amico\n   3) Settings\n");

    scanf("%d", &scelta);
    while(!(scelta >= 1 && scelta <= 3))
        scanf("%d", &scelta);

    switch (scelta) {
        case 1:
            return SINGLEPLAYER;
        case 2:
            return MULTIPLAYER;
        default:
            return SETTINGS;
    }
}

/**
 * Metodo per stampare con tecnica particolare il titolo "Settings"
 */
void __print_settingstitle() {
    printf("\n"
           "  ___      _   _   _              \n"
           " / __| ___| |_| |_(_)_ _  __ _ ___\n"
           " \\__ \\/ -_)  _|  _| | ' \\/ _` (_-<\n"
           " |___/\\___|\\__|\\__|_|_||_\\__, /__/\n"
           "                         |___/    ");
    printf("\n");
}

void __add_username() {
    string_t new_nome = "\0";
    printf("\nADD PLAYER\n");
    printf("Scegli il nome del nuovo giocatore:\n");
    scanf("%s", new_nome);
    new_nome += '\0';

    printf("## %s\n", new_nome);
}

void print_settingsmenu() {
    int operazione_scelta = -1;
    __print_settingstitle();
    printf("Scegli che tipo di operazione vuoi eseguire:\n"
           "1) Inserisci utente nel sistema\n");
    printf("> ");

    scanf("%d", &operazione_scelta);

    switch (operazione_scelta) {
        case 1:
            __add_username();
            break;
        default:
            break;
    }
}