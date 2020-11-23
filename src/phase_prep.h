#ifndef PHASEPREP_H
#define PHASEPREP_H

#include <stdlib.h>
#include <stdio.h>
#include "boolean.h"
#include "stacklist.h"
#include "point.h"
#include "game.h"
#include "mesinkata.h"

/* Materials.txt */
#define MATERIALS_IdxMin 0
#define MATERIALS_IdxMax 9
#define ValUndef NULL

/* Struktur Data untuk MATERIAL */
typedef struct{
    int price;
    int kuantitas;
    Kata name;    
} MATERIALS_ElType;

typedef struct {
    MATERIALS_ElType TI[10];
} TabMaterial;

#define Tabmat(T, i) (T).TI[(i)]
#define MaterialName(T, i) ((T).TI[(i)]).name
#define MaterialQuantity(T, i) ((T).TI[(i)]).kuantitas
#define MaterialPrice(T, i) ((T).TI[(i)]).price

void LoadMaterial(TabMaterial *TabMat, char *filename);

void preparation_phase(Kata *gameInstance);

void Build(MAP *M, POINT P, int i);   
//Fungsi untuk membangun wahana baru, i merupakan indeks wahana yang akan dibuat, menunjuk pada array wahana
void Upgrade(); //Fungsi untuk meng-upgrade wahana
void Buy(TabMaterial *TabMat, Kata Material, int Jumlah);     //Fungsi untuk membeli bahan bangunan
void Undo(Stack *S, JAM *timeNeeded, int *moneyNeeded);    //Fungsi untuk melakukan UNDO pada eksekusi terakhir pemain
void Execute(Stack *S, int *globalCurrency); //Fungsi untuk mengeksekusi setiap command yang diberikan pemain
//void Main(Stack *S);    //Fungsi untuk mengosongkan stack dan masuk ke main phase
void toTarget(Stack *S, Stack *Target);
void Undo (Stack *S, JAM *timeNeeded, int *moneyNeeded);
int SearchForPrice(TabMaterial TabMat, Kata Material);
int SearchForQuantity(TabMaterial TabMat, Kata Material);
void PrintAllMaterials(TabMaterial TabMat); //testing
boolean SearchForMaterial(TabMaterial TabMat, Kata Material); //mencari jika material ada
boolean SearchForBuilding(Kata Building); //mencari jika building ada
boolean SearchForUpgrade(); //mencari jika upgrade ada
int SearchForIndexBuilding(Kata Building);
boolean CheckNearGate(MAP *M);
int SearchForIndexMaterial(Kata Material);
#endif