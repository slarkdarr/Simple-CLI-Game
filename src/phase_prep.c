#include "phase_prep.h"
#include "stacklist.h"
#include "map.h"
#include "jam.h"
#include "game.h"
#include <stdio.h>
#include <stdlib.h>

int preparation_phase() // buat jadi int return -1 kalo keluar prep phase tapi sekalian keluar dari game
{
    boolean prep_phase = true;

    _money; // variable global money (Uang yang dimiliki)

    // ACTION_List actions;
    // ACTION_Init();

    int moneyNeeded = 0; 
    //untuk display uang yang dibutuhkan, sekaligus dibandingkan dengan uang yang dimiliki

    _time; //display current time (prep phase tidak berubah kecuali execute/main)
    //check jam, _time tidak diubah dulu

    JAM batasTime = MakeJAM(12, 0, 1); // Batas time tiap prep phase 12 jam, karena memakai JLT maka dibuat 1 detik lebih lama agar dapat melakukan 12 jam worth of action
    JAM timeNeeded = MakeJAM(0, 0, 0); // Awalnya akan 0, untuk display waktu yang diperlukan

    Kata command;

    int nBuy; // jumlah barang yang dibeli
    Kata buyName; // nama barang

    Kata buildWahana; // setelah build, variable penyimpanan nama wahana yang akan di build

    //int unbuilt = 11; // pas di build awal w kecil, saat di build menjadi W besar indeksnya sementara 11
    int cont = 0;
    char* messageBuffer;
    int total_action = 0;// variable total aksi yang akan dilakukan
    Stack Actions;
    Stack TargetExecution;
    STACK_CreateEmpty(&Actions);
    STACK_CreateEmpty(&TargetExecution);
    DrawMap(_map, "wtf is this\n");
    //43200 adalah 12 jam
    //while (JLT(PrevNDetik(JCheck, 43200), NextNDetik(JOpening, 43200)))
    PrintAllMaterials(_mlist); // checking buy function
    while(prep_phase)
    {
        printf("Perintah : ");
        ReadInput(&command);
        switch(command.TabKata[0])
        {
            case 'w':
            case 'W':
                Move(&_map, 'W', &messageBuffer);
                DrawMap(_map, messageBuffer);
                info_prep(Actions, timeNeeded, moneyNeeded);
                break;
            case 'a':
            case 'A':
                Move(&_map, 'A', &messageBuffer);
                DrawMap(_map, messageBuffer);
                info_prep(Actions, timeNeeded, moneyNeeded);
                break;
            case 's':
            case 'S':
                Move(&_map, 'S', &messageBuffer);
                DrawMap(_map, messageBuffer);
                info_prep(Actions, timeNeeded, moneyNeeded);
                break;
            case 'd':
            case 'D':
                Move(&_map, 'D', &messageBuffer);
                DrawMap(_map, messageBuffer);
                info_prep(Actions, timeNeeded, moneyNeeded);
                break;
            case 'x':
                cont = -1;
                break;
            case 'b':
                if (IsKataSama(command, CreateKata("buy")))
                {
                    JAM JCheck = NextNDetik(timeNeeded, GetDuration(_actions, command)); //Check GetDuration nya bro
                    
                    if (JLT(JCheck, batasTime))
                    {
                        ReadCommand(&nBuy,&buyName);
                        if (SearchForMaterial(_mlist, buyName))
                        {
                            int price = nBuy * SearchForPrice(_mlist, buyName);
                            if ((moneyNeeded + price) <= _money)
                            {
                                int indeks = SearchForIndexMaterial(buyName);
                                Push(&Actions, command, indeks, nBuy, Player(_map));
                                timeNeeded = JCheck;
                                moneyNeeded += price;
                                DrawMap(_map, "Buy sukses\n");
                            }
                            else
                            {
                                DrawMap(_map, "Uang tidak mencukupi\n");
                            }
                        }
                        else
                        {
                            DrawMap(_map, "Material tidak terdapat pada katalog\n");
                        }
                        
                        //if (MoneyNow < TotalPrIce) {
                        //  printf("Uang tidak mencukupi")
                        //}
                        //else {buys things}
                        //jika berhasil maka timeneeded akan ditambahkan
                        
                    }
                    else
                    {
                        DrawMap(_map, "Waktu tidak mencukupi\n");
                    }
                    info_prep(Actions, timeNeeded, moneyNeeded);

                }
                else if (IsKataSama(command, CreateKata("build")))
                {
                    if (CheckNearGate(&_map) && CheckObject(&_map, 'O') && CheckObject(&_map, 'W') && CheckObject(&_map, 'w'))
                    {
                        PrintBuildableWahana(); // Print Wahana yang dapat dibuat
                        JAM JCheck = NextNDetik(timeNeeded, GetDuration(_actions, command));
                        if (JLT(JCheck, batasTime))
                        {
                            ReadInput(&buildWahana);
                            if (SearchForBuilding(buildWahana))
                            {
                                int indeks = SearchForIndexBuilding(buildWahana);
                                TypeElmtAtP(_map, Player(_map).X, Player(_map).Y) = 'w'; // w menandakan sedang dibuat, setelah execute akan menjadi W
                                InfoElmtAtP(_map, Player(_map).X, Player(_map).Y) = indeks; // indeks array
                                Push(&Actions, command, indeks, 1, Player(_map));
                                Player(_map) = GetObjectP(&_map,'-'); // memindahkan player ke '-' terdekat
                                DrawMap(_map, messageBuffer);
                                // moneyNeeded = 
                                // item langsung dikurang, check item, tambahin ke inventory kalo undo
                                // time needed ditambah
                                // money needed ditambah
                                timeNeeded = JCheck;
                            }
                            else
                            {
                                DrawMap(_map, "Wahana tidak terdapat dalam katalog\n");
                            }
                            //build stuff
                            //teleport player using getobjectp(*M, '-')
                            //point player dikasih w nanti pas execute jadi W
                            //Push point player, /*check berada di office atau bukan*/
                            
                        }
                        else
                        {
                            DrawMap(_map, "Waktu tidak mencukupi\n");
                        }
                    }
                    else
                    {
                        DrawMap(_map, "Tidak dapat membangun di depan gerbang atau di dalam Office/dekat office/dekat wahana\n");
                        // printf("Tidak dapat membangun di depan gerbang\n");
                    }
                    info_prep(Actions, timeNeeded, moneyNeeded);
                }
                break;
            case 'u':
                if (IsKataSama(command, CreateKata("undo")))
                {
                    if (!STACK_IsEmpty(Actions))
                    {
                        Undo(&Actions, &timeNeeded, &moneyNeeded);
                        DrawMap(_map, "Undo sukses\n");
                    }
                    else
                    {
                        DrawMap(_map, "Tidak ada aksi untuk di Undo\n");
                    }
                    info_prep(Actions, timeNeeded, moneyNeeded);
                }
                break;
            case 'e':
                if (IsKataSama(command, CreateKata("execute")))
                {
                    toTarget(&Actions, &TargetExecution);
                    Execute(&TargetExecution, &_money);
                    // does executing shit
                    _money -= moneyNeeded;
                    prep_phase = false;
                    SetOpen(&_time);
                    TulisJAM(_time);
                    DrawMap(_map, "Pindah ke main phase\n"); //testing
                    // Set jam ke jam buka, pindah ke main phase
                }
                break;
            case 'm':
                if (IsKataSama(command, CreateKata("main")))
                {
                    while (!STACK_IsEmpty(Actions))
                    {
                        Undo(&Actions, &timeNeeded, &moneyNeeded);
                    }
                    prep_phase = false;
                    SetOpen(&_time);
                    TulisJAM(_time);printf("\n");
                    info_prep(Actions, timeNeeded, moneyNeeded);
                    DrawMap(_map, "Pindah ke main phase\n");
                    printf("testing\n");
                    // Set jam ke jam buka, pindah ke main phase
                }
                break;
        }
    }
    return -1;
}

//ini command yang dijalanin kalo command build, tambahin build ke stack
void Build(MAP *M, POINT P, int i) //indeks pada array wahana
{
    int x = P.X;
    int y = P.Y;
    InfoElmtAtP(*M, x, y) = i;
    TypeElmtAtP(*M, x, y) = 'W';
    //_money -= moneyNeeded;
    // time - timeNeeded, 
}

// i merupakan indeks wahana upgrade
// lebih dari wCount-1 tapi kurang dari wCount*2
void Upgrade(MAP *M, POINT P, int i) //Mengakses array of tree wahana
{
    printf("Upgrade kosong");
}

void Buy(TabMaterial *TabMat, int Jumlah, int Index) //Buys shit
{
    MaterialQuantity(*TabMat, Index) += Jumlah;
    // ((*TabMat).TI[(Index)]).kuantitas += Jumlah;
    // menambahkan kuantitas pada TabMat
}

// sebelum execut pindah stack ke stack target dan lakukan dari aksi awal
void Execute(Stack *S, int *globalCurrency)
{
    Kata command_;
    int specCommand_;
    int infoCommand_;
    POINT pointPlayer_;

    Kata KataBuild = CreateKata("build");
    Kata KataUpgrade = CreateKata("upgrade");
    Kata KataBuy = CreateKata("buy");

    while (!STACK_IsEmpty(*S))
    {
        Pop(S, &command_, &specCommand_, &infoCommand_, &pointPlayer_);
        if (IsKataSama(command_, KataBuild))
        {
            Build(&_map, pointPlayer_, specCommand_);
            // does things
        }
        else if (IsKataSama(command_, KataUpgrade))
        {
            // does things
        }
        else if (IsKataSama(command_, KataBuy))
        {
            Buy(&_mlist, infoCommand_, specCommand_); //adds item
        }
    }
    
}

void toTarget(Stack *S, Stack *Target)
// Stack Target di Create Empty terlebih dahulu
// lalu baru dieksekusi
{
    Kata command_;
    int specCommand_;
    int infoCommand_;
    POINT pointPlayer_;
    while (!STACK_IsEmpty(*S))
    {
        Pop(S, &command_, &specCommand_, &infoCommand_, &pointPlayer_);
        Push(Target, command_, specCommand_, infoCommand_, pointPlayer_);
    }
}

/*void Main(Stack *S)
// Langsung lanjut ke main phase
// Tidak mengeksekusi isi stack
{
    while (!STACK_IsEmpty(*S))
    {
        Undo(S);
    }
}*/

void Undo (Stack *S, JAM *timeNeeded, int *moneyNeeded) // untuk fungsi user undo
{ //money needed dikurangin, time needed juga dikurangin
    Kata command__;
    int specCommand__;
    int infoCommand__;
    POINT pointPlayer__;
    addressStack P = Top(*S);
    if (P == STACK_Nil)
    {
        printf("Tidak ada aksi untuk di undo\n");
    }
    else
    {
        Pop(S, &command__, &specCommand__, &infoCommand__, &pointPlayer__);
        if (IsKataSama(command__, CreateKata("build")))
        {
            int x = pointPlayer__.X;
            int y = pointPlayer__.Y;
            InfoElmtAtP(_map, x, y) = -1;
            TypeElmtAtP(_map, x, y) = '-'; //mengembalikan ke '-'
            // refund bahan bangunan
        }
        else if (IsKataSama(command__, CreateKata("upgrade")))
        {
            //pointPlayer pada upgrade merupakan point wahana yang akan di upgrade
            //mengembalikan ke akar dari tree upgrade
            //mengurangkan timeneeded
            //mengganti ID pada x dan y menjadi id sebelumnya
            // tambah material yang dipake
            if (specCommand__ > (_wTCount - 1) && specCommand__ < (_wTCount * 2))
            {
                int y = specCommand__ % _wTCount;
                // WNama(Left(_wType(specCommand__))); //Ambil info upgrade bahan bangunan, refund (Buy)
                // Wnama ganti bahan bangunan yang bakal di refund
            }
            else
            {
                //gamungkin kurang dari _wTCount -1
                //berarti > wCount*2
            }
        }
        else if (IsKataSama(command__, CreateKata("buy")))
        {
            //mengurangkan money needed,
            //mengurangkan timeneeded
            *moneyNeeded -= infoCommand__ * MaterialPrice(_mlist, specCommand__);
        }
        long waktu = JAMToDetik(*timeNeeded);
        waktu -= GetDuration(_actions, command__);
        *timeNeeded = DetikToJAM(waktu);
    }
}

boolean SearchForBuilding(Kata Building)
//untuk memasukkan perintah build ke stack, cari dulu bangunannya ada atau tidak
{
    int i = 0;
    boolean found = false;
    while (!found && i < _wTCount)
    {
        if (IsKataSama(WNama(_wType(i)), Building))
        {
            found = true;
        }
        else
        {
            i++;
        }
    }
    return found;
}

int SearchForIndexBuilding(Kata Building)
// return Indeks Building pada array setelah dicek true atau tidak (SearchForBuilding)
{
    int i = 0;
    boolean found = false;
    while (!found && i < _wTCount)
    {
        if (IsKataSama(WNama(_wType(i)), Building))
        {
            found = true;
        }
        else
        {
            i++;
        }
    }
    return i;
}

boolean CheckNearGate(MAP *M)
// fungsi untuk cek bisa build, agar tidak build di sebelah gate
{
    if (TypeElmtAtP(*M, (Player(*M).X) - 1, Player(*M).Y) == '<')
    {
        return false;
    }
    else if (TypeElmtAtP(*M, (Player(*M).X + 1), Player(*M).Y) == '>')
    {
        return false;
    }
    else if (TypeElmtAtP(*M, (Player(*M).X), (Player(*M).Y + 1)) == 'V')
    {
        return false;
    }
    else if (TypeElmtAtP(*M, (Player(*M).X), (Player(*M).Y - 1)) == '^')
    {
        return false;
    }
    else
    {
        return true;
    }  
}



// boolean SearchForUpgrade(Kata Upgrade)
// // untuk memasukkan perintah upgrade ke stack, cari dulu upgrade ada atau tidak
// {
//     int i = 0;
//     boolean found = false;
//     while (!found && i < _wTCount)
//     {
//         if (IsKataSama(WNama(_wType(i)), Upgrade))
//         {

//         }
//     }
// }

void info_prep(Stack Action, JAM timeNeeded, int moneyNeeded)
{
    Kata KName = CreateKata(_name); 

    printf("Nama                            :   "); PrintKata(KName); printf("\n"); 
    printf("Money                           :   %d\n", _money); 
    printf("Current Time                    :   21.00\n"); 
    printf("Opening Time                    :   09.00\n");
    printf("Time Remaining                  :   12 jam\n");
    printf("Total aksi yang akan dilakukan  :   %d\n", STACK_NbElmt(Action));
    printf("Total waktu yang dibutuhkan     :   "); TulisJAM(timeNeeded); printf("\n");
    printf("Total uang yang dibutuhkan      :   %d", moneyNeeded); printf("\n");
}

/*
Name: wangkie kumalasari
Money: 1000
Current Time: 21.00
Opening Time: 09.00
Time Remaining: 12 hour(s)
Total aksi yang akan dilakukan: 0
Total waktu yang dibutuhkan: 0
Total uang yang dibutuhkan: 0
*/
int SearchForIndexMaterial(Kata Material)
{
    int i = 0;
    boolean found = false;
    while (!found && i < _wTCount)
    {
        if (IsKataSama(Material, MaterialName(_mlist, i)))
        {
            found = true;
        }
        else
        {
            i++;
        }
    }
    return i;
}

void PrintNamaWahana()
{
    printf("List nama wahana:\n");
    for (int i=0; i<_wTCount;i++)
    {
        printf("- "); PrintKata(WNama(_wType(i)));
    }
}

void PrintUpgradeWahana(int i) //i adalah indeks base build
// Digunakan untuk display list upgrade wahana
{
    Kata UpgradeOne = WNama(Left(_wType(i))); //tanya govin bener apa engga
    Kata UpgradeTwo = WNama(Right(_wType(i)));
    printf("Upgrade menjadi : \n");
    printf("- "); PrintKata(UpgradeOne);
    printf("- "); PrintKata(UpgradeTwo);
    printf("  Pilihan: ");
}

void PrintBuildableWahana()
// Display Wahana yang dapat di build
{
    int i;
    for (int i = 0; i < _wTCount; i++)
    {
        WAHANA_PrintInfo(_wType(i));
    }
}

// boolean CheckOffice(MAP *M)
// // Mengecek jika dalam office atau dekat office
// // Returns true jika dekat atau dalam office
// {
//     return (POINT_EQ(GetObjectP(M, 'O'), MakePOINT(0, 0)) || POINT_EQ(MakePOINT(Player(*M).X, Player(*M).Y), MakePOINT(12, 5)));
// }

// boolean CheckOffice(MAP *M)
// // Mengecek jika dalam office atau dekat office
// // Returns true jika dekat atau dalam office
// {
//     if (TypeElmtAtP(*M, (Player(*M).X) - 1, Player(*M).Y) == 'O')
//     {
//         return false;
//     }
//     else if (TypeElmtAtP(*M, (Player(*M).X + 1), Player(*M).Y) == 'O')
//     {
//         return false;
//     }
//     else if (TypeElmtAtP(*M, (Player(*M).X), (Player(*M).Y + 1)) == 'O')
//     {
//         return false;
//     }
//     else if (TypeElmtAtP(*M, (Player(*M).X), (Player(*M).Y - 1)) == 'O')
//     {
//         return false;
//     }
//     else if (POINT_EQ(MakePOINT(Player(*M).X, Player(*M).Y), MakePOINT(12, 5)))
//     {
//         return false;
//     }
//     else
//     {
//         return true;
//     }  
// }

boolean CheckObject(MAP *M, char C)
// Mencari jika object dengan TypeElmt char C ada di dekat atau pada player
{
    if (TypeElmtAtP(*M, (Player(*M).X) - 1, Player(*M).Y) == C)
    {
        return false;
    }
    else if (TypeElmtAtP(*M, (Player(*M).X + 1), Player(*M).Y) == C)
    {
        return false;
    }
    else if (TypeElmtAtP(*M, (Player(*M).X), (Player(*M).Y + 1)) == C)
    {
        return false;
    }
    else if (TypeElmtAtP(*M, (Player(*M).X), (Player(*M).Y - 1)) == C)
    {
        return false;
    }
    else if (TypeElmtAtP(*M, (Player(*M).X - 1), (Player(*M).Y - 1)) == C)
    {
        return false;
    }
    else if (TypeElmtAtP(*M, (Player(*M).X - 1), (Player(*M).Y + 1)) == C)
    {
        return false;
    }
    else if (TypeElmtAtP(*M, (Player(*M).X + 1), (Player(*M).Y - 1)) == C)
    {
        return false;
    }
    else if (TypeElmtAtP(*M, (Player(*M).X + 1), (Player(*M).Y + 1)) == C)
    {
        return false;
    }
    else if (TypeElmtAtP(*M, (Player(*M).X), (Player(*M).Y)) == C)
    {
        return false;
    }
    else
    {
        return true;
    }  
}
