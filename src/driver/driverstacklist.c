#include "../boolean.h"
#include "../stacklist/stacklist.h"
#include "../mesinkata/mesinkata.h"
#include "../point/point.h"
#include "../map/map.h"

int main()
{
    Stack TestStack;
    STACK_CreateEmpty(&TestStack);

    MAP TEST;
    gAddress_V FULLMAP;
    LoadFullMap(&TEST, "../map.txt", &FULLMAP);

    Kata command1 = CreateKata("build");
    Kata command2 = CreateKata("upgrade");
    int specCommand1 = 1;
    int specCommand2 = 2;
    int infoCommand1 = 11;
    int infoCommand2 = 22;
    POINT TestPoint1 = MakePOINT(5, 5);
    POINT TestPoint2 = MakePOINT(6, 6);

    Push(&TestStack, command1, specCommand1, infoCommand1, TestPoint1, FULLMAP);
    Push(&TestStack, command2, specCommand2, infoCommand2, TestPoint2, FULLMAP);

    PrintIsiStack(TestStack);

    Kata print1;
    Kata print2;
    int printSpec1;
    int printSpec2;
    int printInfo1;
    int printInfo2;
    POINT printPoint1;
    POINT printPoint2;

    gAddress_V One;
    gAddress_V Two;

    printf("Hasil pop : \n");
    Pop(&TestStack, &print1, &printSpec1, &printInfo1, &printPoint1, &One);
    Pop(&TestStack, &print2, &printSpec2, &printInfo2, &printPoint2, &Two);

    PrintKata(print1); printf("\n");
    printf("Spec : %d  Info : %d  Point : ", printSpec1, printInfo1); 
    TulisPOINT(printPoint1); printf("\n");
    PrintKata(print2), printf("\n");
    printf("Spec : %d  Info : %d  Point : ", printSpec2, printInfo2); 
    TulisPOINT(printPoint2); printf("\n");

    Push(&TestStack, command1, specCommand1, infoCommand1, TestPoint1, One);
    Push(&TestStack, command2, specCommand2, infoCommand2, TestPoint2, Two);

    while(!STACK_IsEmpty(TestStack))
    {
        Pop(&TestStack, &print1, &printSpec1, &printInfo1, &printPoint1, &One);
        PrintKata(print1); printf("\n");
        printf("Spec : %d  Info : %d  Point : ", printSpec1, printInfo1);
        TulisPOINT(printPoint1); printf("\n"); 
    }


    // Hasil eksekusi driverstacklist.exe
    // Perintah: upgrade
    // Spec    : 2
    // Info    : 22
    // Point   : (6,6)


    // Perintah: build
    // Spec    : 1
    // Info    : 11
    // Point   : (5,5)
    // gcc -o driverstacklist driverstacklist.c ../stacklist/stacklist.c ../mesinkata/mesinkata.c ../point/point.c ../mesinkata/mesinkar.c ../map/map.c
    // ./driverstacklist.exe


    return 0;
}