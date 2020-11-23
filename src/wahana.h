/*
File Wahana (wahana.txt)
Digunakan untuk menyimpan ​tree​ bangunan yang mencakup:
Wahana yang setiap ​node​-nya mencakup:
    i.Nama Wahana
    ii.Harga Wahana
    iii.Kapasitas Wahana
    iv.Durasi Wahana
    v.Deskripsi Wahana
Cost yang dibutuhkan untuk upgrade wahana(pindah ke node ​tree​ lain):
    i.Uang yang dibutuhkan
    ii.Bahan bangunan yang dibutuhkan
*/
#ifndef WAHANA_H
#define WAHANA_H

#include <stdio.h>
#include <stdlib.h>

#include "mesinkata.h"


typedef struct tWAHANA_Eltype {
    Kata nama;
    Kata deskripsi;
    int harga;
    int kapasitas;
    int durasi;    
} WAHANA_ElType;

#define WNama(W) (W).nama
#define WHarga(W) (W).harga
#define WKapasitas(W) (W).kapasitas
#define WDurasi(W) (W).durasi
#define WDeskripsi(W) (W).deskripsi  

typedef struct tWAHANA_UpgradeTree *tAddress;
#define WAHANA_Nil NULL

typedef struct tWAHANA_UpgradeTree {
    WAHANA_ElType wahana;
    tAddress right;
    tAddress left; 
} WAHANA_UpgradeTree;

#define Akar(U) (U)->wahana
#define Right(U) (U)->right
#define Left(U) (U)->left

void LoadWahanaTypes(tAddress *wahanaTypes[], char *fileName, int *count);
void LoadWahanas(WAHANA_ElType *wahana[], char* filename);

tAddress WAHANAT_Alokasi(char name[], int price, int cap, int dur, char desc[], int left, int right);
WAHANA_ElType WAHANAT_Create(Kata name, int price, int cap, int dur, Kata desc);
FILE* readWahanaType(tAddress *WAHANAT); 

void WAHANA_PrintInfo(tAddress wahana);
#endif