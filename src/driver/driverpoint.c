#include <stdio.h>
#include <math.h>
#include "../point.h"
#include "../boolean.h"

int main()
{
    /* KAMUS */
    POINT Point1, Point2 ;
    int validatorjenis, cekkuadran, cerminsumbu;
    float pergeseranX, pergeseranY, a, sudut, jarak;
    char validator;
    boolean SbX;
    /* ALGORITMA */
    validator = "N";
    /* Penggunaan BacaPoint, TulisPoint*/
    while (validator == "N")
    {
        printf("Tuliskan koordinat point dalam X dan Y:\n");
        BacaPOINT(&Point1);
        printf("Point: ");
        TulisPOINT(Point1);
        printf("Apakah point sudah benar? [Y/N]\n");
        scanf(" %c", &validator);
    };
    validator = "N";
    while (validator == "N")
    {
        printf("Tuliskan koordinat point ke-2 dalam X dan Y:\n");
        BacaPOINT(&Point2);
        printf("Point ke-2: ");
        TulisPOINT(Point2);
        printf("Apakah point ke-2 sudah benar? [Y/N]\n");
        scanf("%c", &validator);
    };
    /* Penggunaan EQ dan NEQ */
    printf("Check kesamaan Point 1 dengan Point 2\n");
    if ((POINT_EQ(Point1, Point2) == true) && (POINT_NEQ(Point1, Point2) == false))
    {
        printf("Point 1 sama dengan Point 2\n");
    }
    else
    {
        printf("Point 1 tidak sama dengan Point 2\n");
    };
    /* Penggunaan IsOrigin, IsOnSbX, IsOnSbY, dan Kuadran */
    while (validatorjenis != 3)
    {
        printf("Mengecek letak point:\n");
        printf("Point 1 atau Point 2? [1/2] (ketik 3 untuk lanjut)\n");
        scanf("%d", &validatorjenis);
        if (validatorjenis == 1)
        {
            if (IsOrigin(Point1) == true)
            {
                printf("Point 1 merupakan titik origin\n");
                printf("Point 1 tidak berada pada kuadran manapun\n");
            };
            if ((IsOnSbX(Point1) == true) && (IsOrigin(Point1) == false))
            {
                printf("Point 1 berada pada Sumbu X\n");
                printf("Point 1 tidak berada pada kuadran manapun\n");
            };
            if ((IsOnSbY(Point1) == true) && (IsOrigin(Point1) == false))
            {
                printf("Point 1 berada pada Sumbu Y");
                printf("Point 1 tidak berada pada kuadran manapun\n");
            };
            if (IsOrigin(Point1) == false)
            {
                cekkuadran = Kuadran(Point1);
                printf("Point 1 berada pada Kuadran %d\n", &cekkuadran);
            };
        };
        if (validatorjenis ==2)
        {
            if (IsOrigin(Point2) == true)
            {
                printf("Point 2 merupakan titik origin\n");
                printf("Point 2 tidak berada pada kuadran manapun\n");
            };
            if ((IsOnSbX(Point2) == true) && (IsOrigin(Point2) == false))
            {
                printf("Point 2 berada pada Sumbu X\n");
                printf("Point 2 tidak berada pada kuadran manapun\n");
            };
            if ((IsOnSbY(Point2) == true) && (IsOrigin(Point2) == false))
            {
                printf("Point 2 berada pada Sumbu Y");
                printf("Point 2 tidak berada pada kuadran manapun\n");
            };
            if (IsOrigin(Point2) == false)
            {
                cekkuadran = Kuadran(Point1);
                printf("Point 2 berada pada Kuadran %d\n", &cekkuadran);
            };
        };
    };
    /* Penggunaan NextX, NextY, PlusDelta */
    printf("Proses menggeser point 1:\n");
    validator = "Y";
    while (validator == "Y")
    {
        printf("Menggeser seberapa banyak pada sumbu X?\n");
        scanf("%f\n", &pergeseranX);
        printf("Menggeser seberapa banyak pada sumbu Y?\n");
        scanf("%f\n", &pergeseranY);
        if ((pergeseranX == 1) && (pergeseranY == 0))
        {
            NextX(Point1);
        };
        if ((pergeseranX == 0) && (pergeseranY == 1))
        {
            NextY(Point1);
        };
        if ((pergeseranX != 0) || (pergeseranY != 0))
        {
            PlusDelta(Point1, pergeseranX, pergeseranY);
        };
        printf("Point 1 sekarang berada pada: ");
        TulisPOINT(Point1);
        printf(" \n");
        printf("Apakah masih ingin menggeser Point 1? [Y/N]\n");
        scanf("%c", &validator);
    };
    printf("Proses menggeser point 2:\n");
    validator = "Y";
    while (validator == "Y")
    {
        printf("Menggeser seberapa banyak pada sumbu X?\n");
        scanf("%f\n", &pergeseranX);
        printf("Menggeser seberapa banyak pada sumbu Y?\n");
        scanf("%f\n", &pergeseranY);
        if ((pergeseranX == 1) && (pergeseranY == 0))
        {
            NextX(Point2);
        };
        if ((pergeseranX == 0) && (pergeseranY == 1))
        {
            NextY(Point2);
        };
        if ((pergeseranX != 0) || (pergeseranY != 0))
        {
            PlusDelta(Point2, pergeseranX, pergeseranY);
        };
        printf("Point 2 sekarang berada pada: ");
        TulisPOINT(Point2);
        printf(" \n");
        printf("Apakah masih ingin menggeser Point 2? [Y/N]\n");
        scanf("%c", &validator);
    };
    /* MirrorOf, Geser, GeserKeSbX, GeserKeSbY Geser */
    printf("Masukkan 1 jika ingin geser Point 1 ke SbX, 2 jika ingin geser ke SbY, dan 3 jika ingin dicerminkan: \n");
    scanf("%d", &validatorjenis);
    if (validatorjenis == 1)
    {
        GeserKeSbX(&Point1);
    };
    if (validatorjenis == 2)
    {
        GeserKeSbY(&Point1);
    };
    if (validatorjenis == 3)
    {
        printf("Dicerminkan terhadap sumbu X atau sumbu Y? [1 untuk X, selain 1 untuk Y]\n");
        scanf("%d", &cerminsumbu);
        if (cerminsumbu == 1)
        {
            SbX = true;
        }
        else
        {
            SbX = false;
        };
        MirrorOf(Point1, SbX);
    };
    printf("Point 1 sekarang berada pada: ");
    TulisPOINT(Point1);
    printf(" \n");
    printf("Masukkan 1 jika ingin geser Point 2 ke SbX, 2 jika ingin geser ke SbY, dan 3 jika ingin dicerminkan: \n");
    scanf("%d", &validatorjenis);
    if (validatorjenis == 1)
    {
        a = (Ordinat(Point2) * -1);
        Geser(&Point2, 0, a);
    };
    if (validatorjenis == 2)
    {
        a = (Absis(Point2) * -1);
        Geser(&Point2, a, 0);
    };
    if (validatorjenis == 3)
    {
        printf("Dicerminkan terhadap sumbu X atau sumbu Y? [1 untuk X, selain 1 untuk Y]\n");
        scanf("%d", &cerminsumbu);
        if (cerminsumbu == 1)
        {
            SbX = true;
        }
        else
        {
            SbX = false;
        };
        Mirror(&Point2, SbX);
    };
    printf("Point 2 sekarang berada pada: ");
    TulisPOINT(Point2);
    printf(" \n");
    /* Putar, Jarak0, dan Panjang */
    printf("Apakah ingin memutar point? [Y/N]\n");
    scanf("%c", &validator);
    if (validator == "Y")
    {
        printf("Point 1 atau 2? [1/2]\n");
        scanf("%d", &validatorjenis);
        if (validatorjenis == 1)
        {
            printf("Memutar berapa derajat?\n");
            scanf("%f", &sudut);
            Putar(&Point1, sudut);
        };
        if (validatorjenis == 2)
        {
            printf("Memutar berapa derajat?\n");
            scanf("%f", &sudut);
            Putar(&Point2, sudut);
        };
    };
    printf("Point 1 sekarang berada pada: ");
    TulisPOINT(Point1);
    printf(" \n");
    printf("Point 2 sekarang berada pada: ");
    TulisPOINT(Point2);
    printf(" \n");
    printf("Jarak Point 1 terhadap (0,0): ");
    printf("%.2f", Jarak0(Point1));
    printf(" \n");
    printf("Jarak Point 2 terhadap (0,0): ");
    printf("%.2f", Jarak0(Point2));
    printf(" \n");
    printf("Jarak Point 1 terhadap Point 2: \n");
    jarak = Panjang(Point1, Point2);
    printf("%.2f", &jarak);
    printf(" \n");
    printf("Terimakasih sudah menggunakan program ini\n");
    
    return 0;
}