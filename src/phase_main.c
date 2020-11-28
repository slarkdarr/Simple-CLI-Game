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
        RandomEnqueue(&antrian, _wCount);
        Kata Wnama;
        printf("Perintah : ");
        ReadInput(&command);
        // if (Durasi(_time, closetiem) < GetDuration(_actions, command))
        if (JAMToDetik(_time) >= JAMToDetik(closetiem))
        {
            printf("Time exceeded, moving on to prepare phase.\n");
            _time = closetiem;
            return 0;
        }

        // printf("test\n");
        switch(command.TabKata[0])
        {
            case 'w':
            case 'W':
                Move(&_map, 'W', &messageBuffer);
                ActionAddTime(_actions, command, &_time);
                DrawMap(_map, messageBuffer);
                break;
            case 'a':
            case 'A':
                Move(&_map, 'A', &messageBuffer);
                ActionAddTime(_actions, command, &_time);
                DrawMap(_map, messageBuffer);
                break;
            case 's':
            case 'S':
                if (command.Length == 1)
                {
                    Move(&_map, 'S', &messageBuffer);
                    ActionAddTime(_actions, command, &_time);
                    DrawMap(_map, messageBuffer);
                } else {
                    Kata WahanaServe;
                    // printf("HUHI"); /////
                    WahanaServe = ParseKata(command, CreateKata("serve "));
                    // printf("Huhi2"); /////
                    if (WahanaServe.Length > 1)
                    {
                        if (GetObject(_map, 'A') != -10)
                        {
                            // ListWahana p = ListWP(InfoHead(antrian));
                            // akses elemen ElmtWahana(p,i);
                            // printf("HAHA");
                            int idw = SearchForIndexWahanaFromAntrian(antrian, WahanaServe);
                            printf("idw yang didapat : %d\n", idw); /////
                            if (idw != -10)
                            {
                                serve(&antrian, &inWahana, idw);
                                ActionAddTime(_actions, CreateKata("serve"), &_time);
                                DrawMap(_map, messageBuffer);
                            }
                            else
                            {
                                printf("Wahana tidak ditemukan\n");
                            }
                        }
                        else
                        {
                            printf("Harus bersebelahan dengan Antrian untuk serve\n");
                        }
                    }
                    else
                    {
                        printf("Input tidak benar\n");
                    }
                }
                break;
            case 'd':
            case 'D':
                if (command.Length == 1)
                {
                    Move(&_map, 'D', &messageBuffer);
                    ActionAddTime(_actions, command, &_time);
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
                        prepare(antrian, inWahana);
                        main_phase = false;
                    }
                }
            case 'x':
                return -1;
                break;
        }
        // Dequeue isi wahana
        boolean deq = true;
        while (deq)
        {
            Penumpang X;
            WahanaToAntrian(&inWahana,&X,_time,&antrian,_wCount,&deq);
            // decr current load
            int idWahana = CurrWahana(X);
            _wahana(idWahana).currentLoad--;

        }
        
        DecrKesabaran(&antrian);
        KesabaranHabis(&antrian);
        if (JAMToDetik(_time) < JAMToDetik(closetiem))
        {
            printInfo(antrian);
        }
    }
    return 0;
}


void serve(PrioQueue *antrian, PrioQueueWahana *inWahana, int idw)
{
    if (idw== -10)
        printf("Wahana yang ingin dinaiki sudah penuh\n");
    else
    {
        if (_wahana(idw).status = false)
        {
            printf("Wahana yang ingin dinaiki rusak\n");
        }
        else if (PengunjungWahana(InfoHead(*antrian), idw, _wCount))
        {
            Pengunjung X;
            DequeueAntrian(antrian, &X, idw, _wCount);
            EnqueueWahana(inWahana, X, idw, WDurasi(_wahana(idw).current), _time);
            
            _wahana(idw).currentLoad++;
            _wahana(idw).timesUsed++;
            _wahana(idw).timesUsedToday++;

            _wahana(idw).totalIncome += WHarga(_wahana(idw).current);
            _money += WHarga(_wahana(idw).current);
        }
        else
        {
            printf("Pengunjung tidak berencana naik wahana ini\n");
        }
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
            ActionAddTime(_actions, command, &_time);
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
                printf("Command tidak ada\n");
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

    while (select > _wCount || select <= 0)
    {
        printf("Masukkan nomor ID wahana: ");
        ReadInputInteger(&select);
        if (select <= 0)
        {
            printf("Masukkan tidak valid, silahkan input ulang angka\n");
        }
    }

    return select-1;
}


void prepare(PrioQueue antrian, PrioQueueWahana inWahana)
{
    _time = MakeJAM(21, 0, 0);
    DeAlokasi(&antrian);
    DeAlokasiQWahana(&inWahana);

    for (int i = 0; i<_wCount; i++)
    {
        _wahana(i).currentLoad = 0;
        _wahana(i).timesUsed = 0;
        _wahana(i).timesUsedToday = 0;
        _wahana(i).status = true;   
    }

    // reset antrian, dan antrian wahana?
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
          PrintKata(WNama((_wahana(i)).current));
          // i = idwahana
          first = false;
        }
        else if (X.listWahana.W[i] == 1 && !first)
        {
          PrintKata(WNama(_wahana(i).current));
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
void SearchForIndexWahana(Kata W, int idWahana, Pengunjung *X, int *ret)
/* JANGAN DIPAKE */ /////
{
    boolean found = false;
    int i = idWahana%_wCount;

    if (WAHANA_IsFull(_wahana(idWahana)))
    {   
        do{
            if (IsKataSama(WNama(_wahana(i).current), W) && !WAHANA_IsFull(_wahana(i)))
            {
                found = true;
            }
            else
            {
                i = (i+1)%_wCount;
            }
        } while(i != idWahana);
        
        if (found)
        {
            *ret = i;
            // Ubah tujuan dari si pengunjun
            ListWahana L = ListWP(*X);

            for (int k = 0; k < _wCount; k++)
            {
                if (k==idWahana)
                    ElmtWahana(L, k) = -1;
                if (k==*ret)
                    ElmtWahana(L, k) = 1;
            }
        }
        else
        {
            *ret = -10;
        }
    }

    *ret = idWahana;
}

int SearchForIndexWahanaFromAntrian(PrioQueue Antrian, Kata W)
{
    boolean found = false;
    int i = 0;
    PrioQueue cekAntrian = Antrian;
    Pengunjung Check;
    Dequeue(&cekAntrian, &Check);
    while (!found && i < _wCount)
    {
        if (Check.listWahana.W[i] == 1)
        {
            if (IsKataSama(W, WNama((_wahana(i)).current)))
            {
                found = true;
                PrintKata(WNama((_wahana(i)).current));printf("\n\n\n");
            }
            else
            {
                i++;
            }
        }
        else
        {
            i++;
        }
    }
    if (found)
    {
        return i;
    }
    else
    {
        return -10;
    }
}

/* Apabila ada wahana rusak */
void RemoveFromWahana(PrioQueue *Antrian, PrioQueueWahana *QWahana, int idWahana, int nWahana)
{
  PrioQueueWahana QNew;

  CreateEmptyPrioQueueWahana(&QNew, MaxElPrioQueue(*QWahana));

  while (!IsEmptyPrioQueueW(*QWahana))
  {
    Penumpang X;
    DequeueWahana(QWahana, &X);

    if (CurrWahana(X) == idWahana)
      if (!IsFullPrioQueue(*Antrian)) 
        Enqueue(Antrian, Pengunjung(X));

    else EnqueuePenumpang(&QNew, X);
  }

  *QWahana = QNew;
}
