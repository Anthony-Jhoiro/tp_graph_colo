#include "graph.h"

/**
 * \brief function to create a squared matrix size * size
 * 
 * \param size : number of line or columns of the matrix
 * 
 * \return a pointer to the brand new created matrix
 * 
 */
adjacency_matrix *createMatrix(int size)
{
    // Allocate the memory
    adjacency_matrix *newMatrix = malloc(sizeof(adjacency_matrix));

    newMatrix->size = size;

    newMatrix->content = malloc(sizeof(coeff *) * size);
    // Set 0 for all coeffs
    for (int i = 0; i < size; i++)
    {
        newMatrix->content[i] = malloc(sizeof(coeff) * i);
        for (int j = 0; j < i; j++)
        {
            newMatrix->content[i][j] = 0;
        }
    }

    return newMatrix;
}

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
int setCoeff(adjacency_matrix matrix, node x, node y)
{
    if (x > matrix.size || y > matrix.size || x <= 0 || y <= 0 || x == y)
    {
        fprintf(stderr, "ERROR : Invalid nodes %d, %d", x, y);
        return 0;
    }

    int line, column;

    if (x > y)
    {
        line = x - 1;
        column = y - 1;
    }
    else
    {
        line = y - 1;
        column = x - 1;
    }

    if (matrix.content[line][column] == 0)
    {
        matrix.content[line][column] = 1;
        return 1;
    }
    return 0;
}

/**
 * \brief display the matrix
 * 
 * \param myMatrix : matrix to display
 * 
 * \return void
 */
void printMatrix(adjacency_matrix myMatrix)
{
    printf("    ");
    for (int j = 0; j < myMatrix.size; j++)
    {
        printf("\033[0;31m");
        printf("%4d", j + 1);
        printf("\033[0;37m");
    }
    printf("\n");
    for (int i = 0; i < myMatrix.size; i++)
    {
        printf("\033[0;36m");
        printf("%4d", i + 1);
        printf("\033[0;37m");

        for (int j = 0; j < myMatrix.size; j++)
        {
            if (j > i)
            {
                if (myMatrix.content[j][i])
                {
                    printf("\e[0;32m%4d\e[0;37m", myMatrix.content[j][i]);
                }
                else
                {
                    printf("%4d", myMatrix.content[j][i]);
                }
            }
            else if (j < i)
            {
                if (myMatrix.content[i][j])
                {
                    printf("\e[0;32m%4d\e[0;37m", myMatrix.content[i][j]);
                }
                else
                {
                    printf("%4d", myMatrix.content[i][j]);
                }
            }
            else
            {
                printf("\e[0;33m   X\e[0;37m");
            }
        }

        printf("\n");
    }
}

/**
 * \brief Create a new graph
 * 
 * \param size : number of nodes in the graph
 * 
 * \return the graph created
 */
graph createGraph(int size)
{
    adjacency_matrix *adjacencies = createMatrix(size);
    return adjacencies;
}

/**
 * \brief Add a new egdge to the graph between the given nodes
 * \param myGraph - graph to update
 * \param origin - origin of the new edge
 * \param destination - destination of the new edge
 * 
 * \return 1 if the modification was successful
 * \return 0 otherwise
 */
int newEdge(graph myGraph, node origin, node destination)
{
    return setCoeff(*myGraph, origin, destination);
}

/**
 * \brief Print the content of the graph in the form of a adjacency matrix.
 * \param myGraph The graph to display
 */
void printGraph(graph myGraph)
{
    if (myGraph != GRAPH_NULL)
    {
        printMatrix(*myGraph);
    }
    else
    {
        printf("graph null : unable to display\n");
    }
}

/**
 * \brief function to free the memory allocated to the given matrix
 * 
 * \param matrix : the matrix to free
 * 
 * \return void
 * 
 */
void freeMatrix(adjacency_matrix *matrix)
{
    for (int i = 0; i < matrix->size; i++)
    {
        free(matrix->content[i]);
    }
    free(matrix->content);
    free(matrix);
}

/**
 * \brief function to free the memory allocated to the given graph
 * 
 * \param graph : the matrix to free
 * 
 * \return void
 * 
 */
void freeGraph(graph *myGraph)
{
    freeMatrix(*myGraph);
    *myGraph = GRAPH_NULL;
}

/**
 * \brief Get the coefficient 
 * 
 * \param myGraph the graph that contains the tnodes
 * \param x the first node
 * \param y the secound node
 * 
 * \return the coefficient
 */
int edgeExists(graph myGraph, node x, node y)
{
    if (x > myGraph->size || y > myGraph->size || x <= 0 || y <= 0)
    {
        fprintf(stderr, "ERROR : [edgeExists] Invalid nodes %d, %d", x, y);
        exit(1);
        return -1;
    }

    int line, column;

    if (x > y)
    {
        line = x - 1;
        column = y - 1;
    }
    else
    {
        line = y - 1;
        column = x - 1;
    }

    return myGraph->content[line][column];
}

int degree(graph myGraph, node x)
{
    if (x > myGraph->size || x <= 0)
    {
        fprintf(stderr, "ERROR : [degree] Invalid nodes %d", x);
        exit(1);
        return -1;
    }
    int cpt = 0;

    int lineNumber = x - 1;

    for (int i = 0; i < lineNumber; i++)
    {
        cpt += myGraph->content[lineNumber][i] == 1;
    }
    for (int i = lineNumber; i < myGraph->size; i++)
    {
        cpt += myGraph->content[lineNumber][i] == 1;
    }

    return cpt;
}