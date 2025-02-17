#include "phase_prep.h"
#include "stacklist.h"
#include "map.h"
#include "game.h"
#include <stdio.h>
#include <stdlib.h>

void preparation_phase()
{
    boolean prep_phase = true;

    _money; // variable global money (Uang yang dimiliki)

    ACTION_List actions;
    ACTION_Init();

    int moneyNeeded = 0; 
    //untuk display uang yang dibutuhkan, sekaligus dibandingkan dengan uang yang dimiliki

    _time; //display current time (prep phase tidak berubah kecuali execute/main)
    //check jam, _time tidak diubah dulu

    JAM batasTime = MakeJAM(12, 0, 0); // Batas time tiap prep phase 12 jam
    JAM timeNeeded = MakeJAM(0, 0, 0); // Awalnya akan 0, untuk display waktu yang diperlukan

    Kata command;

    int nBuy; // jumlah barang yang dibeli
    Kata buyName; // nama barang

    Kata buildWahana; // setelah build, variable penyimpanan nama wahana yang akan di build

    int unbuilt = 11; // pas di build awal w kecil, saat di build menjadi W besar indeksnya sementara 11
    int cont = 0;
    char* messageBuffer;
    int total_action = 0;// variable total aksi yang akan dilakukan
    Stack Actions;
    Stack TargetExecution;
    STACK_CreateEmpty(&Actions);
    STACK_CreateEmpty(&TargetExecution);

    //43200 adalah 12 jam
    //while (JLT(PrevNDetik(JCheck, 43200), NextNDetik(JOpening, 43200)))
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
                break;
            case 'a':
            case 'A':
                Move(&_map, 'A', &messageBuffer);
                DrawMap(_map, messageBuffer);
                break;
            case 's':
            case 'S':
                Move(&_map, 'S', &messageBuffer);
                DrawMap(_map, messageBuffer);
                break;
            case 'd':
            case 'D':
                Move(&_map, 'D', &messageBuffer);
                DrawMap(_map, messageBuffer);
                break;
            case 'x':
                cont = -1;
                break;
            case 'b':
                if (IsKataSama(command, CreateKata("buy")))
                {
                    JAM JCheck = NextNDetik(timeNeeded, GetDuration(command)); //Check GetDuration nya bro
                    
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
                            }
                            else
                            {
                                printf("Uang tidak mencukupi\n");
                            }
                        }
                        else
                        {
                            printf("Material tidak terdapat pada katalog\n");
                        }
                        
                        //if (MoneyNow < TotalPrIce) {
                        //  printf("Uang tidak mencukupi")
                        //}
                        //else {buys things}
                        //jika berhasil maka timeneeded akan ditambahkan
                        
                    }
                    else
                    {
                        printf("Waktu tidak mencukupi\n");
                    }
                }
                else if (IsKataSama(command, CreateKata("build")))
                {
                    if (CheckNearGate(&_map))
                    {
                        JAM JCheck = NextNDetik(timeNeeded, GetDuration(command));
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
                                // moneyNeeded = 
                                // item langsung dikurang, check item, tambahin ke inventory kalo undo
                                // time needed ditambah
                                // money needed ditambah
                                timeNeeded = JCheck;
                            }
                            else
                            {
                                printf("Wahana tidak terdapat dalam katalog\n");
                            }
                            //build stuff
                            //teleport player using getobjectp(*M, '-')
                            //point player dikasih w nanti pas execute jadi W
                            //Push point player, /*check berada di office atau bukan*/
                            
                        }
                        else
                        {
                            printf("Waktu tidak mencukupi\n");
                        }
                    }
                    else
                    {
                        printf("Tidak dapat membangun di depan gerbang\n");
                    }
                }
                break;
            case 'u':
                if (IsKataSama(command, CreateKata("undo")))
                {
                    Undo(&Actions, &timeNeeded, &moneyNeeded);
                }
                break;
            case 'e':
                if (IsKataSama(command, CreateKata("execute")))
                {
                    toTarget(&Actions, &TargetExecution);
                    Execute(&TargetExecution, &_money);
                    // does executing shit
                    prep_phase = false;
                    SetOpen(&_time);
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
                    // Set jam ke jam buka, pindah ke main phase
                }
                break;
        }
    }
}

//ini command yang dijalanin kalo command build, tambahin build ke stack
void Build(MAP *M, POINT P, int i) //indeks pada array wahana
{
    Kata BUILD = CreateKata("build");
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
        Push(S, command_, specCommand_, infoCommand_, pointPlayer_);
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
    if (P == Nil)
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
        }
        else if (IsKataSama(command__, CreateKata("upgrade")))
        {
            //pointPlayer pada upgrade merupakan point wahana yang akan di upgrade
            //mengembalikan ke akar dari tree upgrade
            //mengurangkan timeneeded
            //mengganti ID pada x dan y menjadi id sebelumnya
            // tambah material yang dipake
            if (specCommand__ > (_wCount - 1) && specCommand__ < (_wCount * 2))
            {
                int y = specCommand__ % _wCount;
                // WNama(Left(_wType(specCommand__))); //Ambil info upgrade bahan bangunan, refund (Buy)
                // Wnama ganti bahan bangunan yang bakal di refund
            }
            else
            {
                //gamungkin kurang dari _wCount -1
                //berarti > wCount*2
            }
        }
        else if (IsKataSama(command__, CreateKata("buy")))
        {
            //mengurangkan money needed,
            //mengurangkan timeneeded
            *moneyNeeded -= infoCommand__ * MaterialPrice(_mlist, specCommand__);
        }
        PrevNDetik(*timeNeeded, GetDuration(command__));
    }
}

void LoadMaterial(TabMaterial *TabMat, char *filename)
{
    FILE *materialFile;
    char line[20];
    int price;
    char Sname[10];
    Kata Kname;
    int quantity;

    materialFile = fopen(filename,"r");
    if (materialFile == NULL)
    {
        printf("FAILED TO READ MATERIALS\n");
        return;
    }
    int i = 0;
    while (fgets(line, 100, materialFile) != NULL)
    {
        if (line[0] == '#' && line[1] == 'm' && line[2] == 't')
        {
            int nb;
            fscanf(materialFile, "%d", &nb);
            for (int i = 0; i < nb; i++)
            {
                fscanf(materialFile, "%d %d %s", &price, &quantity, &Sname);
                ((*TabMat).TI[(i)]).price = price;
                ((*TabMat).TI[(i)]).kuantitas = quantity;
                ((*TabMat).TI[(i)]).name = CreateKata(Sname);
            }
        }
    }
}

int SearchForPrice(TabMaterial TabMat, Kata Material)
{
    boolean found = false;
    int i = MATERIALS_IdxMin;
    while (!found && i <= MATERIALS_IdxMax)
    {
        if (IsKataSama(Material, MaterialName(TabMat, i)))
        {
            found = true;
            return MaterialPrice(TabMat, i);
        }
        else
        {
            i++;
        }
    }
}

int SearchForQuantity(TabMaterial TabMat, Kata Material)
{
    boolean found = false;
    int i = MATERIALS_IdxMin;
    while (!found && i <= MATERIALS_IdxMax)
    {
        if (IsKataSama(Material, MaterialName(TabMat, i)))
        {
            found = true;
            return MaterialQuantity(TabMat, i);
        }
        else
        {
            i++;
        }
    }
}

void PrintAllMaterials(TabMaterial TabMat) //testing
{
    for (int i = 0; i < 3; i++)
    {
        PrintKata(MaterialName(TabMat, i));
        printf("%d\n", MaterialPrice(TabMat, i));
        printf("%d\n", MaterialQuantity(TabMat, i));
    }
}

boolean SearchForMaterial(TabMaterial TabMat, Kata Material) 
// untuk memasukkan perintah buy pada stack, cari terlebih dahulu jika ada atau tidak
{
    boolean found = false;
    int i = MATERIALS_IdxMin;
    while (!found && i <= MATERIALS_IdxMax)
    {
        if (IsKataSama(Material, MaterialName(TabMat, i)))
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

boolean SearchForBuilding(Kata Building)
//untuk memasukkan perintah build ke stack, cari dulu bangunannya ada atau tidak
{
    int i = 0;
    boolean found = false;
    while (!found && i < _wCount)
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
    while (!found && i < _wCount)
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

int SearchForIndexMaterial(Kata Material)
{
    int i = 0;
    boolean found = false;
    while (!found && i < _wCount)
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
//     while (!found && i < _wCount)
//     {
//         if (IsKataSama(WNama(_wType(i)), Upgrade))
//         {

//         }
//     }
// }

void info_prep(Stack Action, JAM timeNeeded, int moneyNeeded)
{
    Kata KName = CreateKata(_name); 

    printf("Nama                            :   "); PrintKata(KName); 
    printf("Money                           :   %d\n", _money); 
    printf("Current Time                    :   21.00\n"); 
    printf("Opening Time                    :   09.00\n");
    printf("Time Remaining                  :   12 jam\n");
    printf("Total aksi yang akan dilakukan  :   %d\n", STACK_NbElmt(Action));
    printf("Total waktu yang dibutuhkan     :   "); TulisJAM(timeNeeded); printf("\n");
    printf("Total uang yang dibutuhkan      :   %d", moneyNeeded);
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

void PrintNamaWahana()
{
    print("List nama wahana:\n");
    for (int i=0; i<_wCount;i++)
    {
        print("- "); PrintKata(WNama(_wType(i)));
    }
}



void PrintUpgradeWahana(int i) //i adalah indeks base build
{
    Kata UpgradeOne = WNama(Left(_wType(i))); //tanya govin bener apa engga
    Kata UpgradeTwo = WNama(Right(_wType(i)));
    printf("Upgrade menjadi : \n");
    printf("- "); PrintKata(UpgradeOne);
    printf("- "); PrintKata(UpgradeTwo);
    printf("  Pilihan: ");
}