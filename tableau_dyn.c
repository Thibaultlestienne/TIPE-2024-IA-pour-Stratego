#include "tableau_dyn.h" 

tableau_dyn tableau_dyn_initialisation(int n) {
    tableau_dyn t;
    t.taille = n;
    t.nbelt = 0;
    t.tab = malloc(n*sizeof(coup));
    if (t.tab == NULL) {
        printf("Erreur d'allocation mémoire\n");
        exit(1);
    } 
    return t;
};

void agrandir(tableau_dyn* t) {
    coup* tmp = malloc(2*t->taille*sizeof(coup));
    if (tmp == NULL) {
        printf("Erreur d'allocation mémoire\n");
        exit(1);
    } 
    int ntaille = 2*t->taille;
    for (int i=0; i<t->nbelt; i++) {
        tmp[i] = t->tab[i];
    };
    t->taille = ntaille;
    free(t->tab);
    t->tab = tmp;
};

void tableau_dyn_ajoute(tableau_dyn* t, coup c) {
    if (t->taille == t->nbelt) {
        agrandir(t);
    };
    t->tab[t->nbelt] = c;
    t->nbelt += 1;
};

void tableau_dyn_vider(tableau_dyn* t) {
    if (t->tab == NULL) {
        printf("Erreur d'allocation mémoire\n");
        exit(1);
    } 
    t->taille = 1;
    t->nbelt = 0;
};

void tableau_dyn_supp(tableau_dyn* t){
    free(t->tab);

};

void affiche_tableau_dyn(tableau_dyn* t) {
    printf("Liste des coups possibles\n");
    for (int i=0; i<t->nbelt; i++) {
        printf(" Coup %d : (%d/%d) -> (%d/%d) \n", i+1, t->tab[i].xd, t->tab[i].yd, t->tab[i].xf, t->tab[i].yf);
    };
};

/*
int main() {
    tableau_dyn t = tableau_dyn_initialisation(10);
    for (int i=0; i<100; i++) {
        coup c = {.xd = 0, .yd = i, .xf = i-2, .yf = 0};
        tableau_dyn_ajoute(&t, c);
    };
    affiche_tableau_dyn(t);
    free(t.tab);
    t.nbelt = 0;
    t.taille;
    return 1;
};*/