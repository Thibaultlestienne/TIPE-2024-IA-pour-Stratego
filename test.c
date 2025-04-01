/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
/////////////////// affichage et tests //////////////////
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////

void afficher_tableau(int tableau[], int taille) {// affiche un tableau en console
    printf("[");
    for (int i = 0; i < taille; i++) {
        printf("%d", tableau[i]);
        if (i < taille - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

void afficher_ia(ia ia_a_afficher){
    printf("Découvertes: ");
    for (int i = 0; i < NBPIECESDIFF; i++) {
        printf("%.3f ", ia_a_afficher.decouvertes[i]);
    }

    printf("\nValeur: ");
    for (int i = 0; i < NBPIECESDIFF; i++) {
        printf("%.3f ", ia_a_afficher.valeur[i]);
    }

    printf("\nmouvement: ");
    printf("%.3f ", ia_a_afficher.mouvement);

    printf("\n");
}

void afficher_tableau_ia(ia tableau[], int taille) {// affiche un tableau en console
    printf("[");
    for (int i = 0; i < taille; i++) {
        afficher_ia(tableau[i]);
        if (i < taille - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}