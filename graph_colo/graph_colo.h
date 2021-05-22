#ifndef GRAPH_COLO_H
#define GRAPH_COLO_H

#include "../graph/graph.h"

typedef unsigned int color;

typedef struct s_graph_colo {
    graph g;
    color* colors;
} t_graph_colo;

typedef t_graph_colo* graph_colo;



/**
 * \brief Create a new colored graph
 * 
 * \param size : number of nodes in the graph
 * 
 * \return the graph created
 */
graph_colo createGraphColo(int size);

/**
 * \brief Add a new egdge to the colored graph between the given nodes
 * \param myGraph - colored graph to update
 * \param origin - origin of the new edge
 * \param destination - destination of the new edge
 * 
 * \return 1 if the modification was successful
 * \return 0 otherwise
 */
int newEdgeColo(graph_colo myGraph, node origin, node destination);

/**
 * \brief Print the content of the colored graph in the form of a adjacency matrix.
 * \param myGraph The colored graph to display
 */
void printGraphColo(graph_colo myGraph);

/**
 * \brief function to free the memory allocated to the given colored graph
 * 
 * \param graph : the colored graph to free
 * 
 * \return void
 * 
 */
void freeGraphColo(graph_colo* myGraph);

/**
 * \brief Find the saturation of the target node in the colored graph
 * 
 * \param myGraph colored graph that contains the node
 * \param target the node we want the saturation of
 * 
 * \return the saturation
 */
int getSaturation(graph_colo myGraph, node target);

/**
 * \brief function to set a color to a node
 * 
 * \param g : colored graph we work with
 * \param x : the node we're coloring with the colored color
 * \param col: the colored color we're setting the node to
 * 
 * \return 1 if the color has been successfully set
 * \return 0 otherwise
 */
int setColor(graph_colo g, node x, color col);

/**
 * \brief functon checking whether a node is colored
 * 
 * \param g: the colored graph we're working with
 * \param x : the node we're checking
 * 
 * \return 1 if the node is colored
 * \return 0 otherwise
 */
int isColored(graph_colo g, node x);

/**
 * \brief function checking if a node has a neighbor with the given color
 * 
 * \param g: the colored graph we're working with
 * \param x: the node which neighbors we're checking
 * \param col: the color we're looking for
 * 
 * \return 1 if one of the neighbors has the color
 * \return 0 otherwise
 */
int isNeighborColoredWithColoredColor(graph_colo g, node x, color col);

/**
 * \brief function getting the maximum color in a given colored graph
 * 
 * \param g: the colored graph we're working with
 * 
 * \return the max color
 */
color getMaxColor(graph_colo myGraph);

#endif 