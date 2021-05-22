#include "./taboue/taboue.c"
#include "time.h"

#define TAILLE_POP 10

int main(int argc, char const *argv[])
{
    srand(time(NULL));
    graph myGraph = readGraph("./assets/1-FullIns_3.col");

    graph_colo myGraphColo = createGraphColo(myGraph->size);
    myGraphColo->g = myGraph;

    printGraphColo(myGraphColo);

    colorGraphWithRandomColors(myGraphColo);

    printf("interferences : %d\n", nbInterferences(myGraphColo));

    printGraphColo(myGraphColo);

    writePumlColo("res0.puml", myGraphColo);


    return 0;
}