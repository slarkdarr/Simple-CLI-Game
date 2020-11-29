#include "mesinkata.h"
#include <stdio.h>

boolean EndKata;
Kata CKata;

void IgnoreBlank()
/* Mengabaikan satu atau beberapa BLANK
   I.S. : CC sembarang 
   F.S. : CC ≠ BLANK atau CC = MARK */
{
    while (CC == BLANK || CC == MARK)
    {
        ADV();
    }
}

void STARTKATA()
/* I.S. : CC sembarang 
   F.S. : EndKata = true, dan CC = MARK; 
          atau EndKata = false, CKata adalah kata yang sudah diakuisisi,
          CC karakter pertama sesudah karakter terakhir kata */
{
    START();
    IgnoreBlank();
    if(CC == MARK){
        EndKata = true;
    }
    else{
        EndKata = false;
        SalinKata();
    }
}

void ADVKATA()
/* I.S. : CC adalah karakter pertama kata yang akan diakuisisi 
   F.S. : CKata adalah kata terakhir yang sudah diakuisisi, 
          CC adalah karakter pertama dari kata berikutnya, mungkin MARK
          Jika CC = MARK, EndKata = true.		  
   Proses : Akuisisi kata menggunakan procedure SalinKata */
{
    if(CC == MARK){
        EndKata = true;
    }
    else{
        SalinKata();
        IgnoreBlank();
        if (CC == MARK)
        {
            EndKata = true;
        }
    }
}

void SalinKata()
/* Mengakuisisi kata, menyimpan dalam CKata
   I.S. : CC adalah karakter pertama dari kata
   F.S. : CKata berisi kata yang sudah diakuisisi; 
          CC = BLANK atau CC = MARK; 
          CC adalah karakter sesudah karakter terakhir yang diakuisisi.
          Jika panjang kata melebihi NMax, maka sisa kata "dipotong" */
{
    int i = 0;

    while(CC != MARK && CC != BLANK){
        CKata.TabKata[i] = CC;
        ADV();
        i++;
        if(i >= NMax){
            CC = MARK;
        }
    }
    CKata.Length = i;
    IgnoreBlank();
}

Kata CreateKata(char String[])
// Fungsi yang digunakan untuk mengkonversi data bertipe string ke Kata
{
    int len = 0;
    char current = String[0];
    Kata result;
    while (current != '\0' && current != '\n')
    {
        result.TabKata[len] = current;
        len += 1;
        current = String[len];
    }

    result.Length = len;
    return result;
}

boolean IsKataSama(Kata Kata1, Kata Kata2)
// Fungsi yang digunakan untuk membandingkan 2 argumen bertipe Kata. Mengembalikan true jika kata sama
{
    boolean sama = true;

    if (Kata1.Length == Kata2.Length)
    {
        int length = Kata1.Length;
        int check = 0;
        while (sama && (check < length))
        { 
            if (Kata1.TabKata[check] != Kata2.TabKata[check])
            {
                sama = false;
            }
            else
            {
                check += 1;
            }
        }
    }
    else
    {
        sama = false;
    }
    return sama;
}

boolean Command(char CommandAsString[], Kata Command)
{
    Kata CommandAsKata = CreateKata(CommandAsString);
    return IsKataSama(Command, CommandAsKata);
}

void Input(Kata *InputKata)
{
    char character;
    int count = 0;
    boolean start = true;
    while(start)
    {
        scanf("%c", &character);
        if (character == '\n')
        {
            start = false;
        }
        (*InputKata).TabKata[count] = character;
        if (character != '\n')
        {
            count += 1;
        }
    }
    (*InputKata).Length = count;
}

void PrintKata(Kata print)
// Untuk Print dari ADT bertipe Kata
{
    int traverse = 0;
    while (traverse < print.Length)
    {
        printf("%c", print.TabKata[traverse]);
        traverse += 1;
    }
    printf("");
}

void ReadInput(Kata *InputKata)
// Membaca input dari pengguna dan menyimpan input ke InputKata
// Dimulai dengan memanggil start dan langsung menggunakan IgnoreBlank
{
    START();
    IgnoreBlank();
    int count = 0;
    while(CC != MARK)
    {
        (*InputKata).TabKata[count] = CC;
        count += 1;
        ADV();
    }
    (*InputKata).Length = count;
}

void ReadInputInteger(int *out)
// Untuk membaca input dari pengguna jika yang diperlukan hanya dalam bentuk integer
{
    START();
    int output = 0;
    while (CC != MARK)
    {
        switch(CC)
        {
            case '0' :  output = output * 10; break;
            case '1' :  output = output * 10 + 1; break;
            case '2' :  output = output * 10 + 2; break;
            case '3' :  output = output * 10 + 3; break;
            case '4' :  output = output * 10 + 4; break;
            case '5' :  output = output * 10 + 5; break;
            case '6' :  output = output * 10 + 6; break;
            case '7' :  output = output * 10 + 7; break;
            case '8' :  output = output * 10 + 8; break;
            case '9' :  output = output * 10 + 9; break;
        }
        ADV();
    }
    *out = output;
}

void ReadCommand(int *out, Kata *InputKata)
// Membaca input integer diikuti dengan Kata 
{
    START();
    int output = 0;
    while (CC != BLANK)
    {
        switch(CC)
        {
            case '0' :  output = output * 10; break;
            case '1' :  output = output * 10 + 1; break;
            case '2' :  output = output * 10 + 2; break;
            case '3' :  output = output * 10 + 3; break;
            case '4' :  output = output * 10 + 4; break;
            case '5' :  output = output * 10 + 5; break;
            case '6' :  output = output * 10 + 6; break;
            case '7' :  output = output * 10 + 7; break;
            case '8' :  output = output * 10 + 8; break;
            case '9' :  output = output * 10 + 9; break;
        }
        ADV();
    }

    *out = output;
    IgnoreBlank();
    
    int count = 0;
    while(CC != MARK && CC != BLANK)
    {
        (*InputKata).TabKata[count] = CC;
        count += 1;
        ADV();
    }
    (*InputKata).Length = count;
}

void ReadServe(Kata *InputKata1, Kata *InputKata2)
// Prosedur yang digunakan untuk menerima input berupa dua kata yang terpisah oleh spasi
{
    START();
    int count1 = 0;
    int count2 = 0;
    while (CC != BLANK)
    {
        (*InputKata1).TabKata[count1] = CC;
        count1 += 1;
        ADV();
    }
    (*InputKata1).Length = count1;

    IgnoreBlank();

    while (CC != MARK)
    {
        (*InputKata2).TabKata[count2] = CC;
        count2 += 1;
        ADV();
    }
    (*InputKata2).Length = count2;
}

void ReadServeName(Kata *WahanaServe)
// Prosedur untuk melewati kata pertama dan mengambil kata kedua
{
    int count = 0;
    START();
    while (CC != BLANK)
    {
        ADV();
    }
    IgnoreBlank();
    while (CC != MARK)
    {
        (*WahanaServe).TabKata[count] = CC;
        count += 1;
        ADV();
    }
    (*WahanaServe).Length = count;
}

Kata ParseKata(Kata Command, Kata Serve)
// Fungsi yang mengembalikan Kata kedua setelah Kata Serve
{
    // Kata Serve = CreateKata("Serve ")
    boolean sama = true;
    int length = Serve.Length;
    int check = 0; // integer pencacah
    while (sama && (check < length))
    { 
        if (Command.TabKata[check] != Serve.TabKata[check])
        {
            sama = false;
        }
        else
        {
            check += 1;
        }
    }
    Kata toReturn;
    int tr = 0; // integer pencacah
    if (sama && (Command.Length > 6))
    {
        while (check < Command.Length)
        {
            toReturn.TabKata[tr] = Command.TabKata[check];
            check++;
            tr++;
        }
        toReturn.Length = tr;
        return toReturn;
    }
    else
    {
        return (CreateKata("."));
    }
}