#include "player.h"

Player_t create_newplayer(const string_t nome)
{
    Player_t new_player;
    new_player.nome = (string_t) malloc(sizeof(char) * 20);
    strcpy(new_player.nome, nome);
    new_player.points = 0;
    return new_player;
}

void print_player(const Player_t p) {
    printf("[%s - %d punti]\n", p.nome, p.points);
}