#include "prioqueue.h"

#ifndef broken_H
#define broken_H

void RemoveFromWahana(PrioQueue *Antrian, PrioQueueWahana *QWahana, int idWahana, int nWahana);
/* Prosedur untuk mengeluarkan penumpang dari wahana ketika wahana rusak */

void DequeueWahanaP(PrioQueueWahana *QWahana, Pengunjung *X);
/* Prosedur yang melakukan dequeue penumpang dari wahana ketika wahana rusak */

void EnqueueWahanaP(PrioQueueWahana * QWahana, Penumpang X);
/* Prosedur yang melakukan enqueue penumpang ke antrian apabila wahana rusak */

void MakeBrokenWahana(WAHANA_Instance *W, PrioQueueWahana *QWahana, Penumpang *X, PrioQueue *Antrian, int idWahana, int nWahana);
/* Prosedur yang menentukan rusaknya wahana */

#endif
