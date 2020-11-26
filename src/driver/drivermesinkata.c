#include "../mesinkata.h"
#include <stdio.h>

int main()
{
    Kata test;
    printf("Input 1:");
    ReadInput(&test);
    PrintKata(test);printf("\n");
    printf("%d\n", test.Length);

    Kata test2;
    printf("Input 2:");
    ReadInput(&test2);
    PrintKata(test2);printf("\n");
    printf("%d\n", test2.Length);

    if (IsKataSama(test, test2))
    {
        printf("sama\n");
    }
    // gcc -o drivermesinkata drivermesinkata.c ../mesinkata.c ../mesinkar.c
    // drivermesinkata.exe
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
    printf("Format input : kuantitas nama\n");
    ReadCommand(&quantity, &primogem);
    printf("kuantitas : ");
    printf("%d\n", quantity);
    printf("nama : ");
    PrintKata(primogem);printf("\n");

    Kata INPUT1, INPUT2;
    ReadServe(&INPUT1, &INPUT2);
    PrintKata(INPUT1); printf("\n");
    printf("length 1 : %d\n", INPUT1.Length);
    PrintKata(INPUT2); printf("\n");
    printf("length 2 : %d\n", INPUT2.Length);

    return 0;
}