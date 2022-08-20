#ifndef XTETRIS_PIANODIGIOCO_H
#define XTETRIS_PIANODIGIOCO_H

#include "../Elements/boolType.h"
#include "../Tetramino/tetramino.h"
#include "../GameSetting/Player/player.h"

/** Numero di righe della matrice di gioco */
#define ROWS 15
/** Numero di colonne della matrice di gioco */
#define COLS 10

/**
 * Tipo di dato strutturato avente il compito di rappresentare una cella della matrice di gioco. Ciascuna cella deve
 * memorizzare al proprio interno lo stato della cella stessa (ovvero se è piena o vuota) e in caso sia piena che
 * tetramino essa sta contenendo.\n
 * I dati memorizzati al suo interno sono quindi due variabili:\n
 *  - <b><code>is_vuota</code></b>: tipo <code>Bool_t</code>, da me specificato e documentato, per informare sullo stato della cella\n
 *  - <b><code>tetramino_contenuto</code></b>: tipo <code>Tetramino_t</code>, da me specificato e documentato, che memorizza
 *  informazioni relative al tetramino contenuto nella determinata cella.
 */
typedef
struct cella_t {
    Bool_t is_vuota;
    Tetramino_t tetramino_contenuto;
}
Cella_t;

/**
 * Tipo di dato strutturato di fondamentale importanza per l'intero progetto. Esso contiene la <code><b>matrice_di_gioco</b></code>,
 * matrice <code>ROWS x COLS</code> di variabili di tipo <code>Cella_t</code>, e una variabile di tipo <code>Bool_t</code>,
 * <b><code>is_limiteraggiunto</code></b> utile per riconoscere se si è superato il limite superiore della <code>matrice_di_gioco</code>.
 */
typedef
struct pianodigioco_t {
    Cella_t matrice_di_gioco[ROWS][COLS];
    Bool_t is_limiteraggiunto;
}
PianoDiGioco_t;

/**
 * Metodo in grado di creare un nuovo piano di gioco
 * @return piano di gioco con settaggio di partenza per partita singleplayer
 */
PianoDiGioco_t create_pianodigioco();

/**
 * Metodo che stampa il piano di gioco con una tecnica di stampa avanzata.
 * @param p: piano di gioco da stampare
 */
void print_pianodigioco(const PianoDiGioco_t p);

/**
 * Metodo che stampa il piano di gioco con una tecnica di stampa basilare (zeri e uni).
 * @param p: piano di gioco da stampare
 */
void print_pianodigioco_basic(const PianoDiGioco_t p);

/**
 * Metodo avente il compito di posizionare effettivamente un tetramino nel piano di gioco andando a settare il limite
 * raggiunto nel caso in cui si fosse raggiunto l'apice della matrice di gioco.
 * @param p: piano di gioco sul quale applicare la modifica e l'inserimento del tetramino
 * @param player: giocatore corrente al quale assegnare punti per eventuali eliminazioni di riga
 * @param t: tetramino da posizionare
 * @param col: colonna in cui calare il tetramino
 * @return <code>true</code> se e solo se il tetramino è stato posizionato correttamente, <code>false</code> altrimenti
 */
Bool_t set_tetraminosupianodigioco(PianoDiGioco_t* p, Player_t* player, Tetramino_t t, int col);

#endif
