#include "game.h"

GAME gameInstance;

void GAME_Init()
{
    LoadMap(&Map(gameInstance), "map.txt");
    LoadWahanaTypes(&(WahanaType(gameInstance)), "wahana.txt", &WahanaTypeCount(gameInstance));
    WahanaCount(gameInstance) = 0;
    AntrianData(gameInstance) = 0;
    Money(gameInstance) = 0;
    Time(gameInstance) = MakeJAM(21, 0, 0);
    Day(gameInstance) = 1;
    LoadMaterial(&MaterialList(gameInstance), "material.txt");
    InitializeArrayAction(&Actions(gameInstance));
    _money = 10000;

    //     Kata nama;
    // Kata deskripsi;
    // int harga;
    // int kapasitas;
    // int durasi;    

    // printf("\n");
    // PrintKata((Akar((WahanaType(gameInstance))[0])).nama);
    // PrintKata((Akar((WahanaType(gameInstance))[0])).deskripsi);
    // printf("HARGA %d\n", (Akar((WahanaType(gameInstance))[0])).harga);
    // printf("KAP %d\n", (Akar((WahanaType(gameInstance))[0])).kapasitas);
    // printf("DURASI %d\n", (Akar((WahanaType(gameInstance))[0])).durasi);

    // printf("OUTSIDE WAHANA.C\n");
    // WAHANA_PrintInfo(WahanaType(gameInstance)[0]);
    // WAHANA_PrintInfo(WahanaType(gameInstance)[1]);   
}

void GAME_Load()
{

};

void GAME_Save()
{

};