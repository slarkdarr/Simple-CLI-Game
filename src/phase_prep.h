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

void preparation_phase();

void build(Stack S);   //Fungsi untuk membangun wahana baru
void upgrade(Stack S); //Fungsi untuk meng-upgrade wahana
void buy(Stack S);     //Fungsi untuk membeli bahan bangunan
void undo(Stack S, infotype X);    //Fungsi untuk melakukan UNDO pada eksekusi terakhir pemain
void execute(Stack S, infotype X); //Fungsi untuk mengeksekusi setiap command yang diberikan pemain
void main();    //Fungsi untuk mengosongkan stack dan masuk ke main phase

#endif