#include "Tetramino/tetramino.h"

int main() {
    int i, j;
    Tetramino_t t;
    t = create_tetramino3();
    t.rotazione = ADD180;

    print_tetramino(t);
    return 0;
}
