#include "../boolean.h"
#include "../jam/jam.h"
#include <stdio.h>


int main()
{
    JAM made = MakeJAM(10, 10, 10);
    JAM made2;
    BacaJAM(&made2);
    TulisJAM(made); printf("\n");
    TulisJAM(made2); printf("\n");
    printf("%d\n", JAMToDetik(made));
    TulisJAM(DetikToJAM(JAMToDetik(made))); printf("\n");
    if (!JEQ(made, made2))
    {
        printf("tidak sama\n");
    }
    if (JNEQ(made, made2))
    {
        printf("tidak sama\n");
    }
    TulisJAM(NextDetik(PrevDetik(made)));printf("\n");
    TulisJAM(NextNDetik(PrevNDetik(made, 200), 200));printf("\n");
    SetOpen(&made);
    TulisJAM(made);printf("\n");

    // gcc -o driverjam driverjam.c ../jam/jam.c
    // driverjam.exe

    // Hasil Eksekusi:
    // User Input : JJ MM SS
    // 10:10:10
    // 12:12:12
    // 36610
    // 10:10:10
    // tidak sama
    // tidak sama
    // 10:10:10
    // 10:10:10
    // 9:0:0

    return 0;
}