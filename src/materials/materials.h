#ifndef MATERIALS_H
#define MATERIALS_H

// testing

#include "../boolean.h"
#include "../mesinkata/mesinkata.h"

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
// Prosedur membaca material dari file eksternal
int SearchForPrice(TabMaterial TabMat, Kata Material);
// Fungsi untuk mencari harga dari suatu material yang sudah dicari terlebih dahulu oleh fungsi SearchForMaterial 
// sehingga pasti akan ditemukan jika SearchForMaterial mengembalikan true
int SearchForQuantity(TabMaterial TabMat, Kata Material);
// Fungsi yang menerima sebuah Kata Material dan mencari kuantitas yang dimiliki dari jenis kata material yang diinput
// Fungsi akan selalu mengeluarkan angka karena Kata Material telah di cek terlebih dahulu jika ada atau tidak dalam _mlist (dari gameInstance) oleh fungsi
// SearchForMaterial
void PrintAllMaterials(TabMaterial TabMat);
// Fungsi untuk men-display seluruh material dengan harganya
boolean SearchForMaterial(TabMaterial TabMat, Kata Material); 
// Fungsi untuk mencari jika Kata Material terdapat dalam _mlist (gameInstance) yang merupakan input dari TabMaterial TabMat
int SearchForIndexMaterial(Kata Material);
// Fungsi yang mengembalikan indeks dari Kata Material dalam TabMaterial (_mlist dari gameInstance)

#endif
