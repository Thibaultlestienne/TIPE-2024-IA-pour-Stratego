#include "evaluation.h"

int distancePieceType( int i, int j, int val, int maximisateur, piece** equipe0, piece** equipe1 ) {
    int min = 24;
    int tmp;
    if (maximisateur == 0 ) {
        for (int k = 0; k<NBPIECES; k++) {
            tmp = 0;
            if (equipe0[k] != NULL && equipe0[k]->cell != NULL && equipe0[k]->val == val) {
                tmp = abs(i - equipe0[k]->cell->x) + abs(j - equipe0[k]->cell->y);
                if ( tmp < min ) {
                    min = tmp;
                }
            }

        }
    } else {
        for (int k = 0; k<NBPIECES; k++) {
            tmp = 0;
            if (equipe1[k] != NULL && equipe1[k]->cell != NULL && equipe1[k]->val == val) {
                tmp = abs(i - equipe1[k]->cell->x) + abs(j - equipe1[k]->cell->y);
                if ( tmp < min ) {
                    min = tmp;
                }
            }

        }
    }
    return min;
}

int distanceDEnnemi( int maximisateur, piece** equipe0, piece** equipe1 ) {
    int min = DISTANCEMAX+1;
    int tmp;
    int i;
    int j;
    if ( maximisateur == 0) {
        for (int k=0; k<NBPIECES; k++) {
            if ( equipe0[k] != NULL && equipe0[k]->cell != NULL && equipe0[k]->val == 0 ) {
                i = equipe0[k]->cell->x;
                j = equipe0[k]->cell->y;
            }
            break;
        }
        for ( int k=0; k<NBPIECES; k++) {
            tmp = 0;
            if (equipe1[k]->cell != NULL ) {
                tmp = abs(i - equipe1[k]->cell->x) + abs(j - equipe1[k]->cell->y); 
                if ( tmp < min ) {
                    min = tmp;
                }           
            }
        }
    } else {
        for (int k=0; k<NBPIECES; k++) {
            if ( equipe1[k] != NULL && equipe1[k]->cell != NULL && equipe1[k]->val == 0 ) {
                i = equipe1[k]->cell->x;
                j = equipe1[k]->cell->y;
            }
            break;
        }
        for ( int k=0; k<NBPIECES; k++) {
            tmp = 0;
            if (equipe0[k]->cell != NULL ) {
                tmp = abs(i - equipe0[k]->cell->x) + abs(j - equipe0[k]->cell->y); 
                if ( tmp < min ) {
                    min = tmp;
                }           
            }
        }
    }
    return tmp;
}

int distanceD8( int maximisateur, piece** equipe0, piece** equipe1 ) {
    int min = DISTANCEMAX+1;
    int tmp;
    int i;
    int j;
    if ( maximisateur == 0) {
        for ( int k = 0; k < NBPIECES; k++) {
            if ( equipe0[k]->cell != NULL && equipe0[k]->val == 0) {
                i = equipe0[k]->cell->x;
                j = equipe0[k]->cell->y;
                break;
            }
        }
        for ( int k=0; k<NBPIECES; k++) {
            tmp = 0;
            if (equipe0[k] != NULL && equipe0[k]->cell != NULL && equipe0[k]->val >= 8) {
                tmp = abs(i - equipe0[k]->cell->x) + abs(j - equipe0[k]->cell->y); 
                if ( tmp < min ) {
                    min = tmp;
                }           
            }
        }
    } else {
        for ( int k = 0; k < NBPIECES; k++) {
            if ( equipe1[k]->cell != NULL && equipe1[k]->val == 0) {
                i = equipe1[k]->cell->x;
                j = equipe1[k]->cell->y;
                break;
            }
        }
        for ( int k=0; k<NBPIECES; k++) {
            tmp = 0;
            if (equipe1[k] != NULL && equipe1[k]->cell != NULL && equipe1[k]->val >= 8) {
                tmp = abs(i - equipe1[k]->cell->x) + abs(j - equipe1[k]->cell->y); 
                if ( tmp < min ) {
                    min = tmp;
                }           
            }
        }
    }
    return tmp;
}

int distance18(int maximisateur, piece** equipe0, piece** equipe1) {
    int min = DISTANCEMAX + 1;
    int tmp;
    int i;
    int j;
    if ( maximisateur == 0) {
        for ( int k = 0; k < NBPIECES; k++) {
            if ( equipe0[k]->cell != NULL && equipe0[k]->val == 1) {
                i = equipe0[k]->cell->x;
                j = equipe0[k]->cell->y;
                break;
            }
        }
        for (int k=0; k<NBPIECES; k++) {
            tmp = 0;
            if ( equipe0[k] != NULL && equipe0[k]->cell != NULL && equipe0[k]->val >= 8 ) {
                tmp = abs(equipe0[k]->cell->x - i) + abs(equipe0[k]->cell->y - j);
                if ( tmp < min ) {
                    min = tmp;
                }
            }
        }
    } else {
        for ( int k = 0; k < NBPIECES; k++) {
            if ( equipe1[k]->cell != NULL && equipe1[k]->val == 1) {
                i = equipe1[k]->cell->x;
                j = equipe1[k]->cell->y;
                break;
            }
        }
        for ( int k=0; k<NBPIECES; k++) {
            tmp = 0;
            if ( equipe1[k] != NULL && equipe1[k]->cell != NULL && equipe1[k]->val >= 8 ) {
                tmp = abs(equipe1[k]->cell->x - i) + abs(equipe1[k]->cell->y - j);
                if ( tmp < min ) {
                    min = tmp;
                }
            }
        }
    }
    return tmp;
}

int distance3B(int maximisateur, int nbimmobile, piece** equipe0, piece** equipe1) {
    int min = DISTANCEMAX + 1;
    int nb3 = 0;
    int* t3 = malloc(3*sizeof(piece));
    int tmp;
    for (int k=0; k<3; k++ ) {
        t3[k] = (-1);
    }
    if (maximisateur == 0 ) {
        for (int k = 0; k<NBPIECES; k++ ) {
            if( equipe0[k]->cell != NULL && equipe0[k]->val == 3 ) {
                t3[nb3] = k;
                nb3 += 1;
            }
        }
        for (int k = 0; k<NBPIECES; k++) {
            if ( (equipe1[k] != NULL && equipe1[k]->cell != NULL && equipe1[k]->devoile && equipe1[k]->val == NUMERO_BOMBE) ) { // CHANGER
                for (int i=0; i<3; i++) {
                    tmp = 0;
                    if ( t3[i] != (-1) && equipe0[t3[i]] != NULL && equipe0[t3[i]]->cell != NULL ) {
                        tmp = abs(equipe1[k]->cell->x - equipe0[t3[i]]->cell->x) + abs(equipe1[k]->cell->y - equipe0[t3[i]]->cell->y);
                        if ( tmp < min ) {
                            min = tmp;
                        }
                    }
                }
            }

        }
    } else {
        for (int k = 0; k<NBPIECES; k++ ) {
            if( equipe1[k]->cell != NULL && equipe1[k]->val == 3 ) {
                t3[nb3] = k;
                nb3 += 1;
            }
        }
        for (int k = 0; k<NBPIECES; k++) {
            if ( (equipe0[k] != NULL && equipe0[k]->cell != NULL && equipe0[k]->devoile && equipe0[k]->val == 11) ) {
                for (int i=0; i<3; i++) {
                    tmp = 0;
                    if ( t3[i] != (-1) && equipe1[t3[i]] != NULL && equipe1[t3[i]]->cell != NULL) {
                        tmp = abs(equipe0[k]->cell->x - equipe1[t3[i]]->cell->x) + abs(equipe0[k]->cell->y - equipe1[t3[i]]->cell->y);
                        if ( tmp < min ) {
                            min = tmp;
                        }
                    }
                }
            }

        }
    }
    free(t3);
    if ( min = DISTANCEMAX + 1 ) {
        return 0;
    } else {
        return min;
    }
}


float evaluationV1(plateau* P, piece** equipe0, piece** equipe1, ia intelligence, int maximisateur, int tour) {
    float eval = ( generer_valeur_aleatoire_0_1() ) * intelligence.parametres[ALEATOIREV1];
        /*if ( tour < 10 ) {
        //printf("tour : %d", tour);
        return (float)rand() / (float)RAND_MAX;
    }*/
    //printf("----------------------------- EVALUATION -----------------------------\n");
    //afficher_equipe(equipe1);
    //printf("maximisateur : %d\n", maximisateur);
    //afficher_plateau(P);
    //printf(" tour : %d ", tour);
    
    if (maximisateur == 0){
        for (int i=0; i<NBPIECES; i++) {
            if (equipe0[i]->cell != NULL) { //piece en vie 
                eval += intelligence.parametres[VALEURV1(equipe0[i]->val)];
                if (equipe0[i]->devoile) { eval -= intelligence.parametres[DECOUVERTEV1(equipe0[i]->val)]; }
                else if (equipe0[i]->bouger){ eval -= intelligence.parametres[MOUVEMENTV1];}
            } 
            
            if (equipe1[i]->cell != NULL) { // piece en vie
                eval -= intelligence.parametres[VALEURV1(equipe1[i]->val)];
                if (equipe1[i]->devoile) { eval += intelligence.parametres[DECOUVERTEV1(equipe1[i]->val)]; }
                else if (equipe1[i]->bouger){ eval += intelligence.parametres[MOUVEMENTV1];}

            } 
        }
    } else { // joueur 1 maximise
        for (int i=0; i<NBPIECES; i++) {
            if (equipe0[i]->cell != NULL) {
                eval -= intelligence.parametres[VALEURV1(equipe0[i]->val)];
                if (equipe0[i]->devoile) { eval += intelligence.parametres[DECOUVERTEV1(equipe0[i]->val)];}
                else if (equipe0[i]->bouger){ eval += intelligence.parametres[MOUVEMENTV1];}
            }
            
            if (equipe1[i]->cell != NULL) {
                eval += intelligence.parametres[VALEURV1(equipe1[i]->val)];
                if (equipe1[i]->devoile) { eval -= intelligence.parametres[DECOUVERTEV1(equipe1[i]->val)]; }
                else if (equipe1[i]->bouger){ eval -= intelligence.parametres[MOUVEMENTV1];}
            } 
        }
    }
    //printf("------------------------------ %f ----------------------------------\n \n",eval);
    
    return eval;
}

float evaluationV2(plateau* P, piece** equipe0, piece** equipe1, ia intelligence, int maximisateur, int tour){
    float eval = ( generer_valeur_aleatoire_0_1() ) * intelligence.parametres[ALEATOIREV1];

    int nb3 = 0;
    int nbimmobile = 0;

    if (maximisateur == 0){
        for (int i=0; i<NBPIECES; i++) {
             if ( equipe0[i]->cell != NULL && equipe0[i]->val == 3 ) {
                nb3 += 1;
            }

            if ( equipe1[i]->cell != NULL && !(equipe1[0]->bouger) ) {
                nbimmobile += 1;
            }
        }

        if ( nb3 != 0 ) {
            eval += intelligence.parametres[DISTANCE3(distance3B(0, nbimmobile, equipe0, equipe1 ))]; // numero piece et numero maximisateur
        }

        for (int i=0; i<NBPIECES; i++) {

            if (equipe0[i]->cell != NULL) { //piece en vie 
                if ( nb3 == 1 && equipe0[i]->val == 3) {
                    eval += intelligence.parametres[VALEUR13];
                }
                eval += intelligence.parametres[VALEURV1(equipe0[i]->val)];
                if (equipe0[i]->devoile) { eval -= intelligence.parametres[DECOUVERTEV1(equipe0[i]->val)]; }
            } 
            
            if (equipe1[i]->cell != NULL) { // piece en vie
                eval -= intelligence.parametres[VALEURV1(equipe1[i]->val)];
                if (equipe1[i]->devoile) { eval += intelligence.parametres[DEVOILEV1]; }
                else if (equipe1[i]->bouger){ eval += intelligence.parametres[MOUVEMENTV1];}

            } 
        }
    } else { // joueur 1 maximise
        for (int i=0; i<NBPIECES; i++) {
             if ( equipe1[i]->cell != NULL && equipe1[i]->val == 3 ) {
                nb3 += 1;
            }

            if ( equipe0[i]->cell != NULL && !(equipe0[0]->bouger) ) {
                nbimmobile += 1;
            }
        }

        if ( nb3 != 0 ) {
            eval += intelligence.parametres[DISTANCE3(distance3B(1, nbimmobile, equipe0, equipe1 ))];
        }

        for (int i=0; i<NBPIECES; i++) {

            if (equipe0[i]->cell != NULL) {
                eval -= intelligence.parametres[VALEURV1(equipe0[i]->val)];
                if (equipe0[i]->devoile) { eval += intelligence.parametres[DEVOILEV1];}
                else if (equipe0[i]->bouger){ eval += intelligence.parametres[MOUVEMENTV1];}
            }
            
            if (equipe1[i]->cell != NULL) {
                if( nb3 == 1 && equipe1[i]->val == 3 ) {
                    eval += intelligence.parametres[VALEUR13];
                };
                eval += intelligence.parametres[VALEURV1(equipe1[i]->val)];
                if (equipe1[i]->devoile) { eval -= intelligence.parametres[DECOUVERTEV1(equipe1[i]->val)]; }
            } 
        }
    }
    //printf("------------------------------ %f ----------------------------------\n \n",eval);

    return eval;
}

float evaluationV3(plateau* P, piece** equipe0, piece** equipe1, ia intelligence, int maximisateur, int tour){
    float eval = ( generer_valeur_aleatoire_0_1() ) * intelligence.parametres[ALEATOIREV1];

    int nb3 = 0;
    int nb1 = 0;
    int nbimmobile = 0;


    if (maximisateur == 0){
        for (int i=0; i<NBPIECES; i++) {
             if ( equipe0[i]->cell != NULL && equipe0[i]->val == 3 ) {
                nb3 += 1;
            }

            if ( equipe1[i]->cell != NULL && !(equipe1[0]->bouger) ) {
                nbimmobile += 1;
            }

            if ( equipe0[i]->cell != NULL && equipe0[i]->val == 1 ) {
                nb1 += 1;
            }
        }

        if ( nb3 != 0 ) {
            eval += intelligence.parametres[DISTANCE3(distance3B(0, nbimmobile, equipe0, equipe1 ))];
        }

        if ( ( nb1 != 0 ) && ( distance18(0, equipe0, equipe1 ) <= 2 ) ) {
            eval += intelligence.parametres[DISTANCE1]; // numero piece et numero maximisateur               
        }

        for (int i=0; i<NBPIECES; i++) {

            if (equipe0[i]->cell != NULL) { //piece en vie 
                if ( nb3 == 1 && equipe0[i]->val == 3) {
                    eval += intelligence.parametres[VALEUR13];
                }
                eval += intelligence.parametres[VALEURV1(equipe0[i]->val)];
                if (equipe0[i]->devoile) { eval -= intelligence.parametres[DECOUVERTEV1(equipe0[i]->val)]; }
            } 
            
            if (equipe1[i]->cell != NULL) { // piece en vie
                eval -= intelligence.parametres[VALEURV1(equipe1[i]->val)];
                if (equipe1[i]->devoile) { eval += intelligence.parametres[DEVOILEV1]; }
                else if (equipe1[i]->bouger){ eval += intelligence.parametres[MOUVEMENTV1];}

            } 
        }
    } else { // joueur 1 maximise
        for (int i=0; i<NBPIECES; i++) {
             if ( equipe1[i]->cell != NULL && equipe1[i]->val == 3 ) {
                nb3 += 1;
            }

            if ( equipe0[i]->cell != NULL && !(equipe0[0]->bouger) ) {
                nbimmobile += 1;
            }

            if ( equipe1[i]->cell != NULL && equipe1[i]->val == 1 ) {
                nb1 += 1;
            }
        }

        if ( nb3 != 0 ) {
            eval += intelligence.parametres[DISTANCE3(distance3B(1, nbimmobile, equipe0, equipe1 ))];
        }

        if ( ( nb1 != 0 ) && distance18(1, equipe0, equipe1 ) <= 2 ) {
            eval += intelligence.parametres[DISTANCE1]; // numero piece et numero maximisateur               
        }

        for (int i=0; i<NBPIECES; i++) {

            if (equipe0[i]->cell != NULL) {
                eval -= intelligence.parametres[VALEURV1(equipe0[i]->val)];
                if (equipe0[i]->devoile) { eval += intelligence.parametres[DEVOILEV1];}
                else if (equipe0[i]->bouger){ eval += intelligence.parametres[MOUVEMENTV1];}
            }
            
            if (equipe1[i]->cell != NULL) {
                if( nb3 == 1 && equipe1[i]->val == 3 ) {
                    eval += intelligence.parametres[VALEUR13];
                };
                eval += intelligence.parametres[VALEURV1(equipe1[i]->val)];
                if (equipe1[i]->devoile) { eval -= intelligence.parametres[DECOUVERTEV1(equipe1[i]->val)]; }
            } 
        }
    }
    //printf("------------------------------ %f ----------------------------------\n \n",eval);

    return eval;
}

float evaluationV4(plateau* P, piece** equipe0, piece** equipe1, ia intelligence, int maximisateur, int tour){
    float eval = ( generer_valeur_aleatoire_0_1() ) * intelligence.parametres[ALEATOIREV1];

    int nb3 = 0;
    int nb1 = 0;
    int nbimmobile = 0;


    if (maximisateur == 0){
        for (int i=0; i<NBPIECES; i++) {
             if ( equipe0[i]->cell != NULL && equipe0[i]->val == 3 ) {
                nb3 += 1;
            }

            if ( equipe1[i]->cell != NULL && !(equipe1[0]->bouger) ) {
                nbimmobile += 1;
            }

            if ( equipe0[i]->cell != NULL && equipe0[i]->val == 1 ) {
                nb1 += 1;
            }
        }

        if ( nb3 != 0 ) {
            eval += intelligence.parametres[DISTANCE3(distance3B(0, nbimmobile, equipe0, equipe1 ))];
        }

        if ( ( nb1 != 0 ) && distance18(0, equipe0, equipe1 ) <= 2 ) {
            eval += intelligence.parametres[DISTANCE1]; // numero piece et numero maximisateur               
        }

        if ( distanceD8( 0, equipe0, equipe1 ) <= distanceDEnnemi(0, equipe0, equipe1)) {
            eval += intelligence.parametres[DISTANCED];
        }

        for (int i=0; i<NBPIECES; i++) {

            if (equipe0[i]->cell != NULL) { //piece en vie 
                if ( nb3 == 1 && equipe0[i]->val == 3) {
                    eval += intelligence.parametres[VALEUR13];
                }
                eval += intelligence.parametres[VALEURV1(equipe0[i]->val)];
                if (equipe0[i]->devoile) { eval -= intelligence.parametres[DECOUVERTEV1(equipe0[i]->val)]; }
            } 
            
            if (equipe1[i]->cell != NULL) { // piece en vie
                eval -= intelligence.parametres[VALEURV1(equipe1[i]->val)];
                if (equipe1[i]->devoile) { eval += intelligence.parametres[DEVOILEV1]; }
                else if (equipe1[i]->bouger){ eval += intelligence.parametres[MOUVEMENTV1];}

            } 
        }
    } else { // joueur 1 maximise
        for (int i=0; i<NBPIECES; i++) {
             if ( equipe1[i]->cell != NULL && equipe1[i]->val == 3 ) {
                nb3 += 1;
            }

            if ( equipe0[i]->cell != NULL && !(equipe0[0]->bouger) ) {
                nbimmobile += 1;
            }

            if ( equipe1[i]->cell != NULL && equipe1[i]->val == 1 ) {
                nb1 += 1;
            }
        }

        if ( nb3 != 0 ) {
            eval += intelligence.parametres[DISTANCE3(distance3B(1, nbimmobile, equipe0, equipe1 ))];
        }

        if ( ( nb1 != 0 )  && distance18(1, equipe0, equipe1 ) <= 2 ) {
            eval += intelligence.parametres[DISTANCE1]; // numero piece et numero maximisateur               
        }

        if ( distanceD8(1, equipe0, equipe1 ) <= distanceDEnnemi(1, equipe0, equipe1)) {
            eval += intelligence.parametres[DISTANCED];
        }

        for (int i=0; i<NBPIECES; i++) {

            if (equipe0[i]->cell != NULL) {
                eval -= intelligence.parametres[VALEURV1(equipe0[i]->val)];
                if (equipe0[i]->devoile) { eval += intelligence.parametres[DEVOILEV1];}
                else if (equipe0[i]->bouger){ eval += intelligence.parametres[MOUVEMENTV1];}
            }
            
            if (equipe1[i]->cell != NULL) {
                if( nb3 == 1 && equipe1[i]->val == 3 ) {
                    eval += intelligence.parametres[VALEUR13];
                };
                eval += intelligence.parametres[VALEURV1(equipe1[i]->val)];
                if (equipe1[i]->devoile) { eval -= intelligence.parametres[DECOUVERTEV1(equipe1[i]->val)]; }
            } 
        }
    }
    //printf("------------------------------ %f ----------------------------------\n \n",eval);

    return eval;
}

float evaluationV10(plateau* P, coup c, ia intelligence, int tour){
    float eval = 0;

    piece* attaquant = P->scene[c.xd][c.yd].pion;
    int i = attaquant->val;
    piece* defenseur = P->scene[c.xf][c.yf].pion;

    if (defenseur != NULL && defenseur->devoile && !((defenseur->val < i)
                                                || ( defenseur->val == NUMERO_BOMBE     && attaquant->val == 3 ) 
                                                || ( defenseur->val == 10               && attaquant->val == 1 ))
                                                )
        {return -100000;}

    eval += intelligence.parametres[PREMIERCOUPV10(i)]                * (tour<2);
    eval += intelligence.parametres[ATTAQUEPIECEIMMOBILEV10(i)]       * (defenseur != NULL && !defenseur->bouger && !defenseur->devoile);
    eval += intelligence.parametres[ATTAQUEPIECEPLUFAIBLEV10(i)]      * (defenseur != NULL && defenseur->devoile && ((defenseur->val < i)
                                                                                                                    || ( defenseur->val == NUMERO_BOMBE     && attaquant->val == 3 ) 
                                                                                                                    || ( defenseur->val == 10               && attaquant->val == 1 ))
                                                                                                                   );

    eval += intelligence.parametres[AVANCERV10(i)]                    * (attaquant->equipe == 0 && c.xd < c.xf)
                                                                    || (attaquant->equipe == 1 && c.xd > c.xf) ;

    eval += intelligence.parametres[MOUVEMENTDV10(i)]                 * (attaquant->equipe == 0 && c.yd > c.yf)
                                                                    || (attaquant->equipe == 1 && c.yd < c.yf) ;

    eval += intelligence.parametres[RECULERV10(i)]                    * (attaquant->equipe == 0 && c.xd > c.xf)
                                                                    || (attaquant->equipe == 1 && c.xd < c.xf) ;

    eval += intelligence.parametres[MOUVEMENTGV10(i)]                 * (attaquant->equipe == 0 && c.yd < c.yf)
                                                                    || (attaquant->equipe == 1 && c.yd > c.yf) ;

    eval += intelligence.parametres[ATTAQUERPIECEBOUGERV10(i)]        * (defenseur != NULL && defenseur->bouger && !defenseur->devoile);

    eval += intelligence.parametres[PROTEGERCHEMINV10(i)]             * ( 2 < c.yf && c.yf < 5) && !( 2 < c.yd && c.yd < 5);
    eval += intelligence.parametres[DERRIERELACV10(i)]                * ( 2 < c.xf && c.xf < 5) && !( 2 < c.xd && c.xd < 5);
    eval += intelligence.parametres[ALEATOIREV10(i)]                * generer_valeur_aleatoire_0_1();
    return eval;
}

float evaluationV11(plateau* P, coup c, ia intelligence, int tour){
    float eval = 0;

    piece* attaquant = P->scene[c.xd][c.yd].pion;
    int i = attaquant->val;
    piece* defenseur = P->scene[c.xf][c.yf].pion;

    if (defenseur != NULL && defenseur->devoile && !((defenseur->val < i)
                                                || ( defenseur->val == NUMERO_BOMBE     && attaquant->val == 3 ) 
                                                || ( defenseur->val == 10               && attaquant->val == 1 ))
                                                )
        {return -100000;}

    eval += intelligence.parametres[PREMIERCOUPV11(i)]                * (tour<2);
    eval += intelligence.parametres[ATTAQUEPIECEIMMOBILEV11(i)]       * (defenseur != NULL && !defenseur->bouger && !defenseur->devoile);
    eval += intelligence.parametres[ATTAQUEPIECEPLUFAIBLEV11(i)]      * (defenseur != NULL && defenseur->devoile && ((defenseur->val < i)
                                                                                                                    || ( defenseur->val == NUMERO_BOMBE     && attaquant->val == 3 ) 
                                                                                                                    || ( defenseur->val == 10               && attaquant->val == 1 ))
                                                                                                                   );

    eval += intelligence.parametres[AVANCERV11(i)]                    * (attaquant->equipe == 0 && c.xd < c.xf)
                                                                    || (attaquant->equipe == 1 && c.xd > c.xf) ;

    eval += intelligence.parametres[MOUVEMENTCOTEV11(i)]                 * (attaquant->equipe == 0 && c.yd > c.yf)
                                                                    || (attaquant->equipe == 1 && c.yd < c.yf) ;

    eval += intelligence.parametres[RECULERV11(i)]                    * (attaquant->equipe == 0 && c.xd > c.xf)
                                                                    || (attaquant->equipe == 1 && c.xd < c.xf) ;

    eval += intelligence.parametres[MOUVEMENTCOTEV11(i)]                 * (attaquant->equipe == 0 && c.yd < c.yf)
                                                                    || (attaquant->equipe == 1 && c.yd > c.yf) ;

    eval += intelligence.parametres[ATTAQUERPIECEBOUGERV11(i)]        * (defenseur != NULL && defenseur->bouger && !defenseur->devoile);

    eval += intelligence.parametres[PROTEGERCHEMINV11(i)]             * ( 2 < c.yf && c.yf < 5) && !( 2 < c.yd && c.yd < 5);
    eval += intelligence.parametres[DERRIERELACV11(i)]                * ( 2 < c.xf && c.xf < 5) && !( 2 < c.xd && c.xd < 5);
    eval += intelligence.parametres[ALEATOIREV11(i)]                * generer_valeur_aleatoire_0_1();
    return eval;
}

float evaluationV12(plateau* P, coup c, ia intelligence, int tour){
    float eval = 0;

    piece* attaquant = P->scene[c.xd][c.yd].pion;
    int i = attaquant->val;
    piece* defenseur = P->scene[c.xf][c.yf].pion;

    if (defenseur != NULL && defenseur->devoile && !((defenseur->val < i)
                                                || ( defenseur->val == NUMERO_BOMBE     && attaquant->val == 3 ) 
                                                || ( defenseur->val == 10               && attaquant->val == 1 ))
                                                )
        {return -100000;}

    eval += intelligence.parametres[PREMIERCOUPV12(i)]                * (tour<2);
    eval += intelligence.parametres[ATTAQUEPIECEIMMOBILEV12(i)]       * (defenseur != NULL && !defenseur->bouger && !defenseur->devoile);
    eval += intelligence.parametres[ATTAQUEPIECEPLUFAIBLEV12(i)]      * (defenseur != NULL && defenseur->devoile && ((defenseur->val < i)
                                                                                                                    || ( defenseur->val == NUMERO_BOMBE     && attaquant->val == 3 ) 
                                                                                                                    || ( defenseur->val == 10               && attaquant->val == 1 ))
                                                                                                                   );

    eval += intelligence.parametres[AVANCERV12(i)]                    * (attaquant->equipe == 0 && c.xd < c.xf)
                                                                    || (attaquant->equipe == 1 && c.xd > c.xf) ;

    eval += intelligence.parametres[MOUVEMENTDV12(i)]                 * (attaquant->equipe == 0 && c.yd > c.yf)
                                                                    || (attaquant->equipe == 1 && c.yd < c.yf) ;

    eval += intelligence.parametres[RECULERV12(i)]                    * (attaquant->equipe == 0 && c.xd > c.xf)
                                                                    || (attaquant->equipe == 1 && c.xd < c.xf) ;

    eval += intelligence.parametres[MOUVEMENTGV12(i)]                 * (attaquant->equipe == 0 && c.yd < c.yf)
                                                                    || (attaquant->equipe == 1 && c.yd > c.yf) ;

    eval += intelligence.parametres[ATTAQUERPIECEBOUGERV12(i)]        * (defenseur != NULL && defenseur->bouger && !defenseur->devoile);

    eval += intelligence.parametres[PROTEGERCHEMINV12(i)]             * ( 2 < c.yf && c.yf < 5) && !( 2 < c.yd && c.yd < 5);
    eval += intelligence.parametres[DERRIERELACV12(i)]                * ( 2 < c.xf && c.xf < 5) && !( 2 < c.xd && c.xd < 5);
    return eval;
}

float evaluation(plateau* P, piece** equipe0, piece** equipe1, ia intelligence, int maximisateur, int tour) {
    switch ( intelligence.version) {
        case 1 : return evaluationV1(P, equipe0, equipe1, intelligence, maximisateur, tour); break;
        case 2 : return evaluationV2(P, equipe0, equipe1, intelligence, maximisateur, tour); break;
        case 3 : return evaluationV3(P, equipe0, equipe1, intelligence, maximisateur, tour); break;
        case 4 : return evaluationV4(P, equipe0, equipe1, intelligence, maximisateur, tour); break;
        default : printf(" VERSION IA INCONNU : %d \n", intelligence.version); exit(1);
    }
}

float evaluationDeBoer(plateau* P, coup c, ia intelligence, int tour){
    switch (intelligence.version)
    {
        case 10 : return evaluationV10(P, c, intelligence, tour); break; // classique
        case 11 : return evaluationV11(P, c, intelligence, tour); break; // droite = gauche
        case 12 : return evaluationV12(P, c, intelligence, tour); break; // sans aleatoire
        default : printf(" VERSION IA INCONNU : %d \n", intelligence.version); exit(1);
    }
}

