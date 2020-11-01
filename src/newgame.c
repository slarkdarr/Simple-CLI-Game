#include <stdio.h>
#include <stdlib.h>

int main(){
    char name;
    FILE *new;
    char new, f;

    println("Memulai permainan baru...");
    println("Masukkan nama:");
    scanf("%lc", &name);

    f = fopen("map.txt","r");
    if ("map.txt" == NULL){
        println("Error. File map missing atau tidak dapat dibuka");
        exit(-1);
    }

    new = fgetc(f);
    while (new != EOF){
        printf("%c", new);
        new = fgetc(f);
    }
    fclose(f);

    println("Legend:");
    println("A = Antrian");
    println("P = Player");
    println("W = Wahana");
    println("O = Office");
    println("<, ^, >, V = Gerbang");
}