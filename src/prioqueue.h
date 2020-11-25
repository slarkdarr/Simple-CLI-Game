#ifndef prioqueuechar_H
#define prioqueuechar_H

#include "boolean.h"
#include <stdlib.h>
#include <stdio.h>
#include "wahana.h"
#include <time.h>
#define Nil -1

typedef int idWahana; 
typedef int address;

typedef struct {
    idWahana *W;
} ListWahana;
/* Panjang list wahana sebanyak jumlah wahana */
/* Wahana di indeks ke i yang ingin dinaiki diberi diisi integer 1 */
/* Contoh = [-1,1,1,-1] artinya pengunjung ingin menaiki wahana indeks 1 dan 2 */

typedef struct {
    int prio;
    int kesabaran;
    ListWahana listWahana;
} Pengunjung;

typedef struct {
    Pengunjung *T;
    address HEAD;
    address TAIL;
    int MaxElPrioQueue;
} PrioQueue;

typedef struct{
    Pengunjung T;
    JAM out; // waktu dia keluar
    int idWahana; // id wahana yang dinaiki
    int durasi; // durasi wahana
} Penumpang;

typedef struct{
    Penumpang *P;
    address HEAD;
    address TAIL;
    int MaxElPrioQueue;
} PrioQueueWahana;

#define Prio(e)     (e).prio
#define Kesabaran(e) (e).kesabaran
#define ListWahana(e) (e).listWahana
#define ElmtWahana(l,i) (L).W[(i)]
#define Info(e)     (e).W
#define Head(Q)     (Q).HEAD
#define Tail(Q)     (Q).TAIL
#define InfoHead(Q) (Q).T[(Q).HEAD]
#define InfoHeadW(W) (W).P[(W).HEAD]
#define InfoTail(Q) (Q).T[(Q).TAIL]
#define InfoTailW(W) (W).P[(W).TAIL]
#define MaxElPrioQueue(Q)    (Q).MaxElPrioQueue
#define ElmtQ(Q,i)   (Q).T[(i)]
#define ElmtW(W, i) (W).P[(i)] 
#define JAMOut(P)   (P).out
#define Dur(P) (P).durasi 
#define Pengunjung(P) (P).T 
#define CurrWahana(P) (P).idWahana 

void CreateEmptyPrioQueue(PrioQueue *Q, int MaxElPrioQueue);
/* Prosedur membuat antrian kosong dengan MaxElPrioQueue sebagai panjang antrian maksimal definisi antrian kosong Head(Q) = Tail(Q) = Nil dengan queue circular buffer */

void CreateEmptyPrioQueueWahana(PrioQueueWahana *Wahana);

void CreateEmptyPenumpang(Penumpang *P);

void CreateEmptyListWahana(ListWahana *W);

boolean IsEmptyPrioQueue (PrioQueue Antrian);
/* Fungsi ini mengecek apakah suatu antrian kosong atau tidak */

boolean IsEmptyPrioQueueW (PrioQueueWahana Antrian);
/* Versi prioqueue wahana */

boolean IsFullPrioQueue (PrioQueue Antrian);
/* Fungsi ini mengecek apakah suatu antrian penuh atau tidak, definisi antrian penuh adalah Head(Antrian) dan Tail(Antrian) bersebelahan */

int NBElmtPrioQueue (PrioQueue Antrian);
/* Fungsi ini mengembalikan jumlah orang dalam antrian */

int NBElmtWahana(ListWahana SW);
/* Fungsi ini mengembalikan jumlah wahana yang ingin dinaiki pengunjung */

int NBElmtPrioQueueW (PrioQueueWahana Antrian);
/* Versi prioqueue isi wahana */

void DeAlokasi(PrioQueue * Antrian);
/* Prosedur untuk dealokasi dan pengosongan antrian */

void DeAlokasiQWahana(PrioQueueWahana *Wahana);

void DelWahana(ListWahana *Wahana, int idxWahana);

void Enqueue (PrioQueue * Antrian, Pengunjung X);
/* Prosedur menambahkan pengunjung ke antrian */

void EnqueueWahana (PrioQueueWahana * Wahana, Pengunjung X, int idWahana);
/* Prosesdur menambahkan penunpang ke isi wahana */

void Dequeue (PrioQueue * Antrian, Pengunjung *X);
/* Prosedur mengeluarkan pengunjung dari antrian */

boolean adaWahana(ListWahana LW, int idxWahana);

void DequeueAntrian(PrioQueue * Antrian, Pengunjung * X, int idxWahana);
/* Dequeue dengan mengecek apakah pengunjung ingin menaiki wahana terkait */

void DequeueWahana(PrioQueueWahana *Wahana, Pengunjung *X);
/* Dequeue pengunjung dari isi wahana */

// void DequeueVersi2 (PrioQueue * Q, Pengunjung * X, int *Minute, int *money, int idxWahana);
/* Prosedur mengeluarkan pengunjung dari antrian dan mencatat durasi dan uang yang dibutuhkan serta idWahana */

void DecrKesabaran(PrioQueue *Antrian);
/* Prosedur decrement kesabaran dari pengunjung dalam antrian */

void KesabaranHabis(PrioQueue *Antrian);
/* Prosedur mengeluarkan pengunjung yang kesabarannya habis dari antrian */

void PrintPrioQueue(PrioQueue Antrian);
/* Prosedur menampilkan list wahana yang ingin dinaiki pengunjung serta kesabarannya */

void RandomEnqueue(PrioQueue *Q);
/* Prosedur menambahkan pengunjung ke antrian secara acak */

void setPrio(Pengunjung *X, int prio);
/* Set prio ketika pengunjung ingin balik ke antrian */

// WAHANA_ElType indeksToWahana(int index);

// int wahanaToIndex(WAHANA_ElType Wahana);

boolean IsEmptyWahana(ListWahana LW);
/* Fungsi mengecek apakah wahana yang ingin dinaiki pengunjung kosong  */

#endif
