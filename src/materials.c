#include "materials.h"
#include "mesinkata.h"

#include <stdio.h>
#include <stdlib.h>

// testing

void LoadMaterial(TabMaterial *TabMat, char *filename)
{
    FILE *materialFile;
    char line[20];
    int price;
    char Sname[10];
    Kata Kname;
    int quantity;

    materialFile = fopen(filename,"r");
    if (materialFile == NULL)
    {
        printf("FAILED TO READ MATERIALS\n");
        return;
    }
    int i = 0;
    while (fgets(line, 100, materialFile) != NULL)
    {
        if (line[0] == '#' && line[1] == 'm' && line[2] == 't')
        {
            int nb;
            fscanf(materialFile, "%d", &nb);
            for (int i = 0; i < nb; i++)
            {
                fscanf(materialFile, "%d %d %s", &price, &quantity, &Sname);
                ((*TabMat).TI[(i)]).price = price;
                ((*TabMat).TI[(i)]).kuantitas = quantity;
                ((*TabMat).TI[(i)]).name = CreateKata(Sname);
            }
        }
    }
}

int SearchForPrice(TabMaterial TabMat, Kata Material)
{
    boolean found = false;
    int i = MATERIALS_IdxMin;
    while (!found && i <= MATERIALS_IdxMax)
    {
        if (IsKataSama(Material, MaterialName(TabMat, i)))
        {
            found = true;
            return MaterialPrice(TabMat, i);
        }
        else
        {
            i++;
        }
    }
}

int SearchForQuantity(TabMaterial TabMat, Kata Material)
{
    boolean found = false;
    int i = MATERIALS_IdxMin;
    while (!found && i <= MATERIALS_IdxMax)
    {
        if (IsKataSama(Material, MaterialName(TabMat, i)))
        {
            found = true;
            return MaterialQuantity(TabMat, i);
        }
        else
        {
            i++;
        }
    }
}

void PrintAllMaterials(TabMaterial TabMat) //testing
{
    for (int i = 0; i < 3; i++)
    {
        PrintKata(MaterialName(TabMat, i));
        printf("%d\n", MaterialPrice(TabMat, i));
        printf("%d\n", MaterialQuantity(TabMat, i));
    }
}

boolean SearchForMaterial(TabMaterial TabMat, Kata Material) 
// untuk memasukkan perintah buy pada stack, cari terlebih dahulu jika ada atau tidak
{
    boolean found = false;
    int i = MATERIALS_IdxMin;
    while (!found && i <= MATERIALS_IdxMax)
    {
        if (IsKataSama(Material, MaterialName(TabMat, i)))
        {
            found = true;
        }
        else
        {
            i++;
        }
    }
    return found;
}