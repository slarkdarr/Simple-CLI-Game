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
    
    CreateEmptyPrioQueue(&antrian, 5);
    CreateEmptyPrioQueueWahana(&inWahana, 10);

    DrawMap(_map, "");
    printInfo(antrian);

    while(main_phase)
    {
        RandomEnqueue(&antrian, _wTCount);

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
                printInfo(antrian);
                
                break;
            case 'a':
            case 'A':
                Move(&_map, 'A', &messageBuffer);
                DrawMap(_map, messageBuffer);
                printInfo(antrian);
                break;
            case 's':
            case 'S':
                if (command.Length == 1)
                {
                    Move(&_map, 'S', &messageBuffer);
                    DrawMap(_map, messageBuffer);
                    printInfo(antrian);
                } else {
                    if (IsKataSama(command, CreateKata("serve")))
                    {
                        int idw; // id wahana yang ingin di serve
                        serve(&antrian, &inWahana, idw);
                    }
                }
                break;
            case 'd':
            case 'D':
                if (command.Length == 1)
                {
                    Move(&_map, 'D', &messageBuffer);
                    DrawMap(_map, messageBuffer);
                    printInfo(antrian);
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
        // Dequeue isi wahana
        boolean deq = true;
        while (deq)
        {
            Pengunjung X;
            DequeueWahana2(&inWahana,&X,_time,&antrian,_wTCount,&deq);
        }
        
        DecrKesabaran(&antrian);
        KesabaranHabis(&antrian);
    }
    return 0;
}


void serve(PrioQueue *antrian, PrioQueueWahana *inWahana, int idw)
{
    if (PengunjungWahana(InfoHead(*antrian), idw, _wTCount))
    {
        Pengunjung X;
        DequeueAntrian(antrian, &X, idw, _wTCount);
    
        EnqueueWahana(inWahana, X, idw, WDurasi(_wahana(idw).current), _time);
        // tambah kapasitas
    
    }
    else
    {
        printf("Pengunjung tidak berencana naik wahana ini\n");
    }
}

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

void printInfo(PrioQueue Antrian)
{
    Kata KName = CreateKata(_name);
    JAM ClosingTime = MakeJAM(21, 0, 0);
    JAM TimeRemaining = DetikToJAM(Durasi(_time, ClosingTime));

    printf("Nama                            :   "); PrintKata(KName); printf("\n"); 
    printf("Money                           :   %d\n", _money); 
    printf("Current Time                    :   "); TulisJAM(_time); printf("\n"); 
    printf("Closing Time                    :   21:0:0\n"); 
    printf("Time Remaining                  :   "); PrintJAM(TimeRemaining); printf("\n");
    PrintAntrian(Antrian, _wCount);
}

void PrintAntrian(PrioQueue Antrian, int nWahana)
{
  printf("Antrian [%d/%d]\n", NBElmtPrioQueue(Antrian), MaxElPrioQueue(Antrian));
  if (!IsEmptyPrioQueue(Antrian))
  {
    PrioQueue printAntrian = Antrian;
    int j = 0;
    while (!IsEmptyPrioQueue(printAntrian))
    {
      Pengunjung X;
      Dequeue(&printAntrian, &X);
      printf("(");
      boolean first = true;
      for (int i =0; i < nWahana; i++)
      {
        if(X.listWahana.W[i] == 1 && first)
        {
          printf("%d",i);
          // i = idwahana
          first = false;
        }
        else if (X.listWahana.W[i] == 1 && !first)
        {
          printf(",%d",i);
          // i = idwahana
        }
        
      }
      printf(") ");
      printf("| kesabaran %d", Kesabaran(X));
      printf("\n\n");
      j++;
    }
  }
}