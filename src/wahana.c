#include "wahana.h"

#include <stdio.h>
#include <stdlib.h>

void LoadWahanaTypes(WAHANA_UpgradeTree *wahanaTypes[], char* fileName)
{
    /*
    Membaca data map dari file mulai dari penanda #map. 
    Bisa untuk membaca dari file map.txt dan state.txt
    FORMAT:
        #map
        id H W
        gateCount dest1 dest2 dest3
        <matriks M> 
        
        KETERANGAN:
        H, W            : int, dimensi dari M
        M               : matriks of char
        id              : int, id dari map
        gateCount       : int, jumlah gate pada map
        dest<N>         : int, id dari tujuan gate ke-N (penomoran gate dibaca terurut seperti paragraf)
    
    Ukuran M adalah HxW

    Jika ada Wahana atau Antrian pada matriks, InfoElmt diinisialisasi dengan -1. 
    (Untuk map.txt, tidak ada Wahana atau Antrian)
    (Untuk state.txt, Wahana dan Antrian diisi oleh fungsi pembaca dari file untuk Wahana dan Antrian)

    NOTES:
        Untuk sekarang hanya membaca satu map. Nanti kalau udah diajarin graf, dia dipakai buat baca banyak map kemudian menyusun graf petanya
        Tapi dia udah bisa baca banyak map dalam satu file, tapi semuanya ngubah ke M aja untuk sekarang.
    */

    FILE *wtFile;
    char line[100];

    int mapH, mapW, mapID;
    int gateCount = 0;


    wtFile = fopen(fileName, "r"); 
    if (wtFile == NULL)
    {
        printf("FAILED TO READ MAP\n");
        return;
    }

    while (fgets(line, 100, wtFile) != NULL)
    {
        if (line[0] == '#' && line[1] == 'm')
        {
            // fseek(mapFile, ftell(mapFile), SEEK_SET);
            // Mulai dari data map
            fscanf(wtFile, "%d %d %d", &mapID, &mapH, &mapW);
            fscanf(wtFile, "%d", &gateCount);

            int* gateDestinations = malloc(gateCount * sizeof(int));
            for (int i = 0; i < gateCount; i++)
            {
                fscanf(wtFile, "%d", &gateDestinations[i]);
            }
            
            // printf("MAP %d DIMENSIONS %d %d\n", mapID, mapH, mapW);
            // printf("GATE DATA %d, %d %d\n", gateCount, gateDestinations[0], gateDestinations[1]);
            fgets(line, 100, wtFile);

            NBrs(*M) = mapH;
            NKol(*M) = mapW;

            int gate = 0;

            for (int i = 0; i < mapH + 1; i++)
            {
                fgets(line, 100, wtFile);
                
            }

            free(gateDestinations);
            // Akhir dari data map
        }
    }

    fclose(wtFile);
    return;
}

