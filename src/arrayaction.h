/* MODUL TABEL INTEGER DENGAN ELEMEN POSITIF */
/* Berisi definisi dan semua primitif pemrosesan tabel integer dengan elemen positif */
/* Penempatan elemen selalu rapat kiri */
/* Banyaknya elemen didefinisikan secara implisit, memori tabel statik */

#ifndef ARRAYACTION_H
#define ARRAYACTION_H

#include "boolean.h"
#include "mesinkata.h"
#include "jam.h"

/*  Kamus Umum */
#define ArrayAction_IdxMax 10
/* Indeks maksimum array */
#define ArrayAction_IdxMin 0
/* Indeks minimum array */

/* Definisi elemen dan koleksi objek */
typedef struct {
    Kata Action;
    int Duration;
} ArrayAction_ElType;   /* type elemen tabel */

typedef struct { 
  ArrayAction_ElType TI[ArrayAction_IdxMax+1]; /* memori tempat penyimpan elemen (container) */
} ArrayAction_TabInt;
/* Indeks yang digunakan [IdxMin..IdxMax] */
/* Indeks ke-0 tidak digunakan */
/* Jika T adalah TabInt, cara deklarasi dan akses: */
/* Deklarasi : T : TabInt */
/* Maka cara akses: 
   T[i] untuk mengakses elemen ke-i */
/* Definisi : 
   Tabel kosong: semua elemen bernilai ValUndef
   Definisi elemen pertama : T[i] dengan i=1 */
  
/* ********** SELEKTOR ********** */
#define Action(E) (E).Action
#define Duration(E) (E).Duration
#define ArrayAction_Elmt(T,i) (T).TI[(i)]

ArrayAction_ElType AlokasiElementAction(Kata action, int durasi);
void TulisIsiTab (ArrayAction_TabInt T);
/* Proses : Menuliskan isi tabel dengan traversal, tabel ditulis di antara kurung siku; 
   antara dua elemen dipisahkan dengan separator "koma", tanpa tambahan karakter di depan,
   di tengah, atau di belakang, termasuk spasi dan enter */
/* I.S. T boleh kosong */
/* F.S. Jika T tidak kosong: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika tabel kosong : menulis [] */

/* ********** SEARCHING ********** */
int GetDuration(ArrayAction_TabInt T, Kata action);

// /* ********** MENAMBAH DAN MENGHAPUS ELEMEN DI AKHIR ********** */
// /* *** Menambahkan elemen terakhir *** */
// void AddAsLastEl (ArrayAction_TabInt * T, ArrayAction_ElType X);
// /* Proses: Menambahkan X sebagai elemen terakhir tabel */
// /* I.S. Tabel T boleh kosong, tetapi tidak penuh */
// /* F.S. X adalah elemen terakhir T yang baru */

// /* ********** MENGHAPUS ELEMEN ********** */
// void DelLastEl (ArrayAction_TabInt * T, ArrayAction_ElType * X);
// /* Proses : Menghapus elemen terakhir tabel */
// /* I.S. Tabel tidak kosong */
// /* F.S. X adalah nilai elemen terakhir T sebelum penghapusan, */
// /*      Banyaknya elemen tabel berkurang satu */
// /*      Tabel T mungkin menjadi kosong */

void ActionAddTime(ArrayAction_TabInt T, Kata action, JAM *time);

void InitializeArrayAction(ArrayAction_TabInt *Tab);


#endif