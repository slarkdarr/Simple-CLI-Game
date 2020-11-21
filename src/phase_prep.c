#include "phase_prep.h"
#include "stacklist.h"
#include "map.h"
#include "game.h"
#include <stdio.h>
#include <stdlib.h>

void preparation_phase()
{
    int MoneyNow = _money;
    JAM JCheck = _time; //check jam, _time tidak diubah dulu
    JAM JOpening = MakeJAM(9, 0, 0);

    Kata command;

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
    while(Durasi(JCheck, JOpening) <= 43200)
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
                    JCheck = NextNDetik(JCheck, GetDuration(command));

                }
                else if (IsKataSama(command, CreateKata("build")))
                {
                    //wahanaList = open("wahana.txt", "r")
                    //print(wahanaList.read())
                    ReadInput(&buildWahana);
                    JCheck = NextNDetik(JCheck, GetDuration(command));

                }
                break;
            case 'u':
                if (IsKataSama(command, CreateKata("undo")))
                {
                    // harusnya undo mengurangi waktu sama nambahin resource yang dipake
                }
                break;
            case 'e':
                if (IsKataSama(command, CreateKata("execute")))
                {
                    JCheck = NextNDetik(JCheck, GetDuration(command));

                }
                break;
            case 'm':
                if (IsKataSama(command, CreateKata("main")))
                {
                    JCheck = NextNDetik(JCheck, GetDuration(command));
                    
                }
                break;
        }
    }
    // Force execute?
    // Pindah ke Main phase
    

    
}

//ini command yang dijalanin kalo command build, tambahin build ke stack
void Build(MAP *M, POINT P, int i) //indeks pada array wahana
{
    Kata BUILD = CreateKata("build");
    int x = P.X;
    int y = P.Y;
    if ((InfoElmtAtP(*M, x, y) == -1) && (TypeElmtAtP(*M, x, y) != 'O'))
    //jika tidak terdapat bangunan dan bukan Office maka dapat dibangun
    {
        //GetWahanaID

        
    }
    else
    {
        //refund?
        printf("Sudah terdapat bangunan pada tempat tersebut\n");
    }
    
}

void Upgrade() //Mengakses array wahana
{
    
}

void Buy()
{

}

// sebelum execut pindah stack ke stack target dan lakukan dari aksi awal
void Execute(Stack *S, int *currency, int *time)
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

void Main(Stack *S)
// Langsung lanjut ke main phase
// Tidak mengeksekusi isi stack
{
    while (!STACK_IsEmpty(*S))
    {
        Undo(S);
    }
}

void Undo (Stack *S) // untuk fungsi user undo
{
    Kata command__;
    int specCommand__;
    int infoCommand__;
    POINT pointPlayer__;
    addressStack P = Top(*S);
    if (Next(P) == Nil)
    {
        Pop(S, &command__, &specCommand__, &infoCommand__, &pointPlayer__);
        if IsKataSama(command__, CreateKata("build"))
        {

        }
        else if IsKataSama(command__, CreateKata("upgrade"))
        {
            
        }
        else if IsKataSama(command__, CreateKata("buy"))
        {
            
        }
        Top(*S) = Nil;
        STACK_Dealokasi(P);
    }
    else if (P == Nil)
    {
        printf("Tidak ada aksi untuk di undo\n");
    }
    else
    {
        Top(*S) = Next(P);
        Next(P) = Nil;
        STACK_Dealokasi(P);
    }
}