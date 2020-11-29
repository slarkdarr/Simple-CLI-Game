/* File: jam.h */
/* Tanggal: 01 September 2020 */
/* Definisi ADT JAM */

#include <stdio.h>
#include "../boolean.h"
#include "jam.h"

/* ***************************************************************** */
/* DEFINISI PRIMITIF                                                 */
/* ***************************************************************** */
/* KELOMPOK VALIDASI TERHADAP TYPE                                   */
/* ***************************************************************** */
boolean IsJAMValid (int H, int M, int S)
{
    return ((H < 24 && H >= 0) && (M >= 0 && M < 60) && (S >= 0 && S < 60));
}
/* Mengirim true  jika H,M,S dapat membentuk J yang valid */
/* dipakai untuk mentest SEBELUM membentuk sebuah Jam */

/* *** Konstruktor: Membentuk sebuah JAM dari komponen-komponennya *** */
JAM MakeJAM (int HH, int MM, int SS)
{
    JAM J;
    Hour(J) = HH;
    Minute(J) = MM;
    Second(J) = SS;
    return J;
}
/* Membentuk sebuah JAM dari komponen-komponennya yang valid */
/* Prekondisi : HH, MM, SS valid untuk membentuk JAM */

/* ***************************************************************** */
/* KELOMPOK BACA/TULIS                                               */
/* ***************************************************************** */
void BacaJAM (JAM * J)
{
    int HH, MM, SS, valid;
    valid = 0;
    while (valid == 0)
    {
        scanf("%d %d %d", &HH, &MM, &SS);
        if (IsJAMValid(HH, MM, SS) == true)
        {
            *J = MakeJAM(HH, MM, SS);
            valid = 1;
        }
        else
        {
            printf("Jam tidak valid\n");
        };
    };
}
/* I.S. : J tidak terdefinisi */
/* F.S. : J terdefinisi dan merupakan jam yang valid */
/* Proses : mengulangi membaca komponen HH, MM, SS sehingga membentuk J */
/* yang valid. Tidak mungkin menghasilkan J yang tidak valid. */
/* Pembacaan dilakukan dengan mengetikkan komponen HH, MM, SS
   dalam satu baris, masing-masing dipisahkan 1 spasi, diakhiri enter. */
/* Jika JAM tidak valid maka diberikan pesan: "Jam tidak valid", dan pembacaan
   diulangi hingga didapatkan jam yang valid. */
/* Contoh:
   60 3 4
   Jam tidak valid
   1 3 4
   --> akan terbentuk JAM <1,3,4> */

void TulisJAM (JAM J)
{
    printf("%d:%d:%d", Hour(J), Minute(J), Second(J));
}
/* I.S. : J sembarang */
/* F.S. :   Nilai J ditulis dg format HH:MM:SS */
/* Proses : menulis nilai setiap komponen J ke layar dalam format HH:MM:SS
   tanpa karakter apa pun di depan atau belakangnya, termasuk spasi, enter, dll.
   Jika jam / menit / detik hanya satu digit, tuliskan satu digit tanpa 0 di depannya. */

void PrintJAM (JAM J)
{
    if (Hour(J) != 0)
    {
        printf("%d hour(s) ", Hour(J));
    }

    if (Minute(J) != 0)
    {
        printf("%d minute(s) ", Minute(J));
    }

    if (Second(J) != 0)
    {
        printf("%d seconds(s)", Second(J));
    }
}

/* ***************************************************************** */
/* KELOMPOK KONVERSI TERHADAP TYPE                                   */
/* ***************************************************************** */
long JAMToDetik (JAM J) /* tandain dulu ntar ganti */
{
    long detik;
    detik = (3600 * Hour(J)) + (60 * Minute(J)) + Second(J);
    if (detik >= 86400)
    {
        detik %= 86400;
    }
    return detik;
}
/* Diberikan sebuah JAM, mengkonversi menjadi jumlah detik dari pukul 0:0:0 */
/* Rumus : detik = 3600*HH + 60*MM + SS */
/* Nilai maksimum = 3600*23+59*60+59 */

JAM DetikToJAM (long N)
{
    int a, b, c;
    if (N >= 86400)
    {
        N %= 86400;
    }
    if (N < 0)
    {
        N += 86400;
    }
    a = N / 3600;
    b = (N % 3600) / 60; 
    c = N % 60;
    return (MakeJAM(a, b, c));
}
/* Mengirim  konversi detik ke JAM */
/* Catatan: Jika N >= 86400, maka harus dikonversi dulu menjadi jumlah detik yang
   mewakili jumlah detik yang mungkin dalam 1 hari, yaitu dengan rumus:
   N1 = N mod 86400, baru N1 dikonversi menjadi JAM */

/* ***************************************************************** */
/* KELOMPOK OPERASI TERHADAP TYPE                                    */
/* ***************************************************************** */
/* *** Kelompok Operator Relational *** */
boolean JEQ (JAM J1, JAM J2)
{
    return ((Hour(J1) == Hour(J2)) && (Minute(J1) == Minute(J2)) && (Second(J1) == Second(J2)));
}
/* Mengirimkan true jika J1=J2, false jika tidak */
boolean JNEQ (JAM J1, JAM J2)
{
    return ((Hour(J1) != Hour(J2)) || (Minute(J1) != Minute(J2)) || (Second(J1) != Second(J2)));
}
/* Mengirimkan true jika J1 tidak sama dengan J2 */
boolean JLT (JAM J1, JAM J2)
{
    return (JAMToDetik(J1) < JAMToDetik(J2));
}
/* Mengirimkan true jika J1<J2, false jika tidak */
boolean JGT (JAM J1, JAM J2)
{
    return (JAMToDetik(J1) > JAMToDetik(J2));
}
/* Mengirimkan true jika J1>J2, false jika tidak */

boolean JLET (JAM J1, JAM J2)
{
    return (JAMToDetik(J1) <= JAMToDetik(J2));
}
/* Mengirimkan true jika J1<=J2, false jika tidak */
boolean JGET (JAM J1, JAM J2)
{
    return (JAMToDetik(J1) >= JAMToDetik(J2));
}
/* Mengirimkan true jika J1>=J2, false jika tidak */

/* *** Operator aritmatika JAM *** */
JAM NextDetik (JAM J)
{
    return DetikToJAM(JAMToDetik(J) + 1);
}
/* Mengirim 1 detik setelah J dalam bentuk JAM */
JAM NextNDetik (JAM J, int N)
{
    return DetikToJAM(JAMToDetik(J) + N);
}
/* Mengirim N detik setelah J dalam bentuk JAM */
JAM PrevDetik (JAM J)
{
    return DetikToJAM(JAMToDetik(J) - 1);
}
/* Mengirim 1 detik sebelum J dalam bentuk JAM */
JAM PrevNDetik (JAM J, int N)
{
    return DetikToJAM(JAMToDetik(J) - N);
}
/* Mengirim N detik sebelum J dalam bentuk JAM */
/* *** Kelompok Operator Aritmetika *** */
long Durasi (JAM JAw, JAM JAkh)
{
    long durasi1, durasi2;
    durasi1 = JAMToDetik(JAw);
    durasi2 = JAMToDetik(JAkh);
    if (durasi1 > durasi2)
    {
        return (86400 - (durasi1 - durasi2));
    }
    else
    {
        return (durasi2 - durasi1);
    };
}
/* Mengirim JAkh-JAw dlm Detik, dengan kalkulasi */
/* Jika JAw > JAkh, maka JAkh adalah 1 hari setelah JAw */
void SetOpen (JAM *currentTime)
{
    *currentTime = MakeJAM(9, 0, 0);
}
void SetClose(JAM *currentTime)
{
    *currentTime = MakeJAM(21, 0, 0);
}