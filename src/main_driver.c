// Main Driver Willy Wangky's World //

#include <stdio.h>
#include "boolean.h"
// #include "matriks.h"
#include "game.h"
#include "main_menu.h"
#include "mesinkata.h"

/*
COMPILE COMMAND (ganti dir ke src):
    gcc -o test  main_driver.c point.c map.c main_menu.c jam.c game.c mesinkata.c mesinkar.c

RUN COMMANd:
    ./test.exe

MAKEFILE COMING SOON
*/

void init_game()
{

}

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

int main()
{
    int cont;
    Kata input;

    main_menu();

    while (input.TabKata[0] != 'x')
    {
        ReadInput(&input);
        run_test(input);
    }
    

    return 0;
}

