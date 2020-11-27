#include "phase_main.h"
#include "map.h"
#include "jam.h"
#include "game.h"
#include <stdio.h>
#include <stdlib.h>

int main_phase()
{
    const JAM opentiem = MakeJAM(9, 0, 0);
    const JAM closetiem = MakeJAM(21, 0, 0);
    
    boolean main_phase = true;
    char *messageBuffer;
    Kata command;
    
    DrawMap(_map, "");

    while(main_phase)
    {
        printf("Perintah : ");
        ReadInput(&command);
        switch(command.TabKata[0])
        {
            case 'w':
            case 'W':
                Move(&_map, 'W', &messageBuffer);
                DrawMap(_map, messageBuffer);
                break;
            case 'a':
            case 'A':
                Move(&_map, 'A', &messageBuffer);
                DrawMap(_map, messageBuffer);
                break;
            case 's':
            case 'S':
                if (command.Length == 1)
                {
                    Move(&_map, 'S', &messageBuffer);
                    DrawMap(_map, messageBuffer);
                } else {
                    if (IsKataSama(command, CreateKata("serve")))
                    {
                        serve();
                    }
                }
                break;
            case 'd':
            case 'D':
                if (command.Length == 1)
                {
                    Move(&_map, 'D', &messageBuffer);
                    DrawMap(_map, messageBuffer);
                } else {
                    if (IsKataSama(command, CreateKata("detail")))
                    {
                        detail();
                    }
                }
                break;
            case 'r':
                if (command.Length > 1)
                {
                    if (IsKataSama(command, CreateKata("repair")))
                    {
                        repair();
                    }
                }
            case 'o':
                if (command.Length > 1)
                {
                    if (IsKataSama(command, CreateKata("office")))
                    {
                        office_enter();
                    }
                }
            case 'p':
                if (command.Length > 1)
                {
                    if (IsKataSama(command, CreateKata("prepare")))
                    {
                        prepare();
                    }
                }
            case 'x':
                break;
        }
    }


    return 0;
}

void serve();

void repair();

void detail()
{
    int indeks = GetObject(&_map, 'W');
    if (indeks != -10)
    {
        printf("Detail Wahana: \n");
        printf("Nama    : "); PrintKata(WNama(_wahana(indeks).current)); printf("\n");
    }
    else
    {
        DrawMap(_map, "Tidak terdapat wahana di sekitar Anda\n");
    }
}

void office_enter();
void office_details();
void office_report();
void office_exit();

void prepare()
{
    _time = MakeJAM(21, 0, 0);
    return;
};