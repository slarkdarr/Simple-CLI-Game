// Main Driver Willy Wangky's World //

#include <stdio.h>
#include "boolean.h"
// #include "matriks.h"
#include "point.h"
#include "map.h"

/*
COMPILE COMMAND (ganti dir ke src):
    gcc -o test main_driver.c point.c map.c

RUN COMMANd:
    ./test.exe

MAKEFILE COMING SOON
*/

int main()
{
    printf("Welcome to Willy Wangky's World!!\n");
    printf("New / Load / Exit\n");

    int cont;

    printf("STARTING TEST: MAP. Press any key to continue  ");
    scanf("%d", &cont);
    MAP test;
    LoadMap(&test, "map.txt");
    DrawMap(test);
    // DrawMapInfo(test);

    return 0;
}