#include <stdio.h>
#include <math.h>
#include "../point/point.h"
#include "../boolean.h"

// compile command gcc -o driverpoint driverpoint.c ../point/point.c
// input: 2 point x y x y

int main()
{
    POINT P, Q;
    BacaPOINT(&P);
    TulisPOINT(P);
    BacaPOINT(&Q);
    TulisPOINT(Q);
    if (POINT_EQ(P, Q))
    {
        printf("POINT sama\n");
    }
    else if (POINT_NEQ(P, Q))
    {
        printf("POINT tidak sama\n");
    }
    Mirror(&P, true);
    Mirror(&Q, false);
    TulisPOINT(P); printf("\n");
    TulisPOINT(Q); printf("\n");

    GeserKeSbX(&P); TulisPOINT(P);
    GeserKeSbY(&Q); TulisPOINT(Q);
    printf("Driver selesai\n");
    
    return 0;
}