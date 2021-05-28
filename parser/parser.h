#ifndef PARSER_H
#define PARSER_H

#include "../graph_colo/graph_colo.c"

#define BUFFER_SIZE 256



/**
 * \brief Parse graph informations from file in a new graph
 * 
 * \param filename: the file holding the informations
 * 
 * \return: the graph obtained
 */
graph readGraph(char* filename);

void writePuml(char* filename, graph g);

void writePumlColo(char* filename, graph_colo myGraph);


#endif 