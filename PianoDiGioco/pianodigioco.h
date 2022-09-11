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
void print_pianodigioco(const PianoDiGioco_t);

/**
 * Metodo che stampa il piano di gioco con una tecnica di stampa basilare (zeri e uni).
 * @param p: piano di gioco da stampare
 */
void print_pianodigioco_basic(const PianoDiGioco_t);

/**
 * Metodo avente il compito di posizionare il tetramino scelto dall'utente sul piano di gioco in base alla colonna da
 * lui scelta in modalità SinglePlayer. Viene poi anche verificato il numero di righe che sono state rimosse con
 * l'aggiunta del tetramino e in base ad esse viene attribuito un punteggio all'utente passato come parametro
 * del metodo.\n
 * @param p il piano di gioco contenente la matrice di gioco su cui posizionare il tetramino
 * @param player il giocatore che ha effettuato la mossa in analisi
 * @param t il tetramino da posizionare
 * @param col la colonna di partenza della matrice di gioco (sulla quale basarsi per il posizionamento)
 * @param righe_eliminate puntatore per poter memorizzare al suo interno il numero di righe che sono state eliminate con una singola mossa
 * @return <code>TRUE</code> - se il tetramino è stato correttamente posizionato\n
 *         <code>FALSE</code> - in caso di qualsiasi errore (tetramino non posizionabile nella colonna scelta)
 */
Bool_t set_tetraminosupianodigioco_sp(PianoDiGioco_t* p, Player_t* player, Tetramino_t t, int col, int* righe_eliminate);

/**
 * Metodo avente il compito di posizionare il tetramino scelto dall'utente sul piano di gioco in base alla colonna da
 * lui scelta in modalità Multiplayer. Viene poi anche verificato il numero di righe che sono state rimosse con
 * l'aggiunta del tetramino e in base ad esse viene attribuito un punteggio all'utente passato come parametro
 * del metodo e in aggiunta, se il numero di righe eliminate è 3 o 4, verranno invertite le corrispettive righe nella parte
 * inferiore del piano di gioco dell'avversario.\n
 * @param p il piano di gioco contenente la matrice di gioco su cui posizionare il tetramino
 * @param other il piano di gioco dell'avversario
 * @param player il giocatore che ha effettuato la mossa in analisi
 * @param t il tetramino da posizionare
 * @param col la colonna di partenza della matrice di gioco (sulla quale basarsi per il posizionamento)
 * @return
 */
Bool_t set_tetraminosupianodigioco_mp(PianoDiGioco_t* p, PianoDiGioco_t* other, Player_t* player, Tetramino_t t, int col);

#endif
