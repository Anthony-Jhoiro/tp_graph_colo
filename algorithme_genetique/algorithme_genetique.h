#ifndef COLO_GENETIQUE_H
#define COLO_GENETIQUE_H

#include "../graph_colo/graph_colo.h"

// graph_colo* genererColorationAleatoire(graph_colo g);

// graph_colo* genererPopulation(int taillePopulation, graph_colo g);

// int calculerConflits(graph_colo g);

// graph_colo *selectionnerElements(graph_colo *origin, int taillePopulation);

// void crossOver(graph_colo* population, int taillePopulation,graph_colo* dans) ;

void alg_genetique(graph_colo g, int taillePopulation, int nbIter);


#endif