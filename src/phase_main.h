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

void serve();

void repair();

void detail();

void office_enter();
void office_details();
void office_report();
void office_exit();

void prepare();

#endif