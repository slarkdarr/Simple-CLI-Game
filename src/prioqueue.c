#include "boolean.h"
#include "jam.h"
#include "prioqueue.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void CreateEmptyPrioQueue(PrioQueue *Antrian, int Max)
{
  PrioQueue QTemp;
  QTemp.T = (Pengunjung *)malloc((Max) * sizeof(Pengunjung));

  if (QTemp.T != NULL)
    MaxElPrioQueue(QTemp) = Max;
  else
    MaxElPrioQueue(QTemp) = 0;
  
  Head(QTemp) = -1;
  Tail(QTemp) = -1;
  *Antrian = QTemp;
}

void CreateEmptyPrioQueueWahana(PrioQueueWahana *QWahana, int MaxCap)
{
  PrioQueueWahana WTemp;
  WTemp.P = (Penumpang *)malloc((MaxCap) * sizeof(Penumpang));

  if (WTemp.P != NULL)
    MaxElPrioQueue(WTemp) = MaxCap;
  else
    MaxElPrioQueue(WTemp) = 0;
  
  Head(WTemp) = -1;
  Tail(WTemp) = -1;
  *QWahana = WTemp;
}

void CreatePenumpang(Penumpang *P, JAM out, int idWahana, Pengunjung X, int durasi)
{
  Pengunjung(*P) = X;
  JAMOut(*P) = out;
  CurrWahana(*P) = idWahana;
  Dur(*P) = durasi;
}

void CreateEmptyListWahana(ListWahana *W, int nWahana)
{
  ListW(*W) = (int*) malloc (nWahana * sizeof(int));
  
  for(int i = 0; i < nWahana; i++)
  {
    ElmtWahana(*W, i) = -1;
  }
}

boolean IsEmptyPrioQueue (PrioQueue Antrian)
{
  return (Head(Antrian)==-1) && (Tail(Antrian)==-1);
}

boolean IsEmptyPrioQueueW (PrioQueueWahana QWahana)
{
  return (Head(QWahana)==-1) && (Tail(QWahana)==-1);
}

boolean IsEmptyWahana(ListWahana LWahana, int nWahana)
{
  return (NBElmtWahana(LWahana, nWahana)==0);
}

boolean IsFullPrioQueue (PrioQueue Antrian)
{
  return (Head(Antrian) == (Tail(Antrian) + 1)%MaxElPrioQueue(Antrian));
}

int NBElmtWahana(ListWahana W, int nWahana)
{
  int n = 0;
  
  for (int i = 0; i<nWahana; i++)
    if(ElmtWahana(W, i)!=-1) n++;

  return n;
}

int NBElmtPrioQueue (PrioQueue Antrian)
{
  if (IsEmptyPrioQueue(Antrian)) return 0;
  return ((Tail(Antrian) - Head(Antrian) + MaxElPrioQueue(Antrian))%MaxElPrioQueue(Antrian))+1;
}

int NBElmtPrioQueueW (PrioQueueWahana QWahana)
{
  if (IsEmptyPrioQueueW(QWahana)) return 0; 
  return ((Tail(QWahana) - Head(QWahana) + MaxElPrioQueue(QWahana))%MaxElPrioQueue(QWahana))+1;
}

void DeAlokasi(PrioQueue * Antrian)
{
  Head(*Antrian) = -1;
  Tail(*Antrian) = -1;
  MaxElPrioQueue(*Antrian) = 0;
  free(Antrian->T);;
}

void DeAlokasiQWahana(PrioQueueWahana *QWahana)
{
  Head(*QWahana) = -1;
  Tail(*QWahana) = -1;
  MaxElPrioQueue(*QWahana) = 0;
  free(QWahana->P);
}

void DelWahana(ListWahana *W, int idxWahana, int nWahana)
{
  int i = 0;
  while (i < nWahana && i != idxWahana)
    i++;
  if (i != nWahana)
    ElmtWahana(*W, i) = -1;
}

void Enqueue (PrioQueue * Antrian, Pengunjung X)
{
  if (IsEmptyPrioQueue(*Antrian))
    Head(*Antrian) = 0;
  
  Tail(*Antrian) = (Tail(*Antrian)+1) % MaxElPrioQueue(*Antrian);
  
  InfoTail(*Antrian) = X;
  
  int i = Tail(*Antrian);
  int j = (i + MaxElPrioQueue(*Antrian)-1)% MaxElPrioQueue(*Antrian);

  Pengunjung temp;
  while (i != Head(*Antrian) && Prio(ElmtQ(*Antrian, i))<Prio(ElmtQ(*Antrian, j))){    
    temp = ElmtQ(*Antrian, i);
    ElmtQ(*Antrian, i) = ElmtQ(*Antrian, j);
    ElmtQ(*Antrian, j) = temp;

    i = j;
    j = (i + MaxElPrioQueue(*Antrian)-1)% MaxElPrioQueue(*Antrian);
  }
}

void EnqueueWahana (PrioQueueWahana * QWahana, Pengunjung X, int idWahana, int durasiWahana, JAM CurrTime)
{
  /* Create Penumpang */
  Penumpang PNew;
  int durasi = durasiWahana + JAMToDetik(CurrTime);
  JAM out = DetikToJAM(durasi);

  CreatePenumpang(&PNew, out, idWahana, X, durasi);

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

void EnqueueWahanaP (PrioQueueWahana * QWahana, Penumpang X)
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

void Dequeue (PrioQueue * Antrian, Pengunjung * X)
{
  *X = InfoHead(*Antrian);
  if (Head(*Antrian) == Tail(*Antrian))
  {
    Head(*Antrian) = -1;
    Tail(*Antrian) = -1;
  } 
  else 
  {
    Head(*Antrian) = (Head(*Antrian)+1)%MaxElPrioQueue(*Antrian);
  }
}

boolean adaWahana(ListWahana LW, int idxWahana, int nWahana)
{
  for (int i =0; i<nWahana; i++)
    if (i == idxWahana && ElmtWahana(LW, i) == 1)
      return true;
  return false;
}

void DequeueAntrian(PrioQueue * Antrian, Pengunjung * X, int idxWahana, int nWahana)
{
  if (adaWahana(ListWP(InfoHead(*Antrian)), idxWahana, nWahana))
    {
      Dequeue(Antrian, X);
    }
  else
    printf("Pengunjung tidak berencana menaiki wahana tersebut\n");
}

void DequeueWahana(PrioQueueWahana *QWahana, Penumpang *X)
{
  if (!IsEmptyPrioQueueW(*QWahana))
  {
    *X = InfoHeadW(*QWahana);
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

void DequeueWahana2 (PrioQueueWahana *QWahana, Pengunjung *X, JAM CurrTime,PrioQueue *Antrian, int nWahana, boolean *b)
{
  if (!IsEmptyPrioQueueW(*QWahana))
  {  
    if (JGT(CurrTime, JAMOut(InfoHeadW(*QWahana))))
    {
      *X = Pengunjung(InfoHeadW(*QWahana));

      DelWahana(&ListWP(*X), CurrWahana(InfoHeadW(*QWahana)), nWahana);
      Prio(*X) = -1;
      Kesabaran(*X) = MaxElPrioQueue(*Antrian) + 5;

      if (Head(*QWahana) == Tail(*QWahana))
      {
        Head(*QWahana) = -1;
        Tail(*QWahana) = -1;
      } 
      else 
      {
        Head(*QWahana) = (Head(*QWahana)+1)%MaxElPrioQueue(*QWahana);
      }
      
      printf("work\n");
      if (!IsEmptyWahana(ListWP(*X), nWahana))
        Enqueue(Antrian, *X);
      
      *b = true;
    }
    else
    {
      *b = false;
    }
  }
  else
  {
    *b = false;
  }
  
  return;
}

/* Menghapus pengunjung yang kesabaran nya habis */
void KesabaranHabis(PrioQueue *Antrian)
{
  int i = 0;
  PrioQueue AntrianNew;
  Pengunjung X;
  CreateEmptyPrioQueue(&AntrianNew, MaxElPrioQueue(*Antrian));

  while (!IsEmptyPrioQueue(*Antrian))
  {
    Dequeue(Antrian, &X);
    if (Kesabaran(X) > 0)
      Enqueue(&AntrianNew, X);
  }
  *Antrian = AntrianNew;
}

void DecrKesabaran(PrioQueue *Antrian)
{
  // Mengurangi kesabaran Pengunjung
  if (!IsEmptyPrioQueue(*Antrian))
  {
    int n = NBElmtPrioQueue(*Antrian);
    int idx = Head(*Antrian) % MaxElPrioQueue(*Antrian);;

    while (idx != Tail(*Antrian))
    {
      Kesabaran(ElmtQ(*Antrian, idx)) -= 1;
      Prio(ElmtQ(*Antrian, idx)) -= 1;

      idx = (idx+1)%MaxElPrioQueue(*Antrian);
    }
    Kesabaran(ElmtQ(*Antrian, Tail(*Antrian))) -= 1;
  }
}

void setPrio(Pengunjung *X, int prio)
{
  Prio(*X) = prio;
}
void RandomEnqueue(PrioQueue *Antrian, int nWahana) // Memunculkan Pengunjung
{
  if (IsEmptyPrioQueue(*Antrian))
  {
    int nEnque = rand() % 2 + 1;
    //printf("Hasil random 1 %d\n", nEnque);
    for (int i = 0; i < nEnque; i++)
    {
      ListWahana LW;
      CreateEmptyListWahana(&LW, nWahana);
      int j = 0;

      while (j < nWahana)
      {
        int x = rand() % 2;

        if (x==1)
        {
      //    printf("%d\n", x);
          ElmtWahana(LW, j) = 1; 
        }
        j++;
      }

      if (!IsEmptyWahana(LW, nWahana))
      {
        Pengunjung A;
        Kesabaran(A) = MaxElPrioQueue(*Antrian) + 5;

        if (!IsEmptyPrioQueue(*Antrian))
          Prio(A) = Prio(InfoTail(*Antrian)) + 1;
        else
          Prio(A) = 1;
        
        ListWP(A) = LW;
        Enqueue(Antrian, A);
      }
    }
  }

  else if (!IsFullPrioQueue(*Antrian))
  {
    int nEnque = rand() % 3;
    for (int i = 0; i < nEnque; i++)
    {
      ListWahana LW;
      CreateEmptyListWahana(&LW, nWahana);
      int j = 0;

      while (j < nWahana)
      {
        int x = rand() % 3;

        if (x==1)
        {
        //  printf("%d\n", x);
          ElmtWahana(LW, j) = 1; 
        }
        j++;
      }

      if (!IsEmptyWahana(LW, nWahana) && !IsFullPrioQueue(*Antrian))
      {
        Pengunjung A;
        Kesabaran(A) = MaxElPrioQueue(*Antrian) + 5;

        if (!IsEmptyPrioQueue(*Antrian))
          Prio(A) = Prio(InfoTail(*Antrian)) + 1;
        else
          Prio(A) = 1;
        
        ListWP(A) = LW;
        Enqueue(Antrian, A);
      }
    }
  }
}
/* testing */
void PrintPrioQueue(PrioQueue Antrian, int nWahana)
{
  printf("Antrian [%d/%d]\n", NBElmtPrioQueue(Antrian), MaxElPrioQueue(Antrian));
  if (!IsEmptyPrioQueue(Antrian))
  {
    PrioQueue printAntrian = Antrian;
    int j = 0;
    while (!IsEmptyPrioQueue(printAntrian))
    {
      printf("Pengungjung ke %d ", j + 1);
      Pengunjung X;
      Dequeue(&printAntrian, &X);
      printf("[");
      boolean first = true;
      for (int i =0; i < nWahana; i++)
      {
        if(X.listWahana.W[i] == 1 && first)
        {
          printf("%d",i);
          first = false;
        }
        else if (X.listWahana.W[i] == 1 && !first)
        {
          printf(",%d",i);
        }
        
      }
      printf("]");
      printf("\n");
      printf("Tingkat kesabaran %d", Kesabaran(X));
      printf("\n\n");
      j++;
    }
  }
}

boolean PengunjungWahana(Pengunjung X, int idxWahana, int nWahana)
{
  ListWahana W = ListWP(X);

  return(adaWahana(W,idxWahana,nWahana)); 
}