#include "preparation.h"

int time = 0;

void build(Stack S){
    MATRIKS M;
    POINT P;
    FILE *wahana;
    char f, wahana, bangun;

    println("Apa bangunan yang ingin Anda bangun?\nList bangunan:");

    // Load file berisi list bangunan
    f = fopen("wahana.txt", "r");
    if ("map.txt" == NULL){
        println("Error. File map missing atau tidak dapat dibuka");
        exit(-1);
    }

    wahana = fgetc(f);
    while (wahana != EOF){
        printf("%c", wahana);
        wahana = fgetc(f);
    }
    // End of load

    scanf("%s\n", &bangun);
    switch (bangun)
    {
        case 'WankCoaster':
            if (Moonstone < 250 && Anaptanium < 100 && Arcanite < 50)
                println("Bahan bangunan tidak mencukupi");
            else
                println("Memasukkan perintah build WankCoaster ke dalam Stack");
                Push(&S, "Build WankCoaster");
                M.Mem[(int)Absis(P)][(int)Ordinat(P)] = 'W';
        case 'Carousel':
            if (Moonstone < 150 && Anaptanium < 150 && Arcanite < 100)
                println("Bahan bangunan tidak mencukupi");
            else
                println("Memasukkan perintah build Carousel ke dalam Stack");
                Push(&S, "Build Carousel");
                M.Mem[(int)Absis(P)][(int)Ordinat(P)] = 'W';
        case 'Wheel of Fum':
            if (Moonstone < 300 && Anaptanium < 50 && Arcanite < 150)
                println("Bahan bangunan tidak mencukupi");
            else
                println("Memasukkan perintah build Wheel of Fum ke dalam Stack");
                Push(&S, "Build Wheel of Fum");
                M.Mem[(int)Absis(P)][(int)Ordinat(P)] = 'W';
        case 'Bump Bump Boom!!':
            if (Moonstone < 100 && Anaptanium < 250 && Arcanite < 100)
                println("Bahan bangunan tidak mencukupi");
            else
                println("Memasukkan perintah build Bump Bump Boom!! ke dalam Stack");
                Push(&S, "Build Bump Bump Boom!!");
                M.Mem[(int)Absis(P)][(int)Ordinat(P)] = 'W';
        case 'FUNswing':
            if (Moonstone < 150 && Anaptanium < 150 && Arcanite < 200)
                println("Bahan bangunan tidak mencukupi");
            else
                println("Memasukkan perintah build FUNswing ke dalam Stack");
                Push(&S, "Build FUNswing");
                M.Mem[(int)Absis(P)][(int)Ordinat(P)] = 'W';
    }
}

void upgrade(Stack S){
    MATRIKS M;
    POINT P;
    FILE *upgradable;
    char f, up;

    println("Apa bangunan yang ingin Anda upgrade?\nList bangunan yang dapat di-upgrade:");

    // Belum FIX //
    /* // Load file berisi list bangunan yang dapat di-upgrade
    f = fopen("wahana.txt", "r");
    if ("map.txt" == NULL){
        println("Error. File map missing atau tidak dapat dibuka");
        exit(-1);
    }

    wahana = fgetc(f);
    while (wahana != EOF){
        printf("%c", wahana);
        wahana = fgetc(f);
    }
    // End of load */

    scanf("%s\n", &up);
}

void buy(Stack S){
    FILE *resource;
    char f, resource, bahan;
    int sum;

    println("Apa bahan bangunan yang ingin Anda beli?\nList bahan bangunan:");

    // Load file berisi list bangunan yang dapat di-upgrade
    f = fopen("resources.txt", "r");
    if ("resources.txt" == NULL){
        println("Error. File map missing atau tidak dapat dibuka");
        exit(-1);
    }

    resource = fgetc(f);
    while (resource != EOF){
        printf("%c", resource);
        resource = fgetc(f);
    }
    // End of load

    scanf("%s\n", &bahan);
    printf("Jumlah yang ingin dibeli : ");
    scanf("%d\n", &sum);
    printf("Memasukkan perintah membeli ", &bahan); printf(" sebanyak ", &sum); println(" ke dalam Stack...");
    int i = 1;
    do{
        Push(&S, bahan);
    } while (i <= sum);
}

void undo(Stack S, infotype X){
    Pop(&S, &X);
    printf("Menghapus perintah", &X); println("dari Stack");
}

void execute(Stack S, infotype X);