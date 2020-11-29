#include "phase_main.h"
#include "map.h"
#include "jam.h"
#include "game.h"
#include <stdio.h>
#include <stdlib.h>

int main_phase()
{
    /*
    Pindah alih kontrol ke main phase
    */
    const JAM opentiem = MakeJAM(9, 0, 0);
    const JAM closetiem = MakeJAM(21, 0, 0);
    
    boolean main_phase = true;
    char *messageBuffer;
    Kata command;

    PrioQueue antrian;
    PrioQueueWahana inWahana;
    
    CreateEmptyPrioQueue(&antrian, 5); // Inisialisasi Antrian
    CreateEmptyPrioQueueWahana(&inWahana, 200); // Inisialisasi Penumpang wahana
    RandomEnqueue(&antrian, _wCount);

    DrawMap(_map, "");
    printInfo(antrian);

    while(main_phase)
    {
        Kata Wnama;
        printf("Perintah  ");
        if(TypeElmtAtP(_map, Player(_map).X, Player(_map).Y) == 'O')
        {
            printf("(Masukkan 'office' untuk mengakses office) ");
        }
        printf(": \n");
        ReadInput(&command);
        if (JAMToDetik(_time) >= JAMToDetik(closetiem)) // Langsung pindah ke main phase jika telah melebih batas waktu
        {
            printf("Time exceeded, moving on to prepare phase.\n");
            _time = closetiem;
            return 0;
        }

        switch(command.TabKata[0])
        {
            case 'w':
            case 'W':
                if (command.Length == 1)
                {
                    Move(&_map, 'W', &messageBuffer, &_fullMap);
                    ActionAddTime(_actions, command, &_time);
                    DrawMap(_map, messageBuffer);
                }
                else
                {
                    DrawMap(_map, "Input tidak dikenal\n");
                }
                break;
            case 'a':
            case 'A':
                if (command.Length == 1)
                {
                    Move(&_map, 'A', &messageBuffer, &_fullMap);
                    ActionAddTime(_actions, command, &_time);
                    DrawMap(_map, messageBuffer);
                }
                else
                {
                    DrawMap(_map, "Input tidak dikenal\n");
                }
                break;
            case 's':
            case 'S':
                if (command.Length == 1)
                {
                    Move(&_map, 'S', &messageBuffer, &_fullMap);
                    ActionAddTime(_actions, command, &_time);
                    DrawMap(_map, messageBuffer);
                } else if (IsKataSama(command, CreateKata("save")))
                {
                    GAME_Save();
                    DrawMap(_map, "Game telah disave\n");
                } else {
                    Kata WahanaServe;
                    WahanaServe = ParseKata(command, CreateKata("serve "));
                    if (WahanaServe.Length > 1)
                    {
                        if (GetObject(_map, 'A') != -10 && !IsEmptyPrioQueue(antrian))
                        {
                            int idw = SearchForIndexWahanaFromAntrian(antrian, WahanaServe);
                            if (idw != -10 && idw != -11)
                            {
                                if ((_wahana(idw).status) == true)
                                {
                                    serve(&antrian, &inWahana, idw);
                                    ActionAddTime(_actions, CreateKata("serve"), &_time);

                                    // Mengacak kerusakan dari sebuah wahana ketika aksi serve digunakan
                                    time_t t;
                                    srand((unsigned)time(&t));

                                    int random = rand();

                                    DrawMap(_map, "");
                                    if ((random%10) == 0) // 10% kesempatan untuk rusak
                                    {
                                        printf("Wahana dengan id %d rusak, memulai proses mengeluarkan penumpang\n", idw);
                                        RemoveFromWahana(&antrian, &inWahana, idw, _wCount); // Mengembalikan penumpang yang sedang menaiki wahana dan mengembalikannya ke antrian
                                        _wahana(idw).status = false; // Berfungsi untuk membuat suatu wahana rusak
                                    }
                                }
                                else
                                {
                                    DrawMap(_map, "Wahana yang ingin dinaiki rusak\n");
                                }
                            }
                            else if (idw == -10)
                            {
                                DrawMap(_map, "Wahana tidak ditemukan\n");
                            }
                            else
                            {
                                DrawMap(_map, "Kapasitas wahana penuh\n");
                            }
                        }
                        else
                        {
                            if (IsEmptyPrioQueue(antrian))
                            {
                                DrawMap(_map, "Antrian kosong, tidak ada pengunjung untuk di serve\n");
                            }
                            else
                            {
                                DrawMap(_map, "Harus bersebelahan dengan Antrian untuk serve\n");
                            }
                        }
                    }
                    else
                    {
                        DrawMap(_map, "Input tidak benar\n");
                    }
                }
                break;
            case 'd':
            case 'D':
                if (command.Length == 1)
                {
                    Move(&_map, 'D', &messageBuffer, &_fullMap);
                    ActionAddTime(_actions, command, &_time);
                    DrawMap(_map, messageBuffer);
                } else {
                    if (IsKataSama(command, CreateKata("detail")))
                    {
                        DrawMap(_map, "");
                        detail();
                    }
                }
                break;
            case 'r':
                if (command.Length > 1)
                {
                    if (IsKataSama(command, CreateKata("repair")))
                    {
                        int id = GetObject(_map, 'W');
                        if (id != -10)
                        {
                            if (!_wahana(id).status)
                            {
                                _wahana(id).status = true;
                                ActionAddTime(_actions, command, &_time);
                                _money -= WBuildPrice((_wahana(id)).current) / 2;
                                DrawMap(_map, "Wahana berhasil diperbaiki\n");
                            } else {
                                DrawMap(_map, "Wahana sudah berfungsi dengan baik\n");
                            }
                        } else {
                            DrawMap(_map, "Tidak ada wahana di dekat Anda\n");
                        }
                    }
                }
                break;
            case 'o':
                if (command.Length > 1)
                {
                    if (IsKataSama(command, CreateKata("office")))
                    {
                        if (TypeElmtAtP(_map, Player(_map).X, Player(_map).Y) == 'O')
                        {
                            office_enter();
                        } else {
                            DrawMap(_map, "Anda tidak berada didalam office\n");
                            printInfo(antrian);
                        }
                        
                    }
                }
                break;
            case 'p':
                if (command.Length > 1)
                {
                    if (IsKataSama(command, CreateKata("prepare")))
                    {
                        prepare(antrian, inWahana);
                        main_phase = false;
                        return 0;
                    }
                }
                break;
            case 'q':
                if (command.Length > 1)
                {
                    if (IsKataSama(command, CreateKata("quit")))
                    {
                        return -1;
                    }
                }
            default:
                DrawMap(_map, "Input tidak dikenali\n");
        }
        // Dequeue isi wahana
        boolean deq = true;
        while (deq)
        {
            Penumpang X;
            WahanaToAntrian(&inWahana,&X,_time,&antrian,_wCount,&deq);
            // decr current load
            if (deq)
            {
                int idWahana = CurrWahana(X);
                _wahana(idWahana).currentLoad--;
            }
        }
        
        DecrKesabaran(&antrian); // Mengurangi kesabaran dari tiap pengunjung
        KesabaranHabis(&antrian); // Mengecek jika kesabaran dari suatu pengunjung habis maka akan dikeluarkan dari antrian
        RandomEnqueue(&antrian, _wCount); // Fungsi untuk mengacak masuknya seorang pengunjung ke dalam antrian untuk menunggu di serve
        if (JAMToDetik(_time) < JAMToDetik(closetiem) && JGT(_time, opentiem))
        {
            printInfo(antrian); // Fungsi untuk print info saat Main Phase
        }
        
    }
    return 0;
}


void serve(PrioQueue *antrian, PrioQueueWahana *inWahana, int idw)
// Fungsi untuk serve pengunjung paling depan antrian
{
    if (idw== -10)
        printf("Wahana yang ingin dinaiki sudah penuh\n");
    else
    {
        if (PengunjungWahana(InfoHead(*antrian), idw, _wCount))
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

void detail()
// Prosedur untuk menampilkan detail dari wahana terdekat
{
    /* menampilkan detail dari wahana terdekat */
    int id = GetObject(_map, 'W'); // Fungsi untuk mengambil indeks / InfoElmtAtP dari Wahana terdekat dengan player
    if (id != -10)
    {
        WAHANA_PrintDetails(_wahana(id));
    } else {
        printf("Tidak ada wahana didekat anda\n");
    }
};

void office_enter()
// Prosedur simulasi masuk ke dalam office
{
    /* Pindah alih kontrol ke office */
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
    /*
    Print DETAILS dari wahana hasil selectScreen

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

    if(_wCount != 0)
    {
        int wahanaId = selectWahanaScreen();
        WAHANA_PrintOfficeDetails(_wahana(wahanaId));
    } else {
        printf("Belum ada wahana\n");
    }

    
    return;
};

void office_report()
{
    /*
    Print report dari wahana hasil pilihan selectWahana
    */
    if (_wCount != 0)
    {
        int wahanaId = selectWahanaScreen();
        WAHANA_PrintOfficeReport(_wahana(wahanaId));
    } else {
        printf("Belum ada wahana\n");
    }

    

    return;
};
void office_exit()
{
    /*
    Meninggalkan office, pindah alih kontrol balik ke main phase
    */
    printf("Anda telah meninggalkan office\n");
    return;
};

int selectWahanaScreen()
{
    /*
    Meminta user memberikan indeks (input mulai dari 1, indeks mulai dari 0, offset -1) di _wahana dari wahana yang diinginkan
    */
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
    /*
    Mengosongkan semua wahana dan reset frekuensi digunakan hari ini.
    Juga memperbaiki semua wahana yang rusak
    
    */
    _time = MakeJAM(21, 0, 0);
    DeAlokasi(&antrian);
    DeAlokasiQWahana(&inWahana);

    for (int i = 0; i<_wCount; i++)
    {
        _wahana(i).currentLoad = 0;
        _wahana(i).timesUsedToday = 0;
        _wahana(i).status = true;   
    }
    _day += 1;

    return;
};

void printInfo(PrioQueue Antrian)
{
    /*
    print Info pendamping map
    */
    Kata KName = CreateKata(_name);
    JAM ClosingTime = MakeJAM(21, 0, 0);
    JAM TimeRemaining = DetikToJAM(Durasi(_time, ClosingTime));

    printf("Main Phase Day %d\n", _day);
    printf("Nama                            :   "); PrintKata(KName); printf("\n"); 
    printf("Money                           :   %d\n", _money); 
    printf("Current Time                    :   "); TulisJAM(_time); printf("\n"); 
    printf("Closing Time                    :   21:0:0\n"); 
    printf("Time Remaining                  :   "); PrintJAM(TimeRemaining); printf("\n");
    PrintAntrian(Antrian, _wCount);
}

void PrintAntrian(PrioQueue Antrian, int nWahana)
// Prosedur untuk print antrian untuk dilihat oleh player (kegunaannya adalah untuk serve Antrian saat Main Phase)
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
      printf("   (");
      boolean first = true;
      for (int i =0; i < nWahana; i++)
      {
        if(X.listWahana.W[i] == 1 && first)
        {
          // printf("%d",i); /////
          PrintKata(WNama((_wahana(i)).current));
          // i = idwahana
          first = false;
        }
        else if (X.listWahana.W[i] == 1 && !first)
        {
          printf(", ");
          PrintKata(WNama(_wahana(i).current));
          // printf(",%d",i);
          // i = idwahana
        }
        
      }
      printf(") ");
      printf("| kesabaran %d", Kesabaran(X));
      printf("\n");
      j++;
    }
  }
  printf("\n");
}

int SearchForIndexWahanaFromAntrian(PrioQueue Antrian, Kata W)
// Mencari indeks yang merepresentasikan wahana yang ingin dinaiki pengunjung paling depan antrian saat itu
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
        if (!WAHANA_IsFull(_wahana(i)))
            return i;
        else
        {
            return -11;
        }
    }
    else
    {
        return -10;
    }
}

/* Apabila ada wahana rusak */
void RemoveFromWahana(PrioQueue *Antrian, PrioQueueWahana *QWahana, int idWahana, int nWahana)
{
    /*menghilangkan semua pengunjung didalam wahana yang rusak didalam queue wahana*/
  PrioQueueWahana QNew;

  CreateEmptyPrioQueueWahana(&QNew, MaxElPrioQueue(*QWahana));

  while (!IsEmptyPrioQueueW(*QWahana))
  {
    Penumpang X;
    DequeueWahana(QWahana, &X);
    _wahana(idWahana).currentLoad--;

    if (CurrWahana(X) == idWahana)
      if (!IsFullPrioQueue(*Antrian)) 
        Enqueue(Antrian, Pengunjung(X));

    else EnqueuePenumpang(&QNew, X);
  }

  *QWahana = QNew;
}