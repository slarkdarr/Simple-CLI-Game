// Main Driver Willy Wangky's World //

#include <stdio.h>
#include "boolean.h"
// #include "matriks.h"
#include "game.h"
#include "main_menu.h"

/*
COMPILE COMMAND (ganti dir ke src):
    gcc -o test main_driver.c point.c map.c

RUN COMMANd:
    ./test.exe

MAKEFILE COMING SOON
*/

void init_game(GAME *gameInstance)
{

}

void run_test(GAME *gameInstance)
{
    boolean end_game = false;
    char input;

    while (!end_game)
    {
        DrawMap((*gameInstance).map);
        scanf("%c", &input);
        Move(&(*gameInstance).map, input);
    }
};

int main()
{
    GAME gameInstance;

    int cont;

    main_menu(&gameInstance);
    run_test(&gameInstance);

    return 0;
}

