#include "boolean.h"
#include "jam.h"
#include "prioqueue.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void CreateEmptyPrioQueue(PrioQueue *Antrian, int Max)
/* Prosedur membuat antrian pengunjung kosong */
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
/* Prosedur membuat isi wahana kosong dengan representasi prioqueue */
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
/* Prosedur membuat penumpang dengan elemen penyusunnya */
{
  Pengunjung(*P) = X;
  JAMOut(*P) = out;
  CurrWahana(*P) = idWahana;
  Dur(*P) = durasi;
}

void CreateEmptyListWahana(ListWahana *W, int nWahana)
/* Prosedur membuat list wahana kosong */
{
  ListW(*W) = (int*) malloc (nWahana * sizeof(int));
  
  for(int i = 0; i < nWahana; i++)
  {
    ElmtWahana(*W, i) = -1;
  }
}

boolean IsEmptyPrioQueue (PrioQueue Antrian)
/* Mengirimkan true apabila antrian kosong */
{
  return (Head(Antrian)==-1) && (Tail(Antrian)==-1);
}

boolean IsEmptyPrioQueueW (PrioQueueWahana QWahana)
/* Mengirimkan true apabila isi wahana kosong */
{
  return (Head(QWahana)==-1) && (Tail(QWahana)==-1);
}

boolean IsEmptyWahana(ListWahana LWahana, int nWahana)
/* Mengirimkan true apabila list wahana kosong */
{
  return (NBElmtWahana(LWahana, nWahana)==0);
}

boolean IsFullPrioQueue (PrioQueue Antrian)
/* Mengirimkan true apabila antrian penuh */
{
  return (Head(Antrian) == (Tail(Antrian) + 1)%MaxElPrioQueue(Antrian));
}

int NBElmtWahana(ListWahana W, int nWahana)
/* Mengirimkan jumlah pengunjung dalam antrian */
/* Elemen pada list wahana bernilai 1 apabila pengunjung ingin naik wahana tersebut */
{
  int n = 0;
  
  for (int i = 0; i<nWahana; i++)
    if(ElmtWahana(W, i)!=-1) n++;

  return n;
}

int NBElmtPrioQueue (PrioQueue Antrian)
/* Mengirimkan jumlah pengunjung dalam antrian */
{
  if (IsEmptyPrioQueue(Antrian)) return 0;
  return ((Tail(Antrian) - Head(Antrian) + MaxElPrioQueue(Antrian))%MaxElPrioQueue(Antrian))+1;
}

int NBElmtPrioQueueW (PrioQueueWahana QWahana)
/* Mengirimkan jumlah queue isi wahana */
{
  if (IsEmptyPrioQueueW(QWahana)) return 0; 
  return ((Tail(QWahana) - Head(QWahana) + MaxElPrioQueue(QWahana))%MaxElPrioQueue(QWahana))+1;
}

void DeAlokasi(PrioQueue * Antrian)
/* Dealokasi antrian */

{
  Head(*Antrian) = -1;
  Tail(*Antrian) = -1;
  MaxElPrioQueue(*Antrian) = 0;
  free(Antrian->T);;
}

void DeAlokasiQWahana(PrioQueueWahana *QWahana)
/* Dealokasi isi wahana */
{
  Head(*QWahana) = -1;
  Tail(*QWahana) = -1;
  MaxElPrioQueue(*QWahana) = 0;
  free(QWahana->P);
}

void DelWahana(ListWahana *W, int idxWahana, int nWahana)
/* Menghapus wahana dengan pada indeks idxWahana pada list wahana, dilakukan dengan mengubah elemen pada array list wahana menjadi -1 */
{
  int i = 0;
  while (i < nWahana && i != idxWahana)
    i++;
  if (i != nWahana)
    ElmtWahana(*W, i) = -1; // elemen idxwahana diubah
}

void Enqueue (PrioQueue * Antrian, Pengunjung X)
{
  /* Prosedur menambahkan pengunjung ke antrian */
  if (IsEmptyPrioQueue(*Antrian))
    Head(*Antrian) = 0;
  
  Tail(*Antrian) = (Tail(*Antrian)+1) % MaxElPrioQueue(*Antrian);
  InfoTail(*Antrian) = X;
  
  int i = Tail(*Antrian);
  int j = (i + MaxElPrioQueue(*Antrian)-1)% MaxElPrioQueue(*Antrian);

  Pengunjung temp;
  while (i != Head(*Antrian) && Prio(ElmtQ(*Antrian, i)) < Prio(ElmtQ(*Antrian, j))){    
    temp = ElmtQ(*Antrian, i);
    ElmtQ(*Antrian, i) = ElmtQ(*Antrian, j);
    ElmtQ(*Antrian, j) = temp;

    i = j;
    j = (i + MaxElPrioQueue(*Antrian)-1)% MaxElPrioQueue(*Antrian);
  }
}

void EnqueueWahana (PrioQueueWahana * QWahana, Pengunjung X, int idWahana, int durasiWahana, JAM CurrTime)
/* Prosesdur menambahkan penunpang ke isi wahana */
{
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

void EnqueuePenumpang (PrioQueueWahana * QWahana, Penumpang X)
/* Prosedur menambahkan penumpang ke isi wahana dengan parameter penumpang */
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
/* Prosedur mengeluarkan pengunjung dari antrian */
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
/* Mengirimkan true apabila ada wahana dengan idxWahana pada sebuah list wahana */
{
  for (int i =0; i<nWahana; i++)
    if (i == idxWahana && ElmtWahana(LW, i) == 1)
      return true;
  return false;
}

void DequeueAntrian(PrioQueue * Antrian, Pengunjung * X, int idxWahana, int nWahana)
/* Dequeue dengan mengecek apakah pengunjung ingin menaiki wahana terkait */
{
  if (adaWahana(ListWP(InfoHead(*Antrian)), idxWahana, nWahana))
    {
      Dequeue(Antrian, X);
    }
  else
    printf("Pengunjung tidak berencana menaiki wahana tersebut\n");
}

void DequeueWahana(PrioQueueWahana *QWahana, Penumpang *X)
/* Dequeue pengunjung dari isi wahana */
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

void WahanaToAntrian (PrioQueueWahana *QWahana, Penumpang *X, JAM CurrTime,PrioQueue *Antrian, int nWahana, boolean *b)
/* Dequeue pengunjung dari isi wahana dan langsung enqueue ke antrian */
{
  if (!IsEmptyPrioQueueW(*QWahana))
  {  
    if (JGT(CurrTime, JAMOut(InfoHeadW(*QWahana))))
    {
      *X = InfoHeadW(*QWahana);
      DelWahana(&ListWP(Pengunjung(*X)), CurrWahana(InfoHeadW(*QWahana)), nWahana);
      Prio(Pengunjung(*X)) = -1;
      Kesabaran(Pengunjung(*X)) = MaxElPrioQueue(*Antrian) + 5;

      if (Head(*QWahana) == Tail(*QWahana))
      {
        Head(*QWahana) = -1;
        Tail(*QWahana) = -1;
      } 
      else 
      {
        Head(*QWahana) = (Head(*QWahana)+1)%MaxElPrioQueue(*QWahana);
      }
      
      //printf("work\n");
      if (!IsEmptyWahana(ListWP(Pengunjung(*X)), nWahana))
        Enqueue(Antrian, Pengunjung(*X));
      
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
/* Prosedur mengeluarkan pengunjung yang kesabarannya habis dari antrian */
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
/* Prosedur decrement kesabaran dari pengunjung dalam antrian */
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
/* Prosedur menambahkan pengunjung ke antrian secara acak */
{

  if (IsEmptyPrioQueue(*Antrian)) // Apabila empty maka akan mengirimkan minimal 1 pengunjung
  {
    int nEnque = rand() % 2 + 1;
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
/* Mengirimkan true apabila pengunjung X memiliki idxWahana pada list wahana yang dimilikinya, atau apabila pengunjung X ingin menaiki wahana pada idxWahana */
{
  ListWahana W = ListWP(X);

  return(adaWahana(W,idxWahana,nWahana)); 
}