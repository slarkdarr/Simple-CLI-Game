// Main Driver Willy Wangky's World //

#include <stdio.h>
#include "boolean.h"
// #include "matriks.h"
#include "game.h"
#include "main_menu.h"
#include "mesinkata.h"

/*
COMPILE COMMAND (ganti dir ke src):
    gcc -o test  main_driver.c point.c stacklist.c materials.c map.c main_menu.c jam.c game.c mesinkata.c mesinkar.c wahana.c phase_prep.c arrayaction.c -lm

RUN COMMANd:
    ./test.exe

MAKEFILE COMING SOON
*/

void run_test(Kata input)
{
    boolean end_game = false;
    char* message;
    Move(&_map, input.TabKata[0], &message);
    DrawMap(_map, message);
    _money = 1000;
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
};

int readCommand();

int main()
{
    int cont;

    main_menu();
    WAHANA_PrintInfo(_wType(1));
    printf("WCOUNT FAK %d\n", _wCount);
    printf("Mann is this compiling?777777\n");

    while (cont != -1)
    {
        cont = readCommand();
    }

    return 0;
}

int readCommand()
{
    const JAM OpeningTime = MakeJAM(9, 0, 0);
    const JAM ClosingTime = MakeJAM(21, 0, 0);
    
    int cont = 0;

    while(cont != -1)
    {

    }

    preparation_phase();



    return 0;
}