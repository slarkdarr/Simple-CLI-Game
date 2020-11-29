#include <stdio.h>
#include <stdlib.h>

#include "../map.h"
#include "../point.h"
#include "../boolean.h"


/*
    compile command:
        gcc -o drivergraph drivergraph.c ../map.c ../point.c -lm
*/

int main()
{
    MAP TEST;
    gAddress_V FULLMAP;
    LoadFullMap(&TEST, "../map.txt", &FULLMAP);
    char* messageBuffer;
    
    

    // DrawMap(VertexMap(FULLMAP), "");
    gAddress_E TT = VertexTrail(FULLMAP);
    
    int i = 0;
    printf("\n");

    while(TT != NULL)
    {
        // printf("HUHI");
        printf("EDGE %d TO MAP ID %d\n", i, VertexId(EdgeDest(TT)));
        
        TT = NextEdge(TT);
        i++;
    }
    
    int T;
    printf("PRINTING MAPS, 0 to stop, enter any number to continue\n");
    scanf("%d", &T);
    while(T != 0)
    {
        if (FULLMAP != NULL)
        {
            DrawMap(VertexMap(FULLMAP), "");
            printf("THIS IS MAP ID %d\n", VertexId(FULLMAP));
            FULLMAP = VertexNext(FULLMAP);
            scanf("%d", &T);
        } else {
            printf("NO MORE MAPS");
            T = 0;
        }
    }

    return;
}