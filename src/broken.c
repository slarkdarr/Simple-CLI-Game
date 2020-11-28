#include "broken.h"

void RemoveFromWahana(PrioQueue *Antrian, PrioQueueWahana *QWahana, int idWahana, int nWahana)
{
  PrioQueueWahana QNew;

  CreateEmptyPrioQueueWahana(&QNew, MaxElPrioQueue(*QWahana));

  while (!IsEmptyPrioQueueW(*QWahana))
  {
    Penumpang X;
    DequeueWahanaP(QWahana, &X);

    if (CurrWahana(X) == idWahana)
      if (!IsFullPrioQueue(*Antrian)) 
        Enqueue(Antrian, Pengunjung(X));

    else EnqueueWahanaP(&QNew, X);
  }

  *QWahana = QNew;
}

void DequeueWahanaP(PrioQueueWahana *QWahana, Pengunjung *X)
{
  if (!IsEmptyPrioQueueW(*QWahana))
  {
    *X = Pengunjung(InfoHeadW(*QWahana));
    if (Head(*QWahana) == Tail(*QWahana))
    {
      Head(*QWahana) = -1;
      Tail(*QWahana) = -1;
    } 
    else 
    {
      Head(*QWahana) = (Head(*QWahana)+1)%MaxElPrioQueue(*QWahana);
    }
  }
}

void EnqueueWahanaP(PrioQueueWahana * QWahana, Penumpang X)
{
  Penumpang PNew = X;

  if (IsEmptyPrioQueueW(*QWahana))
    Head(*QWahana) = 0;
  
  Tail(*QWahana) = (Tail(*QWahana)+1) % MaxElPrioQueue(*QWahana);
  
  InfoTailW(*QWahana) = PNew;
  
  int i = Tail(*QWahana);
  int j = (i + MaxElPrioQueue(*QWahana)-1)% MaxElPrioQueue(*QWahana);

  Penumpang temp;
  while (i != Head(*QWahana) && Dur(ElmtW(*QWahana, i))<Dur(ElmtW(*QWahana, j))){    
    temp = ElmtW(*QWahana, i);
    ElmtW(*QWahana, i) = ElmtW(*QWahana, j);
    ElmtW(*QWahana, j) = temp;

    i = j;
    j = (i + MaxElPrioQueue(*QWahana)-1)% MaxElPrioQueue(*QWahana);
  }
}

void MakeBrokenWahana(WAHANA_Instance *W, PrioQueueWahana *QWahana, Penumpang *X, PrioQueue *Antrian, int idWahana, int nWahana)
{
  srand(time(NULL));
  int broken = rand();
  int consbroken = rand();

  if (broken == consbroken){
    (*W).status == false;

    if (IsFullPrioQueue(*Antrian)){
      DequeueWahanaP(QWahana, X);
    }
    else{
      RemoveFromWahana(Antrian, QWahana, idWahana, nWahana);
    }
    printf("Maaf, wahana sedang rusak\n");
  }
}
