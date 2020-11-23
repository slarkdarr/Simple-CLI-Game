#include "game.h"

GAME gameInstance;

void GAME_Init()
{
    LoadMap(&Map(gameInstance), "map.txt");
    LoadWahanaTypes(&(WahanaType(gameInstance)[0]), "wahana.txt");
    //Barang(gameInstance) = 0;
    //BarangData(gameInstance) = 0;
    AntrianData(gameInstance) = 0;
    Money(gameInstance) = 0;
    Time(gameInstance) = MakeJAM(9, 0, 0);
    Day(gameInstance) = 1;
    // LoadMaterial(&MaterialList(gameInstance), "material.txt");

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

    
}

void GAME_Load()
{

};

void GAME_Save()
{

};