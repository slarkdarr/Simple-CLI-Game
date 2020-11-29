#include "../wahana/wahana.h"
#include "../mesinkata/mesinkata.h"
#include "../game/game.h"
#include "../point/point.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    GAME_Init();
    WAHANA_Instance Wahana;
    Wahana.current = _wType(0);
    Wahana.position = MakePOINT(0, 0);
    Wahana.upgrades = AlokUpgrade(_wType(0));
    Wahana.size = 1;
    Wahana.exPosition[0] = MakePOINT(0, 0);
    Wahana.root = 0;
    Wahana.currentLoad = 0;
    Wahana.timesUsed = 0;
    Wahana.timesUsedToday = 0;
    Wahana.status = true;
    Wahana.totalIncome = 0;
    // Test upgrade history
    for (int i = 0; i < 6; i++)
    {
        if (i % 2 == 0)
        {
            printf("Adding false\n");
            AddToUpgradeHistory(&Wahana.upgrades, false);
        }
        else
        {
            printf("Adding true\n");
            AddToUpgradeHistory(&Wahana.upgrades, true);
        }
    }
    // Test upgrade
    upgrade P = Wahana.upgrades;
    while (P != NULL)
    {
        if (UpgradeInfo(P))
        {
            printf("true\n");
        }
        else
        {
            printf("false\n");
        }
        P = NextUpgrade(P);
    }

    //gcc -o driverlistlinier driverlistlinier.c ../wahana/wahana.c ../mesinkata/mesinkar.c ../mesinkata/mesinkata.c ../point/point.c ../game/game.c ../jam/jam.c ../map/map.c ../arrayaction/arrayaction.c ../materials/materials.c -lm 
    //.\driverlistlinier.c
    return 0;
}