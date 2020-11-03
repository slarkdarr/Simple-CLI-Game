#include "boolean.h"
#include "matriks.h"
#include <stdio.h>

/* ********** DEFINISI PROTOTIPE PRIMITIF ********** */              
/* *** Konstruktor membentuk MATRIKS *** */
void MakeMATRIKS (int NB, int NK, MATRIKS * M)
{
    NBrsEff(*M) = NB;
    NKolEff(*M) = NK;
}
/* Membentuk sebuah MATRIKS "kosong" yang siap diisi berukuran NB x NK di "ujung kiri" memori */
/* I.S. NB dan NK adalah valid untuk memori matriks yang dibuat */
/* F.S. Matriks M sesuai dengan definisi di atas terbentuk */

/* *** Selektor "DUNIA MATRIKS" *** */
boolean IsIdxValid (int i, int j)
{
    return ((i <= BrsMax && i >= BrsMin) && (j <= KolMax && j >= KolMin));
}
/* Mengirimkan true jika i, j adalah indeks yang valid untuk matriks apa pun */

/* *** Selektor: Untuk sebuah matriks M yang terdefinisi: *** */
indeks GetFirstIdxBrs (MATRIKS M)
{
    return (BrsMin);
}
/* Mengirimkan indeks baris terkecil M */
indeks GetFirstIdxKol (MATRIKS M)
{
    return (KolMin);
}
/* Mengirimkan indeks kolom terkecil M */
indeks GetLastIdxBrs (MATRIKS M)
{
    return (NBrsEff(M) - 1);
}
/* Mengirimkan indeks baris terbesar M */
indeks GetLastIdxKol (MATRIKS M)
{
    return (NKolEff(M) - 1);
}
/* Mengirimkan indeks kolom terbesar M */
boolean IsIdxEff (MATRIKS M, indeks i, indeks j)
{
    return ((i >= BrsMin && i < NBrsEff(M)) && (j >= KolMin && j < NKolEff(M)));
}
/* Mengirimkan true jika i, j adalah indeks efektif bagi M */
ElType GetElmtDiagonal (MATRIKS M, indeks i)
{
    return (Elmt(M, i, i));
}
/* Mengirimkan elemen M(i,i) */

/* ********** Assignment  MATRIKS ********** */
void CopyMATRIKS (MATRIKS MIn, MATRIKS * MHsl)
{
    int i, j;
    /* TODO */
    MakeMATRIKS(NBrsEff(MIn), NKolEff(MIn), MHsl);
    for (i = BrsMin; i < NBrsEff(MIn); i++)
    {
        for (j = KolMin; j < NKolEff(MIn); j++)
        {
            Elmt(*MHsl, i, j) = Elmt(MIn, i, j);
        }
    }
}
/* Melakukan assignment MHsl  MIn */

/* ********** KELOMPOK BACA/TULIS ********** */ 
void BacaMATRIKS (MATRIKS * M, int NB, int NK)
{
    int i, j;
    /* TODO */
    MakeMATRIKS(NB, NK, M);
    for (i = BrsMin; i < NB; i++)
    {
        for (j = KolMin; j < NK; j++)
        {
            scanf("%d", &Elmt(*M, i, j));
        }
    }
}
/* I.S. IsIdxValid(NB,NK) */ 
/* F.S. M terdefinisi nilai elemen efektifnya, berukuran NB x NK */
/* Proses: Melakukan MakeMATRIKS(M,NB,NK) dan mengisi nilai efektifnya */
/* Selanjutnya membaca nilai elemen per baris dan kolom */
/* Contoh: Jika NB = 3 dan NK = 3, maka contoh cara membaca isi matriks :
1 2 3
4 5 6
8 9 10 
*/
void TulisMATRIKS (MATRIKS M)
{
    int i, j;
    for (i = BrsMin; i < NBrsEff(M); i++)
    {
        for (j = KolMin; j < NKolEff(M); j++)
        {
            printf("%d", Elmt(M, i, j));
            if (j != NKolEff(M) - 1)
            {
                printf(" ");
            }
        }
        if (i != NBrsEff(M) - 1)
        {
            printf("\n");
        }
    }
}
/* I.S. M terdefinisi */
/* F.S. Nilai M(i,j) ditulis ke layar per baris per kolom, masing-masing elemen per baris 
   dipisahkan sebuah spasi */
/* Proses: Menulis nilai setiap elemen M ke layar dengan traversal per baris dan per kolom */
/* Contoh: menulis matriks 3x3 (ingat di akhir tiap baris, tidak ada spasi)
1 2 3
4 5 6
8 9 10
*/

/* ********** KELOMPOK OPERASI ARITMATIKA TERHADAP TYPE ********** */                                  
MATRIKS TambahMATRIKS (MATRIKS M1, MATRIKS M2)
{
    int i, j;
    MATRIKS MSum;
    if (NBrsEff(M1) == NBrsEff(M2) && NKolEff(M1) == NKolEff(M2))
    {
        MakeMATRIKS(NBrsEff(M1), NKolEff(M1), &MSum);
        for (i = BrsMin; i < NBrsEff(M1); i++)
        {
            for (j = KolMin; j < NKolEff(M1); j++)
            {
                Elmt(MSum, i, j) = Elmt(M1, i, j) + Elmt(M2, i, j);
            }
        }
    }
    return MSum;
}
/* Prekondisi : M1  berukuran sama dengan M2 */
/* Mengirim hasil penjumlahan matriks: M1 + M2 */ 
MATRIKS KurangMATRIKS (MATRIKS M1, MATRIKS M2)
{
    int i, j;
    MATRIKS MSum;
    MakeMATRIKS(NBrsEff(M1), NKolEff(M1), &MSum);
    for (i = BrsMin; i < NBrsEff(M1); i++)
    {
        for (j = KolMin; j < NKolEff(M1); j++)
        {
            Elmt(MSum, i, j) = Elmt(M1, i, j) - Elmt(M2, i, j);
        }
    }
    return MSum;
}
/* Prekondisi : M berukuran sama dengan M */
/* Mengirim hasil pengurangan matriks: salinan M1 – M2 */ 
MATRIKS KaliMATRIKS (MATRIKS M1, MATRIKS M2)
/* TODO */
{
    MATRIKS MSum;
    int i, j, k;
    MakeMATRIKS(NBrsEff(M1), NKolEff(M2), &MSum);
    for (i = BrsMin; i < NBrsEff(M1); i++)
    {
        for (j = KolMin; j < NKolEff(M2); j++)
        {
            for (k = KolMin; k < NKolEff(M1); k++)
            {
                Elmt(MSum, i, j) += (Elmt(M1, i, k) * Elmt(M2, k, j));
            }
        }
    }
    return MSum;
}
/* Prekondisi : Ukuran kolom efektif M1 = ukuran baris efektif M2 */
/* Mengirim hasil perkalian matriks: salinan M1 * M2 */
MATRIKS KaliKons (MATRIKS M, ElType X)
{
    int i, j;
    MATRIKS MSum;
    MakeMATRIKS(NBrsEff(M), NKolEff(M), &MSum);
    for (i = BrsMin; i < NBrsEff(M); i++)
    {
        for (j = KolMin; j < NKolEff(M); j++)
        {
            Elmt(MSum, i, j) = Elmt(M, i, j) * X;
        }
    }
    return MSum;
}
/* Mengirim hasil perkalian setiap elemen M dengan X */
void PKaliKons (MATRIKS * M, ElType K)
{
    int i, j;
    for (i = BrsMin; i < NBrsEff(*M); i++)
    {
        for (j = KolMin; j < NKolEff(*M); j++)
        {
            Elmt(*M, i, j) *= K;
        }
    }
}
/* I.S. M terdefinisi, K terdefinisi */
/* F.S. Mengalikan setiap elemen M dengan K */

/* ********** KELOMPOK OPERASI RELASIONAL TERHADAP MATRIKS ********** */
boolean MATRIKS_EQ (MATRIKS M1, MATRIKS M2)
{
    boolean same;
    int i, j;
    same = true;
    if (NBrsEff(M1) == NBrsEff(M2) && NKolEff(M1) == NKolEff(M2))
    {
        while (i < NBrsEff(M1) && j <= NKolEff(M1) && same == true)
        {
            if (Elmt(M1, i, j) == Elmt(M2, i, j))
            {
                j += 1;
                if (j == NKolEff(M1))
                {
                    j = KolMin;
                    i += 1;
                }
            }
            else
            {
                same = false;
            }
        }
    }
    else
    {
        same = false;
    }
    return same;
}
/* Mengirimkan true jika M1 = M2, yaitu NBElmt(M1) = NBElmt(M2) dan */
/* untuk setiap i,j yang merupakan indeks baris dan kolom M1(i,j) = M2(i,j) */
/* Juga merupakan strong EQ karena GetFirstIdxBrs(M1) = GetFirstIdxBrs(M2) 
   dan GetLastIdxKol(M1) = GetLastIdxKol(M2) */
boolean MATRIKS_NEQ (MATRIKS M1, MATRIKS M2)
/* TODO */
{
    return !(MATRIKS_EQ(M1, M2));
}
/* Mengirimkan true jika M1 tidak sama dengan M2 */
boolean EQSize (MATRIKS M1, MATRIKS M2)
{
    return (NBrsEff(M1) == NBrsEff(M2) && NKolEff(M1) == NKolEff(M2));
}
/* Mengirimkan true jika ukuran efektif matriks M1 sama dengan ukuran efektif M2 */
/* yaitu GetBrsEff(M1) = GetNBrsEff (M2) dan GetNKolEff (M1) = GetNKolEff (M2) */

/* ********** Operasi lain ********** */
int MATRIKS_NBElmt (MATRIKS M)
{
    return (NBrsEff(M) * NKolEff(M));
}
/* Mengirimkan banyaknya elemen M */

/* ********** KELOMPOK TEST TERHADAP MATRIKS ********** */
boolean IsBujurSangkar (MATRIKS M)
{
    return (NBrsEff(M) == NKolEff(M));
}
/* Mengirimkan true jika M adalah matriks dg ukuran baris dan kolom sama */
boolean IsSimetri (MATRIKS M)
{
    int i, j;
    boolean simetri;
    simetri = true;
    i = BrsMin;
    j = KolMin;
    if (IsBujurSangkar(M))
    {
        while (simetri == true && i < NBrsEff(M) && j <= NKolEff(M))
        {
            if (Elmt(M, i, j) == Elmt(M, j, i))
            {
                j += 1;
            }
            else
            {
                simetri = false;
            }
            if (j == NKolEff(M))
            {
                j = KolMin;
                i += 1;
            }
        }
    }
    else
    {
        simetri = false;
    }
    return simetri;
}
/* Mengirimkan true jika M adalah matriks simetri : IsBujurSangkar(M) 
   dan untuk setiap elemen M, M(i,j)=M(j,i) */
boolean IsSatuan (MATRIKS M)
{
    int i, j;
    boolean satuan;
    satuan = true;
    i = BrsMin;
    j = KolMin;
    if (IsBujurSangkar(M))
    {
        while (satuan == true && i < NBrsEff(M) && j <= NKolEff(M))
        {
            if (i == j)
            {
                if (Elmt(M, i, j) != 1)
                {
                    satuan = false;
                }
            }
            else
            {
                if (Elmt(M, i, j) != 0)
                {
                    satuan = false;
                }
            }
            j += 1;
            if (j == NKolEff(M))
            {
                j = KolMin;
                i += 1;
            }
        }
    }
    else
    {
        satuan = false;
    }
    return satuan;
}
/* Mengirimkan true jika M adalah matriks satuan: IsBujurSangkar(M) dan 
   setiap elemen diagonal M bernilai 1 dan elemen yang bukan diagonal bernilai 0 */ 
boolean IsSparse (MATRIKS M)
/* TODO */
{
    int count, jarang, i, j;
    jarang = (MATRIKS_NBElmt(M) / 20);
    count = 0;
    for (i = BrsMin; i < NBrsEff(M); i++)
    {
        for (j = KolMin; j < NKolEff(M); j++)
        {
            if (Elmt(M, i, j) != 0)
            {
                count += 1;
            }
        }
    }
    if (count > jarang)
    {
        return false;
    }
    else
    {
        return true;
    }
}
/* Mengirimkan true jika M adalah matriks sparse: mariks “jarang” dengan definisi: 
   hanya maksimal 5% dari memori matriks yang efektif bukan bernilai 0 */ 
MATRIKS Inverse1 (MATRIKS M)
{
    MATRIKS MInverse;
    MakeMATRIKS(NBrsEff(M), NKolEff(M), &MInverse);
    int i, j;
    for (i = BrsMin; i < NBrsEff(M); i++)
    {
        for (j = KolMin; j < NKolEff(M); j++)
        {
            Elmt(MInverse, i, j) = Elmt(M, i, j) * -1;
        }
    }
    return MInverse;
}
/* Menghasilkan salinan M dengan setiap elemen "di-invers", yaitu dinegasikan (dikalikan -1) */
float Determinan (MATRIKS M)
/* TODO */
{
    MATRIKS MMinor;
    int basis, i, kolM, kolMinor, sign;
    float det;
    MakeMATRIKS(NBrsEff(M) - 1, NKolEff(M) - 1, &MMinor);
    if(NBrsEff(M) == 0)
    {
        return 0;
    }
    if(NBrsEff(M) == 1) 
    {
        return (Elmt(M, 0, 0));
    }
    if(NBrsEff(M) == 2)
    {
        return (Elmt(M, 0, 0) * Elmt(M, 1, 1) - Elmt(M, 0, 1) * Elmt(M, 1, 0));
    }
    det = 0;
    sign = 1;
    for (basis = 0; basis < NBrsEff(M) ; basis++)
    {
        for (i = 1; i < NBrsEff(M); i++)
        {
            kolMinor = 0;
            for (kolM = 0; kolM < NKolEff(M); kolM++)
            {
                if (kolM != basis) 
                {
                    Elmt(MMinor, i - 1, kolMinor) = Elmt(M, i, kolM);
                    kolMinor += 1;
                }
            }
        }
        det += (sign * Elmt(M, 0, basis) * Determinan(MMinor));
        sign *= -1;
    }
    return det;
}
/* Prekondisi: IsBujurSangkar(M) */
/* Menghitung nilai determinan M */
void PInverse1 (MATRIKS * M)
{
    int i, j;
    for (i = BrsMin; i < NBrsEff(*M); i++)
    {
        for (j = KolMin; j < NKolEff(*M); j++)
        {
            Elmt(*M, i, j) = Elmt(*M, i, j) * -1;
        }
    }
}
/* I.S. M terdefinisi */
/* F.S. M di-invers, yaitu setiap elemennya dinegasikan (dikalikan -1) */
void Transpose (MATRIKS * M)
{
    int i, j, temp;
    for (i = BrsMin; i < NBrsEff(*M); i++)
    {
        for (j = i; j < NKolEff(*M); j++)
        {
            temp = Elmt(*M, i, j);
            Elmt(*M, i, j) = Elmt(*M, j, i);
            Elmt(*M, j, i) = temp;
        }
    }
}
/* I.S. M terdefinisi dan IsBujursangkar(M) */
/* F.S. M "di-transpose", yaitu setiap elemen M(i,j) ditukar nilainya dengan elemen M(j,i) */

/* Operasi berbasis baris dan per kolom */

float RataBrs (MATRIKS M, indeks i)
{
    int j;
    float sum;
    sum = 0;
    for (j = GetFirstIdxKol(M); j <= GetLastIdxKol(M); j++)
    {
        sum += Elmt(M, i, j);
    }
    return (sum / (NKolEff(M)));
}
/* Menghasilkan rata-rata dari elemen pada baris ke-i */
/* Prekondisi: i adalah indeks baris efektif dari M */
float RataKol (MATRIKS M, indeks j)
{
    int i;
    float sum;
    sum = 0;
    for (i = GetFirstIdxBrs(M); i <= GetLastIdxBrs(M); i++)
    {
        sum += Elmt(M, i, j);
    }
    return (sum / (NBrsEff(M)));
}
/* Menghasilkan rata-rata dari elemen pada kolom ke-j */
/* Prekondisi: j adalah indeks kolom efektif dari M */
void MaxMinBrs (MATRIKS M, indeks i, ElType * max, ElType * min)
{
    int j;
    *max = Elmt(M, i, 0);
    *min = Elmt(M, i, 0);
    for (j = GetFirstIdxKol(M); j <= GetLastIdxKol(M); j++)
    {
        if (*max < Elmt(M, i, j))
        {
            *max = Elmt(M, i, j);
        }
        if (*min > Elmt(M, i, j))
        {
            *min = Elmt(M, i, j);
        }
    }
}
/* I.S. i adalah indeks baris efektif dari M, M terdefinisi */
/* F.S. max berisi elemen maksimum pada baris i dari M
           min berisi elemen minimum pada baris i dari M */
void MaxMinKol (MATRIKS M, indeks j, ElType * max, ElType * min)
{
    int i;
    *max = Elmt(M, 0, j);
    *min = Elmt(M, 0, j);
    for (i = GetFirstIdxBrs(M); i <= GetLastIdxBrs(M); i++)
    {
        if (*max < Elmt(M, i, j))
        {
            *max = Elmt(M, i, j);
        }
        if (*min > Elmt(M, i, j))
        {
            *min = Elmt(M, i, j);
        }
    }
}
/* I.S. j adalah indeks kolom efektif dari M, M terdefinisi */
/* F.S. max berisi elemen maksimum pada kolom j dari M
           min berisi elemen minimum pada kolom j dari M */
int CountXBrs (MATRIKS M, indeks i, ElType X)
{
    int j, count;
    count = 0;
    for (j = GetFirstIdxKol(M); j <= GetLastIdxKol(M); j++)
    {
        if (Elmt(M, i, j) == X)
        {
            count += 1;
        }
    }
    return count;
}
/* Menghasilkan banyaknya kemunculan X pada baris i dari M */
int CountXKol (MATRIKS M, indeks j, ElType X)
{
    int i, count;
    count = 0;
    for (i = GetFirstIdxBrs(M); i <= GetLastIdxBrs(M); i++)
    {
        if (Elmt(M, i, j) == X)
        {
            count += 1;
        }
    }
    return count;
}
/* Menghasilkan banyaknya kemunculan X pada kolom j dari M */