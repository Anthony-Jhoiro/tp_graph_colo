# Projet coloration de graphes

## Auteurs

**Anthony QUERE**  
**Kilian DEBRAUX**

## Utilisation

pour essayer les différents algorithmes, vous pouvez compiler le programme à l'aide de la commande suivante :
```
make 
```

Puis, pour executer un algorithme, entrer la commande suivante : 
```
./make <nom_algorithme> <nom_fichier_graph>
```

Le paramètre `nom_algorithme` peut prendre les valeurs suivantes :
- greedy
- genetique
- recherche_locale

Le paramètre `nom_fichier_graph` doit pointer vers un des fichiers du dossier **assets** qui contient de quoi construire un graph.

## Structure de graph

Pour représenter un graph coloré, nous somme partie sur une structure en 2 composants :
- Une matrice d'adjacence qui représente les sommets ainsi que les arrêtes du graph. L'ordre de la matrice est le nombre de sommet (les sommets sont nommés de 1 à l'ordre de la matrice). Notre matrice n'est pas vraiment une matrice : en effet, comme une matrice d'adjacence est symétrique par rapport à une diagonale, nous n'avons stocké que les valeurs présente d'un côté de cette diagonale, et nous avons tous les sommets ainsi que toutes les arrêtes.
- Un tableau de int, représentant une coloration. Le tableau a pour longueur le nombre de noeuds, et dans chaque case il y a une couleur (sous forme numérique) qui est associée au noeud ayant comme numéro l'indice de la case + 1.