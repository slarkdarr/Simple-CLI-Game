#include "mesinkata.h"
#include <stdio.h>

int main()
{
    Kata test;
    ReadInput(&test);
    PrintKata(test);
    printf("%d\n", test.Length);

    Kata test2;
    ReadInput(&test2);
    PrintKata(test2);
    printf("%d\n", test2.Length);

    if (IsKataSama(test, test2))
    {
        printf("sama\n");
    }

    //int integer;
    //ReadInputInteger(&integer);
    //printf("%d\n", integer);

    //int int2; Kata kata;
    //ReadInputInteger(&int2);
    //ReadInput(&kata);

    //printf("%d\n", int2);
    //PrintKata(kata);

    /* Menggunakan format int diikuti dengan Kata */
    int quantity; Kata primogem;
    ReadCommand(&quantity, &primogem);
    printf("%d\n", quantity);
    PrintKata(primogem);

    return 0;
}