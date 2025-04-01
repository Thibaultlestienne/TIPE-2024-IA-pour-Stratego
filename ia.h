#ifndef INTELLIGENCEARTIFICIEL
#define INTELLIGENCEARTIFICIEL

typedef struct ia ia;

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include "stratego.h"

#define TYPEIA 11// priviligier la version 11
// les versons 10 et 11 sont les plus performantes et les plus rapides a former
// la version 12 est depourvu de mouvement aléatoire et ne parvient pas a eviter les nulles
// les versions 1, 2,3 et 4 sont trés lentes a former et ne sont pas performantes sans un trés grand temps de formation
// compter une dizaines de minutes pour former une generation IA de type 1, 2, 3 ou 4
#define ALEAMIN -1
#define ALEAMAX 1 

#define NBJOUEURSACHARGER 0 // nombre de joueur chargé depuis la mémoire
#define NBJOUEURASAUVEGARDER 10 // nombre de joueur sauvegarder pour une prochaine execution

#define NBJOUEURPARPOULE 100 // nombre de joueur par generation (une centaine semble être un bon compromis)
#define NBGENERATION 10 // nombre de generation (1000 semble coherent)
#define NBSURVIVANTS NBJOUEURASAUVEGARDER // nombre de joueur conservé sans modification a chaque generation (prendre environ 10% de la population)
#define NBALEATOIREPARGENERATION 30 // nombre de joueur aleatoire a chaque génération (prendre entre 20 et 50% de la population)
#define DEGRESDESURETE 1 // nombre de fois ou la poule est jouer mais ne semble pas très utile de mettre cette valeur au dessus de 1

//mutation type A changement léger de nombreux paramètres
#define PROBABILITEMUTATIONA 0.5 //proba de mutation
#define VARIATIONMUTATIONA 0.1 // valeur max de la mutation
//mutation type B remise a 0 de certain parametres
#define PROBABILITEMUTATIONB 0.005 //proba de mutation

#define NBPARAMETRES 110

/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
//////////////    IA V1/V2/V3/V4   //////////////////////
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////

#define DISTANCEMAX 6

#define DECOUVERTEV1(i) i
#define VALEURV1(i) (i+NBPIECESDIFF)
#define MOUVEMENTV1 (2*NBPIECESDIFF)
#define ALEATOIREV1 (2*NBPIECESDIFF)+1
#define DEVOILEV1 (2*NBPIECESDIFF)+2
#define DISTANCE3(i) (2*NBPIECESDIFF)+2+i
#define VALEUR13 (2*NBPIECESDIFF)+3+DISTANCEMAX
#define DISTANCE1 (2*NBPIECESDIFF)+4+DISTANCEMAX
#define DISTANCED (2*NBPIECESDIFF)+5+DISTANCEMAX



/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
////////////////////    IA V10   ////////////////////////
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////

// version de de boer qui se base sur les coups
// cette version ne s’intéresse ni aux bombes ni au drapeau 
// i est donc compris entre 1 et 10

#define PREMIERCOUPV10(i) (-1 + i)           // est le premier coup ?
#define ATTAQUEPIECEIMMOBILEV10(i) (9 + i)    // la piece attaquée est t-elle immobile ?
#define ATTAQUEPIECEPLUFAIBLEV10(i) (19 + i) // la piece attaquée est-elle connu et plus faible ?
#define AVANCERV10(i) (29 + i)               // la piece avance t-elle ?
#define MOUVEMENTDV10(i) (39 + i)            // la piece va t-elle a droite ?
#define RECULERV10(i) (49 + i)               // la piece recule t_elle ?
#define MOUVEMENTGV10(i) (59 + i)            // la piece va t-elle a gauche ?
#define ATTAQUERPIECEBOUGERV10(i) (69 + i)   // la piece attaquée a t-elle bouger ? est elle inconnu
#define PROTEGERCHEMINV10(i) (79 + i)        // la piece se deplace t-elle deriere le lac
#define DERRIERELACV10(i) (89 + i)           // la piece se deplace t-elle en derriere le lac
#define ALEATOIREV10(i) (99 + i)             // part aleatoire

/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
////////////////////    IA V11   ////////////////////////
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////

// Amelioration de la V10 avec mvtD = mvtG

// version de de boer qui se base sur les coups
// cette version ne s’intéresse ni aux bombes ni au drapeau 
// i est donc compris entre 1 et 10

#define PREMIERCOUPV11(i) (-1 + i)           // est le premier coup ?
#define ATTAQUEPIECEIMMOBILEV11(i) (9 + i)    // la piece attaquée est t-elle immobile ?
#define ATTAQUEPIECEPLUFAIBLEV11(i) (19 + i) // la piece attaquée est-elle connu et plus faible ?
#define AVANCERV11(i) (29 + i)               // la piece avance t-elle ?
#define MOUVEMENTCOTEV11(i) (39 + i)         // la piece va t-elle a sur le coté ?
#define RECULERV11(i) (49 + i)               // la piece recule t_elle ?
// 60 à 69 sans informations
#define ATTAQUERPIECEBOUGERV11(i) (69 + i)   // la piece attaquée a t-elle bouger ? est elle inconnu
#define PROTEGERCHEMINV11(i) (79 + i)        // la piece se deplace t-elle deriere le lac
#define DERRIERELACV11(i) (89 + i)           // la piece se deplace t-elle en derriere le lac
#define ALEATOIREV11(i) (99 + i)             // part aleatoire

/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
////////////////////    IA V12   ////////////////////////
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////

// Amelioration de la V10 sans aleatoire

// version de de boer qui se base sur les coups
// cette version ne s’intéresse ni aux bombes ni au drapeau 
// i est donc compris entre 1 et 10

#define PREMIERCOUPV12(i) (-1 + i)           // est le premier coup ?
#define ATTAQUEPIECEIMMOBILEV12(i) (9 + i)    // la piece attaquée est t-elle immobile ?
#define ATTAQUEPIECEPLUFAIBLEV12(i) (19 + i) // la piece attaquée est-elle connu et plus faible ?
#define AVANCERV12(i) (29 + i)               // la piece avance t-elle ?
#define MOUVEMENTDV12(i) (39 + i)            // la piece va t-elle a droite ?
#define RECULERV12(i) (49 + i)               // la piece recule t_elle ?
#define MOUVEMENTGV12(i) (59 + i)            // la piece va t-elle a gauche ?
#define ATTAQUERPIECEBOUGERV12(i) (69 + i)   // la piece attaquée a t-elle bouger ? est elle inconnu
#define PROTEGERCHEMINV12(i) (79 + i)        // la piece se deplace t-elle deriere le lac
#define DERRIERELACV12(i) (89 + i)           // la piece se deplace t-elle en derriere le lac


// pour la v 13 floor(10*ia[110]) donne le nombre de tour considerer comme premier tour

typedef struct ia {
    float parametres[NBPARAMETRES];
    int famille;
    int version;
} ia;



/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
//////////////////// Gestion IA /////////////////////////
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////

ia muter_ia(ia pere);
void recuperer_indices_N_plus_grands_elements(int tableau[], int indices[], int taille, int N);
void jouer_poule(ia tableau_ia[NBJOUEURPARPOULE], int nombre_joueur_sortie, ia vainqueurs[NBJOUEURPARPOULE]);

#endif
