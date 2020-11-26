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

#include "boolean.h"
#include "mesinkata.h"
#include "point.h"

typedef struct tWAHANA_Eltype {
    Kata nama;
    Kata deskripsi;
    int harga;
    int kapasitas;
    int durasi;    
    int wood; // Bahan bangunan untuk membuat
    int stone; // Bahan bangunan untuk membuat
    int iron; // Bahan bangunan untuk membuat
    int buildprice; // Harga untuk membuat
} WAHANA_ElType;

#define WahanaNama(W) (W).nama
#define WahanaHarga(W) (W).harga
#define WahanaKapasitas(W) (W).kapasitas
#define WahanaDurasi(W) (W).durasi
#define WahanaDeskripsi(W) (W).deskripsi  
#define WahanaWood(W) (W).wood
#define WahanaStone(W) (W).stone
#define WahanaIron(W) (W).iron
#define WahanaBuildPrice(W) (W).buildprice



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

#define WNama(W) WahanaNama(Akar(W))
#define WHarga(W) WahanaHarga(Akar(W))
#define WKapasitas(W) WahanaKapasitas(Akar(W))
#define WDurasi(W) WahanaDurasi(Akar(W))
#define WDeskripsi(W) WahanaDeskripsi(Akar(W))
#define WWood(W) WahanaWood(Akar(W))
#define WStone(W) WahanaStone(Akar(W))
#define WIron(W) WahanaIron(Akar(W))
#define WBuildPrice(W) WahanaBuildPrice(Akar(W))

typedef struct 
{
    tAddress current; // sekarang wahananya apa
    POINT position; // letak wahana, kalau jadi ada ukuran, make list of position

    boolean upgradeHistory[25]; // Upgrade history disimpen pake List Implementasi Array, true = Left, false = right      
    int upgradeHistoryNEff; // NEff dari upgradeHistory
    // Example tftttf: left right left left left right (dari root)

    int root; // id tipe awal wahananya apa
    int currentLoad; // sekarang isinya ada berapa orang
    
    int timesUsed; // total dipakai berapa kali
    int timesUsedToday; // hari ini dipakai berapa kali
} WAHANA_Instance;


void LoadWahanaTypes(tAddress *wahanaTypes[], char *fileName, int *count);
void LoadWahanas(WAHANA_ElType *wahana[], char* filename);

tAddress WAHANAT_Alokasi(char name[], int price, int cap, int dur, char desc[], int left, int right, int wood, int stone, int iron, int buildprice);
WAHANA_ElType WAHANAT_Create(Kata name, int price, int cap, int dur, Kata desc, int wood, int stone, int iron, int buildprice);
FILE* readWahanaType(tAddress *WAHANAT); 

void WAHANA_PrintInfo(tAddress wahana);

void WAHANA_CreateInstance(POINT location, int type); // Membuat wahana baru di location dengan tipe _wType(type)

void WAHANA_PrintUpgrade(tAddress W);

void WAHANA_PrintCommandUpgrade(tAddress W);

#endif