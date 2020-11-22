#ifndef GAME_H
#define GAME_H

#include "map.h"
#include "jam.h"
#include "wahana.h"
#include "mesinkata.h"
#include "phase_prep.h"

typedef struct {
    MAP map;
    char PName[25];
    WAHANA_UpgradeTree wahanaType[10];
    WAHANA_ElType wahana[50];
    //int barangType;
    //int barang;
    int antrianData;
    int money;
    JAM time;
    int day; //penanda hari ke berapa
    TabMaterial MaterialList;
} GAME;


#define Map(G) (G).map
#define PName(G) (G).PName
#define WahanaType(G) (G).wahanaType
#define Wahana(G) (G).wahana
#define Barang(G) (G).barangType
#define BarangData(G) (G).barang
#define AntrianData(G) (G).antrianData
#define Money(G) (G).money
#define Time(G) (G).time
#define MaterialList(G) (G).MaterialList // Harga dan Tipe Material dan Kuantitas yang dimiliki
#define Day(G) (G).day

extern GAME gameInstance;

#define _map Map(gameInstance)
#define _name PName(gameInstance)
#define _time Time(gameInstance)
#define _money Money(gameInstance) //gua tambahin vin -Noler

void GAME_Init();
void GAME_Save();
void GAME_Load();

#endif