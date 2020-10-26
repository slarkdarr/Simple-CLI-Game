#ifndef MAP_H
#define MAP_H

#define MaxEl 100

//Ukuran Map
#define UkuranMap 10

#include "matriks.h"
#include "boolean.h"
#include "point.h"

#define Nil -1

//cek definisi lagi, soalnya gabisa diakses id sama type nya
typedef char keytype;
typedef int infotype;
typedef struct {
                keytype type; 
                infotype id; // Selain bangunan/gate ber-id Nil *untuk Antrian?
                } mapEntry;

typedef struct {
                mapEntry *T[MaxEl][MaxEl];
                int NBrsEff;
                int NKolEff;
                POINT P;
                } Map;

/* Selektor */
#define Elmt(M, i, j) M.T[(i)][(j)]
#define Info(Entry) (Entry).id
#define Key(Entry) (Entry).type
#define Player(M) M.P
#define NBrsEff(M) M.NBrsEff
#define NKolEff(M) M.NKolEff

/* KONSTRUKTOR */
void MakeEmptyMap(Map *M);
void LoadMap(Map *M);

/* GETTER SETTER */


/* PROSEDUR */
// Menggerakkan Point P sesuai command W
void Move(Map *M, char W);

// SystemPrint matriks Map M
void DrawMap(Map M);

/* FUNGSI */
// Mengembalikan id dari object dengan tipe O terdekat dengan P
// Object yang diprioritaskan untuk dicek pertama adalah di atas P, kemudian secara clock-wise dicek dengan prioritas paling utama adalah diatas
int GetObject(char O);

#endif