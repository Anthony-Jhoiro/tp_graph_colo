#include "algorithme_genetique/algorithme_genetique.h"
#include "greedy/greedy.h"
#include "recherche_locale/recherche_locale.h"
#include "parser/parser.h"
#include <time.h>

/**
 * Compare 2 char* char by char. If they are the same return 1 els, return 0
 * \param str1 first char* to compare
 * \param str2 second char* to compare
 */
int compareStr(const char *str1, const char *str2)
{

    int cpt = 0;

    while (str1[cpt] != '\0')
    {
        if (str1[cpt] != str2[cpt])
        {
            return 0;
        }
        cpt++;
    }

    return str2[cpt] == '\0';
}

int main(int argc, char *argv[])
{
    if (argc != 3 && argc != 4)
    {
        fprintf(stderr, "Error : 2 arguments needed, try :  ./main ALGO SOURCE [destination]\n");
        exit(1);
    }

    char *filename = argv[2];
    char *algo = argv[1];

    srand(time(NULL));
    graph myGraph = readGraph(filename);

    graph_colo myGraphColo = createGraphColo(myGraph->size);

    myGraphColo->g = myGraph;

    if (compareStr(algo, "greedy"))
    {
        runGreedyAlgorithm(myGraphColo);
    }
    else if (compareStr(algo, "genetique"))
    {
        alg_genetique(myGraphColo, 100, 200);
    }
    else if (compareStr(algo, "recherche_locale"))
    {
        runRechercheLocale(myGraphColo);
    }
    else
    {
        fprintf(stderr, "Error: Undefined algorithme (try greedy | genetique | recherche_locale)\n");
        exit(1);
    }

    if (argc == 4)
    {
        writePumlColo(argv[3], myGraphColo);
    }

    return 0;
}