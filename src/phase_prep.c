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
                    JAM JCheck = NextNDetik(timeNeeded, GetDuration(command));
                    
                    if (JLT(JCheck, batasTime))
                    {
                        ReadCommand(&nBuy,&buyName);
                        //if (MoneyNow < TotalPrIce) {
                        //  printf("Uang tidak mencukupi")
                        //}
                        //else {buys things}
           
                        JCheck = JCheck2;
                    }
                    else
                    {
                        printf("Waktu tidak mencukupi\n");
                    }
                }
                else if (IsKataSama(command, CreateKata("build")))
                {
                    JAM JCheck = NextNDetik(timeNeeded, GetDuration(command));
                    if (JLT(JCheck, batasTime))
                    {
                        ReadInput(&buildWahana);
                        //cek kondisi build
                        //build stuff
                        //Jcheck diganti Jcheck2
                        //Push point player, check berada di office atau bukan
                        JCheck = JCheck2;
                    }
                    else
                    {
                        printf("Waktu tidak mencukupi\n");
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
                    // does executing shit
                    prep_phase = false;
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
}

void Upgrade() //Mengakses array wahana
{
    
}

void Buy()
{

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
            // does things
        }
        else if (IsKataSama(command_, KataUpgrade))
        {
            // does things
        }
        else if (IsKataSama(command_, KataBuy))
        {
            // does things
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
            //mengembalikan ke akar dari tree upgrade
        }
        else if (IsKataSama(command__, CreateKata("buy")))
        {
            
        }
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

int SearchForPrice(TabMaterial *TabMat, Kata Material)
{
    
}

int SearchForQuantity(TabMaterial *TabMat, Kata Material)
{
    
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