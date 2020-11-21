#ifndef BUILD_H
#define BUILD_H

#define BORDER '*'

#include <stdlib.h>
#include <stdio.h>
#include "boolean.h"
#include "stackt.h"
#include "point.h"
#include "game.h"
#include "mesinkata.h"

void preparation_phase(Kata *gameInstance);

void Build();   //Fungsi untuk membangun wahana baru
void Upgrade(); //Fungsi untuk meng-upgrade wahana
void Buy();     //Fungsi untuk membeli bahan bangunan
void Undo();    //Fungsi untuk melakukan UNDO pada eksekusi terakhir pemain
void Execute(); //Fungsi untuk mengeksekusi setiap command yang diberikan pemain
void Main();    //Fungsi untuk mengosongkan stack dan masuk ke main phase
void Undo (Stack *S);

#endif