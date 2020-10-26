#ifndef MAP_H
#define MAP_H

#define MaxEl 100

#include "matriks.h"
#include "boolean.h"
#include "point.h"

typedef char keytype;
typedef int infotype;
typedef struct {
                keytype type; 
                infotype id; 
                } mapEntry;

typedef struct {
                mapEntry T[MaxEl-1][MaxEl-1];
                int NbElmt;
                POINT P;
                } Map;

/* KONSTRUKTOR */
MakeEmptyMap(Map *M);
LoadMap(Map *M);

/* GETTER SETTER */


/* PROSEDUR */
// Menggerakkan Point P sesuai command W
Move(Map *M, char W);

// SystemPrint matriks Map M
DrawMap(Map M);

/* FUNGSI */
// Mengembalikan id dari object dengan tipe O terdekat dengan P
GetObject(char O);

#endif