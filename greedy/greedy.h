#ifndef GREEDY_H
#define GREEDY_H

#include "../graph_colo/graph_colo.h"

/**
 * \brief this function colors a colored graph with a colored color
 * 
 * \param g the colored graph we want to color with a colored color
 * 
 * \return void
 */
void runGreedyAlgorithm(graph_colo g);

/**
 * \brief function to find the uncolored node with the highest saturation and degree within a colored graph
 * 
 * \param myGraph: the graph we're working with
 * 
 * \return the uncolored node with the highest saturation and degree
 */
node getUncoloredNodeWithMaxSaturation(graph_colo myGraph);


#endif