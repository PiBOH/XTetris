#ifndef XTETRIS_ROTAZIONI_H
#define XTETRIS_ROTAZIONI_H

/**
 * Tipo di dati enumerativo avente il compito di rappresentare le 4 possibili rotazioni di un tetramino: <code>BASIC, ADD90,
 * ADD180</code> e <code>ADD270</code>.
 */
typedef
enum rotazione_t {
    BASIC = 0,
    ADD90,
    ADD180,
    ADD270
}
Rotazione_t;

#endif
