#ifndef GAME_H
#define GAME_H

#include "map.h"

typedef struct {
    MAP map;
    char PName[25];
    int wahana;
    int wahanaData;
    int barang;
    int barangData;
    int antrianData;
    int money;
    int time;
} GAME;

#endif