#include "parcours.h"

void copierPlateau(const struct plateauType *source, struct plateauType *destination) {
    for (int i = 0; i < NBLIGNES; i++) {
        for (int j = 0; j < NBCOLONNES; j++) {
            destination->scene[i][j].x = source->scene[i][j].x;
            destination->scene[i][j].y = source->scene[i][j].y;

            // Allocation et copie de la pièce
            if (source->scene[i][j].pion != NULL) {
                destination->scene[i][j].pion = (struct pieceType *)malloc(sizeof(struct pieceType));
                *(destination->scene[i][j].pion) = *(source->scene[i][j].pion);
            } else {
                destination->scene[i][j].pion = NULL;
            }
        }
    }
}

void echangePiece(plateau *P, piece* p1, piece* p2) {
    int tmp = p1->val;
    p1->val = p2->val;
    p2->val = tmp;
}

bool coupAvant(coup c, int tour ) {
    if ( tour%2 == 0 ) {
        return ( c.xf - c.xd > 0 );
    } else {
        return ( c.xd - c.xf > 0);
    }
}

bool coupCote(coup c, int tour) {
    return ( (c.yf - c.yd != 0) );
}

void trouverCase(plateau* P, int joueur_actif, int col, int* x) {
    if ( joueur_actif == 1 ) {
        *x = -1;
        for (int i=0; i<NBLIGNES; i++) {
            if ( P->scene[i][col].pion != NULL && P->scene[i][col].pion->equipe == joueur_actif) {
                *x = i;
                break;
            }
        }
    } else {
        *x = -1;
        for (int i=0; i<NBLIGNES; i++) {
            if ( P->scene[NBLIGNES-i-1][col].pion != NULL && P->scene[NBLIGNES-i-1][col].pion->equipe == joueur_actif) {
                *x = NBLIGNES-i-1;
                break;
            }
        }
    }

    if ( *x < 0 || *x > NBCOLONNES || P->scene[*x][col].pion->cell == NULL) {
        //printf("Erreur ");
        //exit(1);
    }
}

coupMM actionMM(  plateau * jeu, coup c, piece* equipe0[NBPIECES], piece* equipe1[NBPIECES], ia ia_joueur, int maximisateur, int tour, int profondeur) {

    //printf(" T>OUR : %d  ", tour );

    piece *attaquant = jeu->scene[c.xd][c.yd].pion;
    piece *defenseur = jeu->scene[c.xf][c.yf].pion;
    coupMM cMM;

    if (defenseur == NULL|| defenseur->devoile || tour%2 == (1-maximisateur)) { 
        action(  jeu, c, tour%2, true ); 
        //printf(" \n\n PION \n\n");
        //afficher_pion(attaquant);
        //printf("\n");
        //if ( tour%2 == (1-maximisateur) ) {
        //    printf(" p \n ");
        //    afficher_coup(c);
        //}
        cMM = MinMax( jeu, equipe0, equipe1, ia_joueur, maximisateur, tour+1, profondeur-1);
        return cMM;
    } else {
        //afficher_coup(c);
        int ndevoile = 0;
        float stats = 0;
        plateau* copie_P = malloc(sizeof(plateau));
        piece **copie_equipe0 = malloc(sizeof(piece*) * NBPIECES);
        piece **copie_equipe1 = malloc(sizeof(piece*) * NBPIECES);

        if ( defenseur->equipe == 0) {

            for (int i=0; i<NBPIECES; i++) {
                //printf(" Pièce %d", i);
                copierPlateau(jeu, copie_P);
                extraire_equipe(copie_P, copie_equipe0, copie_equipe1);
                //afficher_plateau(copie_P);
                defenseur = copie_P->scene[c.xf][c.yf].pion;
                if ( !copie_equipe0[i]->devoile && !(defenseur->bouger && (copie_equipe0[i]->val == NUMERO_BOMBE || copie_equipe0[i]->val == NUMERO_DRAPEAU))) {
                    ndevoile++;
                    echangePiece( copie_P, defenseur, copie_equipe0[i] );
                    action( copie_P, c, tour%2, true ); 
                    cMM = MinMax( copie_P, copie_equipe0, copie_equipe1, ia_joueur, maximisateur, tour+1, profondeur-1);
                    stats += cMM.val;
                }
                libere_equipe_hors_plateau(copie_equipe0);
                libere_equipe_hors_plateau(copie_equipe1);
                libere_plateau(copie_P);
            }

        } else {

          for (int i=0; i<NBPIECES; i++) {
                //afficher_equipe(equipe1);
                copierPlateau(jeu, copie_P);
                extraire_equipe(copie_P, copie_equipe0, copie_equipe1);
                //printf(" Pièce : %d \n ", i);
                //afficher_plateau(copie_P);
                defenseur = copie_P->scene[c.xf][c.yf].pion;
                if ( !copie_equipe1[i]->devoile && !(defenseur->bouger && (copie_equipe1[i]->val == NUMERO_BOMBE || copie_equipe1[i]->val == NUMERO_DRAPEAU))) {
                    ndevoile++;
                    echangePiece( copie_P, defenseur, copie_equipe1[i] );
                    action( copie_P, c, tour%2, true ); 
                    cMM = MinMax( copie_P, copie_equipe0, copie_equipe1, ia_joueur, maximisateur, tour+1, profondeur-1);
                    stats += cMM.val;
                }
                //afficher_plateau(copie_P);
                libere_equipe_hors_plateau(copie_equipe0);
                libere_equipe_hors_plateau(copie_equipe1);
                libere_plateau(copie_P);
            }
        }
        if ( ndevoile == 0 ) {
            printf(" AHAHHAHHA ");
            afficher_plateau(jeu);
            printf(" AHAHHAHHA ");
            exit(1);
            cMM.val = 0;
        } else {
            cMM.val = stats/ndevoile;
        }
        cMM.c = c;

        free(copie_equipe0);
        free(copie_equipe1);
        //libere_plateau(copie_P);   
        free(copie_P);
        return cMM;
    }
}

void extraire_equipe(plateau * P, piece * equipe0[NBPIECES], piece * equipe1[NBPIECES]){

    int indice0 = 0;
    int indice1 = 0;
    for (int i=0; i<NBLIGNES; i++) {
        for (int j=0; j<NBCOLONNES; j++) {
            if ( P->scene[i][j].pion != NULL && P->scene[i][j].pion->equipe == 0  ) {
                equipe0[indice0] = P->scene[i][j].pion;
                indice0++;
            } else if ( P->scene[i][j].pion != NULL && P->scene[i][j].pion->equipe == 1  ) {
                equipe1[indice1] = P->scene[i][j].pion;
                indice1++;
            }
        }
    }
    for (int k = indice0; k < NBPIECES ; k++){
        equipe0[k] = malloc(sizeof(piece));
        equipe0[k]->cell = NULL;
        equipe0[k]->devoile = true;
        equipe0[k]->equipe = -1;
        equipe0[k]->val = -1;
    }
    for (int k = indice1; k < NBPIECES ; k++){
        equipe1[k] = malloc(sizeof(piece));
        equipe1[k]->cell = NULL;
        equipe1[k]->devoile = true;
        equipe1[k]->equipe = -1;
        equipe1[k]->val = -1;
    }

}

void libere_equipe_hors_plateau(piece* equipe[NBPIECES]){
    for (int i = 0 ; i < NBPIECES ; i++){
        if (equipe[i]->cell == NULL)
            free(equipe[i]);
    }
}

coupMM MinMax(plateau * P, piece ** equipe0, piece ** equipe1, ia ia_joueur, int maximisateur, int tour, int profondeur){



    if (profondeur == 0){
        coupMM retour = {.val = evaluation(P, equipe0, equipe1, ia_joueur, maximisateur, tour), .c = {0,0,0,0}};
        //printf("--- --- ---  %f --- --- --- ", retour.val);
        //printf(" EVALUATION :  %f ", retour.val);
        return retour;
    }

    if (tour%2 == maximisateur){
        tableau_dyn liste_coup = tableau_dyn_initialisation(1);
        plateau* copie_P = malloc(sizeof(plateau));
        coupMM cTmp;
        coupMM cMeilleur = { .val = -FLT_MAX, .c = { 0, 0, 0, 0}};

        piece **copie_equipe0 = malloc(sizeof(piece*) * NBPIECES);
        piece **copie_equipe1 = malloc(sizeof(piece*) * NBPIECES);
        liste_coup_possible(*P, &liste_coup, equipe0, equipe1, tour%2);

        for (int i =0; i < liste_coup.nbelt; i++){
            //printf(" \n\n coup i : %d \n\n", i);
            //afficher_plateau(P);
            copierPlateau(P, copie_P);
            extraire_equipe(copie_P, copie_equipe0, copie_equipe1);
            //affiche_tableau_dyn(&liste_coup);
            cTmp = actionMM( copie_P, liste_coup.tab[i], copie_equipe0, copie_equipe1,  ia_joueur, maximisateur, tour, profondeur );
            cTmp.c = liste_coup.tab[i];
            //afficher_plateau(P);

            if ( coupAvant( cTmp.c, tour) ) {
                cTmp.val += AJOUT;
            } else if ( coupCote(cTmp.c, tour)) {
                cTmp.val += AJOUT/1.5;
            }


            if ( cTmp.val > cMeilleur.val ) {
                cMeilleur = cTmp;
            }
            libere_equipe_hors_plateau(copie_equipe0);
            libere_equipe_hors_plateau(copie_equipe1);
            libere_plateau(copie_P);                      // Libère le plateau
        }

        tableau_dyn_supp(&liste_coup);
        free(copie_P);
        free(copie_equipe0);
        free(copie_equipe1);

        return cMeilleur;
    } else {

        int x;
        int y;
        float mini = FLT_MAX;
        tableau_dyn liste_coup = tableau_dyn_initialisation(1);
        plateau* copie_P = malloc(sizeof(plateau));
        plateau* copie_copie_P = malloc(sizeof(plateau));
        coup mvt = {.xd =x, .yd = y, .xf = -1, .yf = -1};
        coupMM cMeilleur = {.val = FLT_MAX, .c = mvt};
        coupMM cInit = { .val = FLT_MAX, .c = mvt };
        coupMM tableauCoupsPossible[NBCOLONNES];

        piece **copie_equipe0 = malloc(sizeof(piece*) * NBPIECES);
        piece **copie_equipe1 = malloc(sizeof(piece*) * NBPIECES);

        piece **copie_copie_equipe0 = malloc(sizeof(piece*) * NBPIECES);
        piece **copie_copie_equipe1 = malloc(sizeof(piece*) * NBPIECES);

        
        int total = 0;
        int nbcoups = 0;

        for (y = 0; y<NBCOLONNES; y++) {
            
            //printf(" Colonne Y %d : ", y);
            //afficher_plateau(P);

            trouverCase(P, tour%2, y, &x);
            //printf("(%d|%d)\n",x,y);

            tableau_dyn_vider(&liste_coup);
            coupMM cTmp = {.val = FLT_MAX, .c = mvt};
            total = 0;
            nbcoups = 0;

            if ( x == (-1) ) {  }//colonne vide
            else if ( P->scene[x][y].pion->devoile ) {
                piece* attaquant = P->scene[x][y].pion;

                coup_case(P, *attaquant, &liste_coup, tour%2);

                for (int i=0; i<liste_coup.nbelt; i++) { // CAS 1

                    copierPlateau(P, copie_P);
                    extraire_equipe(copie_P, copie_equipe0, copie_equipe1);
                    
                    //afficher_plateau(copie_P);

                    cTmp = actionMM(copie_P, liste_coup.tab[i], copie_equipe0, copie_equipe1,  ia_joueur, maximisateur, tour, profondeur);
                    cTmp.c = liste_coup.tab[i];

                    if ( cTmp.val < cMeilleur.val ) {
                        cMeilleur = cTmp;
                    }

                    nbcoups += 1;
                    total += cTmp.val;
                    //afficher_plateau(copie_P);

                    libere_equipe_hors_plateau(copie_equipe0);
                    libere_equipe_hors_plateau(copie_equipe1);
                    libere_plateau(copie_P);   
                }

                tableau_dyn_vider(&liste_coup);

                if ( nbcoups != 0 ) {
                        tableauCoupsPossible[y].val = total / nbcoups;
                } else {
                        tableauCoupsPossible[y].val = 1+evaluation(P, equipe0, equipe1, ia_joueur, maximisateur, tour);
                }
                tableauCoupsPossible[y].c = cMeilleur.c;
                
            } else {

                piece* attaquant = P->scene[x][y].pion;
                
                for (int i = 0; i < NBPIECES; i++) {
                    //printf(" Pièce2 : %d", i);
                    tableau_dyn_vider(&liste_coup);
                    copierPlateau(P ,copie_P);
                    extraire_equipe(copie_P, copie_equipe0, copie_equipe1);
                    attaquant = copie_P->scene[x][y].pion;
                    //printf("-- tycjj i = %d \n", i);
                    //afficher_plateau(P);
                    //afficher_plateau(copie_P);
                    //printf("\n");
                    //afficher_pion(attaquant);

                    if ( attaquant->equipe == 0 ) {
                        echangePiece(copie_P, attaquant, copie_equipe0[i]);
                        coup_case(copie_P, *attaquant, &liste_coup, tour%2);
                        //affiche_tableau_dyn(&liste_coup);
                        if ( !copie_equipe0[i]->devoile && !(attaquant->bouger && (copie_equipe0[i]->val == NUMERO_BOMBE || copie_equipe0[i]->val == NUMERO_DRAPEAU))) {

                            for (int j=0; j<liste_coup.nbelt; j++) { // CAS 1

                                copierPlateau(copie_P, copie_copie_P);
                                extraire_equipe(copie_copie_P, copie_copie_equipe0, copie_copie_equipe1);
                                //afficher_plateau(copie_P);
                                attaquant = copie_copie_P->scene[x][y].pion;
                                
                                cTmp = actionMM(copie_copie_P, liste_coup.tab[j], copie_copie_equipe0, copie_copie_equipe1,  ia_joueur, maximisateur, tour, profondeur);
                                cTmp.c = liste_coup.tab[j];

                                if ( cTmp.val < cMeilleur.val ) {
                                    cMeilleur = cTmp;
                                }

                                nbcoups += 1;
                                total += cTmp.val;
                                //afficher_plateau(copie_P);
                                libere_equipe_hors_plateau(copie_copie_equipe0);
                                libere_equipe_hors_plateau(copie_copie_equipe1);
                                libere_plateau(copie_copie_P);   
                            }

                        }
                        tableau_dyn_vider(&liste_coup);
                    } else if ( attaquant->equipe == 1 ) {
                        echangePiece(copie_P, attaquant, copie_equipe1[i]);
                        coup_case(copie_P, *attaquant, &liste_coup, tour%2);
                        //affiche_tableau_dyn(&liste_coup);
                        if ( !copie_equipe1[i]->devoile && !(attaquant->bouger && (copie_equipe1[i]->val == NUMERO_BOMBE || copie_equipe1[i]->val == NUMERO_DRAPEAU))) {

                            for (int j=0; j<liste_coup.nbelt; j++) { // CAS 1

                                copierPlateau(copie_P, copie_copie_P);
                                extraire_equipe(copie_copie_P, copie_copie_equipe0, copie_copie_equipe1);
                                //afficher_plateau(copie_P);
                                attaquant = copie_copie_P->scene[x][y].pion;
                                
                                cTmp = actionMM(copie_copie_P, liste_coup.tab[j], copie_copie_equipe0, copie_copie_equipe1,  ia_joueur, maximisateur, tour, profondeur);
                                cTmp.c = liste_coup.tab[j];
                                //afficher_plateau(copie_P);

                                if ( cTmp.val < cMeilleur.val ) {
                                    cMeilleur = cTmp;
                                }

                                nbcoups += 1;
                                total += cTmp.val;
                                //afficher_plateau(copie_P);

                                libere_equipe_hors_plateau(copie_copie_equipe0);
                                libere_equipe_hors_plateau(copie_copie_equipe1);
                                libere_plateau(copie_copie_P);   
                            }
                        }
                        tableau_dyn_vider(&liste_coup);
                    } else {
                        printf("!!!!!!!!!!! attaquant sans equipe !!!!!!!!!");
                        //afficher_pion(attaquant);
                        printf("%d - %d", x, y);
                        exit(1);
                    }

                    if ( nbcoups != 0 ) {
                        tableauCoupsPossible[y].val = total / nbcoups;
                    } else {
                        tableauCoupsPossible[y].val = 1+evaluation(P, equipe0, equipe1, ia_joueur, maximisateur, tour);
                    }
                    tableauCoupsPossible[y].c = cMeilleur.c;

                libere_equipe_hors_plateau(copie_equipe0);
                libere_equipe_hors_plateau(copie_equipe1);
                libere_plateau(copie_P);   
                }
            }

            //printf("FIN colonne %d", y);
        }



        for ( int y = 0; y < NBCOLONNES; y++) {
            if ( tableauCoupsPossible[y].val < mini ) {
                cMeilleur = tableauCoupsPossible[y];
                mini = cMeilleur.val;
            }
        }

        coupMM retour = cMeilleur;

        tableau_dyn_supp(&liste_coup);
        free(copie_equipe0);
        free(copie_equipe1);
        free(copie_copie_equipe0);
        free(copie_copie_equipe1);
        //libere_plateau(copie_P);   
        free(copie_P);
        free(copie_copie_P);
    
        //printf(" \n\n cMeilleur \n\n");
        //afficher_coupMM(cMeilleur);
        //printf("\n\n");

        return retour;
    }
}

coupMM MinMaxDeBoer(plateau* P, ia inteligence, int tour, piece* equipe0[], piece* equipe1[]){
    coupMM retour;
    float eval;

    tableau_dyn liste_coup = tableau_dyn_initialisation(1);
    liste_coup_possible(*P, &liste_coup, equipe0, equipe1, tour%2);

    retour.val = -10000;
    retour.c = liste_coup.tab[0];

    for (int i = 0; i < liste_coup.nbelt; i++){
        eval = evaluationDeBoer(P, liste_coup.tab[i], inteligence, tour);
        if (eval > retour.val){
            retour.val = eval;
            retour.c = liste_coup.tab[i];
        }
    }


    tableau_dyn_supp(&liste_coup);
    return retour;
}


/*
int main() {
    srand(3);
    plateau* jeu = malloc(sizeof(plateau));
    initialisation_plateau(jeu); 
    coupMM coup_test;
    int tour%2 = 0;

    piece **equipe0 = malloc(sizeof(piece*) * NBPIECES);
    if (equipe0 == NULL) {
        printf("Erreur d'allocation mémoire\n");
        exit(1);
    }
    pseudo_alea(jeu, 0, equipe0); // Place équipe 0    piece **equipe1 = malloc(sizeof(piece*) * NBPIECES); 

    piece **equipe1 = malloc(sizeof(piece*) * NBPIECES);  
    if (equipe1 == NULL) {
        printf("Erreur d'allocation mémoire\n");
        exit(1);
    }
    pseudo_alea(jeu, 1, equipe1);// Place équipe 1 

    plateau* copieP = malloc(sizeof(plateau));
    piece **copie_equipe0 = malloc(sizeof(piece*) * NBPIECES);
    piece **copie_equipe1 = malloc(sizeof(piece*) * NBPIECES);
    for (int i = 0; i < NBPIECES ; i++){
        copie_equipe0[i] = malloc(sizeof(piece));
        copie_equipe1[i] = malloc(sizeof(piece));
    }

    copierPlateau(jeu, copieP);
    extraire_equipe(copieP, copie_equipe0, copie_equipe1);

    afficher_coupMM(coup_test);

    return 0;
}
*/
