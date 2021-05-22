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

    for (int i = 1; i <= size; i++)
    {
        int sat;
        // If the node is not colored
        if ((!isColored(myGraph, i)))
        {

            if ((sat = getSaturation(myGraph, i)) > maxSat)
            {
                max = i;
                maxSat = sat;
                // reinitialize maxDegree cache
                maxDegree = 0;
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

    while (a = getUncoloredNodesWithMaxSaturation(myGraph))
    {
        color col = 1;
        while (isNeighborColoredWithColoredColor(myGraph, a, col))
        {
            col++;
        }

        setColor(myGraph, a, col);
    }
}