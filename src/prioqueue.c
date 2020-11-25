#include "boolean.h"
//#include "wahana.h"
#include "prioqueue.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "game.h"


void CreateEmptyPrioQueue(PrioQueue *Antrian, int Max)
{
  if (Max > 0)
  {
    Antrian->T = (Pengunjung *)malloc((Max) * sizeof(Pengunjung));
    Head(*Antrian) = Nil;
    Tail(*Antrian) = Nil;
    MaxElPrioQueue(*Antrian) = Max;
  }
  else
  {
    Head(*Antrian) = Nil;
    Tail(*Antrian) = Nil;
    MaxElPrioQueue(*Antrian) = 0;
  }
}
void CreateEmptyPrioQueueWahana(PrioQueueWahana *Wahana)
{
  Wahana->P = (Penumpang *) malloc((1000) * sizeof(Penumpang));
  Head(*Wahana) = Nil;
  Tail(*Wahana) = Nil;
  MaxElPrioQueue(*Wahana) = 100;
}

void CreatePenumpang(Penumpang *P, JAM out, int idWahana, Pengunjung X, int x)
{
  P->T = X;
  P->out = out;
  P->idWahana = idWahana;
  P->durasi = x;
}

void CreateEmptyListWahana(ListWahana *W)
{
  W = (int)malloc(_wCount*sizeof(int));
  
  for(int i = 0; i < _wCount; i++)
  {
    W->W[i] = Nil;
  }
}

boolean IsEmptyPrioQueue (PrioQueue Antrian)
{
  return (Head(Antrian)==Nil) && (Tail(Antrian)==Nil);
}

boolean IsEmptyPrioQueueW (PrioQueueWahana Antrian)
{
  return (Head(Antrian)==Nil) && (Tail(Antrian)==Nil);
}

boolean IsEmptyWahana(ListWahana Wahana)
{
  return (NBElmtWahana(Wahana)==0);
}

boolean IsFullPrioQueue (PrioQueue Antrian)
{
  return (NBElmtPrioQueue(Antrian) == MaxElPrioQueue(Antrian));
}

int NBElmtWahana(ListWahana Wahana)
{
  int n = 0;
  
  for (int i = 0; i<_wCount; i++)
    if(Wahana.W[i]!=-1) n++;

  return n;
}

int NBElmtPrioQueue (PrioQueue Antrian)
{
  if (IsEmptyPrioQueue(Antrian))
  {
    return 0;
  }
  else
  {
    int El = ((Tail(Antrian) - Head(Antrian) + MaxElPrioQueue(Antrian)) % MaxElPrioQueue(Antrian)) + 1;
    return El;
  }
}

int NBElmtPrioQueueW (PrioQueueWahana Antrian)
{
  if (IsEmptyPrioQueueW(Antrian))
  {
    return 0;
  }
  else
  {
    int El = ((Tail(Antrian) - Head(Antrian) + MaxElPrioQueue(Antrian)) % MaxElPrioQueue(Antrian)) + 1;
    return El;
  }
}

void DeAlokasi(PrioQueue * Antrian)
{
  free(Antrian->T);
  MaxElPrioQueue(*Antrian) = 0;
}

void DeAlokasiQWahana(PrioQueueWahana *Wahana)
{
  free(Wahana->P);
}

void DelWahana(ListWahana *Wahana, int idxWahana)
{
  int i = 0;
  while (i < _wCount && i != idxWahana)
    i++;
  if (i != _wCount)
    Wahana->W[i] = Nil;
}

void Enqueue (PrioQueue * Antrian, Pengunjung X)
{
  if (IsEmptyPrioQueue(*Antrian))
  {
    Head(*Antrian) = 0;
    Tail(*Antrian) = 0;
    InfoHead(*Antrian) = X;
  }

  else
  {
    int geser = NBElmtPrioQueue(*Antrian);
    int idx = Tail(*Antrian);

    while(geser > 0 && Prio(ElmtQ(*Antrian, idx)) > Prio(X))
    {
      ElmtQ(*Antrian, (idx % MaxElPrioQueue(*Antrian) + 1)) = ElmtQ(*Antrian, idx);

      geser -= 1; idx -=1; 

      if (idx = -1)
      {
        idx = MaxElPrioQueue(*Antrian) - 1;;
      } 
    }
    //printf("Ini enqueue %d\n", Prio(X));
    int idxp = idx % MaxElPrioQueue(*Antrian) + 1;
    ElmtQ(*Antrian, idxp) = X;
    Tail(*Antrian) = Tail(*Antrian) % MaxElPrioQueue(*Antrian) + 1;
  }
}

void EnqueueWahana (PrioQueueWahana * Wahana, Pengunjung X, int idWahana)
{
  /* Create Penumpang */
  Penumpang PNew;
  int durasi = JAMToDetik(WahanaDurasi(_wType(idWahana))) + JAMToDetik(_time);
  JAM out = DetikToJAM(durasi);

  CreatePenumpang(&PNew, out, idWahana, X, durasi);

  if (IsEmptyPrioQueueW(*Wahana))
  {
    Head(*Wahana) = 0;
    Tail(*Wahana) = 0;
    InfoHeadW(*Wahana) = PNew;
  }

  else
  {
    // diurutkan berdasarkan durasi wahana
    int geser = NBElmtPrioQueueW(*Wahana);
    int idx = Tail(*Wahana);

    while(geser > 0 && Dur(ElmtW(*Wahana, idx)) > Dur(PNew))
    {
      ElmtW(*Wahana, (idx % MaxElPrioQueue(*Wahana) + 1)) = ElmtW(*Wahana, idx);

      geser -= 1; idx -=1; 

      if (idx = -1)
      {
        idx = MaxElPrioQueue(*Wahana) - 1;;
      } 
    }
    //printf("Ini enqueue %d\n", Prio(X));
    int idxp = idx % MaxElPrioQueue(*Wahana) + 1;
    ElmtW(*Wahana, idxp) = PNew;
    Tail(*Wahana) = Tail(*Wahana) % MaxElPrioQueue(*Wahana) + 1;
  }
}

void Dequeue (PrioQueue * Antrian, Pengunjung * X)
{
  *X = InfoHead(*Antrian);

  if (Head(*Antrian)==Tail(*Antrian)) 
  {
		Head(*Antrian)=Nil;
		Tail(*Antrian)=Nil;
	} 
  else 
  {
	  if (Head(*Antrian) == MaxElPrioQueue(*Antrian)-1) 
      Head(*Antrian) = 1;
		else 
      Head(*Antrian)++;
	}
}

boolean adaWahana(ListWahana LW, int idxWahana)
{
  for (int i =0; i<5; i++)
    if (i == idxWahana && LW.W[i] == 1)
      return true;
  return false;
}

void DequeueAntrian(PrioQueue * Antrian, Pengunjung * X, int idxWahana)
{
  if (adaWahana(ListWahana(InfoHead(*Antrian)), idxWahana))
    {
      Dequeue(Antrian, X);
      // _money += WahanaMoney
    }
  else
    printf("Wahana tidak ada di daftar\n");
}

void DequeueWahana(PrioQueueWahana *Wahana, Pengunjung *X)
{
  if (JGT(_time, JAMOut(InfoHeadW(*Wahana))))
  {
    *X = Pengunjung(InfoHeadW(*Wahana));
    DelWahana(&ListWahana(*X), CurrWahana(InfoHeadW(*Wahana)));
  }
}

void DequeueWahana2 (PrioQueueWahana *Wahana)
{
  // penumpang dicek satu satu apakah durasi sudah lewat
}
/* Menghapus pengunjung yang kesabaran nya habis */
void KesabaranHabis(PrioQueue *Antrian)
{
  int i = 0;
  PrioQueue AntrianNew;
  Pengunjung x;
  CreateEmptyPrioQueue(&AntrianNew, 5);

  while (!IsEmptyPrioQueue(*Antrian))
  {
    Dequeue(Antrian, &x);
    if (x.kesabaran != 0)
      Enqueue(&AntrianNew, x);
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
      idx = (idx+1)%MaxElPrioQueue(*Antrian);
    }
    Kesabaran(ElmtQ(*Antrian, Tail(*Antrian))) -= 1;
  }
}

void setPrio(Pengunjung *X, int prio)
{
  X->prio = prio;
}
/*
void RandomEnqueue(PrioQueue *Q) // Memunculkan Pengunjung
{
  int x = rand() % 60;
  ListWahana list;
  CreateEmptyListWahana(&list);

  printf("%d\n", x);
  if (x%3==0){
    int y = rand() % 50;

    if (y%2==0 && (y<10 || y>40))
    {
      list.W[0] = 1;
    }
    if(y%3==0 && y>20)
    {
      list.W[1] = 1;
    }
    if (y%4==0 && y>10)
    {
      list.W[2] = 1;
    }
    if(y%5==0)
    {
      list.W[3] = 1;
    }
    if(y%6==0 || y%25==0)
    {
      list.W[4] = 1;
    }
    printf("%d\n", y);    
  }

  if (!IsEmptyWahana(list)){
    Pengunjung A;
    A.kesabaran = 10;
    if (!IsEmptyPrioQueue(*Q))
      A.prio = Prio(ElmtQ(*Q, Tail(*Q))) + 1;
    else
      A.prio = 1;
    
    A.listWahana = list;
    Enqueue(Q, A);
  }
}
*/
/* testing */
void PrintPrioQueue(PrioQueue Antrian)
{
  PrioQueue printAntrian = Antrian;
  int j =0;
  while (!IsEmptyPrioQueue(printAntrian))
  {
    printf("Pengungjung ke %d ", j);
    Pengunjung X;
    Dequeue(&printAntrian, &X);
    for (int i =0; i < 5; i++)
    {
      if(X.listWahana.W[i] != 0)
      {
        printf("%d=%d",i, X.listWahana.W[i]);
      }
    }
    printf("\n");
    j++;
  }
}
