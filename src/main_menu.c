#include "main_menu.h"
#include "boolean.h"
#include "game.h"

#include <stdio.h>
#include <stdlib.h>

void main_menu(GAME *gameInstance)
{
    boolean endGame = false;
    char commandTemp;

    printf("Welcome to Willy Wangky's World!!\n");
    printf("New / Load / Exit\n");

    scanf("%c", &commandTemp);
    
    switch(commandTemp)
    {
        case 'n':
            new_game(gameInstance);
            break;
        case 'l':
            // load_game(gameInstance);
            break;
        case 'e':
            endGame = true;
            break;
    }
}

void new_game(GAME *gameInstance)
{
    printf("Memulai permainan baru...");
    printf("Masukkan nama:");
    scanf("%lc", &(*gameInstance).PName);
    
    LoadMap(&(*gameInstance).map, "map.txt");
}

void exit_game()
{
    printf("Thanks for playing!!!");
}