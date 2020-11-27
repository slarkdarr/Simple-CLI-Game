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

    PrioQueue antrian;
    PrioQueueWahana inWahana;
    
    DrawMap(_map, "");
    printInfo();

    while(main_phase)
    {
        printf("Perintah : ");
        ReadInput(&command);

        if (Durasi(_time, closetiem) < GetDuration(_actions, command))
        {
            printf("Time exceeded, moving on to prepare phase.\n");
            _time = closetiem;
            return 0;
        } else {
            ActionAddTime(_actions, command, &_time);
        }

        // printf("test\n");
        switch(command.TabKata[0])
        {
            case 'w':
            case 'W':
                Move(&_map, 'W', &messageBuffer);
                DrawMap(_map, messageBuffer);
                printInfo();
                
                break;
            case 'a':
            case 'A':
                Move(&_map, 'A', &messageBuffer);
                DrawMap(_map, messageBuffer);
                printInfo();
                break;
            case 's':
            case 'S':
                if (command.Length == 1)
                {
                    Move(&_map, 'S', &messageBuffer);
                    DrawMap(_map, messageBuffer);
                    printInfo();
                } else {
                    if (IsKataSama(command, CreateKata("serve")))
                    {
                        serve(&antrian, &inWahana);
                    }
                }
                break;
            case 'd':
            case 'D':
                if (command.Length == 1)
                {
                    Move(&_map, 'D', &messageBuffer);
                    DrawMap(_map, messageBuffer);
                    printInfo();
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
                        repair(command);
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
                        main_phase = false;
                    }
                }
            case 'x':
                break;
        }
    }
    return 0;
}


void serve(PrioQueue *antrian, PrioQueueWahana *inWahana)
{
    // Dequeue depan antrian,, Enqueue ke queue wahana
    return;
};

void repair(Kata command)
{
    int id = GetObject(_map, 'W');
    if (id != -10)
    {
        if (!_wahana(id).status)
        {
            _wahana(id).status = true;
            _time = NextNDetik(_time, GetDuration(_actions, command));
        } else {
            printf("Wahana sudah ok\n");
        }
    } else {
        printf("Tidak ada wahana didekat anda\n");
    }
    return;
};

void detail()
{
    int id = GetObject(_map, 'W');
    if (id != -10)
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
        printf("Masukkan perintah (Details / Report / Exit)"); ln;
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
                break;
            case 'R':
                if (O_Command.Length > 1)
                    {
                        if (IsKataSama(O_Command, CreateKata("Report")))
                        {
                            office_report();
                        }
                    }
                    break;
            case 'E':
            if (O_Command.Length > 1)
                {
                    if (IsKataSama(O_Command, CreateKata("Exit")))
                    {
                        office_exit();
                        inOffice = false;
                    }
                }
                break;
            default:
                printf("Command tidak ada");
        }
    }
};

void office_details()
{
    int wahanaId = selectWahanaScreen();
    WAHANA_PrintOfficeDetails(_wahana(wahanaId));

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
    return;
};

void office_report()
{
    int wahanaId = selectWahanaScreen();
    WAHANA_PrintOfficeReport(_wahana(wahanaId));

    return;
};
void office_exit()
{
    printf("YOU WANT TO EXIT EH?\n");
    return;
};

int selectWahanaScreen()
{
    int i;
    printf("Select Wahana\n");
    for (i = 0; i < _wCount; i++)
    {
        printf("\t%d.", i+1);
        PrintKata(WNama(_wahana(i).current));
        printf("\n");
    }
    int select = _wCount+1;

    while (select > _wCount)
    {
        printf("Masukkan nomor ID wahana: ");
        scanf("%d", &select);
    }

    return select-1;
}


void prepare()
{
    _time = MakeJAM(21, 0, 0);
    return;
};

void printInfo()
{
    Kata KName = CreateKata(_name);
    JAM ClosingTime = MakeJAM(21, 0, 0);
    JAM TimeRemaining = DetikToJAM(Durasi(_time, ClosingTime));

    printf("Nama                            :   "); PrintKata(KName); printf("\n"); 
    printf("Money                           :   %d\n", _money); 
    printf("Current Time                    :   "); TulisJAM(_time); printf("\n"); 
    printf("Closing Time                    :   21:0:0\n"); 
    printf("Time Remaining                  :   "); PrintJAM(TimeRemaining); printf("\n");
}