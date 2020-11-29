// Main Driver Willy Wangky's World //

#include "jam/jam.h"
#include <stdio.h>
#include "boolean.h"
#include "game/game.h"
#include "main_menu/main_menu.h"
#include "mesinkata/mesinkata.h"

/*
COMPILE COMMAND (ganti dir ke src):
    gcc -o that main_driver.c ./point/point.c ./stacklist/stacklist.c ./materials/materials.c ./map/map.c ./main_menu/main_menu.c ./jam/jam.c ./game/game.c ./mesinkata/mesinkata.c ./mesinkata/mesinkar.c ./wahana/wahana.c ./phase/phase_prep.c ./arrayaction/arrayaction.c ./phase/phase_main.c ./prioqueue/prioqueue.c -lm
    
    gcc -o wangk main_driver.c ./point/point.c ./stacklist/stacklist.c ./materials/materials.c ./map/map.c ./main_menu/main_menu.c ./jam/jam.c ./game/game.c ./mesinkata/mesinkata.c ./mesinkata/mesinkar.c ./wahana/wahana.c ./phase/phase_prep.c ./arrayaction/arrayaction.c ./phase/phase_main.c ./prioqueue/prioqueue.c -lm
*/

// RUN COMMAND:
//     ./that.exe

int readCommand();

int main()
{
    system("cls");
    int cont;

    cont = main_menu();
    // WAHANA_PrintInfo(_wType(1));

    while (cont != -1)
    {
        cont = readCommand();
    }

    printf("\nThank you and goodbye\n");
    return 0;
}

int readCommand()
{
    const JAM OpeningTime = MakeJAM(9, 0, 0);
    const JAM ClosingTime = MakeJAM(21, 0, 0);
    
    int cont = 0;

    while (cont == 0)
    {
        if (JGET(_time, ClosingTime) || JLT(_time, OpeningTime))
        {
            cont = preparation_phase();
        } else {
            cont = main_phase();
        }
    }


    return -1;
}