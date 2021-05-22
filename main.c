#include "./parser/parser.h"
#include "algorithme_genetique/algorithme_genetique.h"
#include "greedy/greedy.h"
#include <time.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{

    srand(time(NULL)); 
    graph myGraph = readGraph("./assets/1-FullIns_3.col");

    graph_colo myGraphColo = createGraphColo(myGraph->size);

    myGraphColo->g = myGraph;
    printf("Starting genetic alg...\n");
    alg_genetique(myGraphColo, 100, 10000);

    // runGreedyAlgorithm(myGraphColo);

    // colorColoredGraphWithColoredColors(myGraphColo);

    printGraphColo(myGraphColo);


    writePumlColo("res2.puml", myGraphColo);

    return 0;
}