#include "game.h"

GAME gameInstance;

void GAME_Init()
{
    LoadFullMap(&Map(gameInstance), "map.txt", &FullMap(gameInstance));
    RootMap(gameInstance) = FullMap(gameInstance);
    // printf("THIS IS ID OF FIRST MAP %d", VertexId(VertexNext(_fullMap)));
    LoadWahanaTypes(&(WahanaType(gameInstance)), "wahana.txt", &WahanaTypeCount(gameInstance));
    WahanaCount(gameInstance) = 0;
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
    FILE *loadFile;
    char line[100];

    loadFile = fopen("./savefile.txt", "w");


    if (loadFile == NULL)
    {
        printf("FAILED TO READ DATA\n");
        return;
    }

    else
    {
        int jam, menit, detik;

        fscanf(loadFile, "%s\n", &_name); // <PName>
        fscanf(loadFile, "%d\n", &_money); // <money>
        fscanf(loadFile, "%d\n", &_day); // <day>
        fscanf(loadFile, "%d %d %d\n", &jam, &menit, &detik); // <time>
        
        _time = MakeJAM(jam, menit, detik);

        while (fgets(line, 100, loadFile) != NULL)
        {  
            if (line[0] == "#" && line[1] == "C")
            {
                fscanf(loadFile, "%d\n", &_wCount);
            }
            
            for (int i = 0; i < _wCount; i++)
            {
                if (line[0] == "#" && line[1] == "W" && line[2] == "I")
                {
                    fscanf(loadFile, "%d\n %d %d\n %d\n %d\n %d\n %d\n", &_wahana(i).root, &_wahana(i).timesUsed, &_wahana(i).timesUsedToday, &_wahana(i).totalIncome, &_wahana(i).size, &_wahana(i).status, &_wahana(i).mapId);

                    for (int j = 0; j < _wahana(i).size; j++)
                    {
                        int x, y;
                        fscanf("%d %d\n", &x, &y);
                        _wahana(i).exPosition[j] = MakePOINT(x,y);
                    }

                    // upgrades?
                    char up[50];
                    fgets(up, 25, loadFile);
                    
                    int k = 0;
                    while (up[k] != "n" && up[k] != 0 && up[k] != NULL)
                    {
                        /* int roott = _wahana(j).root; */
                        if (up[k] == "L")
                        {
                            _wahana(k).current = Left(_wahana(k).current);
                        }
                        else if (up[k] == "R")
                        {
                            _wahana(k).current = Right(_wahana(k).current);
                        }
                        k++;
                    }
                }
            }
        }   
    }
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