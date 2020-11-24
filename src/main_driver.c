// Main Driver Willy Wangky's World //

#include <stdio.h>
#include "boolean.h"
// #include "matriks.h"
#include "game.h"
#include "main_menu.h"
#include "mesinkata.h"

/*
COMPILE COMMAND (ganti dir ke src):
    gcc -o test  main_driver.c point.c map.c main_menu.c jam.c game.c mesinkata.c mesinkar.c wahana.c

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
    
    Kata command;
    int cont = 0;
    char* messageBuffer;
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
    }

    if (JLT(_time, OpeningTime) | JGT(_time, ClosingTime))
    {
        /* COMMAND UNTUK PREP */
        // phase_preparation();
    } else {
        /* COMMAND UNTUK PREP*/
        // phase_main();
    }

    return cont;
}