#ifndef MATERIALS_H
#define MATERIALS_H

// testing

#include "boolean.h"
#include "mesinkata.h"

#include <stdlib.h>
#include <stdio.h>


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
int SearchForPrice(TabMaterial TabMat, Kata Material);
int SearchForQuantity(TabMaterial TabMat, Kata Material);
void PrintAllMaterials(TabMaterial TabMat); 
boolean SearchForMaterial(TabMaterial TabMat, Kata Material); //mencari jika material ada
int SearchForIndexMaterial(Kata Material);

#endif
