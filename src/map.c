#include "map.h"
#include "point.h"
#include "boolean.h"

#include <stdio.h>
#include <stdlib.h>

/* KONSTRUKTOR */
void MakeEmptyMAP(MAP *M)
{

}

void LoadMap(MAP *M, char* fileName)
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

    FILE *mapFile;
    char line[100];

    int mapH, mapW, mapID;
    int gateCount = 0;

    POINT gates[10];

    mapFile = fopen(fileName, "r"); 
    if (mapFile == NULL)
    {
        printf("FAILED TO READ MAP\n");
        return;
    }

    while (fgets(line, 100, mapFile) != NULL)
    {
        if (line[0] == '#' && line[1] == 'm')
        {
            // fseek(mapFile, ftell(mapFile), SEEK_SET);
            // Mulai dari data map
            fscanf(mapFile, "%d %d %d", &mapID, &mapH, &mapW);
            fscanf(mapFile, "%d", &gateCount);

            int* gateDestinations = malloc(gateCount * sizeof(int));
            for (int i = 0; i < gateCount; i++)
            {
                fscanf(mapFile, "%d", &gateDestinations[i]);
            }
            
            // printf("MAP %d DIMENSIONS %d %d\n", mapID, mapH, mapW);
            // printf("GATE DATA %d, %d %d\n", gateCount, gateDestinations[0], gateDestinations[1]);
            fgets(line, 100, mapFile);

            NBrs(*M) = mapH;
            NKol(*M) = mapW;

            int gate = 0;

            for (int i = 0; i < mapH + 1; i++)
            {
                fgets(line, 100, mapFile);
                
                for (int j = 0; j < mapW; j++)
                {
                    switch(line[j])
                    {
                        case '<':
                        case '>':
                        case '^':
                        case 'V':
                            TypeElmt(*M, i, j) = line[j];
                            InfoElmt(*M, i, j) = gateDestinations[gate];
                            gate++;
                            break;
                        case 'P':
                            Player(*M) = MakePOINT(j, i);
                            TypeElmt(*M, i, j) = '-';
                            InfoElmt(*M, i, j) = -1;
                            break;
                        case '-':
                        case 'O':
                            TypeElmt(*M, i, j) = line[j];
                            InfoElmt(*M, i, j) = -1;
                            break;   
                        default:
                            TypeElmt(*M, i, j) = line[j];
                            InfoElmt(*M, i, j) = 0;                            
                    }
                }
            }

            free(gateDestinations);
            // Akhir dari data map
        }
    }

    fclose(mapFile);
    return;
}

void LoadFullMap(MAP *M, char* fileName, gAddress_V *fullMap)
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

    FILE *mapFile;
    char line[100];

    

    gAddress_V mapsBuffer[25];
    // int mapCount = 0;
    int mapsBufferN = 0;

    gAddress_E edgeBuffer[50];
    // int vertexCount = 0;
    int edgeBufferN = 0;

    int mapH, mapW, mapID;
    int gateCount = 0;

    POINT gates[10];

    mapFile = fopen(fileName, "r"); 
    if (mapFile == NULL)
    {
        printf("FAILED TO READ MAP\n");
        return;
    }

    while (fgets(line, 100, mapFile) != NULL)
    {
        if (line[0] == '#' && line[1] == 'm')
        {
            // fseek(mapFile, ftell(mapFile), SEEK_SET);
            // Mulai dari data map
            // Test(1);
            gAddress_V node = malloc(sizeof(MAP_gVertex));

            fscanf(mapFile, "%d %d %d", &mapID, &mapH, &mapW);
            fscanf(mapFile, "%d", &gateCount);

            int* gateDestinations = malloc(gateCount * sizeof(int));
            int trailStart = edgeBufferN;
            
            // Test(2);
            for (int i = 0; i < gateCount; i++)
            {
                fscanf(mapFile, "%d", &gateDestinations[i]);
                edgeBuffer[edgeBufferN] = malloc(sizeof(MAP_gEdge));
                EdgeDest(edgeBuffer[edgeBufferN]) = gateDestinations[i];
                edgeBufferN++;
            }

            if (edgeBufferN != 0)
            {
                EdgeDest(edgeBuffer[edgeBufferN-1]) = NULL;
            }

            // Test(3);
            
            // printf("MAP %d DIMENSIONS %d %d\n", mapID, mapH, mapW);
            // printf("GATE DATA %d, %d %d\n", gateCount, gateDestinations[0], gateDestinations[1]);
            fgets(line, 100, mapFile);

            NBrs(*M) = mapH;
            NKol(*M) = mapW;

            int gate = 0;

            for (int i = 0; i < mapH + 1; i++)
            {
                fgets(line, 100, mapFile);
                
                for (int j = 0; j < mapW; j++)
                {
                    switch(line[j])
                    {
                        case '<':
                        case '>':
                        case '^':
                        case 'V':
                            TypeElmt(*M, i, j) = line[j];
                            InfoElmt(*M, i, j) = gateDestinations[gate];
                            gate++;
                            break;
                        case 'P':
                            Player(*M) = MakePOINT(j, i);
                            TypeElmt(*M, i, j) = '-';
                            InfoElmt(*M, i, j) = -1;
                            break;
                        case '-':
                        case 'O':
                            TypeElmt(*M, i, j) = line[j];
                            InfoElmt(*M, i, j) = -1;
                            break;   
                        default:
                            TypeElmt(*M, i, j) = line[j];
                            InfoElmt(*M, i, j) = 0;                            
                    }
                }
            }

            printf("%d %d\n", NBrs(*M), NKol(*M));
            // DrawMap(*M, "");

            // Test(4);
            VertexMap(node) = *M;
            VertexId(node) = mapID;
            VertexTrail(node) = edgeBuffer[trailStart];

            mapsBuffer[mapsBufferN] = node;
            mapsBufferN++;

            free(gateDestinations);
            // Akhir dari data map
        }
    }

    int i;
    // Test(5);

    // DrawMap(VertexMap(mapsBuffer[0]), "");
    // printf("%d", mapsBufferN);

    for (i = 0; i < mapsBufferN-1; i++)
    {
        // Test(i);
        VertexNext(mapsBuffer[i]) = mapsBuffer[i+1];
        // Test(i+1);
    }
    VertexNext(mapsBuffer[i]) = NULL;

    // Test(6);
    for (i = 0; i < edgeBufferN; i++)
    {
        EdgeDest(edgeBuffer[i]) = mapsBuffer[(int)EdgeDest(edgeBuffer[i])];
    } 

    *M = VertexMap(mapsBuffer[0]);
    *fullMap = mapsBuffer[0];

    printf("THIS IS ID OF FIRST MAP %d", VertexId(mapsBuffer[0]));

    fclose(mapFile);
    return;
}

/* GETTER DAN SETTER */

/* PROSEDUR */
void Move(MAP *M, char X, char* message[], gAddress_V *fullMap)
{
    POINT P = Player(*M);
    POINT collisionPoint;
    boolean collision = false;
    // DrawMapInfo(*M);
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
            if (InfoElmtAtP(*M, Absis(P), (Ordinat(P) - 1)) < 0)
            //Cek bisa diganti atau engga (int) biar lebih enak diliatnya
            {
                Geser(&P, 0, -1);
            }
            else
            {
                collisionPoint = MakePOINT(Absis(P), (Ordinat(P)-1));
                collision = true;
            }
            break;
        case 'A' :
        case 'a' :
            if (InfoElmtAtP(*M, (Absis(P) - 1),  Ordinat(P)) < 0)
            {
                Geser(&P, -1, 0);
            }
            else
            {
                collisionPoint = MakePOINT(Absis(P)-1, (Ordinat(P)));
                collision = true;
            }
            break;
        case 'S' :
        case 's' :
            if (InfoElmtAtP(*M, Absis(P), (Ordinat(P) + 1)) < 0)
            {
                Geser(&P, 0, 1);
            }
            else
            {
                collisionPoint = MakePOINT(Absis(P), (Ordinat(P)+1));
                collision = true;
            }
            break;
        case 'D' :
        case 'd' :
            if (InfoElmtAtP(*M, (Absis(P) + 1), Ordinat(P)) < 0)
            {
                Geser(&P, 1, 0);
            }
            else
            {
                collisionPoint = MakePOINT(Absis(P)+1, (Ordinat(P)));
                collision = true;
            }
            break;
        default :
            *message = "Bukan input yang valid\n"; //Output jika input yang dimasukkan tidak valid
            break;
    }
    Player(*M) = P; //set POINT baru Player pada MAP
    if (collision)
    {
        if (!IsGate(*M, collisionPoint))
        {
            printf("TYPE %d\n", TypeElmtAtP(*M, collisionPoint.X, collisionPoint.Y));
            printf("INFO %d\n", InfoElmtAtP(*M, collisionPoint.X, collisionPoint.Y));
            *message = "Anda tertabrak\n"; //Output jika Player menabrak bangunan/border
        } else {
            printf("TYPE %d\n", TypeElmtAtP(*M, collisionPoint.X, collisionPoint.Y));
            printf("INFO %d\n", InfoElmtAtP(*M, collisionPoint.X, collisionPoint.Y));
            EnterGate(M, InfoElmtAtP(*M, collisionPoint.X, collisionPoint.Y), fullMap, VertexId(*fullMap));
            *message = "";
        }
        
    } else {
        *message = "";
    }
}

boolean IsGate(MAP M, POINT P)
{
    boolean gate;
    switch(TypeElmtAtP(M, P.X, P.Y))
    {
        case 'V':
        case '^':
        case '>':
        case '<':
            return true;
        default:
            return false;
    }
}

void EnterGate(MAP *M, int destId, gAddress_V *fullMap, int originId)
{
    gAddress_V P = *fullMap;

    printf("WE AT %d\n", VertexId(*fullMap));
    printf("WE WANT %d\n", destId);

    gAddress_E roads = VertexTrail(*fullMap);

    Test(555);
    while (VertexId(EdgeDest(roads)) != destId)
    {
        Test(111);
        roads = NextEdge(roads);
    }

    // fullMap = P;
    VertexMap(*fullMap) = *M;
    *M = VertexMap(EdgeDest(roads));
    *fullMap = EdgeDest(roads);

    Test(666);
    int i = 0;
    int j = 0;
    boolean foundGate = false;

    while (!foundGate && i < NBrs(*M))
    {
        j = 0;
        while(!foundGate && (j < NKol(*M)))
        {
            Test(999);
            if (TypeElmt(*M, i, j) == 'V' || TypeElmt(*M, i, j) == '<' || TypeElmt(*M, i, j) == '>' || TypeElmt(*M, i, j) == '^')
            {
                Test(101010);
                printf("%d %d\n", InfoElmt(*M, i, j), originId);
                if (InfoElmt(*M, i, j) == originId)
                {
                    switch(TypeElmt(*M, i, j))
                    {
                        case 'V':
                            Test(1000);
                            Player(*M) = MakePOINT(j, i-1);
                            break;
                        case '<':
                            Test(2000);
                            Player(*M) = MakePOINT(j+1, i);
                            break;
                        case '>':
                            Test(3000);
                            Player(*M) = MakePOINT(j-1, i);
                            break;
                        case '^':
                            Test(4000);
                            Player(*M) = MakePOINT(j, i+1);
                            break;
                    }
                    TulisPOINT(Player(*M));
                    foundGate = true;
                } 
            }
            j++; 
        }
        i++;
        Test(777);
    }
    return;
}

void DrawMap(MAP M, char message[])
{
    system("cls");
    for (int i = 0; i < NBrs(M); i++)
    {
        for (int j = 0; j < NKol(M); j++)
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

    printf(
    "Legend:\n"
    "A = Antrian\n"
    "P = Player\n"
    "W = Wahana\n"
    "O = Office\n"
    "<, ^, >, V = Gerbang\n");

    printf("%s", message);
}

void DrawMapInfo(MAP M)
{
    printf("\nTHIS IS A DEBUG MAP\nPLAYER AT %d, %d\n", Player(M).X, Player(M).Y);
    
    printf("%d\n", InfoElmt(M, 8, 2));
    printf("SIZE IS %d x %d\n", NBrs(M), NKol(M));

    for (int i = 0; i < NBrs(M); i++)
    {
        for (int j = 0; j < NKol(M); j++)
        {
            if (InfoElmt(M, i, j) < 0)
            {
                if (i == 8 && j == 2)
                {
                    printf("X");
                } else {
                    printf("-");
                }
            } else {
                if (i == 8 && j == 2)
                {
                    printf("Y");
                } else {
                    printf("%d", InfoElmt(M, i, j));
                }
            }
        }
        printf("\n");
    }
}

int GetObject(MAP M, char O)
{
    boolean found = false;
    POINT player = Player(M);
    if (TypeElmtAtP(M, player.X + 1, player.Y) == O)
    {
        return InfoElmtAtP(M, player.X + 1, player.Y);
    }
    else if (TypeElmtAtP(M, player.X, player.Y + 1) == O)
    {
        return InfoElmtAtP(M, player.X, player.Y + 1);
    }
    else if (TypeElmtAtP(M, player.X - 1, player.Y) == O)
    {
        return InfoElmtAtP(M, player.X - 1, player.Y);
    }
    else if (TypeElmtAtP(M, player.X, player.Y - 1) == O)
    {
        return InfoElmtAtP(M, player.X, player.Y - 1);
    }
    else
    {
        return -10; // Digunakan untuk cek jika tidak ada
    }
}

POINT GetObjectP(MAP *M, char O)
{
    boolean found = false;
    POINT player = Player(*M);
    if (TypeElmtAtP(*M, player.X + 1, player.Y) == O)
    {
        return MakePOINT(player.X + 1, player.Y);
    }
    else if (TypeElmtAtP(*M, player.X, player.Y + 1) == O)
    {
        return MakePOINT(player.X, player.Y + 1);
    }
    else if (TypeElmtAtP(*M, player.X - 1, player.Y) == O)
    {
        return MakePOINT(player.X - 1, player.Y);
    }
    else if (TypeElmtAtP(*M, player.X, player.Y - 1) == O)
    {
        return MakePOINT(player.X, player.Y - 1);
    }
    else
    {
        return MakePOINT(0,0); //cek jika 0,0 maka tidak bisa build
    }
}