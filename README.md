# TIPE 2024 

L'objectif de ce TIPE est de créer une Inteligence Artificiel pour le jeu du Stratego. 

## Pour Lancer une formation
- les principaux parametres modifiables sont au début de ia.h.
- lancer la commande make former

## Les differentes versions de l'ia

La plus performante est la V11
### V1,2,3,4
Basé sur un algorithme ExcpectiMinMax l'ia cherche les meilleurs parametre pour une fonction heuristique à paramétres
#### V1
Ne s'interesse que aux pieces encore en vie et au pieces non decouvertes
#### V2 
Compte diffement le dernier demineur en lui attribuant un bonus de valeur
#### V3
Ajoute la distance entre le 1 et le 10 a l'evaluation
#### V4
Ajoute la distance minimal entre un 3 et une bombe a l'evaluation

### V10 V11 V12

méthode largement inspirée par l'algorithme de Vincent De Boer (disponible [ici](https://project.dke.maastrichtuniversity.nl/games/files/msc/Arts_thesis.pdf))

#### V10
Copie de la méthode de Boer

#### V11 
Rends la méthode de Boer symetrique entre le coté droit et gauche du plateau

#### V12
Supprime l'aleatoire 
