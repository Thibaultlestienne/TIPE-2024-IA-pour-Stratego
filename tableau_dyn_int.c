#include "tableau_dyn_int.h" 

tableau_dyn_int tableau_dyn_int_initialisation(int n) {
    tableau_dyn_int t;
    t.taille = n;
    t.nbelt = 0;
    t.tab = malloc(n*sizeof(int));
    if (t.tab == NULL) {
        printf("Erreur d'allocation mémoire\n");
        exit(1);
    } 
    return t;
};

void agrandir_tableau_dyn_int(tableau_dyn_int* t) {
    int* tmp = malloc(2*t->taille*sizeof(int));
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

void tableau_dyn_int_ajoute(tableau_dyn_int* t, int v) {
    if (t->taille == t->nbelt) {
        agrandir_tableau_dyn_int(t);
    };
    t->tab[t->nbelt] = v;
    t->nbelt += 1;
};

void tableau_dyn_int_vider(tableau_dyn_int* t) {
    free(t->tab);
    if (t->tab == NULL) {
        printf("Erreur d'allocation mémoire\n");
        exit(1);
    } 
    t->taille = 1;
    t->nbelt = 0;
};

void tableau_dyn_int_supp(tableau_dyn_int* t){
    free(t->tab);

};

void affiche_tableau_dyn_int(tableau_dyn_int* t) {
    printf("Liste des coups possibles\n");
    for (int i=0; i<t->nbelt; i++) {
        printf(" Dans la case : %d il y a %d\n", i, t->tab[i]);
    };
};

int minimum_dyn_tab_int(tableau_dyn_int dyntab){
    int min = dyntab.tab[0];
    for (int i = 1; i < dyntab.nbelt ; i++){
        if (dyntab.tab[i] < min){min = dyntab.tab[i];}
    }
    return min;
}

int maximum_dyn_tab_int(tableau_dyn_int dyntab){
    int max = dyntab.tab[0];
    for (int i = 1; i < dyntab.nbelt ; i++){
        if (dyntab.tab[i] > max){max = dyntab.tab[i];}
    }
    return max;
}

/*
int main() {
    tableau_dyn_int t = tableau_dyn_int_initialisation(10);
    for (int i=0; i<100; i++) {
        tableau_dyn_int_ajoute(&t, i);
    };
    affiche_tableau_dyn_int(&t);
    printf("min : %d \nmax : %d\n", minimum_dyn_tab_int(t), maximum_dyn_tab_int(t));
    tableau_dyn_int_supp(&t);
    return 0;
};*/