#include "game.h"

GAME gameInstance;

void GAME_Init()
{
    LoadMap(&Map(gameInstance), "map.txt");
    WahanaType(gameInstance);
    //Barang(gameInstance) = 0;
    //BarangData(gameInstance) = 0;
    AntrianData(gameInstance) = 0;
    Money(gameInstance) = 0;
    Time(gameInstance) = MakeJAM(9, 0, 0);
    Day(gameInstance) = 1;
    LoadMaterial(&MaterialList(gameInstance), "material.txt");
}

void GAME_Load()
{

};

void GAME_Save()
{

};