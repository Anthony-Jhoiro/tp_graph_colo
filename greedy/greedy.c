#include "greedy.h"

/**
 * \brief function to find the uncolored node with the highest saturation and degree within a colored graph
 * 
 * \param myGraph: the graph we're working with
 * 
 * \return the uncolored node with the highest saturation and degree
 */
node getUncoloredNodesWithMaxSaturation(graph_colo myGraph)
{
    int size = myGraph->g->size;

    node max = 0;
    int maxSat = 0;
    int maxDegree = 0;

    for (node i = 1; i <= size; i++)
    {
        int sat;
        // If the node is not colored
        if (!isColored(myGraph, i))
        {
            sat = getSaturation(myGraph, i);

            if (sat > maxSat)
            {
                
                max = i;
                maxSat = sat;
                maxDegree = degree(myGraph->g, i);
            }
            else if (sat == maxSat)
            {

                int iDegree = degree(myGraph->g, i);
                // We keep maxDegree value in cache or use it if it has already a value
                maxDegree = max == 0 ? 0 : (maxDegree ? maxDegree : degree(myGraph->g, max));
                if (iDegree > maxDegree)
                {
                    max = i;
                    maxSat = sat;
                    maxDegree = iDegree;
                }
            }
        }
    }

    return max;
}

/**
 * \brief this function color a colored graph with a colored color
 * 
 * \param g the colored graph we want to color with a colored color
 * 
 * \return void
 */
void runGreedyAlgorithm(graph_colo myGraph)
{
    node a;

    printf("\n\n      GREEDY\n\n");
    printf("=============== graph de base ================\n");
    
    printf("nombre de noeuds : %d\n", myGraph->g->size);
    printf("nombre de couleurs : %d\n", getMaxColor(myGraph));

    printf("================ coloration ==================\n");

    int nbColoredNodes = 0;
    while (a = getUncoloredNodesWithMaxSaturation(myGraph))
    {
        color col = 1;
        while (isNeighborColoredWithColoredColor(myGraph, a, col))
        {
            col++;
        }

        setColor(myGraph, a, col);
        nbColoredNodes++;
        printf("nombre de noeuds colores : %d\r", nbColoredNodes);
    }
    printf("nombre de noeuds colores : %d\n", nbColoredNodes);

    printf("=============== graph optimise ================\n");
    
    printf("nombre de noeuds : %d\n", nbColoredNodes);
    printf("nombre d'interferences : %d\n", getNbInterferences(myGraph));
    printf("nombre de couleurs : %d\n", getMaxColor(myGraph));
}