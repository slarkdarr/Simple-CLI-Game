#ifndef prioqueuechar_H
#define prioqueuechar_H

#include "boolean.h"
#include <stdlib.h>
#include <stdio.h>
//#include "wahana.h"
#include <time.h>
#define Nil -1
// List wahana yang ingin dinaiki pengunjung

typedef struct 
{
    int W[5];
} ListWahana;

// ElemenAntrianueue
// Prio dibutuhkan misal setelah pengunjung naik suatu wahana dan masuk keAntrianueue lagi
typedef struct {
    int prio;
    int kesabaran;
    ListWahana listWahana;
} Pengunjung;

typedef int address;

// PrioQueue
typedef struct {
    Pengunjung *T;
    address HEAD;
    address TAIL;
    int MaxElPrioQueue;
} PrioQueue;

#define Prio(e)     (e).prio
#define Kesabaran(e) (e).kesabaran
#define Info(e)     (e).W
#define Head(Q)     (Q).HEAD
#define Tail(Q)     (Q).TAIL
#define InfoHead(Q) (Q).T[(Q).HEAD]
#define InfoTail(Q) (Q).T[(Q).TAIL]
#define MaxElPrioQueue(Q)    (Q).MaxElPrioQueue
#define Elmt(Q,i)   (Q).T[(i)]

int NBElmt(ListWahana W);

void CreateEmptyPrioQueue(PrioQueue *Q, int MaxElPrioQueue);

boolean IsEmptyPrioQueue (PrioQueue Antrian);

boolean IsFull (PrioQueue Antrian);

int NBElmtPrioQueue (PrioQueue Antrian);

int NBElmtWahana(ListWahana SW);

void DeAlokasi(PrioQueue * Antrian); // buat prepare

void Enqueue (PrioQueue * Antrian, Pengunjung X);

void Dequeue (PrioQueue * Antrian, Pengunjung *X);

void DecrKesabaran(PrioQueue *Antrian);

void KesabaranHabis(PrioQueue *Antrian);

void PrintPrioQueue(PrioQueue Antrian);

void RandomEnqueue(PrioQueue *Q);

// WAHANA_ElType indeksToWahana(int index);

// int wahanaToIndex(WAHANA_ElType Wahana);

#endif