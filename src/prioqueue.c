#include "boolean.h"
//#include "wahana.h"
#include "prioqueue.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

/* Membuat PrioQueue kosong */
void CreateEmptyPrioQueue(PrioQueue *Antrian, int Max)
{
  if (Max > 0){
    Antrian->T = (Pengunjung *)malloc((Max) * sizeof(Pengunjung));
    Head(*Antrian) = Nil;
    Tail(*Antrian) = Nil;
    MaxElPrioQueue(*Antrian) = Max;
  }
  else{
    Head(*Antrian) = Nil;
    Tail(*Antrian) = Nil;
    MaxElPrioQueue(*Antrian) = 0;
  }
}

/* Jumlah wahana yang ingin dinaiki seorang pengunjung */
int NBElmt(ListWahana Wahana)
{
  int n = 0;
  for (int i = 0; i<5; i++)
    if(Wahana.W[i]!=0) n++;
  return n;
}

/* Cek PrioQueue Kosong */
boolean IsEmptyPrioQueue (PrioQueue Antrian)
{
  return (Head(Antrian)==Nil) && (Tail(Antrian)==Nil);
}

/* Cek List Wahana Kosong */
boolean IsEmptyWahana(ListWahana Wahana)
{
  return (NBElmt(Wahana)==0);
}

/* Cek PrioQueue Full */
boolean IsFull (PrioQueue Antrian)
{
  return (NBElmtPrioQueue(Antrian) == MaxElPrioQueue(Antrian));
}

/* Cek Jumlah Pengunjung dalam PrioQueue */
int NBElmtPrioQueue (PrioQueue Antrian)
{
  if (IsEmptyPrioQueue(Antrian))
  {
    return 0;
  }
  else{
    int El = ((Tail(Antrian) - Head(Antrian) + MaxElPrioQueue(Antrian)) % MaxElPrioQueue(Antrian)) + 1;
    return El;
  }
}

/* Mengosongkan PrioQueue */
void DeAlokasi(PrioQueue * Antrian)
{
  free(Antrian->T);
  MaxElPrioQueue(*Antrian) = 0;
}

/* Menghapus wahana pada elemen tertentu */
void DelWahana(ListWahana *Wahana, int idxWahana)
{
  int i = 0;
  while (i < 5 && Wahana->W[i] != idxWahana)
    i++;
  if (i != 5)
    Wahana->W[i] = Nil;
}

void Enqueue (PrioQueue * Antrian, Pengunjung X)
{
  // Kasus kosong
  if (IsEmptyPrioQueue(*Antrian)){
    Head(*Antrian) = 0;
    Tail(*Antrian) = 0;
    InfoHead(*Antrian) = X;
  }

  else{
    int geser = NBElmtPrioQueue(*Antrian);
    int idx = Tail(*Antrian);

    while(geser > 0 && Prio(Elmt(*Antrian, idx)) > Prio(X)){
      Elmt(*Antrian, (idx % MaxElPrioQueue(*Antrian) + 1)) = Elmt(*Antrian, idx);

      geser -= 1; idx -=1; 

      if (idx = -1){
        idx = MaxElPrioQueue(*Antrian) - 1;;
      } 
    }
    printf("Ini enqueue %d\n", Prio(X));
    int idxp = idx % MaxElPrioQueue(*Antrian) + 1;
    Elmt(*Antrian, idxp) = X;
    Tail(*Antrian) = Tail(*Antrian) % MaxElPrioQueue(*Antrian) + 1;
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

/* Mengirimkan durasi dan money */
void DequeueVersi2 (PrioQueue * Q, Pengunjung * X, int *Minute, int *money, int idxWahana)
{
  *X = InfoHead(*Q);
  DelWahana(&X->listWahana, idxWahana);
  // getDurasi
  // getMoney
  if (Head(*Q)==Tail(*Q)) {
    Head(*Q)=Nil;
    Tail(*Q)=Nil;
  } 
  else 
  {
    if (Head(*Q) == MaxElPrioQueue(*Q)-1) 
      Head(*Q) = 1;
    else 
      Head(*Q)++;
  }
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
      Kesabaran(Elmt(*Antrian, idx)) -= 1;
      Prio(Elmt(*Antrian, idx)) -= 1;
      idx = (idx+1)%MaxElPrioQueue(*Antrian);
    }
    Kesabaran(Elmt(*Antrian, Tail(*Antrian))) -= 1;
    Prio(Elmt(*Antrian, idx)) -= 1;
  }
}

/* Memunculkan pengunjung secara random ke antrian */
void RandomEnqueue(PrioQueue *Q) // Memunculkan Pengunjung
{
  int x = rand() % 60;
  ListWahana list = {0,0,0,0,0};

  printf("%d\n", x);
  if (x%3==0){
    int y = rand() % 50;

    if (y%2==0 && (y<10 || y>40))
    {
      list.W[0] = 1;
    }
    if(y%3==0 && y>20)
    {
      list.W[1] = 2;
    }
    if (y%4==0 && y>10)
    {
      list.W[2] = 3;
    }
    if(y%5==0)
    {
      list.W[3] = 4;
    }
    if(y%6==0 || y%25==0)
    {
      list.W[4] = 5;
    }
    printf("%d\n", y);    
  }
  if (!IsEmptyWahana(list)){
    Pengunjung A;
    A.kesabaran = 10;
    A.prio = 10;
    A.listWahana = list;
    Enqueue(Q, A);
  }
}

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