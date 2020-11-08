#include "main_menu.h"
#include "boolean.h"
#include "game.h"

#include <stdio.h>
#include <stdlib.h>

void main_menu()
{
    boolean endGame = false;
    char commandTemp;

    printf("Welcome to Willy Wangky's World!!\n");
    printf("New / Load / Exit\n");

    scanf("%c", &commandTemp);
    
    switch(commandTemp)
    {
        case 'n':
            new_game();
            break;
        case 'l':
            // load_game();
            break;
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