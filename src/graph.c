/* *** Definisi ABSTRACT DATA TYPE GRAPH *** */

#ifndef GRAPH_H
#define GRAPH_H

#include "boolean.h"
#include "matriks.h"

typedef char ElType;
typedef struct Node* Address;
typedef struct {
                MATRIKS Map;
                Address Prev;
                Address Next; 
                } Node;
typedef struct Address List;

/* *** Notasi Akses: Selektor GRAPH *** */

#define Prev(P) (P).Prev
#define Next(P) (P).Next
#define Nil -1

/* *** DEFINISI PROTOTIPE PRIMITIF *** */

/* *** KONSTRUKTOR *** */

Node CreateEmpty(Node * PMap){
/* Membentuk node baru,  */
    MATRIKS M;
    MakeMATRIKS(7, 7, &M);
    PMap->Map = M;
    PMap->Prev = Nil;
    PMap->Next = Nil;
}

#endif