#include "player.h"

void save_player(string_t nome)
{

}

Player_t get_nuovoplayer(string_t nome)
{
    Player_t new_player;
    new_player.nome = (string_t) malloc(sizeof(char) * 20);
    strcpy(new_player.nome, nome);
    new_player.max_points = 0;
    return new_player;
}