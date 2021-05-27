#include "algorithme_genetique/algorithme_genetique.h"
#include "greedy/greedy.h"
#include "recherche_taboue/recherche_taboue.c"
#include "recherche_locale/recherche_locale.c"
#include <time.h>

int main(int argc, char const *argv[])
{
    srand(time(NULL)); 
    graph myGraph = readGraph("./assets/3-FullIns_5.col");

    graph_colo myGraphColo = createGraphColo(myGraph->size);

    myGraphColo->g = myGraph;
    // alg_genetique(myGraphColo, 100, 1000);

    // runGreedyAlgorithm(myGraphColo);

    runRechercheLocale(myGraphColo);

    /* printGraphColo(myGraphColo);
    printGraph(myGraph);


    writePumlColo("res0.puml", myGraphColo); */


    return 0;
}