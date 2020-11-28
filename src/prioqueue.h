#ifndef prioqueuechar_H
#define prioqueuechar_H

#include "boolean.h"
#include "wahana.h"
#include "jam.h"
#include <stdlib.h>
#include <stdio.h>
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
    Pengunjung Cust;
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

/* Selektor pengunjung */
#define Prio(e)     (e).prio
#define Kesabaran(e) (e).kesabaran
#define ListWP(e) (e).listWahana

/* Selektor listWahana */
#define ElmtWahana(L,i) (L).W[(i)]
#define ListW(L) (L).W

/* Selektor Queue */
#define Head(Q)     (Q).HEAD
#define Tail(Q)     (Q).TAIL
#define MaxElPrioQueue(Q)    (Q).MaxElPrioQueue

/* Selektor Queue Pengunjung */
#define InfoHead(Q) (Q).T[(Q).HEAD]
#define InfoTail(Q) (Q).T[(Q).TAIL]
#define ElmtQ(Q,i)   (Q).T[(i)]

/* Selektor Queue Wahana */
#define InfoHeadW(W) (W).P[(W).HEAD]
#define InfoTailW(W) (W).P[(W).TAIL]
#define ElmtW(W, i) (W).P[(i)] 

/* Selektor Penumpang */
#define JAMOut(P)   (P).out
#define Dur(P) (P).durasi 
#define Pengunjung(P) (P).Cust 
#define CurrWahana(P) (P).idWahana

void CreateEmptyPrioQueue(PrioQueue *Antrian, int Max);
/* Prosedur membuat antrian kosong dengan MaxElPrioQueue sebagai panjang antrian maksimal definisi antrian kosong Head(Q) = Tail(Q) = Nil dengan queue circular buffer */

void CreateEmptyPrioQueueWahana(PrioQueueWahana *QWahana, int MaxCap);
/* Prosedur membuat isi wahana */

void CreatePenumpang(Penumpang *P, JAM out, int idWahana, Pengunjung X, int durasi);
/* Prosedur membuat penumpang */

void CreateEmptyListWahana(ListWahana *W, int nWahana);
/* Prosedur membuat list wahana kosong */

boolean IsEmptyPrioQueue (PrioQueue Antrian);
/* Fungsi ini mengecek apakah suatu antrian kosong atau tidak */

boolean IsEmptyPrioQueueW (PrioQueueWahana QWahana);
/* Versi prioqueue wahana */

boolean IsEmptyWahana(ListWahana LWahana, int nWahana);
/* Mengirimkan true apabila listwahana kosong */

boolean IsFullPrioQueue (PrioQueue Antrian);
/* Mengirimkan true apabila antrian penuh */

int NBElmtPrioQueue (PrioQueue Antrian);
/* Mengirimkan jumlah pengunjung dalam antrian */

int NBElmtWahana(ListWahana W, int nWahana);
/* Mengirimkan jumlah wahana yang ingin dinaiki seorang pengunjung */

int NBElmtPrioQueueW (PrioQueueWahana QWahana);
/* Mengirimkan jumlah isi wahana */

void DeAlokasi(PrioQueue * Antrian);
/* Dealokasi antrian */

void DeAlokasiQWahana(PrioQueueWahana *QWahana);
/* Dealokasi isi wahana */

void DelWahana(ListWahana *W, int idxWahana, int nWahana);
/* Menghapus wahana pada list wahana */

void Enqueue (PrioQueue * Antrian, Pengunjung X);
/* Prosedur menambahkan pengunjung ke antrian */

void EnqueueWahana (PrioQueueWahana * QWahana, Pengunjung X, int idWahana, int durasiWahana, JAM CurrTime);
/* Prosesdur menambahkan penunpang ke isi wahana */

void Dequeue (PrioQueue * Antrian, Pengunjung *X);
/* Prosedur mengeluarkan pengunjung dari antrian */

boolean adaWahana(ListWahana LW, int idxWahana, int nWahana);
/* Mengirimkan true apabila ada wahana dengan idxWahana pada sebuah list wahana */

boolean PengunjungWahana(Pengunjung X, int idxWahana, int nWahana);
/* Mengirimkan true apabila pengunjung X memiliki idxWahana pada list wahana yang dimilikinya */

void DequeueAntrian(PrioQueue * Antrian, Pengunjung * X, int idxWahana, int nWahana);
/* Dequeue dengan mengecek apakah pengunjung ingin menaiki wahana terkait */

void DequeueWahana(PrioQueueWahana *QWahana, Pengunjung *X, JAM CurrTime, int nWahana);
/* Dequeue pengunjung dari isi wahana */

void DequeueWahana2 (PrioQueueWahana *QWahana, Pengunjung *X, JAM CurrTime,PrioQueue *Antrian, int nWahana, boolean *b);
/* Dequeue pengunjung dari isi wahana dan langsung enqueue */

void DecrKesabaran(PrioQueue *Antrian);
/* Prosedur decrement kesabaran dari pengunjung dalam antrian */

void KesabaranHabis(PrioQueue *Antrian);
/* Prosedur mengeluarkan pengunjung yang kesabarannya habis dari antrian */

void setPrio(Pengunjung *X, int prio);
/* Set prio ketika pengunjung ingin balik ke antrian */

void RandomEnqueue(PrioQueue *Antrian, int nWahana);
/* Prosedur menambahkan pengunjung ke antrian secara acak */

void PrintPrioQueue(PrioQueue Antrian, int nWahana);
/* Prosedur menampilkan list wahana yang ingin dinaiki pengunjung serta kesabarannya */

#endif
