#include "graph.h"

/* *** KONSTRUKTOR *** */

Node CreateEmpty(Node * PMap){
/* Membentuk node baru,  */
    MAP M;
    MakeEmptyMAP(&M);
    PMap->Map = M;
    PMap->Prev = Nil;
    PMap->Next = Nil;
}

