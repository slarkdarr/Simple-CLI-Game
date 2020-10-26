#include "main_menu.h"
#include "boolean.h"
#include "map.h"

#include <stdio.h>
#include <stdlib.h>

void new_game(Map *M, int wahana[], int barang[])
{
    char nama;
    FILE *new;
    char new, f;

    println("Memulai permainan baru...");
    println("Masukkan nama:");
    scanf("%lc", &nama);

    f = fopen("map.txt","r");
    if ("map.txt" == NULL)
    {
        println("File map missing");
        exit(0);
    }

    new = fgetc(f);
    while (new != EOF){
        printf("%c", new);
        new = fgetc(f);
    }
    fclose(f);

    // ini mestinya di bagian gameny bukan di new game menu
    // println("Legend:");
    // println("A = Antrian");
    // println("P = Player");
    // println("W = Wahana");
    // println("O = Office");
    // println("<, ^, >, V = Gerbang");
}

void exit_game()
{

}