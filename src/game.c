#include "game.h"

GAME gameInstance;

void GAME_Init()
{
    LoadFullMap(&Map(gameInstance), "map.txt", &FullMap(gameInstance));
    RootMap(gameInstance) = FullMap(gameInstance);
    // printf("THIS IS ID OF FIRST MAP %d", VertexId(VertexNext(_fullMap)));
    LoadWahanaTypes(&(WahanaType(gameInstance)), "wahana.txt", &WahanaTypeCount(gameInstance));
    WahanaCount(gameInstance) = 0;
    AntrianData(gameInstance) = 0;
    Money(gameInstance) = 0;
    Time(gameInstance) = MakeJAM(21, 0, 0);
    Day(gameInstance) = 1;
    LoadMaterial(&MaterialList(gameInstance), "material.txt");
    InitializeArrayAction(&Actions(gameInstance));
    _money = 10000;

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

    // printf("OUTSIDE WAHANA.C\n");
    // WAHANA_PrintInfo(WahanaType(gameInstance)[0]);
    // WAHANA_PrintInfo(WahanaType(gameInstance)[1]);   
}

void GAME_Load()
{
    
};

void GAME_Save()
{
    FILE *savefile;

    savefile = fopen("./savefile.txt", "w");

    fprintf(savefile, "%s\n", _name);
    fprintf(savefile, "%d\n", _money);
    fprintf(savefile, "%d\n", _day);
    fprintf(savefile, "%d %d %d\n\n", _time.HH, _time.MM, _time.SS);

    fprintf(savefile, "#C\n");
    fprintf(savefile, "%d\n", _wCount);

    for (int i = 0; i < _wCount; i++)
    {
        fprintf(savefile, "#WI\n");
        fprintf(savefile, "%d\n", _wahana(i).root);
        fprintf(savefile, "%d %d\n", _wahana(i).timesUsed, _wahana(i).timesUsedToday);
        fprintf(savefile, "%d\n", _wahana(i).totalIncome);
        fprintf(savefile, "%d\n", _wahana(i).size);
        if (_wahana(i).status)
        {
            fprintf(savefile, "1\n");
        } else {
            fprintf(savefile, "0\n");
        }

        fprintf(savefile, "%d\n",_wahana(i).mapId);

        for (int j = 0; j < _wahana(i).size; j++)
        {
            fprintf(savefile, "%d %d\n", _wahana(i).exPosition[j].X, _wahana(i).exPosition[j].Y);
        }

        upgrade upgrades = _wahana(i).upgrades;
        tAddress P = _wType(_wahana(i).root);
        upgrades = NextUpgrade(upgrades);

        while (upgrades != NULL)
        {
            if(IsKataSama(UpgradeName(upgrades), WNama(Left(P))))
            {
                fprintf(savefile, "L");
                P = Left(P);
            } else if (IsKataSama(UpgradeName(upgrades), WNama(Right(P)))){
                fprintf(savefile, "R");
                P = Right(P);
            }
            upgrades = NextUpgrade(upgrades);
        }
        fprintf(savefile, "\n\n");
    }

    fclose(savefile);
    return;
};