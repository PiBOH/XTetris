#ifndef XTETRIS_EXIT_MODES_H
#define XTETRIS_EXIT_MODES_H

/**
 * Tipo di dato enumerativo che identifica la modalità con cui una partita a <b>X-Tetris</b> è terminata.
 */
typedef
enum ExitMode
{
    NO_PIECES = 0,
    OUT_OF_MATRIX,
    NONE
}
ExitMode_t;
#endif
