#include "graph_colo.h"

/**
 * \brief Create a new colored graph
 * 
 * \param size : number of nodes in the graph
 * 
 * \return the graph created
 */
graph_colo createGraphColo(int size)
{
    graph_colo new_graph = (graph_colo)malloc(sizeof(t_graph_colo));

    new_graph->g = createGraph(size);
    new_graph->colors = (color *)malloc(sizeof(color) * size);

    for (int i = 0; i < size; i++)
    {
        new_graph->colors[i] = 0;
    }

    return new_graph;
}

/**
 * \brief returns a copy of a colored graph
 * 
 * \param myGraphColo the colored graph to copy
 * 
 * \return a copy of the param myGraphColo
 * 
 */
graph_colo copyGraphColo(graph_colo myGraphColo){
    graph_colo newGraphColo = (graph_colo) malloc(sizeof(t_graph_colo));

    newGraphColo->g = copyGraph(myGraphColo->g);

    for(node a = 1; a <= newGraphColo->g->size; a++){
        newGraphColo->colors[a - 1] = myGraphColo->colors[a - 1];
    }

    return newGraphColo;
}

/**
 * \brief Add a new egdge to the colored graph between the given nodes
 * \param myGraph - colored graph to update
 * \param origin - origin of the new edge
 * \param destination - destination of the new edge
 * 
 * \return 1 if the modification was successful
 * \return 0 otherwise
 */
int newEdgeColo(graph_colo myGraph, node origin, node destination)
{
    return newEdge(myGraph->g, origin, destination);
}

/**
 * \brief function to free the memory allocated to the given colored graph
 * 
 * \param graph : the colored graph to free
 * 
 * \return void
 * 
 */
void freeGraphColo(graph_colo *myGraph)
{
    freeGraph(&(*myGraph)->g);
    free((*myGraph)->colors);
    free(myGraph);
}

int setColor(graph_colo myGraph, node x, color col)
{
    if (x > myGraph->g->size || x <= 0)
    {
        fprintf(stderr, "ERROR : [setColor] Invalid nodes %d", x);
        exit(1);
        return 0;
    }

    myGraph->colors[x - 1] = col;
    return 1;
}

int isColored(graph_colo myGraph, node x)
{
    if (x > myGraph->g->size || x <= 0)
    {
        fprintf(stderr, "ERROR : [isColored] Invalid nodes %d", x);
        exit(1);
        return 0;
    }
    return myGraph->colors[x - 1] != 0;
}

/**
 * \brief Find the saturation of the target node in the colored graph
 * 
 * \param myGraph colored graph that contains the node
 * \param target the node we want the saturation
 */
int getSaturation(graph_colo myGraph, node target)
{
    if (target > myGraph->g->size || target <= 0)
    {
        fprintf(stderr, "ERROR : [getSaturation] Invalid nodes %d", target);
        exit(1);
        return 0;
    }
    int cpt = 0;
    for (int i = 1; i <= myGraph->g->size; i++)
    {
        if (isColored(myGraph, i) && edgeExists(myGraph->g, target, i))
        {
            cpt++;
        }
    }

    return cpt;
}

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
int isNeighborColoredWithColoredColor(graph_colo g, node x, color col)
{
    for (int i = 0; i < g->g->size; i++)
    {
        // printf("Edge exists %d, %d => %d\n", x,i + 1,edgeExists(g->g, x, i + 1));
        if (edgeExists(g->g, x, i + 1))
        {
            if (g->colors[i] == col)
            {
                printf("%d taken by %d\n", col, i + 1);
                return 1;
            }
        }
    }
    return 0;
}

color getMaxColor(graph_colo myGraph)
{
    color max = 0;
    for (int i = 0; i < myGraph->g->size; i++)
    {
        if (myGraph->colors[i] > max)
        {
            max = myGraph->colors[i];
        }
    }
    return max;
}

/**
 * \brief Print the content of the colored graph in the form of a adjacency matrix.
 * \param myGraph The colored graph to display
 */
void printGraphColo(graph_colo myGraph)
{
    printf("\033[0;31m");
    for (int i = 1; i <= myGraph->g->size; i++)
    {
        printf("%d\t", i);
    }
    printf("\033[0;37m");

    printf("\n");
    for (int i = 0; i < myGraph->g->size; i++)
    {
        printf("%d\t", myGraph->colors[i]);
    }
    printf("\n");

    printGraph(myGraph->g);
}

/**
 * \brief color a colored graph with random colors (so 2 neighbor vertexes can have the same color)
 * 
 * \param myGraph the graph which have to be colored
 * 
 * \return the colored graph with random colors
 */
void colorGraphWithRandomColors(graph_colo myGraph){
    node a;
    color col;
    int nbColor = 0;

    for(a = 1; a <= myGraph->g->size; a++){
        col = rand() % (nbColor + 1) + 1;
        if(col == nbColor + 1){
            nbColor++;
        }
        setColor(myGraph, a, col);
    }
}

/**
 * \brief give the number of edges which link to vertexes with the same color
 * 
 * \param myGraph the colored graph we want the interferences
 * 
 * \return int : the number of interferences
 */
int getNbInterferences(graph_colo myGraph){
    int nbInterferences = 0;

    for (node a = 1; a <= myGraph->g->size; a++){

        for(node b = 1; b < a; b++){

            nbInterferences += (myGraph->colors[a - 1] == myGraph->colors[b - 1]) && myGraph->g->content[a - 1][b - 1];

        }

    }

    return nbInterferences;

}

/**
 * \brief give the number of interferences for a given node
 * 
 * \param myGraph the colored graph we are working on
 * \param x the node we want interferences
 * \param neighbours the array of x's neighbours
 * 
 * \return int : the number of interferences for x
 */
int getNbInterferenceForNode(graph_colo myGraph, node x, node* neighbours){

    int cpt = 0;
    int interferences = 0;

    while(neighbours[cpt] != 0){
        if(myGraph->colors[x - 1] == myGraph->colors[neighbours[cpt] - 1]){
            interferences++;
        }
        cpt++;
    }

    return interferences;

}

int neighboursInterferencesDecreased(graph_colo myGraph, node x, node** neighbours, int* baseValues){

    node *xNeighbours = neighbours[x - 1];
    node neigh;
    node* secondNeighbours;
    int cpt = 0;

    while(xNeighbours[cpt] != 0){
        neigh = xNeighbours[cpt];
        secondNeighbours = neighbours[neigh - 1];

        if(getNbInterferenceForNode(myGraph, neigh, secondNeighbours) < baseValues[cpt]){
            return 1;
        }

        cpt++;
    }

    return 0;

}

int getNbInterferenceOfNeighbours(graph_colo myGraphColo, node x, node** neighbours){
    
    

    int cpt = 0;
    node* xNeighbours = neighbours[x - 1];
    int res = 0;

    while(xNeighbours[cpt] != 0){
        res += getNbInterferenceForNode(myGraphColo, xNeighbours[cpt], neighbours[xNeighbours[cpt] - 1]);
        cpt++;
    }

    return res;

}