#include "mesinkata.h"

int main()
{
    Kata testkata;
    Input(&testkata);
    PrintKata(testkata);
    printf("\n");
    printf("%d", testkata.Length);
    return 0;
}