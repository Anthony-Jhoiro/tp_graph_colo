#include "parser.h"

/**
 * \brief reads a single line from myFile
 * 
 * \param myFile: the file holding the informations
 * \param buffer: string variable receiving the read line
 * 
 * \return 1 if the line was successfully read
 * \return 0 otherwise
 */
int readLine(FILE *myFile, char *buffer)
{
    if (feof(myFile))
    {
        return 0;
    }
    fgets(buffer, BUFFER_SIZE, myFile);
    return 1;
}

graph readGraph(char *filename)
{
    FILE *source = fopen(filename, "r");

    char buffer[BUFFER_SIZE];

    graph myGraph = GRAPH_NULL;
    int size, nb_edge;

    // find graph definition
    while (readLine(source, buffer))
    {
        if (buffer[0] == 'p')
        {

            sscanf(buffer, "p edge %d %d", &size, &nb_edge);
            myGraph = createGraph(size);
            break;
        }
    }

    if (myGraph == GRAPH_NULL)
    {
        fprintf(stderr, "ERROR : Declaration line not found.");
        exit(1);
    }

    // Fill the graph
    int origin, destination;

    while (readLine(source, buffer))
    {
        if (buffer[0] == 'e')
        {

            sscanf(buffer, "e %d %d", &origin, &destination);
            newEdge(myGraph, origin, destination);
        }
    }

    fclose(source);

    return myGraph;
}

void writePuml(char *filename, graph g)
{
    FILE *output = fopen(filename, "w");

    fprintf(output, "@startuml\n\n");

    for (int i = 0; i < g->size; i++)
    {
        fprintf(output, "usecase \"%d\"\n", i + 1);
    }

    for (int i = 0; i < g->size; i++)
    {
        for (int j = i; j < g->size; j++)
        {
            if (g->content[i][j])
            {
                fprintf(output, "%d --> %d\n", i + 1, j + 1);
            }
        }
    }

    fprintf(output, "\n\n@enduml\n");
    fclose(output);
}

void writePumlColo(char *filename, graph_colo myGraph)
{
    FILE *output = fopen(filename, "w");

    fprintf(output, "@startuml\n\n");

    color maxColor = getMaxColor(myGraph);
    unsigned int colorMaxSize = 256 * 256 * 256;

    for (int i = 0; i < myGraph->g->size; i++)
    {

        color col = (int)((myGraph->colors[i] / (float)maxColor) * (float)colorMaxSize);
        fprintf(output, "usecase \"%d\" #%6X\n", i + 1, col);
    }

    for (int i = 0; i < myGraph->g->size; i++)
    {
        for (int j = i; j < myGraph->g->size; j++)
        {
            if (myGraph->g->content[i][j])
            {
                fprintf(output, "%d -- %d\n", i + 1, j + 1);
            }
        }
    }

    fprintf(output, "\n\n@enduml\n");
    fclose(output);
}