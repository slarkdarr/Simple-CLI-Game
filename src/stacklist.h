/* File : stacklist.h */
#ifndef _STACKLIST_H
#define _STACKLIST_H

#include "point.h"
#include "mesinkata.h"
#include "boolean.h"
#include "map.h"
#include <stdio.h>
#include <stdlib.h>

/* Konstanta */
#define STACK_Nil NULL

/* Deklarasi infotype */
//typedef Kata command; //buy, build, upgrade
//typedef int specCommand; //kalo buy jenis material yang dibeli, kalo build berarti wahana yang di build, 
						 //kalo upgrade wahana yang mana
//typedef int infoCommand; //kalo buy berarti kuantitas, kalo build berarti ukuran, kalo upgrade mau jadi apa
//typedef POINT pointPlayer; //save point player saat command


/* Stack dengan representasi berkait dengan pointer */
typedef struct tElmtStack * addressStack;
typedef struct tElmtStack { 
	Kata Command;
	int SpecCommand;
	int InfoCommand;
	POINT PointPlayer;
	addressStack Next; 
	gAddress_V MapStack;
} ElmtStack; 

/* Type stack dengan ciri TOP : */
typedef struct { 
	addressStack TOP;  /* alamat TOP: elemen puncak */
} Stack;

/* Selektor */
#define Top(S) (S).TOP
#define InfoTop(S) (S).TOP->InfoCommand
#define Next(P) (P)->Next
#define SpecCommand(P) (P)->SpecCommand
#define InfoCommand(P) (P)->InfoCommand
#define Command(P) (P)->Command
#define PointPlayer(P) (P)->PointPlayer
#define MapStack(P) (P)->MapStack

/* Prototype manajemen memori */
void STACK_Alokasi (addressStack *P, Kata command, int specCommand, int infoCommand, POINT pointPlayer, gAddress_V mapStack);
/* I.S. Sembarang */
/* F.S. Alamat P dialokasi, jika berhasil maka Info(P)=X dan 
        Next(P)=Nil */
/*      P=Nil jika alokasi gagal */
void STACK_Dealokasi (addressStack P);
/* I.S. P adalah hasil alokasi, P != Nil */
/* F.S. Alamat P didealokasi, dikembalikan ke sistem */ 

/* ********* PROTOTYPE REPRESENTASI LOJIK STACK ***************/
boolean STACK_IsEmpty (Stack S);
/* Mengirim true jika Stack kosong: TOP(S) = Nil */
void STACK_CreateEmpty (Stack * S);
/* I.S. sembarang */ 
/* F.S. Membuat sebuah stack S yang kosong */
void Push (Stack * S, Kata command, int specCommand, int infoCommand, POINT pointPlayer, gAddress_V MapStack);
/* Menambahkan X sebagai elemen Stack S */
/* I.S. S mungkin kosong, X terdefinisi */
/* F.S. X menjadi TOP yang baru jika alokasi X berhasil, */
/*      jika tidak, S tetap */
/* Pada dasarnya adalah operasi Insert First pada list linier */
void Pop (Stack * S, Kata *command, int *specCommand, int *infoCommand, POINT *pointPlayer, gAddress_V *MapStack);
/* Menghapus X dari Stack S. */
/* I.S. S tidak mungkin kosong */
/* F.S. X adalah nilai elemen TOP yang lama, */
/*      elemen TOP yang lama didealokasi */
/* Pada dasarnya adalah operasi Delete First pada list linier */
int STACK_NbElmt(Stack S);
void PrintIsiStack(Stack S);

#endif
