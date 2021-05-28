#include "./recherche_locale.h"


/**
 * \brief set the best color (with least interferences) to a node on a colored graph
 * 
 * \param myGraph the colored graph we are working on
 * \param x the node we change the color
 * 
 * \return the best color for the node
 */
color changeForBestColor(graph_colo myGraph, node x, node* neighbours){

    color maxColor = (getMaxColor(myGraph) + 1);
    color bestColor = myGraph->colors[x - 1];
    color baseColor = myGraph->colors[x - 1];
    int leastInterferences = getNbInterferenceForNode(myGraph, x, neighbours);
        

    // pour chaque couleur, on colore le noeud avec et on regarde avec quelle couleur on obtient le moins d'interférence
    for(color test = 1; test <= maxColor; test++){
        if(test != baseColor){
            setColor(myGraph, x, test);
            int testInterferences = getNbInterferenceForNode(myGraph, x, neighbours);
            
            if(testInterferences < leastInterferences){
                bestColor = test;
                leastInterferences = testInterferences;
            }
        }

    }

    // on modifie le noeud avec la couleur qui fait le plus baisser les interférences et on retourne cette couleur
    setColor(myGraph, x, bestColor);
    return bestColor;

}


/**
 * \brief change the color of a graph_colo's node to have the least interferences
 * 
 * \param myGraphColo the colored graph we are working on
 * 
 * \return 1 s'il y a eu un changement, 0 sinon
 */
int changeBestNode(graph_colo myGraphColo, node** neighbours){

    int hasChanged = 0;
    node bestNode = 1;
    color bestColor = 1;
    color testColor;
    color baseColor;
    int reductionMax = 0;

    // pour chaque noeud, on va regarder lequel on va changer
    // pour cela on va calculer le nombre max d'interférences que l'on peut enlever pour chaque noeud
    // puis on execute la modification qui permet de faire disparaîter le plus d'interférences
    for(node x = 1; x <= myGraphColo->g->size; x++){

        baseColor = myGraphColo->colors[x - 1];
        int beforeInterferences = getNbInterferenceForNode(myGraphColo, x, neighbours[x - 1]);
        testColor = changeForBestColor(myGraphColo, x, neighbours[x - 1]);
        int afterInterferences = getNbInterferenceForNode(myGraphColo, x, neighbours[x - 1]);
        int reductionTest = beforeInterferences - afterInterferences;

        if(reductionMax < reductionTest){
            hasChanged = 1;
            reductionMax = reductionTest;
            bestNode = x;
            bestColor = testColor;
        }

        setColor(myGraphColo, x, baseColor);
    }

    // si l'on a pas pu faire disparaître d'interférences, alors il est impossible d'en refaire disparaître et on arrête ici
    // si on a pu faire disparaître des interférences, alors on va retenter d'en faire disparaître
    if(hasChanged){
        int nbInterferences = getNbInterferences(myGraphColo);
        printf("interferences : %d                    \r", nbInterferences);
        setColor(myGraphColo, bestNode, bestColor);
        return 1;
    }

    return 0;
}

/**
 * \brief try to remove a color by giving all the nodes with this color another colors without increasing interferences
 * 
 * \param myGraphColo the colored graph we are working on
 * \param col the color to remove
 * 
 * \return 1 if the color has been removed, 0 if it is impossible
 */
int ReduceAColor(graph_colo myGraphColo, color col, node** neighbours){

    int baseInterferences;
    
    int nbNodesChanged = 0;
    int nbNodesWithCol = 0;
    int reductionMax = 0;

    // pour chaque noeud qui est coloré par la couleur col, on essaie de le colorer en une autre couleur
    for(node x = 1; x <= myGraphColo->g->size; x++){
        if(myGraphColo->colors[x - 1] == col){
            // nbNodesWithCol et nbNodesChanged, servent à savoir si l'on a pu changer tous les noeuds d'une même couleur
            nbNodesWithCol++;
            baseInterferences = getNbInterferenceForNode(myGraphColo, x, neighbours[x - 1]);

            for(color c = 1; c <= getMaxColor(myGraphColo); c++){
                if(c != col){
                    setColor(myGraphColo, x, c);
                    // si en changeant par le couleur c, le nombre d'interférences n'augmente pas, alors on garde la couleur c
                    if(getNbInterferenceForNode(myGraphColo, x, neighbours[x - 1]) <= baseInterferences){
                        nbNodesChanged++;
                        break;
                    }
                }
            }
            // si l'on a pas réussie à changer la couleur d'un noeud, on arrête de vouloir retirer la couleur col
            if(nbNodesChanged != nbNodesWithCol){
                setColor(myGraphColo, x, col);
                return 0;
            }
        }        
    }
    printf("nombre de couleurs : %d            \r", getMaxColor(myGraphColo));

    return 1;

}


/**
 * \brief run the taboue algorithm
 * 
 * \param myGraphColo the colored graph we want to optimize
 * 
 * \return void
 */
void runRechercheLocale(graph_colo myGraphColo){

    printf("\n\n         RECHERCHE LOCALE            \n\n");
    
    colorGraphWithRandomColors(myGraphColo);

    // on crée une liste contenant les listes de voisins pour chaque noeud du graph
    node** neighbours = (node**) malloc(sizeof(node*) * myGraphColo->g->size);

    for(node x = 1; x <= myGraphColo->g->size; x++){
        neighbours[x - 1] = getNodeNeighbours(myGraphColo->g, x);
    }
    printf("=============== graph de base =================\n");
    
    printf("interferences : %d\n", getNbInterferences(myGraphColo));
    printf("nombre de couleur : %d\n", getMaxColor(myGraphColo));
    printf("======== reduction des interferences =========\n");
    printf("interferences : %d                    \r", getNbInterferences(myGraphColo));
    
    // on réduit d'abord à 0 le nombre d'interférence
    // dans cette fonction, nous nous autorisons à faire augmenter le nombre de couleurs pour faire baisser les interférences
    // or un graph avec chaque noeud coloré par une couleur différente, le nombre d'interférence tombe à 0
    // à la fin du processus, le graph aura donc forcément 0 interférences
    int continuer = 1;
    while(continuer){
        continuer = changeBestNode(myGraphColo, neighbours);
    }
    printf("interferences : %d\n", getNbInterferences(myGraphColo));
    printf("nombre de couleur : %d\n", getMaxColor(myGraphColo));
    printf("======= reduction des couleurs =========\n");
    printf("interferences : %d\n", getNbInterferences(myGraphColo));
    printf("nombre de couleurs : %d            \r", getMaxColor(myGraphColo));

    // ensuite, on réduit le nombre de couleurs :
    // pour cela, on parcours toutes les couleurs qui existent dans le graphe
    // et on essaie de colorer tous les noeuds de cette couleur par une autre couleur
    // si on a réussie, alors une couleur a été enlevée
    for(color col = getMaxColor(myGraphColo); col >= 1; col--){
        if(ReduceAColor(myGraphColo, col, neighbours)){
            // si on a enlevée une couleur situé au milieu du range
            // (par exemple, on a éliminé la couleur 6, et le graphe contient 9 couleur)
            // alors on procède à un renommage des coueleurs numérotées au dessus de celle éliminée
            for(int i = 0; i < myGraphColo->g->size; i++){
                if(myGraphColo->colors[i] > col){
                    myGraphColo->colors[i]--;
                }
            }
        }
    }


    printf("nombre de couleurs : %d\n", getMaxColor(myGraphColo));
    printf("======== graph optimise =========\n");

    printf("interferences : %d\n", getNbInterferences(myGraphColo));
    printf("nombre de couleurs : %d\n", getMaxColor(myGraphColo));

}