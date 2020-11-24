#ifndef PHASEPREP_H
#define PHASEPREP_H

#include <stdlib.h>
#include <stdio.h>
#include "boolean.h"
#include "stacklist.h"
#include "materials.h"
#include "point.h"
#include "game.h"
#include "jam.h"
#include "mesinkata.h"

/* Materials.txt */

void preparation_phase();

void Build(MAP *M, POINT P, int i);   
//Fungsi untuk membangun wahana baru, i merupakan indeks wahana yang akan dibuat, menunjuk pada array wahana
void Upgrade(); //Fungsi untuk meng-upgrade wahana
void Buy(TabMaterial *TabMat, int Jumlah, int Index);     //Fungsi untuk membeli bahan bangunan
void Undo(Stack *S, JAM *timeNeeded, int *moneyNeeded);    //Fungsi untuk melakukan UNDO pada eksekusi terakhir pemain
void Execute(Stack *S, int *globalCurrency); //Fungsi untuk mengeksekusi setiap command yang diberikan pemain
//void Main(Stack *S);    //Fungsi untuk mengosongkan stack dan masuk ke main phase
void toTarget(Stack *S, Stack *Target);
void Undo (Stack *S, JAM *timeNeeded, int *moneyNeeded);
boolean SearchForBuilding(Kata Building); //mencari jika building ada
boolean SearchForUpgrade(); //mencari jika upgrade ada
int SearchForIndexBuilding(Kata Building);
int SearchForIndexMaterial(Kata Material);
boolean CheckNearGate(MAP *M);
int GetDuration(Kata command);
#endif