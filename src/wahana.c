#include "wahana.h"

#include <stdio.h>
#include <stdlib.h>

void LoadWahanaTypes(WAHANA_UpgradeTree *wahanaTypes[], char* fileName)
{
    /*
    Membaca data map dari file mulai dari penanda #map. 
    Bisa untuk membaca dari file map.txt dan state.txt
    FORMAT (untuk setiap tipe wahana):
        #wt
        nama/harga/kapasitas/durasi/deskripsi
        nama/harga/kapasitas/durasi/deskripsi
        nama/harga/kapasitas/durasi/deskripsi
        nama/harga/kapasitas/durasi/deskripsi
        nama/harga/kapasitas/durasi/deskripsi
        nama/harga/kapasitas/durasi/deskripsi

        KETERANGAN:
        Tiap tipe wahana diawali dengan #wt
        Dibaca PreOrder (Left->Right->Root)
        Setiap level dipisah dengan tab
    */

    FILE *wtFile;
    char line[100];

    // int mapH, mapW, mapID;
    // int gateCount = 0;


    wtFile = fopen(fileName, "r"); 
    if (wtFile == NULL)
    {
        printf("FAILED TO READ MAP\n");
        return;
    }

    int level = 0;

    while(fgets(line, 100, wtFile) != NULL)
    {
        if (line[0] == '#' && line[1] == 'w' && line[2] == 't')
        {
            
        }
    }

    // while (fgets(line, 100, wtFile) != NULL)
    // {
    //     if (line[0] == '#' && line[1] == 'm')
    //     {
    //         // fseek(mapFile, ftell(mapFile), SEEK_SET);
    //         // Mulai dari data map
    //         fscanf(wtFile, "%d %d %d", &mapID, &mapH, &mapW);
    //         fscanf(wtFile, "%d", &gateCount);

    //         int* gateDestinations = malloc(gateCount * sizeof(int));
    //         for (int i = 0; i < gateCount; i++)
    //         {
    //             fscanf(wtFile, "%d", &gateDestinations[i]);
    //         }
            
    //         // printf("MAP %d DIMENSIONS %d %d\n", mapID, mapH, mapW);
    //         // printf("GATE DATA %d, %d %d\n", gateCount, gateDestinations[0], gateDestinations[1]);
    //         fgets(line, 100, wtFile);

    //         NBrs(*M) = mapH;
    //         NKol(*M) = mapW;

    //         int gate = 0;

    //         for (int i = 0; i < mapH + 1; i++)
    //         {
    //             fgets(line, 100, wtFile);
                
    //         }

    //         free(gateDestinations);
    //         // Akhir dari data map
    //     }
    // }

    // fclose(wtFile);
    // return;
}

FILE* readWahanaType()
{
    
}

tAddress WAHANAT_Alokasi()
{
    
};