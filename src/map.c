#include "map.h"

void CreateEmptyMap(MATRIKS *map, int row, int col){
  for (int i = 0; i < row; i++){
    for (int j = 0; j < col; j++){
      if (i==0 || i==row-1 || j==0 || j==col-1){
        Elmt(&map, i, j) = '*'; 
      }
      else{
        Elmt(&map, i, j) = '-';
      }
    }
  }
}

void CreateEmptyMAP(MATRIKS &MAP, int row, int col)
{
    int i, j;
    for (int i = 0; i < row ; i++)
    {
        for (int j = 0)
    }
}