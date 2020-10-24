#include "wasd.h"

#define BLANK '-'
#define BORDER '*'

boolean isDirWASD(char Dir){
// Fungsi yang memeriksa apakah arah gerak valid
    return (Dir =='W' || Dir =='A' || Dir=='S' || Dir=='D');
}

char Path(char Dir, MATRIKS M, POINT P){
// Direction selalu W,A,S,D
    if (Dir == 'W') {
        return M.Mem[(int)Absis(P)][(int)Ordinat(P)+1];
    }
    else if (Dir == 'A') {
        return M.Mem[(int)Absis(P)-1][(int)Ordinat(P)];
    }
    else if (Dir == 'S') {
        return M.Mem[(int)Absis(P)][(int)Ordinat(P)-1];      
    }
    else if (Dir == 'D') {
        return M.Mem[(int)Absis(P)+1][(int)Ordinat(P)]; 
    }
}

boolean Walkable(char Dir, MATRIKS M, POINT P){
// Fungsi yang memeriksa apakah tujuan gerak dapat dipijak atau tidak.
    char path;
    if (isDirWASD(Dir))
        path = Path(Dir, M, P);
        if (path == '*' || path == 'A' || path == 'W' || path =='V' || path=='^' || path=='>' || path=='<') {
            return true;
        }
        else {
            return false;
        }
}

boolean NGate(char path){
// Fungsi yang memeriksa apakah suatu path bukan gerbang. 
    return (path !='V' && path !='^' && path !='>' && path !='<');
}

boolean Gate(char path){
// Fungsi yang memeriksa apakah suatu path berupa gerbang. 
    return (path =='V' || path =='^' || path =='>' || path =='<');
}

void Move(char Dir, MATRIKS M, POINT P) {
// Prosedur yang menggerakan posisi pemain dalam matrix map
    if (Walkable(Dir,M,P)) {
        if (NGate(Path(Dir,M,P))){ // Bergerak dalam peta yang sama
            if (Dir == 'W') {
                M.Mem[(int)Absis(P)][(int)Ordinat(P)] = BLANK;
                Geser(&P,0,1);
            }
            else if (Dir == 'A') {
                M.Mem[(int)Absis(P)][(int)Ordinat(P)] = BLANK;
                Geser(&P,-1,0);
            }
            else if (Dir == 'S') {
                M.Mem[(int)Absis(P)][(int)Ordinat(P)] = BLANK;
                Geser(&P,0,-1);        
            }
            else if (Dir == 'D') {
                M.Mem[(int)Absis(P)][(int)Ordinat(P)] = BLANK;
                Geser(&P,1,0);        
            }
        }
        else { // Bergerak keluar peta melalui gerbang
            Address PMap;
            PMap = (Address) malloc(sizeof(Node));
            CreateEmpty(&PMap);
            /*
            if (Path(Dir,M,P)) {}
            else if (Path(Dir,M,P))
            */
        }
    }
}