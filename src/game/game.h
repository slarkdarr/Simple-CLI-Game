#ifndef GAME_H
#define GAME_H

#include "../jam/jam.h"
#include "../map/map.h"
#include "../wahana/wahana.h"
#include "../materials/materials.h"
#include "../mesinkata/mesinkata.h"
#include "../phase/phase_prep.h"
#include "../phase/phase_main.h"
#include "../arrayaction/arrayaction.h"

typedef struct {
    gAddress_V rootMap; // Vertex dari Map Awal
    gAddress_V fullMap; // Vertex dari FullMap
    MAP map; // Merupakan map player saat ini (akan berganti jika berpindah map)
    char PName[25]; // Nama dari player untuk display
    tAddress wahanaType[10]; // Berisi tipe-tipe wahana yang dapat dibuat dengan fungsi build
    int wahanaTypeCount; // Berisi total jumlah wahana yang dapat dibuat dengan fungsi build
    WAHANA_Instance wahana[50]; // Berisi wahana yang terdapat pada tiap map
    int wahanaCount; // Berisi total jumlah wahana yang terdapat pada map
    int money; // Berisi total uang yang dimiliki oleh player
    JAM time; // Penanda Jam saat ini
    int day; // Penanda hari ke berapa
    TabMaterial MaterialList; // Berisi Material yang dapat digunakan sebagai bahan bangunan
    ArrayAction_TabInt actions; // Berisi aksi yang dapat dilakukan beserta durasinya
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
#define _money Money(gameInstance)
#define _mlist MaterialList(gameInstance)
#define _actions Actions(gameInstance)
#define _day Day(gameInstance)

void GAME_Init();
void GAME_Save();
void GAME_Load();

#endif