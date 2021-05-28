#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdlib.h>
#define GRAPH_NULL NULL

/**
 * \brief represents a graph node.
 */
typedef unsigned int node;

/**
 * \brief represents a matrix coefficient. A node is an unsigned short (2 bytes integer) with a value of 0 or 1.
 */
typedef unsigned short coeff;

/**
 * \brief structure which represent an adjacency matrix (squared matrix)
 * 
 * \param size : size of the squared matrix
 * \param content : coefficient's table's table
 */
typedef struct s_adjacency_matrix
{
    int size;
    coeff **content;
} adjacency_matrix;

/**
 * \brief This type represents a graph. A graph is a pointer to a adjacency matrix.
 */
typedef adjacency_matrix *graph;

// --- Matrix --- //

/**
 * \brief function to create a squared matrix size * size
 * 
 * \param size : number of line or columns of the matrix
 * 
 * \return a pointer to the brand new created matrix
 * 
 */
adjacency_matrix *createMatrix(int size);

/**
 * \brief function to free the memory allocated to the given matrix
 * 
 * \param matrix : the matrix to free
 * 
 * \return void
 * 
 */
void freeMatrix(adjacency_matrix* matrix);

/**
 * \brief Set a coefficient in the given adjacency matrix
 * 
 * \param matrix: the adjacency matrix to modify
 * \param x: the node of origin
 * \param y: the node of destination
 * 
 * \return 1 if the matrix was successfully modified
 * \return 0 otherwise
 */
int setCoeff(adjacency_matrix matrix, node x, node y);

/**
 * \brief display the matrix
 * 
 * \param myMatrix : matrix to display
 * 
 * \return void
 */
void printMatrix(adjacency_matrix myMatrix);

// --- Graphs --- //

/**
 * \brief Create a new graph
 * 
 * \param size : number of nodes in the graph
 * 
 * \return the graph created
 */
graph createGraph(int size);

/**
 * \brief returns a copy of a graph
 * 
 * \param myGraph the graph to copy
 * 
 * \return a copy of the param myGraph
 * 
 */
graph copyGraph(graph myGraph);

/**
 * \brief Add a new egdge to the graph between the given nodes
 * \param myGraph - graph to update
 * \param origin - origin of the new edge
 * \param destination - destination of the new edge
 * 
 * \return 1 if the modification was successful
 * \return 0 otherwise
 */
int newEdge(graph myGraph, node origin, node destination);

/**
 * \brief Print the content of the graph in the form of a adjacency matrix.
 * \param myGraph The graph to display
 */
void printGraph(graph myGraph);

/**
 * \brief function to free the memory allocated to the given graph
 * 
 * \param graph : the graph to free
 * 
 * \return void
 * 
 */
void freeGraph(graph* myGraph);

/**
 * \brief Get the coefficient 
 * 
 * \param myGraph the graph that contains the tnodes
 * \param x the first node
 * \param y the secound node
 * 
 * \return the coefficient
 */
int edgeExists(graph myGraph, node x, node y);

/**
 * \brief give the degree of a giving node
 * 
 * \param myGraph the graph getting the node
 * \param x node we want the degree
 * 
 * \return int : the x node's degree
 */
int degree(graph myGraph, node x);


/**
 * \brief get an array of a given node neihbours
 * 
 * \param myGraph the graph we are working on
 * \param x the node we want the neihbours
 * 
 * \return node* : an array of the x's neighbours
 */
node* getNodeNeighbours(graph myGraph, node x);

#endif