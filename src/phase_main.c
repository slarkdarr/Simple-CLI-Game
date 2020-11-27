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
    int id = GetObject(_map, 'W');
    if (id != -1)
    {
        WAHANA_PrintDetails(_wahana(id));
    } else {
        printf("Tidak ada wahana didekat anda");
    }
};

void office_enter()
{
    boolean inOffice = true;
    Kata O_Command;

    while (inOffice)
    {
        printf("Masukkan perintah (Details / Report / Exit)");
        ReadInput(&O_Command);

        switch(O_Command.TabKata[0])
        {
            case 'D':
                if (O_Command.Length > 1)
                {
                    if (IsKataSama(O_Command, CreateKata("Details")))
                    {
                        office_details();
                    }
                }
            case 'R':
                if (O_Command.Length > 1)
                    {
                        if (IsKataSama(O_Command, CreateKata("Report")))
                        {
                            office_report();
                        }
                    }
            case 'E':
            if (O_Command.Length > 1)
                {
                    if (IsKataSama(O_Command, CreateKata("Exit")))
                    {
                        office_exit();
                    }
                }
        }
    }
};

void office_details();
void office_report();
void office_exit();

void prepare()
{
    _time = MakeJAM(21, 0, 0);
    return;
};