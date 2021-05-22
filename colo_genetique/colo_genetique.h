#ifndef COLO_GENETIQUE_H
#define COLO_GENETIQUE_H

#include "../graph_colo/graph_colo.h"

graph_colo* generergraphAleatoire(int taille);

void genererPopulation(int taillePopulation, graph_colo* dans);

void selectionnerElements(graph_colo* origin, int tailleOrigin, graph_colo* dans, int tailleDans);



#endif