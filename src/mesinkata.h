#ifndef __MESINKATA_H__
#define __MESINKATA_H__

#include "boolean.h"
#include "mesinkar.h"
#include <stdio.h>

#define NMax 50
#define BLANK ' '

typedef struct {
	char TabKata[NMax]; /* container penyimpan kata, indeks yang dipakai [0..NMax-1] */
   int Length;
} Kata;

/* State Mesin Kata */
extern boolean EndKata;
extern Kata CKata;

void IgnoreBlank();
/* Mengabaikan satu atau beberapa BLANK
   I.S. : CC sembarang 
   F.S. : CC ≠ BLANK atau CC = MARK */

void STARTKATA();
/* I.S. : CC sembarang 
   F.S. : EndKata = true, dan CC = MARK; 
          atau EndKata = false, CKata adalah kata yang sudah diakuisisi,
          CC karakter pertama sesudah karakter terakhir kata */

void ADVKATA();
/* I.S. : CC adalah karakter pertama kata yang akan diakuisisi 
   F.S. : CKata adalah kata terakhir yang sudah diakuisisi, 
          CC adalah karakter pertama dari kata berikutnya, mungkin MARK
          Jika CC = MARK, EndKata = true.		  
   Proses : Akuisisi kata menggunakan procedure SalinKata */

void SalinKata();
/* Mengakuisisi kata, menyimpan dalam CKata
   I.S. : CC adalah karakter pertama dari kata
   F.S. : CKata berisi kata yang sudah diakuisisi; 
          CC = BLANK atau CC = MARK; 
          CC adalah karakter sesudah karakter terakhir yang diakuisisi.
          Jika panjang kata melebihi NMax, maka sisa kata "dipotong" */

Kata CreateKata(char *String);

boolean IsKataSama(Kata Kata1, Kata Kata2);
/* Menghasilkan trua jika Kata1 sama dengan Kata2, panjangnya sama dan semua hurufnya sama */

boolean Command(char* CommandAsString, Kata Command);
boolean IsCommand(char* Commands[], Kata com, int CommandsLen);

void Input(Kata *InputKata); //jangan dipake nanti diapus

void PrintKata(Kata print);
/* Menampilkan print kata anjing */
/* For testing purposes */

void ReadInput(Kata *InputKata);
/* membaca input user */

void ReadInputInteger(int *out);
/* membaca input user dan mengubah ke integer */

void ReadCommand(int *out, Kata *InputKata);
/* membaca input dengan format int yang diikuti kata */

void ReadServe(Kata *InputKata1, Kata *InputKata2);
/* membaca input user dengan format kata diikuti dengan kata */ // untuk serve

#endif
