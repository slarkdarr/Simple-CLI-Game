#include "main_menu.h"
#include "boolean.h"
#include "game.h"

#include <stdio.h>
#include <stdlib.h>

int main_menu()
{
    /*
    Pindah kontrol layar ke main menu
    Inisialisasi gameInstance dengan GAME_Init() atau GAME_Load()
    */
    boolean endGame = false;
    printf("Welcome to Willy Wangky's World!!\n");
    

    // scanf("%c", &commandTemp);
    Kata commandTemp;
    
    
    while(!endGame)
    {
        printf("New / Load / Exit\n");
        ReadInput(&commandTemp);
        switch(commandTemp.TabKata[0])
        {
            case 'N':
            case 'n':
                if (IsKataSama(commandTemp, CreateKata("new"))) // Pengecekan input sama dengan Kata new
                {
                    new_game();
                    endGame = true;
                }
                break;
            case 'L':
            case 'l':
                if (IsKataSama(commandTemp, CreateKata("load"))) // Pengecekan input sama dengan Kata load
                {
                    GAME_Load();
                    endGame = true;
                }
                
                break;
            case 'E':
            case 'e':
                if (IsKataSama(commandTemp, CreateKata("exit"))) // Pengecekan input sama dengan Kata exit
                {
                    endGame = true;
                    return -1;
                }
                break;
        }
        system("cls");
        if (!endGame)
        {
            printf("Input tidak dikenali\n");
        }
    }
    
    return 0;
}

void new_game()
{
    /*
    Menu new game
    Meminta input nama user
    */
    printf("Memulai permainan baru...\n");
    GAME_Init();

    printf("Masukkan nama: ");
    scanf("%s", &_name);
    printf("Player name is: %s\n", _name);
}