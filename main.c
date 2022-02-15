#include "PianoDiGioco/pianodigioco.h"



int main() {
    PianoDiGioco_t pianoDiGioco;

    pianoDiGioco = create_pianodigioco_sp();

    print_pianodigioco(pianoDiGioco);
    return 0;
}
