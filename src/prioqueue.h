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

/* ---------- DEFINISI ADT ---------- */

typedef struct {
    idWahana *W;
} ListWahana;
/* Panjang list wahana sebanyak jumlah wahana */
/* Wahana di indeks ke i yang ingin dinaiki diberi diisi integer 1 */
/* Contoh = [-1,1,1,-1] artinya pengunjung ingin menaiki wahana indeks 1 dan 2 */

/* Struktur Data Pengunjung */
/* prio = prioritas masuk ke antrian */
/* kesabaran = derajat kesabaran pengunjung */
/* listWahana = daftar wahana yang ingin dinaiki pengunjung */
typedef struct {
    int prio;
    int kesabaran;
    ListWahana listWahana;
} Pengunjung;

/* PrioQueue dari antrian dengan elemen berupa ADT Pengunjung */
typedef struct {
    Pengunjung *T;
    address HEAD;
    address TAIL;
    int MaxElPrioQueue;
} PrioQueue;

/* Struktur Data Penumpang */
/* out = waktu saat penumpang keluar dari wahana, memanfaatkan ADT JAM */
/* idWahana = menyatakan idWahana yang saat ini sedang dinaiki */
/* durasi = menyatakan durasi yang saat ini sedang dinaiki */
typedef struct{
    Pengunjung Cust;
    JAM out; // waktu penumpang keluar
    int idWahana; // id wahana yang dinaiki
    int durasi; // durasi wahana
} Penumpang;

/* PrioQueue dari isi wahana */
typedef struct{
    Penumpang *P;
    address HEAD;
    address TAIL;
    int MaxElPrioQueue;
} PrioQueueWahana;

/* ---------- SELEKTOR ---------- */
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

/* KONSTRUKTOR */
void CreateEmptyPrioQueue(PrioQueue *Antrian, int Max);
/* Prosedur membuat antrian kosong dengan MaxElPrioQueue sebagai panjang maksimal antrian. */
/* Definisi antrian kosong Head(Q) = Tail(Q) = Nil dengan metode circular buffer */

void CreateEmptyPrioQueueWahana(PrioQueueWahana *QWahana, int MaxCap);
/* Prosedur membuat isi wahana kosong dengan MaxElPrioQueue sebagai panjang maksimal antrian. */
/* Definisi antrian kosong Head(Q) = Tail(Q) = Nil dengan metode circular buffer */

void CreatePenumpang(Penumpang *P, JAM out, int idWahana, Pengunjung X, int durasi);
/* Prosedur membuat penumpang dengan parameter dari penyusun ADT Penumpang*/
/* Tipe bentukan pemumpang tediri dari JAM out, idWahana, pengunjung X dan durasi menaiki wahana */

void CreateEmptyListWahana(ListWahana *W, int nWahana);
/* Prosedur membuat list wahana kosong, definisi list kosong seluruh anggota elemennya adalah -1*/
/* Implementasi list wahana dalam bentuk truth table */
/* [-1,-1,1,1] artinya pengunjung ingin menaiki wahana dengan id 2 dan 3 */

/* ---------- PROSEDUR DAN FUNGSI ---------- */

boolean IsEmptyPrioQueue (PrioQueue Antrian);
/* Mengembalikan true apabila antrian kosong */

boolean IsEmptyPrioQueueW (PrioQueueWahana QWahana);
/* Mengembalikan true apabila isi wahana kosong */

boolean IsEmptyWahana(ListWahana LWahana, int nWahana);
/* Mengirimkan true apabila list wahana kosong */

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
/* Menghapus wahana dengan pada indeks idxWahana pada list wahana, dilakukan dengan mengubah elemen pada array list wahana menjadi -1 */

void Enqueue (PrioQueue * Antrian, Pengunjung X);
/* Prosedur menambahkan pengunjung ke antrian */

void EnqueueWahana (PrioQueueWahana * QWahana, Pengunjung X, int idWahana, int durasiWahana, JAM CurrTime);
/* Prosesdur menambahkan penunpang ke isi wahana */

void EnqueuePenumpang(PrioQueueWahana * QWahana, Penumpang X);
/* Prosedur menambahkan penumpang ke isi wahana dengan parameter penumpang */

void Dequeue (PrioQueue * Antrian, Pengunjung *X);
/* Prosedur mengeluarkan pengunjung dari antrian */

boolean adaWahana(ListWahana LW, int idxWahana, int nWahana);
/* Mengirimkan true apabila ada wahana dengan idxWahana pada sebuah list wahana */

boolean PengunjungWahana(Pengunjung X, int idxWahana, int nWahana);
/* Mengirimkan true apabila pengunjung X memiliki idxWahana pada list wahana yang dimilikinya, atau apabila pengunjung X ingin menaiki wahana pada idxWahana */

void DequeueAntrian(PrioQueue * Antrian, Pengunjung * X, int idxWahana, int nWahana);
/* Dequeue dengan mengecek apakah pengunjung ingin menaiki wahana terkait */

void DequeueWahana(PrioQueueWahana *QWahana, Penumpang *X);
/* Dequeue pengunjung dari isi wahana */

void WahanaToAntrian(PrioQueueWahana *QWahana, Penumpang *X, JAM CurrTime,PrioQueue *Antrian, int nWahana, boolean *b);
/* Dequeue pengunjung dari isi wahana dan langsung enqueue ke antrian */

void DecrKesabaran(PrioQueue *Antrian);
/* Prosedur decrement kesabaran dari pengunjung dalam antrian */

void KesabaranHabis(PrioQueue *Antrian);
/* Prosedur mengeluarkan pengunjung yang kesabarannya habis dari antrian */

void setPrio(Pengunjung *X, int prio);
/* Prosedur mengisi prio ketika pengunjung ingin balik ke antrian */

void RandomEnqueue(PrioQueue *Antrian, int nWahana);
/* Prosedur menambahkan pengunjung ke antrian secara acak */

void PrintPrioQueue(PrioQueue Antrian, int nWahana);
/* Prosedur menampilkan list wahana yang ingin dinaiki pengunjung beserta dengan kesabarannya */

#endif