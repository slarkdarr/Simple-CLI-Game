#ifndef BUILD_H
#define BUILD_H

#define BORDER '*'

#include <stdlib.h>
#include <stdio.h>
#include "boolean.h"
#include "stackt.h"
#include "point.h"
#include "game.h"
#include "mesinkata.h"

/* Materials.txt */
#define MATERIALS_IdxMin = 0
#define MATERIALS_IdxMax = 9
#define ValUndef NULL

typedef struct{
    int price;
    int kuantitas;
    Kata name;    
} MATERIALS_ElType;

typedef struct {
    MATERIALS_ElType TI[10];
} TabMaterial;

void LoadMaterial(TabMaterial *TabMat, char *filename);

void preparation_phase(Kata *gameInstance);

void Build(MAP *M, POINT P, int i);   
//Fungsi untuk membangun wahana baru, i merupakan indeks wahana yang akan dibuat, menunjuk pada array wahana
void Upgrade(); //Fungsi untuk meng-upgrade wahana
void Buy();     //Fungsi untuk membeli bahan bangunan
void Undo(Stack *S, JAM *timeNeeded, int *moneyNeeded);    //Fungsi untuk melakukan UNDO pada eksekusi terakhir pemain
void Execute(Stack *S, int *globalCurrency); //Fungsi untuk mengeksekusi setiap command yang diberikan pemain
//void Main(Stack *S);    //Fungsi untuk mengosongkan stack dan masuk ke main phase
void toTarget(Stack *S, Stack *Target);
void Undo (Stack *S, JAM *timeNeeded, int *moneyNeeded);
int SearchForPrice(TabMaterial *TabMat, Kata Material);
int SearchForQuantity(TabMaterial *TabMat, Kata Material);

#endif