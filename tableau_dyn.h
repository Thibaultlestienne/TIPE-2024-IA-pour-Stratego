#ifndef TABLEAU_DYN
#define TABLEAU_DYN

typedef struct tableau_dyn tableau_dyn;

#include <stdlib.h>
#include <stdio.h>
#include "stratego.h"

typedef struct tableau_dyn {
    int taille;
    int nbelt;
    coup* tab;
} tableau_dyn;

tableau_dyn tableau_dyn_initialisation(int n);

void agrandir(tableau_dyn* t);

void tableau_dyn_ajoute(tableau_dyn* t, coup c);

void tableau_dyn_vider(tableau_dyn* t);

void tableau_dyn_supp(tableau_dyn* t);

void affiche_tableau_dyn(tableau_dyn* t);

#endif // TABLEAU_DYN