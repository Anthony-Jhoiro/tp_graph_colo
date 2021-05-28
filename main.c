#include "algorithme_genetique/algorithme_genetique.c"
#include "greedy/greedy.c"
#include "recherche_locale/recherche_locale.c"
#include <time.h>

int main(int argc, char const *argv[])
{
    srand(time(NULL)); 
    graph myGraph = readGraph("./assets/2-FullIns_4.col");

    graph_colo myGraphColo = createGraphColo(myGraph->size);

    myGraphColo->g = myGraph;

    // alg_genetique(myGraphColo, 100, 200);

    // runGreedyAlgorithm(myGraphColo);

    // runRechercheLocale(myGraphColo);    


    return 0;
}