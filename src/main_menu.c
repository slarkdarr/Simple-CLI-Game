#include "main_menu.h"
#include "boolean.h"
#include "game.h"

#include <stdio.h>
#include <stdlib.h>

void main_menu()
{
    boolean endGame = false;
    printf("Welcome to Willy Wangky's World!!\n");
    printf("New / Load / Exit\n");

    // scanf("%c", &commandTemp);
    Kata commandTemp;
    ReadInput(&commandTemp);
    
    switch(commandTemp.TabKata[0])
    {
        case 'N':
        case 'n':
            new_game();
            break;
        case 'L':
        case 'l':
            GAME_Load();
            break;
        case 'E':
        case 'e':
            endGame = true;
            break;
    }
}

void new_game()
{
    printf("Memulai permainan baru...\n");
    GAME_Init();

    printf("Masukkan nama: ");
    scanf("%s", &_name);
    printf("Player name is: %s\n", _name);
}

void exit_game()
{
    printf("Thanks for playing!!!");
}