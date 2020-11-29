#include "stacklist.h"
#include "point.h"
#include "boolean.h"
#include "map.h"
#include <stdio.h>
#include <stdlib.h>

// Prototype manajemen memori 
void STACK_Alokasi (addressStack *P, Kata command, int specCommand, int infoCommand, POINT pointPlayer, gAddress_V mapStack)
{
    *P = (addressStack) malloc(sizeof(ElmtStack));
    if (*P != STACK_Nil)
    {
        Command(*P) = command;
        SpecCommand(*P) = specCommand;
        InfoCommand(*P) = infoCommand;
        PointPlayer(*P) = pointPlayer;
        MapStack(*P) = mapStack;
        Next(*P) = STACK_Nil;
    }
}
// Mengalokasikan addressStack untuk di Push pada Stack dengan Next sebagai STACK_Nil
// addressStack yang dialokasi memiliki atribut sebagai berikut:
// Command(P) = Kata command
// SpecCommand(P) = int specCommand
// InfoCommand(P) = int infoCommand
// PointPlayer(P) = POINT pointPlayer

void STACK_Dealokasi (addressStack P)
{
    free(P);
}
// Mendealokasi addressStack yang memiliki atribut sebagai berikut:
// Kata, int, int, POINT

/* ********* PROTOTYPE REPRESENTASI LOGIC STACK ***************/
boolean STACK_IsEmpty (Stack S)
{
    return (Top(S) == STACK_Nil);
}
// True jika Stack kosong, false jika berisi

void STACK_CreateEmpty (Stack * S)
{
    Top(*S) = STACK_Nil;
}
// Membuat Stack yang tidak memiliki isi
// Representasi List Linier Stack (LIFO)

void Push (Stack * S, Kata command, int specCommand, int infoCommand, POINT pointPlayer, gAddress_V mapStack)
{
    addressStack P;
    STACK_Alokasi(&P, command, specCommand, infoCommand, pointPlayer, mapStack);
    if (P != STACK_Nil)
    {
        Next(P) = Top(*S);
        Top(*S) = P;
    }
}
// Menambahkan elemen pada sebuah Stack, addressStack sebelumnya dialokasi terlebih dahulu
// Setelah alokasi, addressStack memliki:
// Command(P) : Kata command
// SpecCommand(P) : Spesifikasi command, untuk build misal build wahana apa (indeks pada array wahana)
// InfoCommand(P) : Berisi info dari spesifikasi command, misal untuk Buy, berisi jumlah dari indeks specCommand (pada array material yang ada)
// PointPlayer(P) : Berisi POINT Player saat melakukan aksi
// addressStack P kemudian dimasukkan dalam Stack dengan metode Last In First Out (LIFO)

void Pop (Stack * S, Kata *command, int *specCommand, int *infoCommand, POINT *pointPlayer, gAddress_V *mapStack)
{
    addressStack P = Top(*S);
    if (Next(P) == STACK_Nil)
    {
        Top(*S) = STACK_Nil;
        *command = Command(P);
        *specCommand = SpecCommand(P);
        *infoCommand = InfoCommand(P);
        *pointPlayer = PointPlayer(P);
        *mapStack = MapStack(P);
        STACK_Dealokasi(P);
    }
    else
    {
        Top(*S) = Next(P);
        *command = Command(P);
        *specCommand = SpecCommand(P);
        *infoCommand = InfoCommand(P);
        *pointPlayer = PointPlayer(P);
        *mapStack = MapStack(P);
        Next(P) = STACK_Nil;
        STACK_Dealokasi(P);
    }
}
// Menghapus Top(S) dari sebuah Stack, kemudian di dealokasikan
// command, specCommand, infoCommand, pointPlayer disimpan pada sebuah variable
// kemudian variable tersebut digunakan untuk Undo, Execute, dan sebagainya
// Operasi Delete First pada list linier

int STACK_NbElmt(Stack S)
// Digunakan untuk display jumlah aksi yang akan dilakukan
// Aksi yang akan dilakukan adalah sebanyak isi stack
{
    int count = 0;
    addressStack P = Top(S);
    while (P != STACK_Nil)
    {
        count += 1;
        P = Next(P);
    }
    return count;
}
void PrintIsiStack(Stack S)
// Mem-print isi stack
{
    addressStack P = Top(S);
    while (P != STACK_Nil)
    {
        printf("Perintah: ");
        PrintKata(Command(P)); printf("\n");
        printf("Spec    : %d\n", SpecCommand(P));
        printf("Info    : %d\n", InfoCommand(P));
        printf("Point   : "); TulisPOINT(PointPlayer(P)); printf("\n\n");
        P = Next(P);
    }
}