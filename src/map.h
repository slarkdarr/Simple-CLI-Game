#ifndef MAP_H
#define MAP_H

#define MaxEl 100

#include "matriks.h"
#include "boolean.h"

typedef int keytype;
typedef int infotype;
typedef struct {
                keytype key;
                infotype value;
                } mapEntry;

typedef struct {
                mapEntry T[MaxEl-1];
                int NbElmt;
                } Map;

boolean IsWahana(MATRIKS MAP, int row, int col);

#endif