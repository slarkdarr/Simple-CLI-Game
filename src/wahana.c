#include "wahana.h"
#include "mesinkata.h"
#include "map.h"
#include "game.h"

#include <stdio.h>
#include <stdlib.h>

void LoadWahanaTypes(tAddress *wahanaTypes[], char *fileName, int* Wcount)
{
    /*
    Membaca data map dari file mulai dari penanda #map. 
    Bisa untuk membaca dari file map.txt dan state.txt
    FORMAT (untuk setiap tipe wahana):
        #wt 
        harga
        kapasitas
        durasi
        jumlah upgrade
        <id left> <id right> <elcount>
        nama
        deskripsi

        #wu 
        harga
        kapasitas
        durasi
        biaya upgrade
        <id left> <id right>
        nama
        deskripsi

        KETERANGAN:
        id sesuai urutan kemunculan (wt adalah 0)
        Tiap tipe wahana diawali dengan #wt
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

    int count = 0;

    while(fgets(line, 100, wtFile) != NULL && count < 10)
    {
        if (line[0] == '#' && line[1] == 'w' && line[2] == 't')
        {
            tAddress nodes[25];
            char name[25], desc[50];
            int cap, dur, price, left, right, upprice, elcount;
            int wood, stone, iron, buildprice; // bahan bangunan yang diperlukan untuk membuat wahana

            fscanf(wtFile, "%d\n %d\n %d\n %d\n %d %d %d %d\n %d %d %d\n", &price, &cap, &dur, &upprice, &wood, &stone, &iron, &buildprice, &left, &right, &elcount);
            fgets(name, 25, wtFile);
            fgets(desc, 50, wtFile);

            // printf(" %s %s %d\n %d\n %d\n %d\n %d %d %d\n\n", name, desc, price, cap, dur, upprice, left, right, elcount);
            nodes[0] = WAHANAT_Alokasi(name, price, cap, dur, desc, left, right, wood, stone, iron, buildprice); // tambah buat bahan bangunan

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
                    fscanf(wtFile, "%d\n %d\n %d\n %d\n %d %d %d %d\n %d %d\n", &price, &cap, &dur, &upprice, &wood, &stone, &iron, &buildprice, &left, &right);
                    fgets(name, 25, wtFile);
                    fgets(desc, 50, wtFile);

                    // printf("%d\n %s %s %d\n %d\n %d\n %d\n %d %d\n", i, name, desc, price, cap, dur, upprice, left, right);

                    nodes[i] = WAHANAT_Alokasi(name, price, cap, dur, desc, left, right, wood, stone, iron, buildprice); // tambah buat bahan bangunan
                }

                line[0] = 'x';
            }

            for (int i = 0; i < elcount; i++) // -1
            {
                if (Left(nodes[i]) == -1)
                {
                    Left(nodes[i]) = WAHANA_Nil;
                } else {
                    Left(nodes[i]) = nodes[(int)Left(nodes[i])];
                }

                if (Right(nodes[i]) == -1)
                {
                    Right(nodes[i]) = WAHANA_Nil;
                } else {
                    Right(nodes[i]) = nodes[(int)Right(nodes[i])];
                }

                // WAHANA_PrintInfo(nodes[i]);
                // printf("DONE\n\n");
            }

            // printf("HA\n");
            *(wahanaTypes+count) = nodes[0];
            count++;
        }

        *Wcount = count;
    }
    return;
}
// edited buat naro wood, stone, iron
tAddress WAHANAT_Alokasi(char name[], int price, int cap, int dur, char desc[], int left, int right, int wood, int stone, int iron, int buildprice)
{
    // nama
    // harga
    // kapasitas
    // durasi
    // deskripsi
    // biaya upgrade
    // <id left> <id right>
    tAddress result = malloc(sizeof(WAHANA_UpgradeTree));

    Akar(result) = WAHANAT_Create(CreateKata(name), price, cap, dur, CreateKata(desc), wood, stone, iron, buildprice);
    Right(result) = right;
    Left(result) = left;

    return result;
};
// edited buat naro wood, stone, iron
WAHANA_ElType WAHANAT_Create(Kata name, int price, int cap, int dur, Kata desc, int wood, int stone, int iron, int buildprice)
{
    WAHANA_ElType result;

    WahanaNama(result) = name;
    WahanaHarga(result) = price;
    WahanaKapasitas(result) = cap;
    WahanaDurasi(result) = dur;
    WahanaDeskripsi(result) = desc;
    WahanaWood(result) = wood;
    WahanaStone(result) = stone;
    WahanaIron(result) = iron;
    WahanaBuildPrice(result) = buildprice;

    return result;
};

void WAHANA_PrintInfo(tAddress wahanaT)
{
    WAHANA_ElType wahana = Akar(wahanaT);

    printf("NAME       : ");
    PrintKata(WahanaNama(wahana));
    printf("\n");

    printf("DESC       : ");
    PrintKata(WahanaDeskripsi(wahana));
    printf("\n");

    printf(
        "PRICE      : %d\n"
        "CAP        : %d\n"
        "DURATION   : %d\n",
        WahanaHarga(wahana), WahanaKapasitas(wahana), WahanaDurasi(wahana)
        );

    printf("LEFT       : ");
    // printf("%d", Right(wahanaT));
    if (Left(wahanaT) != WAHANA_Nil)
    {
        PrintKata(WahanaNama(Akar(Left(wahanaT))));
    } else {
        printf("NONE");
    }
    printf("\n");
    

    printf("RIGHT      : ");
    if (Right(wahanaT) != WAHANA_Nil)
    {
        PrintKata(WahanaNama(Akar(Right(wahanaT))));
    } else {
        printf("NONE");
    }
    printf("\n");
    // testing purposes buat bahan bangunan
    printf("Bahan bangunan yang diperlukan\n");
    printf("Wood : %d\n", WWood(wahanaT));
    printf("Stone: %d\n", WStone(wahanaT));
    printf("Iron : %d\n", WIron(wahanaT));
    printf("Price: %d\n", WBuildPrice(wahanaT));
    printf("\n");
    printf("\n");
}

void WAHANA_CreateInstance(POINT location, int type)
{
    // tAddress current; // sekarang wahananya apa
    // POINT position; // letak wahana, kalau jadi ada ukuran, make list of position

    // boolean upgradeHistory[25]; // Upgrade history disimpen pake List Implementasi Array, true = Left, false = right      
    // int upgradeHistoryNEff; // NEff dari upgradeHistory

    // int root; // id tipe awal wahananya apa
    // int currentLoad; // sekarang isinya ada berapa orang
    
    // int timesUsed; // total dipakai berapa kali
    // int timesUsedToday; // hari ini dipakai berapa kali
    WAHANA_Instance newWahana;

    newWahana.current = _wType(type);
    newWahana.position = location;
    newWahana.upgradeHistoryNEff = 0;
    newWahana.root = type;
    newWahana.currentLoad = 0;
    newWahana.timesUsed = 0;
    newWahana.timesUsedToday = 0;
    newWahana.status = true;
    newWahana.totalIncome = 0;
    
    TypeElmtAtP(_map, location.X, location.Y) = 'W';
    InfoElmtAtP(_map, location.X, location.Y) = _wCount;
    _wahana(_wCount) = newWahana;
    _wCount += 1;
    
    return;
}; 

void WAHANA_PrintUpgrade(tAddress W)
// Untuk print Upgrade(s)
{
    printf("[");
    if (Left(W) != WAHANA_Nil)
    {
        PrintKata(WNama(Left(W)));
        if (Right(W) != WAHANA_Nil)
        {
            printf(", ");
        }
    }
    if (Right(W) != WAHANA_Nil)
    {
        PrintKata(WNama(Right(W)));
    }
    printf("]");
}

void WAHANA_PrintCommandUpgrade(tAddress W)
{
    // Cek IsOneELmtTree kalo isOneElmtTree ga print apa apa
    printf("List Upgrade : \n");
    if (Left(W) != WAHANA_Nil)
    {
        printf("    -  "); PrintKata(WNama(Left(W))); printf("\n");
        printf("       Bahan : Wood : %d  Stone : %d  Iron : %d\n", WWood(Left(W)), WStone(Left(W)), WIron(Left(W)));
        printf("       Price : %d\n", WBuildPrice(Left(W)));
    }
    if (Right(W) != WAHANA_Nil)
    {
        printf("    -  "); PrintKata(WNama(Right(W))); printf("\n");
        printf("       Bahan : Wood : %d  Stone : %d  Iron : %d\n", WWood(Right(W)), WStone(Right(W)), WIron(Right(W)));
        printf("       Price : %d\n", WBuildPrice(Right(W)));
    }
    // Kenapa ke print?
}


void WAHANA_PrintDetails(WAHANA_Instance W)
{
    printf("Nama        : ");
    PrintKata(WNama(W.current));
    printf("\n");

    printf("Lokasi      : ");
    TulisPOINT(W.position);

    printf("Upgrade(s)  : [");
    if (Left(W.current) != WAHANA_Nil)
    {
        PrintKata(WNama(Left(W.current)));
        
        if (Right(W.current) != WAHANA_Nil)
        {
            printf(",");
        }
    }

    

    if (Right(W.current) != WAHANA_Nil)
    {
        PrintKata(WNama(Right(W.current)));
    }
    printf("]\n");

    printf("History     : ");
    WAHANA_PrintHistory(W);
    printf("\n");
    
    printf("Status      : ");
    if (W.status)
    {
        printf("Berfungsi\n");
    } else {
        printf("Tidak Berfungsi\n");
    }
}


boolean WAHANA_TREE_IsOneElmt(tAddress W)
{
    return (Right(W) == WAHANA_Nil && Left(W) == WAHANA_Nil);
}

boolean WAHANA_TREE_IsBiner(tAddress W)
{
    return (Right(W) != WAHANA_Nil && Left(W) != WAHANA_Nil);
}

boolean WAHANA_TREE_IsUnerLeft(tAddress W)
{
    return (Left(W) != WAHANA_Nil && Right(W) == WAHANA_Nil);
}

boolean WAHANA_TREE_IsUnerRight(tAddress W)
{
    return (Right(W) != WAHANA_Nil && Left(W) == WAHANA_Nil);
}

void WAHANA_PrintCommandUpgradeLeft(tAddress W)
{
    printf("List Upgrade : \n");
    if (Left(W) != WAHANA_Nil)
    {
        printf("    -  "); PrintKata(WNama(Left(W))); printf("\n");
        printf("       Bahan : Wood : %d  Stone : %d  Iron : %d\n", WWood(Left(W)), WStone(Left(W)), WIron(Left(W)));
        printf("       Price : %d\n", WBuildPrice(Left(W)));
    }
}

void WAHANA_PrintCommandUpgradeRight(tAddress W)
{
    printf("List Upgrade : \n");
    if (Right(W) != WAHANA_Nil)
    {
        printf("    -  "); PrintKata(WNama(Right(W))); printf("\n");
        printf("       Bahan : Wood : %d  Stone : %d  Iron : %d\n", WWood(Right(W)), WStone(Right(W)), WIron(Right(W)));
        printf("       Price : %d\n", WBuildPrice(Right(W)));
    }
}

void WAHANA_PrintOfficeDetails(WAHANA_Instance W)
{
    /*
    DETAILS
    Nama
    Tipe
    Harga
    Lokasi
    Deskripsi
    Kapasitas
    History Upgrade
    Durasi
    Ukuran
    */
    printf("Nama            : ");
    PrintKata(WNama(W.current)); ln;

    printf("Tipe            : ");
    PrintKata(WNama(_wType(W.root))); ln;

    printf("Harga           : %d\n", WHarga(W.current));

    printf("Lokasi          : ");
    TulisPOINT(W.position);

    printf("Deskripsi       : ");
    PrintKata(WDeskripsi(W.current)); ln;

    printf("Kapasitas       : %d\n", WKapasitas(W.current));
    
    printf("History         : ");
    WAHANA_PrintHistory(W); ln;

    printf("Durasi          : %d", WDurasi(W.current)); ln;
    
    printf("Ukuran          : 1\n");
    
}

void WAHANA_PrintOfficeReport(WAHANA_Instance W)
{
    PrintKata(WNama(W.current)); ln;
    printf("Dinaiki sebanyak %d kali (total), %d hari ini", W.timesUsed, W.timesUsedToday); ln;
    printf("Penghasilan:"); ln;
    printf("\tTotal\t%d", W.totalIncome); ln;
    printf("\tHari Ini\t%d", W.timesUsedToday*WHarga(W.current)); ln;
}

void WAHANA_PrintHistory(WAHANA_Instance W)
{
    int i; 
    tAddress pointer;

    pointer = _wType(W.root);
    PrintKata(WNama(pointer));

    if (W.upgradeHistoryNEff > 0)
    {
        for(i = 1; i <= W.upgradeHistoryNEff; i++)
        {
            printf(" -> ");
            if (W.upgradeHistory[i])
            {
                pointer = Left(pointer);    
            } else {
                pointer = Right(pointer);
            }
            PrintKata(WNama(pointer));
        }
    }
}

boolean WAHANA_IsFull (WAHANA_Instance W)
{
    return (WKapasitas(W.current) == W.currentLoad);
}