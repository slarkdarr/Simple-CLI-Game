#include "../prioqueue/prioqueue.h"
#include "../jam/jam.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Testing */
// gcc -o driverprioqueue ../prioqueue/prioqueue.c ../jam/jam.c driverprioqueue.c

int main ()
{ 
  // Definisi ADT
  PrioQueue Antrian;
  PrioQueueWahana QWahana;
  Pengunjung X;
  Pengunjung Y;
  Penumpang A;
  Penumpang B;
  
  int maxAntrian = 15;
  int maxCap = 30;
  int nWahana = 5;

  // Konstruktor
  CreateEmptyPrioQueue(&Antrian, maxAntrian);
  CreateEmptyPrioQueueWahana(&QWahana, maxCap);

  int serve; int idw;
  srand ( time(NULL) );

  // Test enqueue
  RandomEnqueue(&Antrian, nWahana);
  JAM CurrTime = MakeJAM(9, 0, 0);

  for (int i = 0; i < 10; i++)
  {
    RandomEnqueue(&Antrian, nWahana);
    PrintPrioQueue(Antrian, nWahana);
    DecrKesabaran(&Antrian);
    scanf("%d %d", &serve, &idw);
    
    if (serve == 1 && !IsEmptyPrioQueue(Antrian))
    {
      if (PengunjungWahana(InfoHead(Antrian), idw, nWahana))
      {
        // Test dequeue dan enqueue
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
      WahanaToAntrian(&QWahana, &B, CurrTime, &Antrian, nWahana, &deq);
    }
    
    //printf("%d\n",head);
    KesabaranHabis(&Antrian);
  }
  PrintPrioQueue(Antrian, nWahana);
  return 0;
}