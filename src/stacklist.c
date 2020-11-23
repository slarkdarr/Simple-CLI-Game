#include <stdio.h>
#include <stdlib.h>
#include "boolean.h"
#include "stacklist.h"

/* Prototype manajemen memori */
void STACK_Alokasi (addressStack *P, Kata command, int specCommand, int infoCommand, POINT pointPlayer)
{
    *P = (addressStack) malloc(sizeof(ElmtStack));
    if (*P != Nil)
    {
        Command(*P) = command;
        SpecCommand(*P) = specCommand;
        InfoCommand(*P) = infoCommand;
        PointPlayer(*P) = pointPlayer;
        Next(*P) = Nil;
    }
}
/* I.S. Sembarang */
/* F.S. Alamat P dialokasi, jika berhasil maka Info(P)=X dan 
        Next(P)=Nil */
/*      P=Nil jika alokasi gagal */
void STACK_Dealokasi (addressStack P)
{
    free(P);
}
/* I.S. P adalah hasil alokasi, P != Nil */
/* F.S. Alamat P didealokasi, dikembalikan ke sistem */ 

/* ********* PROTOTYPE REPRESENTASI LOJIK STACK ***************/
boolean STACK_IsEmpty (Stack S)
{
    return (Top(S) == Nil);
}
/* Mengirim true jika Stack kosong: TOP(S) = Nil */
void STACK_CreateEmpty (Stack * S)
{
    Top(*S) = Nil;
}
/* I.S. sembarang */ 
/* F.S. Membuat sebuah stack S yang kosong */
void Push (Stack * S, Kata command, int specCommand, int infoCommand, POINT pointPlayer)
{
    addressStack P;
    STACK_Alokasi(&P, command, specCommand, infoCommand, pointPlayer);
    if (P != Nil)
    {
        Next(P) = Top(*S);
        Top(*S) = P;
    }
}
/* Menambahkan X sebagai elemen Stack S */
/* I.S. S mungkin kosong, X terdefinisi */
/* F.S. X menjadi TOP yang baru jika alokasi X berhasil, */
/*      jika tidak, S tetap */
/* Pada dasarnya adalah operasi Insert First pada list linier */
void Pop (Stack * S, Kata *command, int *specCommand, int *infoCommand, POINT *pointPlayer)
{
    addressStack P = Top(*S);
    if (Next(P) == Nil)
    {
        Top(*S) = Nil;
        *command = Command(P);
        *specCommand = SpecCommand(P);
        *infoCommand = InfoCommand(P);
        *pointPlayer = PointPlayer(P);
        STACK_Dealokasi(P);
    }
    else
    {
        Top(*S) = Next(P);
        *command = Command(P);
        *specCommand = SpecCommand(P);
        *infoCommand = InfoCommand(P);
        *pointPlayer = PointPlayer(P);
        Next(P) = Nil;
        STACK_Dealokasi(P);
    }
}
/* Menghapus X dari Stack S. */
/* I.S. S tidak mungkin kosong */
/* F.S. X adalah nilai elemen TOP yang lama, */
/*      elemen TOP yang lama didealokasi */
/* Pada dasarnya adalah operasi Delete First pada list linier */

int STACK_NbElmt(Stack S)
// untuk aksi yang akan dilakukan
{
    int count = 0;
    addressStack P = Top(S);
    while (P != Nil)
    {
        count += 1;
        P = Next(P);
    }
    return count;
}