#include "menus.h"
#include "../Elements/color_codes.h"

void print_titologioco()
{
    printf("\n\n");
    printf("%s██╗  ██╗%s      %s████████╗%s███████╗%s████████╗%s██████╗ %s██╗%s███████╗%s\n", ROSSO, DEFAULT, BIANCO, GIALLO, VERDE, AZZURRO, VIOLA, BLU, DEFAULT);
    printf("%s╚██╗██╔╝%s      %s╚══██╔══╝%s██╔════╝%s╚══██╔══╝%s██╔══██╗%s██║%s██╔════╝%s\n", ROSSO, DEFAULT, BIANCO, GIALLO, VERDE, AZZURRO, VIOLA, BLU, DEFAULT);
    printf("%s ╚███╔╝ %s█████╗%s   ██║   %s█████╗  %s   ██║   %s██████╔╝%s██║%s███████╗%s\n", ROSSO, DEFAULT, BIANCO, GIALLO, VERDE, AZZURRO, VIOLA, BLU, DEFAULT);
    printf("%s ██╔██╗ %s╚════╝%s   ██║   %s██╔══╝  %s   ██║   %s██╔══██╗%s██║%s╚════██║%s\n", ROSSO, DEFAULT, BIANCO, GIALLO, VERDE, AZZURRO, VIOLA, BLU, DEFAULT);
    printf("%s██╔╝ ██╗%s      %s   ██║   %s███████╗%s   ██║   %s██║  ██║%s██║%s███████║%s\n", ROSSO, DEFAULT, BIANCO, GIALLO, VERDE, AZZURRO, VIOLA, BLU, DEFAULT);
    printf("%s╚═╝  ╚═╝%s      %s   ╚═╝   %s╚══════╝%s   ╚═╝   %s╚═╝  ╚═╝%s╚═╝%s╚══════╝%s\n", ROSSO, DEFAULT, BIANCO, GIALLO, VERDE, AZZURRO, VIOLA, BLU, DEFAULT);
    printf("Berton Alex Giulio - 884378\n");
    printf("\n\n");
}

void print_menugioco()
{
    printf("Benvenuto nel menù iniziale di X-Tetris! Seleziona una modalità di gioco:\n"
           "   1) SinglePlayer\n"
           "   2) MultiPlayer\n"
           "   3) Esci\n");
}

void print_turnoinfoplayer(Player_t p) {
    printf("\n\n");
    printf("Turno di: ");
    print_player(p);
}

void print_losetitle(Player_t p) {
    printf("\n\n\n\n");
    printf("  _      ____   _____ ______   _ \n"
           " | |    / __ \\ / ____|  ____| | |\n"
           " | |   | |  | | (___ | |__    | |\n"
           " | |   | |  | |\\___ \\|  __|   |_|\n"
           " | |___| |__| |____) | |____  \n"
           " |______\\____/|_____/|______| (_)\n");
    printf("\n");
    print_player(p);
}

void print_wintitle(Player_t p) {
    printf("\n\n\n\n");
    printf(" __          _______ _   _ _   _ ______ _____      _ \n"
           " \\ \\        / /_   _| \\ | | \\ | |  ____|  __ \\    | |\n"
           "  \\ \\  /\\  / /  | | |  \\| |  \\| | |__  | |__) |   | |\n"
           "   \\ \\/  \\/ /   | | | . ` | . ` |  __| |  _  /    |_|\n"
           "    \\  /\\  /   _| |_| |\\  | |\\  | |____| | \\ \\    \n"
           "     \\/  \\/   |_____|_| \\_|_| \\_|______|_|  \\_\\   (_)");
    printf("\n");
    print_player(p);
}

void print_finishtitle() {
    printf("\n\n\n\n");
    printf("  ______   _____   _   _   _____    _____   _    _ \n"
           " |  ____| |_   _| | \\ | | |_   _|  / ____| | |  | |\n"
           " | |__      | |   |  \\| |   | |   | (___   | |__| |\n"
           " |  __|     | |   | . ` |   | |    \\___ \\  |  __  |\n"
           " | |       _| |_  | |\\  |  _| |_   ____) | | |  | |\n"
           " |_|      |_____| |_| \\_| |_____| |_____/  |_|  |_|\n");
    printf("\n");
}