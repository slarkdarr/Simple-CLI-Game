#include "../mesinkata.h"
#include <stdio.h>

    // gcc -o drivermesinkata drivermesinkata.c ../mesinkata.c ../mesinkar.c
    // drivermesinkata.exe

int main()
{
    // Test ReadInput
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

    // Test ReadInputInteger
    int integer;
    ReadInputInteger(&integer);
    printf("%d\n", integer);

    // Test ReadInputInteger kemudian ReadInput
    int int2; Kata kata;
    ReadInputInteger(&int2);
    ReadInput(&kata);
    printf("%d\n", int2);
    PrintKata(kata);

    // Test ReadCommand, Input integer disusul kata
    int quantity; Kata primogem;
    printf("Format input : kuantitas nama\n");
    ReadCommand(&quantity, &primogem);
    printf("kuantitas : ");
    printf("%d\n", quantity);
    printf("nama : ");
    PrintKata(primogem);printf("\n");

    // Test ReadServe
    Kata INPUT1, INPUT2;
    ReadServe(&INPUT1, &INPUT2);
    PrintKata(INPUT1); printf("\n");
    printf("length 1 : %d\n", INPUT1.Length);
    PrintKata(INPUT2); printf("\n");
    printf("length 2 : %d\n", INPUT2.Length);

    // Test ParseKata
    Kata command;
    ReadInput(&command);
    Kata WNAMA = ParseKata(command, CreateKata("serve "));
    PrintKata(WNAMA); printf("\n");
    printf("%d\n", WNAMA.Length);

    return 0;
}