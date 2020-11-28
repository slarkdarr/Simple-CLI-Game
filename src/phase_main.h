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

void serve(PrioQueue *antrian, PrioQueueWahana *inWahana, int idw);

void repair();

void detail();

void office_enter();
void office_details();
void office_report();
void office_exit();

void prepare();

int selectWahanaScreen();
void printInfo(PrioQueue Antrian);
void PrintAntrian(PrioQueue Antrian, int nWahana);
int SearchForIndexWahana(Kata W);
int SearchForIndexWahanaFromAntrian(PrioQueue Antrian, Kata W);
void printAntrian(PrioQueue Antrian, int nWahana);

#endif
