#include "algorithme_genetique.h"
#include <time.h>
#include <stdlib.h>
#include <math.h>


/**
 * \brief génère un tableau de couleur de façon aléatoire
 * 
 * \param size taille du tableau de couleur
 * 
 * \return color* : le tableau de couleurs
 */
color *genererColorationAleatoire(int size)
{
    color *individu = malloc(sizeof(color) * size);

    for (int i = 0; i < size; i++)
    {
        color rdm = (color)rand() % (size - 1);
        individu[i] = rdm;
    }

    return individu;
}

/**
 * \brief génère une population de colorations aléatoires
 * 
 * \param taillePopulation taille de la population à générer
 * \param g graph sur lequel on se base pour générer une coloration aléatoire
 * 
 * \return color** : le tableau de colorations aléatoires
 */
color **genererPopulation(int taillePopulation, graph_colo g)
{
    color **population = malloc(sizeof(color *) * taillePopulation);

    for (int i = 0; i < taillePopulation; i++)
    {
        population[i] = genererColorationAleatoire(g->g->size);
    }

    return population;
}

/**
 * \brief calcul le nombre d'interférences dans un graph coloré
 * 
 * \param myGraph graph dont on veut les interférences
 * \param individu coloration du graph
 * 
 * \return int : le nombre d'interférences du graphe
 */
int calculerConflits(graph_colo myGraph, color *individu)
{
    int res = 0;

    for (int i = 0; i < myGraph->g->size; i++)
    {
        for (int j = i; j < myGraph->g->size; j++)
        {
            if (edgeExists(myGraph->g, i + 1, j + 1) && individu[i] == individu[j])
            {
                res++;
            }
        }
    }

    return res;
}

/**
 * \brief retourne le nombre de couleurs distinctes dans une coloration
 * 
 * \param individu coloration dont on veut les couleurs distincte
 * \param tailleIndividu taille de la coloration
 * 
 * \return le nombre de couleurs distincte dans une coloration
 */
int nombreCouleur(color *individu, int tailleIndividu)
{
    color *set = malloc(sizeof(color) * tailleIndividu);
    int indexSet = 0;
    int find = 0;

    for (int i = 0; i < tailleIndividu; i++)
    {
        find = 0;
        for (int j = 0; j <= indexSet; j++)
        {
            if (set[j] == individu[i])
            {
                find = 1;
                break;
            }
        }
        if (!find)
        {

            set[indexSet] = individu[i];
            indexSet++;
        }
    }
    free(set);

    return indexSet;
}

#define PROBA_MUTATION 0.2


void muterSelection(graph_colo origin, int tailleSelection, color **individus) {
    for (int i = 0; i < tailleSelection; i++) {
        if (random() <= PROBA_MUTATION) {
            int nodeIndex = floor(random() * origin->g->size);
            individus[i][nodeIndex] = (color) floor(random() * origin->g->size);
        }
    }
}

/**
 * \brief selectionne les meilleurs individus d'une génération
 * 
 * \param origin graph coloré sur lequel on travaille
 * \param taillePopulation taille de la population (génération)
 * \param individus colorations formant la génération
 * 
 * \return color** : la meilleure moitié de individus
 */
color **selectionnerElements(graph_colo origin, int taillePopulation, color **individus)
{
    color **population = malloc(sizeof(color *) * taillePopulation);

    int tailleSelection = (int)taillePopulation / 2;

    int *selectionnesConflits = malloc(sizeof(int) * tailleSelection);
    for (int j = 0; j < tailleSelection; j++)
    {
        selectionnesConflits[j] = origin->g->size;
    }

    for (int i = 0; i < taillePopulation; i++)
    {
        int nbConflits = calculerConflits(origin, individus[i]);
        for (int p = 0; p < tailleSelection; p++)
        {
            if (selectionnesConflits[p] >= nbConflits)
            {

                if (selectionnesConflits[p] == nbConflits)
                {
                    if (nombreCouleur(population[p], origin->g->size) <= nombreCouleur(individus[i], origin->g->size))
                    {
                        continue;
                    }
                }
                for (int k = tailleSelection - 1; k > p  - 1; k--) {
                    selectionnesConflits[k] = selectionnesConflits[k - 1];
                    population[k] = population[k - 1];
                    population[k + tailleSelection] = population[k - 1];
                }
                selectionnesConflits[p] = nbConflits;
                population[p] = individus[i];
                population[p + tailleSelection] = individus[i];
                
                break;
            }
        }
    }


    free(selectionnesConflits);

    return population;
}

/**
 * \brief crée un enfant à partir de 2 colorations
 * 
 * \param papa première coloration parent
 * \param maman deuxième coloration parent
 * \param size taille des colorations de papa et maman
 * 
 * \return color* : une coloration enfant
 */
color *creerEnfant(color *papa, color *maman, int size)
{
    color *enfant = malloc(sizeof(color) * size);
    for (int i = 0; i < size; i++)
    {
        int b = rand() % size;
        color c = (i < b) ? papa[i] : maman[i];
        enfant[i] = c;
    }

    return enfant;
}

/**
 * \brief crée une nouvelle génération
 * 
 * \param origin graph sur lequel on travaille
 * \param individus génération de coloration parentes
 * \param taillePopulation taille de la génération
 * \param dans nouvelle génération de colorations
 * 
 * \return void
 */
void crossOver(graph_colo origin, color **individus, int taillePopulation, color **dans)
{

    int decalage = rand() % taillePopulation;

    for (int i = 0; i < taillePopulation; i++)
    {
        int i2 = (i + decalage) % taillePopulation;
        color *p1 = individus[i];
        color *p2 = individus[i2];

        color *c1 = creerEnfant(p1, p2, origin->g->size);
        color *c2 = creerEnfant(p2, p1, origin->g->size);

        dans[i] = c1;
        dans[i2] = c2;
    }
}

color* selectionnerColoration(graph_colo g, color** population, int taillePopulation) {
    int minSaturation = g->g->size * g->g->size;
    int minColoration = g->g->size;
    color *selectionne = NULL;

    for (int i = 0; i < taillePopulation; i++)
    {
        int saturation = calculerConflits(g, population[i]);
        int coloration = nombreCouleur(g->colors, g->g->size);
        if (saturation < minSaturation)
        {
            minSaturation = saturation;
            minColoration = coloration;
            selectionne = population[i];
        } else if (saturation == minSaturation && coloration < minColoration) {
            minSaturation = saturation;
            minColoration = coloration;
            selectionne = population[i];
        }
    }

    return selectionne;
}

/**
 * \brief fait tourner un algorithme génétique
 * 
 * \param g graph sur lequel on travaille
 * \param taillePopulation taille de la population que l'on veut créer
 * \param nbIter nombre d'itération avant l'arrêt de l'algorithme (= nombre de générations à passer)
 * 
 * \return void
 */
void alg_genetique(graph_colo g, int taillePopulation, int nbIter)
{

    color **pop = genererPopulation(taillePopulation, g);


    for (int i = 0; i < nbIter; i++)
    {
        printf("Iterations : %d/%d\r", i, nbIter);
        color **selection = selectionnerElements(g, taillePopulation, pop);

        crossOver(g, selection, taillePopulation, pop);

        muterSelection(g, taillePopulation, pop);        

        free(selection);
    }
    printf("\n");

    color *selectionne = selectionnerColoration(g, pop, taillePopulation);


    for (int i = 0; i < g->g->size; i++)
    {
        g->colors[i] = selectionne[i];
    }

    for (int j = 0; j < taillePopulation; j++)
    {
        free(pop[j]);
    }


    printf("\ninterference %d\n", calculerConflits(g, g->colors));
    printf("Nombre couleurs %d\n", nombreCouleur(g->colors, g->g->size));
}
