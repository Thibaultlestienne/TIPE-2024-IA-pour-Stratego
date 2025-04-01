#ifndef PARCOURS
#define PARCOURS


typedef struct coupMM coupMM;

#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <float.h>
#include <limits.h>

#include "stratego.h"
#include "aleatoire.h"
#include "affichage.h"
#include "tableau_dyn.h"
#include "evaluation.h"
#include "ia.h"
#include "fichier.h"

#define PROFONDEUR_MIN_MAX 1
#define AJOUT 0.01

typedef struct coupMM {
    float val;
    coup c;
} coupMM;

void copierPlateau(const struct plateauType *source, struct plateauType *destination);

void echangePiece(plateau *P, piece* p1, piece* p2);

void extraire_equipe(plateau * P, piece * equipe0[NBPIECES], piece * equipe1[NBPIECES]);

void libere_equipe_hors_plateau(piece* equipe[NBPIECES]);

coupMM actionMM(  plateau * jeu, coup c, piece* equipe0[NBPIECES], piece* equipe1[NBPIECES], ia ia_joueur, int maximisateur, int tour, int profondeur);

coupMM MinMax(plateau * P, piece ** equipe0, piece ** equipe1, ia ia_joueur, int maximisateur, int tour, int profondeur);

coupMM MinMaxDeBoer(plateau* P, ia inteligence, int tour, piece* equipe0[], piece* equipe1[]);

#endif
