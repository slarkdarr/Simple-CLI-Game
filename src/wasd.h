#include "boolean.h"
#include "graph.h"
#include "matriks.h"
#include "point.h"


#define BLANK '-'
#define BORDER '*'

boolean isDirWASD(char Dir);
char Path(char Dir, MATRIKS M, POINT P);
boolean Walkable(char Dir, MATRIKS M, POINT P);
boolean NGate(char path);
boolean Gate(char path);
void Move(char Dir, MATRIKS M, POINT P);