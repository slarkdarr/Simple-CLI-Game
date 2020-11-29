#ifndef GAME_H
#define GAME_H

#include "jam.h"
#include "map.h"
#include "wahana.h"
#include "jam.h"
#include "materials.h"
#include "mesinkata.h"
#include "phase_prep.h"
#include "phase_main.h"
#include "arrayaction.h"

typedef struct {
    gAddress_V rootMap;
    gAddress_V fullMap;
    MAP map;
    char PName[25];
    tAddress wahanaType[10];
    int wahanaTypeCount;
    WAHANA_Instance wahana[50];
    int wahanaCount;
    int antrianData;
    int money;
    JAM time;
    int day; //penanda hari ke berapa
    TabMaterial MaterialList;
    ArrayAction_TabInt actions;
} GAME;

// #define FullMap(G) (G).fullMap
#define RootMap(G) (G).rootMap
#define FullMap(G) (G).fullMap
#define Map(G) (G).map
#define PName(G) (G).PName
#define WahanaType(G) (G).wahanaType
#define ElWahanaType(G,i) (G).wahanaType[i]
#define WahanaTypeCount(G) (G).wahanaTypeCount
#define Wahana(G) (G).wahana
#define WahanaCount(G) (G).wahanaCount
#define Barang(G) (G).barangType
#define BarangData(G) (G).barang
#define AntrianData(G) (G).antrianData
#define Money(G) (G).money
#define Time(G) (G).time
#define MaterialList(G) (G).MaterialList // Harga dan Tipe Material dan Kuantitas yang dimiliki
#define Day(G) (G).day
#define Actions(G) (G).actions // Array action berisi durasi tiap action yang dilakukan

extern GAME gameInstance;

#define ln printf("\n")

// #define _fullmap FullMap(gameInstance)
#define _rootmap RootMap(gameInstance)
#define _fullMap FullMap(gameInstance)
#define _map Map(gameInstance)
#define _name PName(gameInstance)
#define _time Time(gameInstance)
#define _wType(i) ElWahanaType(gameInstance,i) 
#define _wTCount WahanaTypeCount(gameInstance)
#define _wahana(i) Wahana(gameInstance)[i]
#define _wCount WahanaCount(gameInstance)
#define _money Money(gameInstance) //gua tambahin vin -Noler
#define _mlist MaterialList(gameInstance)
#define _actions Actions(gameInstance)
#define _day Day(gameInstance)

void GAME_Init();
void GAME_Save();
void GAME_Load();

#endif