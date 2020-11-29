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
    LoadFullMap(&Map(gameInstance), "map.txt", &FullMap(gameInstance));
    RootMap(gameInstance) = FullMap(gameInstance);
    LoadWahanaTypes(&(WahanaType(gameInstance)), "wahana.txt", &WahanaTypeCount(gameInstance));
    LoadMaterial(&MaterialList(gameInstance), "material.txt");
    InitializeArrayAction(&Actions(gameInstance));

    FILE *loadFile;
    char line[100];

    loadFile = fopen("./savefile.txt", "r");


    if (loadFile == NULL)
    {
        printf("FAILED TO READ DATA\n");
        return;
    }

    else
    {
        int jam, menit, detik;

        fscanf(loadFile, "%s", &_name); // <PName>
        fscanf(loadFile, "%d", &_money); // <money>
        fscanf(loadFile, "%d", &_day); // <day>
        fscanf(loadFile, "%d %d %d", &jam, &menit, &detik); // <time>
        
        _time = MakeJAM(jam, menit, detik);
        fscanf(loadFile, "%d", &_wCount);

        // fseek(loadFile, 0, SEEK_CUR );
        
        
        printf("%d", _wCount);

        int i = 0;
        while (fgets(line, 100, loadFile) != NULL)
        {   
            printf("%c\n", line[0]);
            if (line[0] == '#' && line[1] == 'W' && line[2] == 'I')
            {
                printf("haha\n");
                int root, timesUsed, timesUsedToday, totalIncome, size, status, mapId;
                fscanf(loadFile, "%d %d %d %d %d %d %d", &root, &timesUsed, &timesUsedToday, &totalIncome, &size, &status, &mapId);
                // printf("WWWW %d %d %d %d %d %d %d\n", root, timesUsed, timesUsedToday, totalIncome, size, status, mapId);

                WAHANA_Instance newWahana;

                // Test(4);

                newWahana.current = _wType(root);
                // Test(3);
                // printf("H1\n");
                newWahana.upgrades = AlokUpgrade(_wType(root));
                // printf("H1\n");
                // Test(2);
                newWahana.size = size;
                // printf("H1\n");

                newWahana.root = root;
                newWahana.currentLoad = 0;
                newWahana.timesUsed = 0;
                newWahana.timesUsedToday = 0;
                newWahana.status = true;
                newWahana.totalIncome = 0;
                printf("H1\n");

                int x, y;
                for (int j = 0; j < newWahana.size; j++)
                {
                    // printf("%d %d", j, newWahana.size);
                    fscanf(loadFile, "%d %d", &x, &y);
                    newWahana.exPosition[j] = MakePOINT(x,y);
                }

                // printf("POSITION READ %d %d\n", x, y);

                // printf("WWWW %d %d %d %d %d %d %d\n", root, timesUsed, timesUsedToday, totalIncome, size, status, mapId);

                newWahana.position = newWahana.exPosition[0];
                gAddress_V map = _rootmap;
                newWahana.mapId = mapId;

                while(VertexId(map) != mapId)
                {
                    map = VertexNext(map);
                }

                

                for (int j = 0; j < newWahana.size; j++)
                {
                    POINT PP = newWahana.exPosition[j];
                    TypeElmtAtP(VertexMap(map), PP.X, PP.Y) = 'W';
                    InfoElmtAtP(VertexMap(map), PP.X, PP.Y) = i;
                }

                DrawMap(VertexMap(map), "");

                // upgrades?
                char up[50];
                fgets(up, 25, loadFile);
                
                int k = 0;
                while (up[k] != "n" && up[k] != 0 && up[k] != NULL)
                {
                    /* int roott = _wahana(j).root; */
                    if (up[k] == "L")
                    {
                        newWahana.current = Left(newWahana.current);
                    }
                    else if (up[k] == "R")
                    {
                        _wahana(k).current = Right(newWahana.current);
                    }
                    k++;
                }

                _wahana(i) = newWahana;
                // printf("%d %d", i, _wCount);
                i++;
                WAHANA_PrintDetails(newWahana);
            }
            
        }
        
    }
    _map = VertexMap(_rootmap);
};

void GAME_Save()
{
    FILE *savefile;

    savefile = fopen("./savefile.txt", "w");

    fprintf(savefile, "%s\n", _name);
    fprintf(savefile, "%d\n", _money);
    fprintf(savefile, "%d\n", _day);
    fprintf(savefile, "%d %d %d\n\n", _time.HH, _time.MM, _time.SS);

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