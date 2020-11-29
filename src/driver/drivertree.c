#include "../boolean.h"
#include "../wahana.h"
#include "../mesinkata.h"
#include "../point.h"
#include "../game.h"
// #include "../map.h"
#include <stdio.h>

/*
    COMPILE COMMAND
        gcc -o drivertree drivertree.c ../wahana.c ../mesinkata.c ../mesinkar.c ../point.c ../game.c ../jam.c ../map.c ../arrayaction.c ../materials.c -lm
*/

int main()
{
    tAddress forest[10];
    int a;
    LoadWahanaTypes(&forest, "../wahana.txt", &a);

    tAddress P = forest[0];
    WAHANA_PrintInfo(P);

    printf("LEFT (0) or RIGHT (1), enter anything else to exit\n");
    scanf("%d", &a);

    while (a == 0 || a == 1)
    {
        if (P == WAHANA_Nil)
        {
            printf("NO MORE WAHANAS\n");
            a = -1;
        } else {
            if (a == 0)
            {
                P = Left(P);
            } else {
                P = Right(P);   
            }

            if (P == WAHANA_Nil)
            {
                printf("NO MORE WAHANAS\n");
                a = -1;
            } else {
                WAHANA_PrintInfo(P);
                scanf("%d", &a);
            }
            
        }
    }

}