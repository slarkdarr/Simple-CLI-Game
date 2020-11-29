#include "../wahana.h"
#include "../mesinkata.h"
#include "../game.h"
#include "../point.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    WAHANA_Instance Wahana;
    tAddress wahanaType[10];
    LoadWahanaTypes(&wahanaType[10], "../wahana.txt", 10);
    Wahana.upgrades = AlokUpgrade(_wType(1));
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



    return 0;
}