/*
13519107
Daffa Ananda Pratama Resyaly
01 Oktober 2020
ADT Telegram
*/

#include <stdio.h>
#include "mesinkar.h"
#include "mesinkata.h"

boolean IsKataSama(Kata K1, Kata K2){
    if(K1.Length == K2.Length){
        for(int i = 0; i < K1.Length; i++){
            return (K1.TabKata[i] == K2.TabKata[i]);
        }
    }
    else{
        return false;
    }
}

int main(){
    Kata TITIK;
    TITIK.TabKata[0] = 'T';
    TITIK.TabKata[1] = 'I';
    TITIK.TabKata[2] = 'T';
    TITIK.TabKata[3] = 'I';
    TITIK.TabKata[4] = 'K';
    TITIK.Length = 5;

    Kata KOMA;
    KOMA.TabKata[0] = 'K';
    KOMA.TabKata[1] = 'O';
    KOMA.TabKata[2] = 'M';
    KOMA.TabKata[3] = 'A';
    KOMA.Length = 4;

    int regular = 0, panjang = 0, lengthkata = 0;
    boolean awal = true;
    
    STARTKATA();

    while(!EndKata){
        lengthkata++;
        if(IsKataSama(CKata,TITIK)){
            printf(".");
        }
        else if(IsKataSama(CKata,KOMA)){
            printf(",");
        }
        else{
            if(!awal){
                printf(" ");
            }
            for(int i = 0; i < CKata.Length; i++){
                printf("%c", CKata.TabKata[i]);
            }
            if(CKata.Length < 10){
                regular++;
            }
            else{
                panjang++;
            }
        }
        awal = false;
        IgnoreBlank();
        ADVKATA();
    }

    printf("\n%d\n%d\n", regular, panjang);

    if(lengthkata > 10){
        printf("%d\n", (((1000 * regular) + (1500 * panjang)) * 90 / 100));
    }
    else{
        printf("%d\n", ((1000 * regular) + (1500*panjang)));
    }
    return 0;
}
