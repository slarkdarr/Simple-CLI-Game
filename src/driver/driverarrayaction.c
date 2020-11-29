#include "../boolean.h"
#include "../mesinkata/mesinkata.h"
#include "../arrayaction/arrayaction.h"
#include "../jam/jam.h"
#include <stdio.h>

int main()
{
    ArrayAction_TabInt TEST;
    InitializeArrayAction(&TEST);
    int durasi = GetDuration(TEST, CreateKata("build")); // mengambil durasi dari action build
    printf("Durasi build : %d\n", durasi);
    TulisIsiTab(TEST);

    // Hasil kompilasi
    // Durasi build : 10800
    // w 60 detik
    // a 60 detik
    // s 60 detik
    // d 60 detik
    // build 10800 detik
    // upgrade 5400 detik
    // buy 3600 detik
    // serve 600 detik
    // repair 3600 detik

    // Compile command :
    // gcc -o driverarrayaction driverarrayaction.c ../arrayaction/arrayaction.c ../mesinkata/mesinkata.c ../mesinkata/mesinkar.c ../jam/jam.c
    // ./driverarrayaction.exe


    return 0;
}