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



typedef struct WAHANA_UpgradeTree *tAddress;
const tAddress WAHANA_Nil = NULL;

typedef struct {
    char nama[25];
    int harga;
    int kapasitas;
    int durasi;
    char deskripsi[50];    
} WAHANA_ElType;

typedef struct {
    WAHANA_ElType wahana;
    tAddress right;
    tAddress left; 
} WAHANA_UpgradeTree;

#define WNama(W) W->nama
#define WHarga(W) W->harga
#define WKapasitas(W) W->kapasitas
#define WDurasi(W) W->durasi
#define WDeskripsi(W) W->deskripsi  

#define Akar(U) U->Wahana
#define Right(U) U->Right
#define Left(U) U->Left

void LoadWahanaTypes(WAHANA_UpgradeTree *wahanaType[], char* filename);
void LoadWahanas(WAHANA_ElType *wahana[], char* filename);

tAddress WAHANAT_Alokasi();
FILE* readWahanaType(tAddress *WAHANAT); 

#endif