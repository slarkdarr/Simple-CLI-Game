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
        nama
        harga
        kapasitas
        durasi
        deskripsi
        jumlah upgrade
        <id left> <id right> <elcount>

        #wu 
        nama
        harga
        kapasitas
        durasi
        deskripsi
        biaya upgrade
        <id left> <id right>

        KETERANGAN:
        id sesuai urutan kemunculan (wt adalah 0)
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
            tAddress nodes[25];
            char name[25], desc[50];
            int cap, dur, price, left, right, upprice, elcount;
            fscanf(wtFile, "%s %d %d %d %s %d %d %d %d", &name, &price, &cap, &dur, &desc, &upprice,&left, &right, &elcount);
            nodes[0] = WAHANAT_Alokasi(name, price, cap, dur, desc, left, right);

            for (int i = 1; i < elcount; i++)
            {
                while (fgets(line, 100, wtFile) != NULL)
                {
                    if (line[0] == '#' && line[1] == 'w' && line[2] == 'u')
                    {
                        fscanf(wtFile, "%s %d %d %d %s %d %d %d", &name, &price, &cap, &dur, &desc, &upprice,&left, &right);
                        nodes[i] = WAHANAT_Alokasi(name, price, cap, dur, desc, left, right);
                    }
                }
            }

            for  (int i = 0; i < elcount; i++)
            {
                Left(nodes[i]) = nodes[(int)Left(nodes[i])];
                Right(nodes[i]) = nodes[(int)Right(nodes[i])];
            }
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

tAddress WAHANAT_Alokasi(char name[], int price, int cap, int dur, char desc[], int left, int right)
{
    // nama
    // harga
    // kapasitas
    // durasi
    // deskripsi
    // biaya upgrade
    // <id left> <id right>
    tAddress result = malloc(sizeof(WAHANA_UpgradeTree));

    Akar(result) = WAHANA_Alokasi(name, price, cap, dur, desc);
    Right(result) = right;
    Left(result) = left;

    // WNama(result) = name;
    // WHarga(result) = price;
    // WKapasitas(result) = cap;
    // WDurasi(result) = dur;
    // WDeskripsi(result) = desc;
};

wAddress WAHANA_Alokasi(char name[], int price, int cap, int dur, char desc[])
{
    wAddress result = malloc(sizeof(WAHANA_ElType));

    if (result != NULL)
    {
        WNama(result) = name;
        WHarga(result) = price;
        WKapasitas(result) = cap;
        WDurasi(result) = dur;
        WDeskripsi(result) = desc;
    }

    return result;
};