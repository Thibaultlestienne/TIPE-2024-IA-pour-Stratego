#ifndef STRATEGO 
#define STRATEGO

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <time.h>
#include <sys/time.h>


// AFFICHAGECOORDONNEES est défini dans affichage.h

#define TYPE_HUMAIN 0
#define TYPE_ALEATOIRE 1
#define TYPE_IA_MM 2

#define TYPE_JOUEUR_0 TYPE_IA_MM
#define TYPE_JOUEUR_1 TYPE_ALEATOIRE

#define NUMERO_BOMBE 11
#define NUMERO_DRAPEAU 0 
#define NUMERO_LAC 12

#define NBPIECES 18
#define NBPIECESDIFF 12
#define NBCOLONNES 6
#define NBLIGNES 8
#define PIECES(x,c)  { .val = x, .equipe = c, .devoile = false, .bouger = false, .cell = NULL}
#define TPIECES(c) { PIECES(NUMERO_DRAPEAU, c), PIECES(NUMERO_BOMBE, c), PIECES(NUMERO_BOMBE, c), PIECES(NUMERO_BOMBE, c), PIECES(1, c), PIECES(2, c), PIECES(2, c), PIECES(2, c), PIECES(3, c), PIECES(3, c), PIECES(3, c), PIECES(7, c), PIECES(7, c), PIECES(7, c), PIECES(8, c), PIECES(8, c), PIECES(9, c), PIECES(10, c)}
#define NBCOUPMAX 1500

struct celluleType;

struct pieceType {
    int val;              // 1 - 10, 11:bombe, 0:drapeau ; 12:case interdite
    int equipe;           // 0 et 1
    bool devoile;
    bool bouger;
    struct celluleType *cell;
};

struct celluleType {  // Défini case
    struct pieceType * pion;
    int x;
    int y;
} ;

struct plateauType {
    struct celluleType scene[NBLIGNES][NBCOLONNES];
} ;

typedef struct pieceType piece;
typedef struct celluleType cellule;
typedef struct plateauType plateau;

typedef struct coup {
    int xd;
    int yd;
    int xf;
    int yf;
} coup;
 
#include "aleatoire.h"
#include "tableau_dyn.h"
#include "ia.h"
//#include "evaluation.h"
#include "parcours.h"
#include "affichage.h"
#include "fichier.h"



// x -> lignes 
// y -> colonnes

void copie_tableau_piece(piece source[], piece destination[], int taille);

void initialisation_plateau(plateau *jeu);

void placement_piece( plateau *jeu, piece *jeton, int xl, int yl, int i) ;

void pseudo_alea(plateau *jeu, int i, piece* equipe[NBPIECES]);

void initialisation_lac(plateau *jeu);

bool hors_plateau(int x, int y);

void coup_case(plateau* P, piece p, tableau_dyn* t, int tour) ;

void liste_coup_possible(plateau P, tableau_dyn* l_coups, piece* equipe0[18], piece* equipe1[18],int tour);

bool mouvement_valide(plateau * jeu, coup c, int tour, bool factice);

bool action(plateau * jeu, coup c, int tour, bool factice);

void libere_plateau(plateau *jeu);

coup mouvement_joueur(plateau *P, int equipe, int tour); // Récupère le mouvement du joueur

int jouer();

int jouer_ia_contre_ia(ia ia1, ia ia2, int * nbtour);

int jouer_humain_contre_ia(ia ia1, int * nbtour);


int jouer_ia_contre_random(ia ia1);


#endif