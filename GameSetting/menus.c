#include <stdlib.h>
#include "menus.h"

void print_titologioco()
{
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

void print_menuiniziale()
{
    printf("Benvenuto! Cosa vuoi fare?\n   1) SinglePlayer\n   2) MultiPlayer\n");
}


Scelta_t menu_gioco()
{
    int scelta = 0;
    print_menuiniziale();

    scanf("%d", &scelta);
    while(!(scelta >= 1 && scelta <= 3))
        scanf("%d", &scelta);

    if (scelta) return SINGLEPLAYER;
    else return MULTIPLAYER;
}

void __add_username()
{
    string_t new_nome = "\0";
    printf("\nADD PLAYER\n");
    printf("Scegli il nome del nuovo giocatore:\n");
    scanf("%s", new_nome);
    new_nome += '\0';

    printf("## %s\n", new_nome);
}