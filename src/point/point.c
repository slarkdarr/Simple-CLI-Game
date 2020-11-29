#include <stdio.h>
#include <math.h>
#include "point.h"

#define M_PI 3.14159

/* *** DEFINISI PROTOTIPE PRIMITIF *** */
/* *** Konstruktor membentuk POINT *** */
POINT MakePOINT (int X, int Y)
{
   POINT P;
   Absis(P) = X;
   Ordinat(P) = Y;
   return P;
}
/* Membentuk sebuah POINT dari komponen-komponennya */

/* *** KELOMPOK Interaksi dengan I/O device, BACA/TULIS  *** */
void BacaPOINT (POINT * P)
{
   int X, Y;
   scanf("%d %d", &X, &Y);
   *P = MakePOINT(X, Y);
}
/* Membaca nilai absis dan ordinat dari keyboard dan membentuk
   POINT P berdasarkan dari nilai absis dan ordinat tersebut */
/* Komponen X dan Y dibaca dalam 1 baris, dipisahkan 1 buah spasi */
/* Contoh: 1 2
   akan membentuk POINT <1,2> */
/* I.S. Sembarang */
/* F.S. P terdefinisi */
void TulisPOINT (POINT P)
{
   printf("(%d,%d)\n", Absis(P), Ordinat(P));
}
/* Nilai P ditulis ke layar dengan format "(X,Y)"
   tanpa spasi, enter, atau karakter lain di depan, belakang,
   atau di antaranya
   Output X dan Y harus dituliskan dalam bilangan riil dengan 2 angka di belakang koma.
*/
/* I.S. P terdefinisi */
/* F.S. P tertulis di layar dengan format "(X,Y)" */

/* *** Kelompok operasi relasional terhadap POINT *** */
boolean POINT_EQ (POINT P1, POINT P2)
{
   return ((Absis(P1) == Absis(P2) && (Ordinat(P1) == Ordinat(P2))));
}
/* Mengirimkan true jika P1 = P2 : absis dan ordinatnya sama */
boolean POINT_NEQ (POINT P1, POINT P2)
{
   return ((Absis(P1) != Absis(P2) || (Ordinat(P1) != Ordinat(P2))));
}
/* Mengirimkan true jika P1 tidak sama dengan P2 */

/* *** Kelompok menentukan di mana P berada *** */
boolean IsOrigin (POINT P)
{
   return (Absis(P) == 0) && (Ordinat(P) == 0);
}
/* Menghasilkan true jika P adalah titik origin */
boolean IsOnSbX (POINT P)
{
   return (Ordinat(P) == 0);
}
/* Menghasilkan true jika P terletak Pada sumbu X */
boolean IsOnSbY (POINT P)
{
   return (Absis(P) == 0);
}
/* Menghasilkan true jika P terletak pada sumbu Y */
int Kuadran (POINT P)
{
   if ((IsOrigin(P) == true) || (IsOnSbX(P) == true) || (IsOnSbY(P) == true)) 
   {
      return -1;
   }
   if ((Absis(P) > 0) && (Ordinat(P) > 0))
   {
      return 1;
   }
   if ((Absis(P) < 0) && (Ordinat(P) > 0))
   {
      return 2;
   };
   if ((Absis(P) < 0) && (Ordinat(P) < 0))
   {
      return 3;
   }
   if ((Absis(P) > 0) && (Ordinat (P) <0))
   {
      return 4;
   };
}
/* Menghasilkan kuadran dari P: 1, 2, 3, atau 4 */
/* Prekondisi : P bukan titik origin, */
/*              dan P tidak terletak di salah satu sumbu */

/* *** KELOMPOK OPERASI LAIN TERHADAP TYPE *** */
POINT NextX (POINT P)
{
   return (MakePOINT(Absis(P) + 1, Ordinat(P)));
}
/* Mengirim salinan P dengan absis ditambah satu */
POINT NextY (POINT P)
{
   return (MakePOINT(Absis(P), Ordinat(P) + 1));
}
/* Mengirim salinan P dengan ordinat ditambah satu */
POINT PlusDelta (POINT P, int deltaX, int deltaY)
{
   return (MakePOINT(Absis(P) + deltaX, Ordinat(P) + deltaY));
}
/* Mengirim salinan P yang absisnya adalah Absis(P) + deltaX dan ordinatnya adalah Ordinat(P) + deltaY */
POINT MirrorOf (POINT P, boolean SbX)
{
   if (SbX == true)
   {
      return (MakePOINT(Absis(P), Ordinat(P) * -1));
   }
   else
   {
      return (MakePOINT(Absis(P) * -1, Ordinat(P)));
   }
   
}
/* Menghasilkan salinan P yang dicerminkan terhadap salah satu sumbu */
/* Jika SbX bernilai true, maka dicerminkan terhadap sumbu X */
/* Jika SbX bernilai false, maka dicerminkan terhadap sumbu Y */
float Jarak0 (POINT P)
{
   float a;
   a = (sqrt((Absis(P) * Absis(P)) + (Ordinat(P) * Ordinat(P))));
   return a;
}
/* Menghitung jarak P ke (0,0) */
float Panjang (POINT P1, POINT P2)
{
   float b;
   b = (sqrt(((Absis(P1) - Absis(P2)) * (Absis(P1) - Absis(P2))) + ((Ordinat(P1) - Ordinat(P2)) * (Ordinat(P1) - Ordinat(P2)))));
   return b; 
}
/* Menghitung panjang garis yang dibentuk P1 dan P2 */
/* Perhatikanlah bahwa di sini spec fungsi kurang baik sebab menyangkut ADT Garis. */
/* Tuliskan spec fungsi yang lebih tepat. */
/* Spek dari fungsi Panjang adalah merupakan fungsi yang menghitung jarak antar dua Point */
void Geser (POINT *P, int deltaX, int deltaY)
{
   *P = PlusDelta(*P, deltaX, deltaY);
}
/* I.S. P terdefinisi */
/* F.S. P digeser, absisnya sebesar deltaX dan ordinatnya sebesar deltaY */
void GeserKeSbX (POINT *P)
{
   Ordinat(*P) = 0;
}
/* I.S. P terdefinisi */
/* F.S. P berada pada sumbu X dengan absis sama dengan absis semula. */
/* Proses : P digeser ke sumbu X. */
/* Contoh : Jika koordinat semula (9,9), maka menjadi (9,0) */
void GeserKeSbY (POINT *P)
{
   Absis(*P) = 0;
}
/* I.S. P terdefinisi*/
/* F.S. P berada pada sumbu Y dengan ordinat yang sama dengan semula. */
/* Proses : P digeser ke sumbu Y. */
/* Contoh : Jika koordinat semula (9,9), maka menjadi (0,9) */
void Mirror (POINT *P, boolean SbX)
{
   *P = MirrorOf(*P, SbX);
}
/* I.S. P terdefinisi */
/* F.S. P dicerminkan tergantung nilai SbX atau SbY */
/* Jika SbX true maka dicerminkan terhadap sumbu X */
/* Jika SbX false maka dicerminkan terhadap sumbu Y */
void Putar (POINT *P, int Sudut)
{
   float putarx, putary;
   Sudut = ((Sudut * M_PI) / 180);
   putarx = (cos(Sudut) * Absis(*P)) + (sin(Sudut) * Ordinat(*P));
   putary = (cos(Sudut) * Ordinat(*P)) - (sin(Sudut) * Absis(*P));
   Absis(*P) = putarx;
   Ordinat(*P) = putary;
}
/* I.S. P terdefinisi */
/* F.S. P digeser sebesar Sudut derajat dengan sumbu titik (0,0) searah jarum jam*/