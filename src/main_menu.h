#ifndef MAINMENU_H
#define MAINMENU_H

#include "game.h"

void main_menu(GAME *gameInstance);

// New game. Wahana dan Barang placeholder, ADT wahana dan barang belum ada
// Wahana -> Tree dari tipe wahana dari file
// Barang -> List Implementasi array berisi nama dan harga barang/bahan
void new_game(GAME *gameInstance);

// Exit game
void exit_game();

// Load game
void load_game(GAME *gameInstance);

#endif