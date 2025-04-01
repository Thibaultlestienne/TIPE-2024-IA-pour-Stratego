#ifndef TABLEAU_DYN_INT
#define TABLEAU_DYN_INT

#include <stdlib.h>
#include <stdio.h>
 
typedef struct tableau_dyn_int {
    int taille;
    int nbelt;
    int* tab;
} tableau_dyn_int;

tableau_dyn_int tableau_dyn_int_initialisation(int n);

void agrandir_tableau_dyn_int(tableau_dyn_int* t);

void tableau_dyn_int_ajoute(tableau_dyn_int* t, int c);

void tableau_dyn_int_vider(tableau_dyn_int* t);

void tableau_dyn_int_supp(tableau_dyn_int* t);

void affiche_tableau_dyn_int(tableau_dyn_int* t);

#endif // TABLEAU_DYN_INT