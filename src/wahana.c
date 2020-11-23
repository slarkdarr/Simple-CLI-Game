#include "wahana.h"
#include "mesinkata.h"

#include <stdio.h>
#include <stdlib.h>

void LoadWahanaTypes(tAddress *wahanaTypes, char *fileName)
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

            fscanf(wtFile, "%d\n %d\n %d\n %d\n %d %d %d\n", &price, &cap, &dur, &upprice,&left, &right, &elcount);
            fgets(name, 25, wtFile);
            fgets(desc, 50, wtFile);

            // printf(" %s %s %d\n %d\n %d\n %d\n %d %d %d\n\n", name, desc, price, cap, dur, upprice, left, right, elcount);
            nodes[0] = WAHANAT_Alokasi(name, price, cap, dur, desc, left, right);

            // WAHANA_PrintInfo(Akar(nodes[0]));

            for (int i = 1; i < elcount; i++)
            {
                while (!(line[0] == '#' && line[1] == 'w' && line[2] == 'u'))
                {
                    fgets(line, 100, wtFile);
                }

                if (line[0] == '#' && line[1] == 'w' && line[2] == 'u')
                {
                    // fseek(wtFile, 0, SEEK_CUR);
                    fscanf(wtFile, "%d\n %d\n %d\n %d\n %d %d\n", &price, &cap, &dur, &upprice,&left, &right);
                    fgets(name, 25, wtFile);
                    fgets(desc, 50, wtFile);

                    // printf("%d\n %s %s %d\n %d\n %d\n %d\n %d %d\n", i, name, desc, price, cap, dur, upprice, left, right);

                    nodes[i] = WAHANAT_Alokasi(name, price, cap, dur, desc, left, right);
                }

                line[0] = 'x';
            }

            for (int i = 0; i < elcount; i++)
            {
                if (nodes[(int)Left(nodes[i])] == -1)
                {
                    Left(nodes[i]) = WAHANA_Nil;
                } else {
                    Left(nodes[i]) = nodes[(int)Left(nodes[i])];
                }

                if (nodes[(int)Right(nodes[i])] == -1)
                {
                    Right(nodes[i]) = WAHANA_Nil;
                } else {
                    Right(nodes[i]) = nodes[(int)Right(nodes[i])];
                }

                WAHANA_PrintInfo(nodes[i]);
            }
            
            *wahanaTypes = nodes[0];
        }
    }
    fclose(wtFile);
    return;
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

    Akar(result) = WAHANAT_Create(CreateKata(name), price, cap, dur, CreateKata(desc));
    Right(result) = right;
    Left(result) = left;
};

WAHANA_ElType WAHANAT_Create(Kata name, int price, int cap, int dur, Kata desc)
{
    WAHANA_ElType result;

    WNama(result) = name;
    WHarga(result) = price;
    WKapasitas(result) = cap;
    WDurasi(result) = dur;
    WDeskripsi(result) = desc;

    return result;
};

void WAHANA_PrintInfo(tAddress wahanaT)
{
    WAHANA_ElType wahana = Akar(wahanaT);

    printf("NAME       : ");
    PrintKata(WNama(wahana));
    printf("\n");

    printf("DESC       : ");
    PrintKata(WDeskripsi(wahana));
    printf("\n");

    printf(
        "PRICE      : %d\n"
        "CAP        : %d\n"
        "DURATION   : %d\n",
        WHarga(wahana), WKapasitas(wahana), WDurasi(wahana)
        );

    printf("LEFT       : ");
    if (Left(wahanaT) != WAHANA_Nil)
    {
        PrintKata(WNama(Akar(Left(wahanaT))));
    } else {
        printf("NONE");
    }
    printf("\n");
    

    printf("RIGHT      : ");
    if (Right(wahanaT) != WAHANA_Nil)
    {
        PrintKata(WNama(Akar(Right(wahanaT))));
    } else {
        printf("NONE");
    }
    printf("\n");
    printf("\n");

}