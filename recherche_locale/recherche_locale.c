#include "./recherche_locale.h"


/**
 * \brief set the best color (with least interferences) to a node on a colored graph
 * 
 * \param myGraph the colored graph we are working on
 * \param x the node we change the color
 * 
 * \return the best color for the node
 */
color changeForBestColor(graph_colo myGraph, node x, node** neighbours){

    color maxColor = (getMaxColor(myGraph) + 1);
    color bestColor = myGraph->colors[x - 1];
    int leastInterferences = getNbInterferenceOfNeighbours(myGraph, x, neighbours);
        

    for(color test = 1; test <= maxColor; test++){

        setColor(myGraph, x, test);
        int testInterferences = getNbInterferenceOfNeighbours(myGraph, x, neighbours);
        
        if(testInterferences < leastInterferences){
            bestColor = test;
            leastInterferences = testInterferences;
        }

    }

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

    for(node x = 1; x <= myGraphColo->g->size; x++){

        baseColor = myGraphColo->colors[x - 1];
        int beforeInterferences = getNbInterferenceOfNeighbours(myGraphColo, x, neighbours);
        testColor = changeForBestColor(myGraphColo, x, neighbours);
        int afterInterferences = getNbInterferenceOfNeighbours(myGraphColo, x, neighbours);
        int reductionTest = beforeInterferences - afterInterferences;

        if(reductionMax < reductionTest){
            hasChanged = 1;
            reductionMax = reductionTest;
            bestNode = x;
            bestColor = testColor;
        }

        setColor(myGraphColo, x, baseColor);
    }

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

    for(node x = 1; x <= myGraphColo->g->size; x++){
        if(myGraphColo->colors[x - 1] == col){
            nbNodesWithCol++;
            baseInterferences = getNbInterferenceOfNeighbours(myGraphColo, x, neighbours);

            for(color c = 1; c <= getMaxColor(myGraphColo); c++){
                if(c != col){
                    setColor(myGraphColo, x, c);
                    if(getNbInterferenceOfNeighbours(myGraphColo, x, neighbours) > baseInterferences){
                        setColor(myGraphColo, x, col);
                    }
                    else {
                        nbNodesChanged++;
                        break;
                    }
                }
            }

            if(nbNodesChanged != nbNodesWithCol){
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
    
    colorGraphWithRandomColors(myGraphColo);

    node** neighbours = (node**) malloc(sizeof(node*) * myGraphColo->g->size);

    for(node x = 1; x <= myGraphColo->g->size; x++){
        neighbours[x - 1] = getNodeNeighbours(myGraphColo->g, x);
    }
    

    printf("=============== graph de base =================\n");
    
    printf("interferences : %d\nnombre de couleur : %d\n======== reduction des interferences =========\n", getNbInterferences(myGraphColo), getMaxColor(myGraphColo));
    printf("interferences : %d                    \r", getNbInterferences(myGraphColo));
    
    int continuer = 1;
    while(continuer){
        continuer = changeBestNode(myGraphColo, neighbours);
    }
    printf("interferences : %d\nnombre de couleur : %d\n======== reduction des couleurs =========\n", getNbInterferences(myGraphColo), getMaxColor(myGraphColo));
    printf("interferences : %d\n", getNbInterferences(myGraphColo));
    printf("nombre de couleurs : %d            \r", getMaxColor(myGraphColo));

    for(color col = getMaxColor(myGraphColo); col >= 1; col--){
        if(ReduceAColor(myGraphColo, col, neighbours)){
            for(int i = 0; i < myGraphColo->g->size; i++){
                if(myGraphColo->colors[i] > col){
                    myGraphColo->colors[i]--;
                }
            }
        }
    }


    printf("nombre de couleurs : %d\n", getMaxColor(myGraphColo));
    printf("======== graph optimise =========\n");

    writePumlColo("res_local.puml", myGraphColo);
    printf("interferences : %d\n", getNbInterferences(myGraphColo));
    printf("nombre de couleurs : %d\n", getMaxColor(myGraphColo));

}