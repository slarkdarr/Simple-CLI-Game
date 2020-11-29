#include "game.h"

#ifndef PHASEMAIN_H
#define PHASEMAIN_H

#include <stdlib.h>
#include <stdio.h>
#include "boolean.h"
#include "point.h"
#include "game.h"
#include "jam.h"
#include "mesinkata.h"
#include "prioqueue.h"

int main_phase();

void serve(PrioQueue *antrian, PrioQueueWahana *inWahana, int idw); // Prosedur untuk serve antrian

void detail();

void office_enter(); // Berfungsi untuk simulasi memasuki office
void office_details(); // Prosedur men-display details pada office
void office_report(); // Prosedur untuk memperlihatkan report saat berada di office
void office_exit(); // Prosedur untuk keluar dari office

void prepare(); // Prosedur untuk langsung kembali ke preparation phase

int selectWahanaScreen(); // Fungsi untuk pendukung simulasi office
void printInfo(PrioQueue Antrian); // Prosedur untuk memperlihatkan info player saat main phase
void PrintAntrian(PrioQueue Antrian, int nWahana); // Prosedur untuk memperlihatkan isi antrian
int SearchForIndexWahanaFromAntrian(PrioQueue Antrian, Kata W); // Mencari indeks wahana yang ingin dinaiki oleh pengunjung
void RemoveFromWahana(PrioQueue *Antrian, PrioQueueWahana *QWahana, int idWahana, int nWahana); 
// Prosedur untuk menghilangkan penumpang yang sedang menaiki suatu wahana ketika wahana tersebut tiba-tiba rusak

#endif