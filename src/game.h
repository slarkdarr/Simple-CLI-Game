#ifndef GAME_H
#define GAME_H

#include "map.h"
#include "jam.h"

typedef struct {
    MAP map;
    char PName[25];
    int wahana;
    int wahanaData;
    int barang;
    int barangData;
    int antrianData;
    int money;
    JAM time;
} GAME;

#define Map(G) (G).map
#define PName(G) (G).PName
#define Wahana(G) (G).wahana
#define WahanaData(G) (G).wahanaData
#define Barang(G) (G).barang
#define BarangData(G) (G).barangData
#define AntrianData(G) (G).antrianData
#define Money(G) (G).money
#define Time(G) (G).time

extern GAME gameInstance;

#define _map Map(gameInstance)
#define _name PName(gameInstance)

void GAME_Init();
void GAME_Save();
void GAME_Load();

#endif