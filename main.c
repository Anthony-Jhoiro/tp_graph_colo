#include "./parser/parser.h"
#include "algorithme_genetique/algorithme_genetique.h"
#include <time.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{

    srand(time(NULL)); 
    graph myGraph = readGraph("./assets/1-FullIns_3.col");
    printGraph(myGraph);

    // graph_colo myGraphColo = createGraphColo(myGraph->size);

    // myGraphColo->g = myGraph;
    // alg_genetique(myGraphColo, 100, 1000);


    // colorColoredGraphWithColoredColors(myGraphColo);

    // printGraphColo(myGraphColo);

    // writePumlColo("res2.puml", myGraphColo);

    return 0;
}