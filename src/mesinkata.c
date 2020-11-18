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
{
    int len = 0;
    char current = String[0];
    Kata result;
    while (current != '\0')
    {
        result.TabKata[len] = current;
        len += 1;
        current = String[len];
    }

    result.Length = len;
    return result;
}

boolean IsKataSama(Kata Kata1, Kata Kata2)
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

// boolean IsCommand(char* Commands[], Kata com, int CommandsLen)
// {
//     boolean isCommand = false;
//     int i = 0;
//     while (!isCommand && i < CommandsLen)
//     {
//         isCommand = Command(Commands[i], com);
//         i++;
//     }

//     return isCommand;
// }

void Input(Kata *InputKata) // ga dipake soalnya ga make mesinkata
// jangan pake yang ini, salah
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
// testing purposes
{
    int traverse = 0;
    while (traverse < print.Length)
    {
        printf("%c", print.TabKata[traverse]);
        traverse += 1;
    }
    printf("\n");
}

void ReadInput(Kata *InputKata)
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
/* Membaca input integer diikuti dengan Kata */
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

