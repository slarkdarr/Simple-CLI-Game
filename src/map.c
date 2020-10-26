#include "map.h"
#include "matriks.h"
#include "point.h"

/* KONSTRUKTOR */
void MakeEmptyMap(Map *M)
{
    for (int i = 0; i < UkuranMap; i++)
    {
        for (int j = 0; j < UkuranMap; j++)
        {
            if (i == 0 || j == UkuranMap)
            {
                // (Elmt(*M, i, j)).type = '*'; /* .type gabisa diakses */
                // Key(Elmt(*M, )) /* .id gabisa diakses */
            }
        }
    }
}

void LoadMap(Map *M)
{

}

/* GETTER SETTER */


/* PROSEDUR */
// Menggerakkan Point P sesuai command W
void Move(Map *M, char W)
{

}

// SystemPrint matriks Map M
void DrawMap(Map M)
{

}

/* FUNGSI */
// Mengembalikan id dari object dengan tipe O terdekat dengan P
// Object yang diprioritaskan untuk dicek pertama adalah di atas P, kemudian secara clock-wise dicek dengan prioritas paling utama adalah diatas
int GetObject(char O)
{

}
