#ifndef RECHERCHE_TABOUE_H
#define RECHERCHE_TABOUE_H

#include "../parser/parser.c"




/**
 * \brief set the best color (with least interferences) to a node on a colored graph
 * 
 * \param myGraph the colored graph we are working on
 * \param x the node we change the color
 * \param xNeighbours an array of x's neighbours
 * 
 * \return the best color for the node
 */
color changeForBestColor(graph_colo myGraph, node x, node** neighbours);

/**
 * \brief change the color of a graph_colo's node to have the least interferences
 * 
 * \param myGraphColo the colored graph we are working on
 * \param neighbours an array of array of all the neighbours of all node in the graph
 * 
 * \return 1 s'il y a eu un chagement, 0 sinon
 */
int changeBestNode(graph_colo myGraphColo, node** neighbours);

/**
 * \brief try to remove a color by giving all the nodes with this color, another colors without increasing interferences
 * 
 * \param myGraphColo the colored graph we are working on
 * \param col the color to remove
 * \param neighbours an array of array of all the neighbours of all node in the graph
 * 
 * \return 1 if the color has been removed, 0 if it is impossible
 */
int reduceAColor(graph_colo myGraphColo, color col, node** neighbours);

/**
 * \brief run the taboue algorithm
 * 
 * \param myGraphColo the colored graph we want to optimize
 * 
 * \return void
 */
void runRechercheLocale(graph_colo myGraphColo);

#endif