#ifndef GRAPH_COLO_H
#define GRAPH_COLO_H

#include "../graph/graph.c"

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
 * \brief returns a copy of a colored graph
 * 
 * \param myGraphColo the colored graph to copy
 * 
 * \return a copy of the param myGraphColo
 * 
 */
graph_colo copyGraphColo(graph_colo myGraphColo);

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

/**
 * \brief color a colored graph with random colors (so 2 neighbor vertexes can have the same color)
 * 
 * \param myGraph the graph which have to be colored
 * 
 * \return the colored graph with random colors
 */
void colorGraphWithRandomColors(graph_colo myGraph);


/**
 * \brief give the number of edges which link to vertexes with the same color
 * 
 * \param myGraph the colored graph we want the interferences
 * 
 * \return int : the number of interferences
 */
int getNbInterferences(graph_colo myGraph);

/**
 * \brief give the number of interferences for a given node
 * 
 * \param myGraph the colored graph we are working on
 * \param x the node we want interferences
 * \param neighbours the array of x's neighbours
 * 
 * \return int : the number of interferences for x
 */
int getNbInterferenceForNode(graph_colo myGraph, node x, node* neighbours);


#endif 