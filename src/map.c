#include "map.h"
#include "point.h"
#include "boolean.h"

#include <stdio.h>
#include <stdlib.h>

/* KONSTRUKTOR */
void MakeEmptyMAP(MAP *M)
{

}

void LoadMap(MAP *M, char fileName[])
{
    /*
    Membaca data map dari file mulai dari penanda #map. 
    Bisa untuk membaca dari file map.txt dan state.txt
    FORMAT:
        #map
        H W
        <matriks M> 
        id <gate1 gate2 gate3>
        
        KETERANGAN:
        H, W    : int, dimensi dari M
        M       : matriks of char
        id      : int, id dari map
        gateN   : int, id dari tujuan dari gateN (dibaca dari kiri->kanan->nextline)
    
    Ukuran M adalah HxW

    Jika ada Wahana atau Antrian pada matriks, InfoElmt diinisialisasi dengan -1. 
    (Untuk map.txt, tidak ada Wahana atau Antrian)
    (Untuk state.txt, Wahana dan Antrian diisi oleh fungsi pembaca dari file untuk Wahana dan Antrian)

    NOTES:
        Untuk sekarang hanya membaca satu map. Nanti kalau udah diajarin graf, dia dipakai buat baca banyak map kemudian menyusun graf petanya
    */

    FILE *mapFile;
    char* line;
    char temp;
    size_t buffer = 0;
    int len;

    int mapH, mapW, mapID;
    int gateCount = 0;

    POINT gates[10];

    mapFile = fopen(fileName, "r"); 

    while ((len = getline(&line, &buffer, mapFile)) != -1)
    {
        if (*line == "#map")
        {
            // Mulai dari data map
            fscanf(mapFile, "%d %d", &mapH, &mapW);
            NbElement(*M) = mapH;
            for (int i = 0; i < mapH; i++)
            {
                for (int j = 0; j < mapW; j++)
                {
                    // Mengisi 
                    fscanf(mapFile, "%c", &temp);
                    if (temp == 'P')
                    {
                        Player(*M) = MakePOINT(i, j);
                        TypeElmt(*M, i, j) = '-';
                    } else {
                        TypeElmt(*M, i, j) = temp;
                        if (temp == 'v' | temp == '^' | temp == '>' | temp == '<')
                        {
                            gates[gateCount] = MakePOINT(i, j);
                            gateCount++;
                        }
                    }

                    InfoElmt(*M, i, j) = -1;
                }
            }
            fscanf(mapFile, "%d", &mapID);

            for (int i = 0; i < gateCount; i++)
            {
                fscanf(mapFile, "%d",TypeElmt(*M, gates[i].X, gates[i].Y));
            }
            // Akhir dati data map
        }
    }

    free(line);
    return;

}

/* GETTER DAN SETTER */

/* PROSEDUR */
void Move(MAP *M, char X)
{
    POINT P = Player(*M);
    boolean collision = false;
    switch (X)
    {
        //Kalau indeks 0 adalah border pada MAP
        //Tambah case jika bertemu dengan Gate
        //Tambah case jika ingin masuk ke Office
        //Kode masih kurang
        //Nil merupakan definisi element pada map bukan merupakan tipe bangunan atau gate
        //Mengecek dulu tipe lokasi yang akan dijalani, jika bukan bangunan/border POINT P (Lokasi Player) akan digeser
        case 'W' :
        case 'w' :
            if (InfoElmt(*M, Absis(P), (Ordinat(P) - 1)) != Nil)
            //Cek bisa diganti atau engga (int) biar lebih enak diliatnya
            {
                Geser(&P, 0, -1);
            }
            else
            {
                collision = true;
            }
            break;
        case 'A' :
        case 'a' :
            if (InfoElmt(*M, (Absis(P) - 1),  Ordinat(P)) != Nil)
            {
                Geser(&P, -1, 0);
            }
            else
            {
                collision = true;
            }
            break;
        case 'S' :
        case 's' :
            if (InfoElmt(*M, Absis(P), (Ordinat(P) + 1)) != Nil)
            {
                Geser(&P, 0, 1);
            }
            else
            {
                collision = true;
            }
            break;
        case 'D' :
        case 'd' :
            if (InfoElmt(*M, (Absis(P) + 1), Ordinat(P)) != Nil)
            {
                Geser(&P, 1, 0);
            }
            else
            {
                collision = true;
            }
            break;
        default :
            printf("Bukan input yang valid\n"); //Output jika input yang dimasukkan tidak valid
            break;
    }
    Player(*M) = P; //set POINT baru Player pada MAP
    if (collision)
    {
        printf("Anda tertabrak\n"); //Output jika Player menabrak bangunan/border
    }
}

void DrawMap(MAP M)
{
    Player(M);
    int a = Player(M).Y;
    
    for (int i = 0; i < NbElement(M); i++)
    {
        for (int j = 0; j < NbElement(M); j++)
        {
            if (i == Player(M).Y && j == Player(M).X)
            {
                printf("P");
            } else {
                printf("%c", TypeElmt(M, i, j));
            }
        }
        printf("\n");
    }
}

int GetObject(MAP *M, char O)
{
    boolean found = false;
    POINT pointer = MakePOINT(0, 1); 
    
    int count = 3;

    while (!found && count != 0)
    {
        if (TypeElmt(*M, Player(*M).X + pointer.X, Player(*M).Y + pointer.Y) == O)
        {
            found = true;
        } else {
            Putar(&pointer, M_PI / 2);
            count -= 1;
        }
    }

    if (found)
    {
        return (InfoElmt(*M, Player(*M).X + pointer.X, Player(*M).Y + pointer.Y));
    } else {
        return -1;
    }
}