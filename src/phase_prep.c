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
    DrawMap(_map, "Prep Phase\n");
    //43200 adalah 12 jam
    //while (JLT(PrevNDetik(JCheck, 43200), NextNDetik(JOpening, 43200)))
    PrintAllMaterials(_mlist); // checking buy function
    PrintYourMaterials(); // checking functions
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
                        PrintBuyMaterials(); // Display Material yang dapat dibeli
                        printf("Kuantitas & Material : "); ReadCommand(&nBuy,&buyName);
                        if (SearchForMaterial(_mlist, buyName))
                        {
                            int price = nBuy * SearchForPrice(_mlist, buyName);
                            if ((nBuy > 0) && ((moneyNeeded + price) <= _money))
                            {
                                int indeks = SearchForIndexMaterial(buyName);
                                Push(&Actions, command, indeks, nBuy, Player(_map));
                                timeNeeded = JCheck;
                                moneyNeeded += price;
                                DrawMap(_map, "Buy sukses\n");
                                PrintYourMaterials(); // Cek disini
                            }
                            else
                            {
                                if (nBuy <= 0)
                                {
                                    DrawMap(_map, "Kuantitas tidak valid\n");
                                }
                                else
                                {
                                    DrawMap(_map, "Uang tidak mencukupi\n");
                                }
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
                    if (CheckNearGate(&_map) && CheckObject(&_map, 'O') && CheckObject(&_map, 'W') && CheckObject(&_map, 'w') && CheckObject(&_map, 'A'))
                    {
                        JAM JCheck = NextNDetik(timeNeeded, GetDuration(_actions, command));
                        if (JLT(JCheck, batasTime)) // Mengecek jika waktu cukup untuk command build
                        {
                            PrintBuildableWahana(); // Print Wahana yang dapat dibuat
                            PrintYourMaterials(); // Print Bahan Bangunan yang dimiliki
                            printf("Wahana : "); ReadInput(&buildWahana);
                            if (SearchForBuilding(buildWahana))
                            {
                                int indeks = SearchForIndexBuilding(buildWahana);
                                if (CheckMaterialCukup(indeks) && (moneyNeeded + WBuildPrice(_wType(indeks))) <= _money)
                                {
                                    MaterialQuantity(_mlist, 0) -= WWood(_wType(indeks)); // Mengonsumsi Wood
                                    MaterialQuantity(_mlist, 1) -= WStone(_wType(indeks)); // Mengonsumsi Wood
                                    MaterialQuantity(_mlist, 2) -= WIron(_wType(indeks)); // Mengonsumsi Wood

                                    TypeElmtAtP(_map, Player(_map).X, Player(_map).Y) = 'w'; // w menandakan sedang dibuat, setelah execute akan menjadi W
                                    InfoElmtAtP(_map, Player(_map).X, Player(_map).Y) = indeks; // indeks array //indeks sementara pada map agar tidak bisa dijalani //CEK
                                    Push(&Actions, command, indeks, 1, Player(_map));
                                    Player(_map) = GetObjectP(&_map,'-'); // memindahkan player ke '-' terdekat
                                    DrawMap(_map, messageBuffer);
                                    // moneyNeeded = 
                                    // item langsung dikurang, check item, tambahin ke inventory kalo undo
                                    // time needed ditambah
                                    // money needed ditambah
                                    timeNeeded = JCheck;
                                    moneyNeeded += WBuildPrice(_wType(indeks));
                                }
                                else
                                {
                                    DrawMap(_map, "Bahan bangunan atau uang tidak cukup untuk build\n");
                                }
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
                        DrawMap(_map, "Tidak dapat membangun di depan gerbang atau di dalam Office/dekat office/dekat wahana/dekat Antrian\n");
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
                else if (IsKataSama(command, CreateKata("upgrade")))
                {
                    int cekobjek = GetObject(&_map, 'W');
                    POINT cekpointobjek = GetObjectP(&_map, 'W'); // untuk mengganti W menjadi w sebagai tanda sedang upgrade
                    if (cekobjek != -10)
                    {
                        JAM JCheck = NextNDetik(timeNeeded, GetDuration(_actions, command));
                        if (JLT(JCheck, batasTime)) // Mengecek jika waktu cukup untuk command upgrade
                        {
                            Kata untukUpgrade;
                            WAHANA_PrintCommandUpgrade((_wahana(cekobjek)).current); // Menampilkan opsi upgrade yang tersedia
                            printf("Pilihan Upgrade : ");ReadInput(&untukUpgrade); // Input
                            if (IsKataSama(untukUpgrade, WNama(Left((_wahana(cekobjek)).current)))) // CEK
                            {
                                if (CheckUpgradeCukup(Left((_wahana(cekobjek)).current)) && (moneyNeeded + WBuildPrice(Left((_wahana(cekobjek)).current)) <= _money))
                                //cek jika uang cukup
                                //cek jika cukup untuk upgrade dan langsung mengurangkan bahan bangunan
                                {
                                    MaterialQuantity(_mlist, 0) -= WWood(Left((_wahana(cekobjek)).current));
                                    MaterialQuantity(_mlist, 1) -= WStone(Left((_wahana(cekobjek)).current));
                                    MaterialQuantity(_mlist, 2) -= WIron(Left((_wahana(cekobjek)).current));
                                    Push(&Actions, command, cekobjek, 1, cekpointobjek);
                                    // 1 berarti left
                                    moneyNeeded += WBuildPrice(Left((_wahana(cekobjek)).current));
                                    timeNeeded = JCheck;
                                    TypeElmtAtP(_map, cekpointobjek.X, cekpointobjek.Y) = 'w';
                                    DrawMap(_map, "Upgrade sukses\n");
                                }
                                else
                                {
                                    DrawMap(_map, "Bahan bangunan atau uang tidak cukup\n");
                                }
                            }
                            else if (IsKataSama(untukUpgrade, WNama(Right((_wahana(cekobjek)).current))))
                            {
                                if (CheckUpgradeCukup(Right((_wahana(cekobjek)).current)) && (moneyNeeded + WBuildPrice(Right((_wahana(cekobjek)).current)) <= _money))
                                {
                                    MaterialQuantity(_mlist, 0) -= WWood(Right((_wahana(cekobjek)).current));
                                    MaterialQuantity(_mlist, 1) -= WStone(Right((_wahana(cekobjek)).current));
                                    MaterialQuantity(_mlist, 2) -= WIron(Right((_wahana(cekobjek)).current));
                                    Push(&Actions, command, cekobjek, 0, Player(_map));
                                    // 0 berarti right
                                    moneyNeeded += WBuildPrice(Left((_wahana(cekobjek)).current));
                                    timeNeeded = JCheck;
                                    DrawMap(_map, "Upgrade sukses\n");
                                }
                                else
                                {
                                    DrawMap(_map, "Bahan bangunan atau uang tidak cukup\n");
                                }
                            }
                            else
                            {
                                DrawMap(_map, "Pilihan upgrade tidak terdapat dalam katalog\n");
                            }
                        }
                        else
                        {
                            DrawMap(_map, "Waktu tidak cukup untuk upgrade\n");
                        } 
                    }
                    else
                    {
                        DrawMap(_map, "Tidak ada Wahana untuk di Upgrade\nTunggu satu hari semenjak build untuk mengupgrade Wahana\nTidak bisa mengupgrade wahana yang sedang dalam proses upgrade\n");
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
            default :
                DrawMap(_map, "Perintah tidak diketahui\n");
                break;
        }
    }
    return -1;
}

//ini command yang dijalanin kalo command build, tambahin build ke stack
void Build(MAP *M, POINT P, int i) //indeks pada array wahana
{
    // int x = P.X;
    // int y = P.Y;
    // InfoElmtAtP(*M, x, y) = i;
    // TypeElmtAtP(*M, x, y) = 'W';
    WAHANA_CreateInstance(P, i);
    // Memasukkan Wahana pada Array yang berisi wahana yang terdapat dalam map
    // Mengganti TypeElmtAtP menjadi 'W' dengan Info menunjuk ke array pada wahana
}

// i merupakan indeks wahana upgrade
// lebih dari wTCount-1 tapi kurang dari wTCount*2
void Upgrade(POINT P, int specCommand_, int infoCommand_)
// Mengakses array of Wahana Instance, upgrade wahana instance
// specCommand_ merupakan indeks array of Wahana Instance, infoCommand_ menentukan upgrade ke left atau right
// infoCommand_ == 1 berarti Left, infoCommand_ == 0 berarti Right
{
    TypeElmtAtP(_map, P.X, P.Y) = 'W';
    // ADD Upgrade history disini
    if (infoCommand_)
    {
        (_wahana(specCommand_)).current = Left(_wahana(specCommand_).current);
    }
    else
    {
        (_wahana(specCommand_)).current = Right(_wahana(specCommand_).current);
    }
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
            Upgrade(pointPlayer_, specCommand_, infoCommand_);
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
            Buy(&_mlist, WWood(_wType(specCommand__)), 0); // refund wood
            Buy(&_mlist, WStone(_wType(specCommand__)), 1); // refund stone
            Buy(&_mlist, WIron(_wType(specCommand__)), 2); // refund iron
            *moneyNeeded -= WBuildPrice(_wType(specCommand__));
            // refund bahan bangunan
        }
        else if (IsKataSama(command__, CreateKata("upgrade")))
        {
            if (infoCommand__) // if infoCommand__ == 1 or true maka Left dari current Wahana
            {
                Buy(&_mlist, WWood(Left((_wahana(specCommand__)).current)), 0); // refund wood
                Buy(&_mlist, WStone(Left((_wahana(specCommand__)).current)), 1); // refund stone
                Buy(&_mlist, WIron(Left((_wahana(specCommand__)).current)), 2); // refund iron
                *moneyNeeded -= WBuildPrice(Left((_wahana(specCommand__)).current)); // refund money
            }
            else // infoCommand__ == 0 or false, maka Right dari current Wahana
            {
                Buy(&_mlist, WWood(Right((_wahana(specCommand__)).current)), 0); // refund wood
                Buy(&_mlist, WStone(Right((_wahana(specCommand__)).current)), 1); // refund stone
                Buy(&_mlist, WIron(Right((_wahana(specCommand__)).current)), 2); // refund iron
                *moneyNeeded -= WBuildPrice(Right((_wahana(specCommand__)).current)); // refund money
            }
            POINT posisi = _wahana(specCommand__).position;
            TypeElmtAtP(_map, posisi.X, posisi.Y) = 'W';
            // //pointPlayer pada upgrade merupakan point wahana yang akan di upgrade
            // //mengembalikan ke akar dari tree upgrade
            // //mengurangkan timeneeded
            // //mengganti ID pada x dan y menjadi id sebelumnya
            // // tambah material yang dipake
            // if (specCommand__ > (_wTCount - 1) && specCommand__ < (_wTCount * 2))
            // {
            //     int y = specCommand__ % _wTCount;
            //     // WNama(Left(_wType(specCommand__))); //Ambil info upgrade bahan bangunan, refund (Buy)
            //     // Wnama ganti bahan bangunan yang bakal di refund
            // }
            // else
            // {
            //     //gamungkin kurang dari _wTCount -1
            //     //berarti > wTCount*2
            // }
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
        printf("- "); PrintKata(WNama(_wType(i))); printf("\n");
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
    printf("List Wahana yang dapat dibuat: \n");
    int i;
    for (int i = 0; i < _wTCount; i++)
    {
        printf("    -  "); PrintKata(WNama(_wType(i))); printf("\n");
        printf("       Deskripsi : "); PrintKata(WDeskripsi(_wType(i))); printf("\n");
        printf("       Bahan     :  Wood : %d  Stone : %d  Iron : %d\n", WWood(_wType(i)), WStone(_wType(i)), WIron(_wType(i)));
        printf("       Price     : %d\n", WBuildPrice(_wType(i)));
    }
}

void PrintYourMaterials()
{
    printf("Your Materials: \n");
    printf("Wood : %d\n", MaterialQuantity(_mlist, 0));
    printf("Stone: %d\n", MaterialQuantity(_mlist, 1));
    printf("Iron : %d\n", MaterialQuantity(_mlist, 2));
    // Tidak menggunakan for loop agar indentasi Colon (:) tepat dan enak dilihat
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

boolean CheckMaterialCukup(int i)
// Mengecek jika material cukup dan langsung ke proses build Wahana (langsung mengurangi bahan bangunan yang dimiliki)
// Add gold for building
{
    if (MaterialQuantity(_mlist, 0) >= WWood(_wType(i)) && MaterialQuantity(_mlist, 1) >= WStone(_wType(i)) && MaterialQuantity(_mlist, 2) >= WIron(_wType(i)))
    {
        return true;
    }
    else
    {
        return false;
    }
}

void PrintBuyMaterials()
{
    printf("List Material : \n");
    for (int i = 0; i < 3; i++)
    {
        printf("    -  "); PrintKata(MaterialName(_mlist, i)); printf("  Harga: %d\n", MaterialPrice(_mlist, i));
    }
    // Perlu pake for loop apa gausah ? tentuin nanti
}

boolean CheckUpgradeCukup(tAddress W)
// Add money for upgrade
{
    if (MaterialQuantity(_mlist, 0) >= WWood(W) && MaterialQuantity(_mlist, 1) >= WStone(W) && MaterialQuantity(_mlist, 2) >= WIron(W))
    {
        return true;
    }
    else
    {
        return false;
    }
}