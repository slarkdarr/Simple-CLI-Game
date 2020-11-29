/* MODUL TABEL INTEGER DENGAN ELEMEN POSITIF */
/* Berisi definisi dan semua primitif pemrosesan tabel integer dengan elemen positif */
/* Penempatan elemen selalu rapat kiri */
/* Banyaknya elemen didefinisikan secara implisit, memori tabel statik */

#include <stdio.h>
#include "arrayaction.h"
#include "../boolean.h"
#include "../mesinkata/mesinkata.h"
#include "../jam/jam.h"

ArrayAction_ElType AlokasiElementAction(Kata action, int durasi)
// Mengalokasikan elemen array action
{
    ArrayAction_ElType E;
    Action(E) = action;
    Duration(E) = durasi;
    return E;
}
void TulisIsiTab (ArrayAction_TabInt T)
/* Proses : Menuliskan isi tabel dengan traversal, tabel ditulis di antara kurung siku; 
   antara dua elemen dipisahkan dengan separator "koma", tanpa tambahan karakter di depan,
   di tengah, atau di belakang, termasuk spasi dan enter */
/* I.S. T boleh kosong */
/* F.S. Jika T tidak kosong: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika tabel kosong : menulis [] */
{
    for (int i=ArrayAction_IdxMin; i<9; i++)
    {
        PrintKata(Action(ArrayAction_Elmt(T, i)));
        printf(" %d detik\n",Duration(ArrayAction_Elmt(T, i)));
    }
}

int GetDuration(ArrayAction_TabInt T, Kata action)
// Kata action pasti ada dalam tabel, karena telah di cek sebelumnya
{
    int i = ArrayAction_IdxMin;
    while (!IsKataSama(Action(ArrayAction_Elmt(T, i)), action))
    {
        i++;
    }

    return Duration(ArrayAction_Elmt(T, i));
}

void ActionAddTime(ArrayAction_TabInt T, Kata action, JAM *time)
// Menambah waktu berdasarkan action dalam array of action
{
    *time = NextNDetik(*time, GetDuration(T, action));
    return;
}

void InitializeArrayAction(ArrayAction_TabInt *Tab)
// Menginisialisasi array action yang akan digunakan untuk data waktu yang akan dikonsumsi
{
    ArrayAction_Elmt(*Tab, 0) = AlokasiElementAction(CreateKata("w"), 60);          // Aksi movement 1 menit
    ArrayAction_Elmt(*Tab, 1) = AlokasiElementAction(CreateKata("a"), 60);          // Aksi movement 1 menit
    ArrayAction_Elmt(*Tab, 2) = AlokasiElementAction(CreateKata("s"), 60);          // Aksi movement 1 menit
    ArrayAction_Elmt(*Tab, 3) = AlokasiElementAction(CreateKata("d"), 60);          // Aksi movement 1 menit
    ArrayAction_Elmt(*Tab, 4) = AlokasiElementAction(CreateKata("build"), 10800);   // Aksi build 3 jam
    ArrayAction_Elmt(*Tab, 5) = AlokasiElementAction(CreateKata("upgrade"), 5400);  // Aksi upgrade 1.5 jam
    ArrayAction_Elmt(*Tab, 6) = AlokasiElementAction(CreateKata("buy"), 3600);      // aksi 1 jam
    ArrayAction_Elmt(*Tab, 7) = AlokasiElementAction(CreateKata("serve"), 600);     // Aksi serve 10 menit
    ArrayAction_Elmt(*Tab, 8) = AlokasiElementAction(CreateKata("repair"), 3600);   // Aksi repair 1 jam
    ArrayAction_Elmt(*Tab, 9) = AlokasiElementAction(CreateKata("extend"), 3600);   // Aksi extend 1 jam
}