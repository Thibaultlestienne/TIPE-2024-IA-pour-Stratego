# TIPE 2024 

L'objectif de ce TIPE est de créer une inteligence artificielle pour le jeu du Stratego. 

## Pour lancer une formation
- les principaux paramètres modifiables sont au début de ia.h.
- lancer la commande make former

## Les différentes versions de l'IA

La plus performante est la V11
### V1,2,3,4
Basées sur un algorithme ExcpectiMinMax l'IA cherche les meilleurs paramétres pour une fonction heuristique à paramétres
#### V1
Ne s'interesse qu'aux pièces encore en vie et au pièces non découvertes
#### V2 
Compte différemment le dernier démineur en lui attribuant un bonus de valeur
#### V3
Ajoute la distance entre le 1 et le 10 à l'évaluation
#### V4
Ajoute la distance minimale entre un 3 et une bombe à l'évaluation

### V10 V11 V12

Méthode largement inspirée par l'algorithme de Vincent De Boer (disponible [ici](https://project.dke.maastrichtuniversity.nl/games/files/msc/Arts_thesis.pdf))

#### V10
Copie de la méthode de Boer

#### V11 
Rend la méthode de Boer symetrique entre le côté droit et le côté gauche du plateau

#### V12
Supprime l'aléatoire 
