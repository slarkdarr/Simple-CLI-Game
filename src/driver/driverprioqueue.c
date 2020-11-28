#include "../prioqueue.h"
#include "../jam.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Testing */
/* gcc -o driverprioqueue prioqueue.c jam.c driverprioqueue.c
driverprioqueue */

int main ()
{ 
  PrioQueue Antrian;
  PrioQueueWahana QWahana;

  Pengunjung X;
  Pengunjung Y;

  Penumpang A;
  Penumpang B;
  
  int maxAntrian = 15;
  int maxCap = 30;

  int nWahana = 5;

  CreateEmptyPrioQueue(&Antrian, maxAntrian);
  CreateEmptyPrioQueueWahana(&QWahana, maxCap);

  int serve; int idw;

  srand ( time(NULL) );

  RandomEnqueue(&Antrian, nWahana);
  JAM CurrTime = MakeJAM(9, 0, 0);

  for (int i = 0; i < 10; i++)
  {
    RandomEnqueue(&Antrian, nWahana);
    PrintPrioQueue(Antrian, nWahana);
    DecrKesabaran(&Antrian);
    scanf("%d %d", &serve, &idw);
    
    if (serve == 1)
    {
      if (PengunjungWahana(InfoHead(Antrian), idw, nWahana))
      {
        DequeueAntrian(&Antrian, &X, idw, nWahana);
        EnqueueWahana(&QWahana, X, idw, 10, CurrTime);
      }
      else
      {
        printf("Pengunjung tidak berencana naik wahana ini\n");
      }
    }

    int incrTime = JAMToDetik(CurrTime) + 10;
    CurrTime = DetikToJAM(incrTime);

    boolean deq = true;
    while (deq)
    {
      DequeueWahana2(&QWahana, &Y, CurrTime, &Antrian, nWahana, &deq);
    }
    
    //printf("%d\n",head);
    KesabaranHabis(&Antrian);
  }
  PrintPrioQueue(Antrian, nWahana);
  return 0;
}