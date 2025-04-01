#include "stratego.h" 

// Variables Globales
bool victoire = false;
int gagnant = 2;

void copie_tableau_piece(piece source[], piece destination[], int taille) { // copie un tableau de piece dans un tableau de piece
    for (int i = 0; i < taille; i++) {
        destination[i] = source[i];
    }
}

void initialisation_plateau(plateau *jeu) { // Créer un plateau vide
    // Initialise le plateau vide
    for (int i = 0 ; i < NBLIGNES ; i++){
        for (int j = 0 ; j < NBCOLONNES ; j++){
            jeu->scene[i][j].pion = NULL;
            jeu->scene[i][j].x = i;
            jeu->scene[i][j].y = j;
        }
    }
    initialisation_lac(jeu);// ajoute le lac
}

void preplacement(plateau *jeu, int i, piece *equipe_joueur[NBPIECES]) {
    piece tab[] = TPIECES(i);
    int j = 0;
    piece placement[18];

    if (i == 0) {
        piece temp[] = { tab[14], tab[5], tab[16], tab[17], tab[6], tab[11], tab[1], tab[12], tab[4], tab[13], tab[7], tab[2], tab[0], tab[3], tab[8], tab[15], tab[9], tab[10] };
        for (int idx = 0; idx < 18; idx++) {
            placement[idx] = temp[idx];
        }
        j = 6 * NBLIGNES;
    } else {
        piece temp[] = { tab[8], tab[1], tab[0], tab[2], tab[11], tab[9], tab[12], tab[14], tab[3], tab[4], tab[5], tab[15], tab[6], tab[13], tab[17], tab[16], tab[10], tab[7] };
        for (int idx = 0; idx < 18; idx++) {
            placement[idx] = temp[idx];
        }
        j = 0;
    }

    for (int k = 0; k < 18; k++) {
        piece *jeton = malloc(sizeof(piece));
        if (jeton == NULL) {
            exit(1);
        }
        *jeton = placement[k];
        equipe_joueur[k] = jeton;
    }

    afficher_plateau(jeu);
}


void placement_piece( plateau *jeu, piece *jeton, int xl, int yl, int i) { 
    //PLACE UNE PIECE AU HASARD selon les conditions xl, yl, et l'équipe i
    int xd = generer_entier_aleatoire(0, xl-1);
    int yd = generer_entier_aleatoire(0, yl-1);
    while ( jeu->scene[i * NBLIGNES + (1 - 2 * i) * xd + (-1) * i][yd].pion != NULL ) {
        xd = generer_entier_aleatoire(0, xl-1);
        yd = generer_entier_aleatoire(0, yl-1);
    };
    jeu->scene[i * NBLIGNES + (1 - 2 * i) * xd + (-1) * i][yd].pion = jeton;
    //afficher_case(&(jeu->scene[i * NBLIGNES + (1 - 2 * i) * xd + (-1) * i][yd]));
    jeton->cell = &(jeu->scene[i * NBLIGNES + (1 - 2 * i) * xd + (-1) * i][yd]);
    //afficher_pion(jeton);
}

void pseudo_alea(plateau *jeu, int i,piece *equipe_joueur[NBPIECES]) { // place les pieces de manière pseudo aleatoire
    // PLACEMENT PIECES de l'équipe i ( 0-1 )
    piece tab0[] = TPIECES(i);
    for (int j=0; j<NBPIECES; j++) {
        piece *jeton = malloc(sizeof(piece)); // allocation sécurisé
        if (jeton == NULL) {
            printf("Erreur d'allocation mémoire\n");
            exit(1);
        } 
        *jeton = tab0[j];
        //printf("val : %d Equipe  %d : \n" ,jeton->val, jeton->equipe);
        if (j == 0) {                   // Place le drapeau
            placement_piece(jeu, jeton, 1, 6, i);
        } else if ( j < 4) {            // Place le 1 ainsi que les 3 bombes
            placement_piece(jeu, jeton, 2, 6, i);
        } else {                        // Place le reste des pièces
            placement_piece(jeu, jeton, 3, 6, i);
        };
        equipe_joueur[j] = jeton;
        //printf("val : %d Equipe  %d : \n" ,jeton->val, jeton->equipe);
        //afficher_plateau(jeu);
    }   
    // for (int i = 0; i < NBPIECES ; i++){afficher_pion(equipe_joueur[i]);}
}

void initialisation_lac(plateau *jeu){ // Initialisation les cases du lac 
    piece *lac0 = malloc(sizeof(piece));
    piece *lac1 = malloc(sizeof(piece));
    piece *lac2 = malloc(sizeof(piece));
    piece *lac3 = malloc(sizeof(piece));
    if (lac0 == NULL || lac1 == NULL ||lac2 == NULL ||lac3 == NULL) {
        printf("Erreur d'allocation mémoire\n");
        exit(1);
    } 
    piece l = PIECES(NUMERO_LAC, 2);
    *lac0 = l;
    lac0->cell = &(jeu->scene[4][2]);
    jeu->scene[4][2].pion = lac0;

    *lac1 = l;
    lac1->cell = &(jeu->scene[3][2]);
    jeu->scene[3][2].pion = lac1;

    *lac2 = l;
    lac2->cell = &(jeu->scene[3][3]);
    jeu->scene[3][3].pion = lac2;

    *lac3 = l;
    lac3->cell = &(jeu->scene[4][3]);
    jeu->scene[4][3].pion = lac3;
};

bool hors_plateau(int x, int y) { // Teste si la case appartient au plateau
    if ( (x > NBLIGNES - 1) || (x < 0) || (y < 0) || (y > NBCOLONNES - 1) ) {
        return true;
    } else {
        return false;
    }
};

bool verifie_mouv2(plateau * P, coup c, int tour) {
    // Vérifie si le mouvement du 2 est valide ou non

    piece p = *P->scene[c.xd][c.yd].pion;
    bool valide = true;
    int signe;

    if (c.xd - c.xf == 0 ) {        // Si le 2 se déplace selon une ligne
        signe = (c.yf - c.yd) / abs( c.yf - c.yd);
        for ( int i = 1; i < signe * (c.yf - c.yd); i ++) {
            if (P->scene[c.xf][c.yd + signe * i].pion != NULL && P->scene[c.xf][c.yd + signe * i].pion->equipe == p.equipe) { // Teste si la case parcourue n'est pas une case alliée
                valide = false;
            };
        };
    } else if ( c.yd - c.yf == 0 ) { // Si le 2 se déplace selon une colonne
        signe = (c.xf - c.xd) / abs( c.xf - c.xd);
        for ( int i = 1; i < signe * (c.xf - c.xd); i ++) {
            if (P->scene[c.xd + signe * i][c.yd].pion != NULL && P->scene[c.xd + signe * i][c.yd].pion->equipe == p.equipe) {
                valide = false;
            };
        };
    } else {                    // Autre cas
        valide = false;
    };

    return valide;

};


bool mouvement_valide(plateau * jeu, coup c, int tour, bool factice) { //teste si le mouvement est valide
    // xd, yd -> case départ,   xf, yf -> case finale, tour -> équipe qui joue
        
    if ( (hors_plateau(c.xf, c.yf)) || (hors_plateau(c.xd, c.yd))) {           // Teste si la case est dans le plateau, ou la case choisie possède un pion
        return false;       
    };

    piece *defenseur = jeu->scene[c.xf][c.yf].pion;
    piece *attaquant = jeu->scene[c.xd][c.yd].pion;


    if (attaquant == NULL) {
        return false;
    };
    
    //printf("defenseur : "); afficher_pion(defenseur);
    //printf("attaquant : "); afficher_pion(attaquant);

    //Teste si le mouvement est valide
    if (    !factice && (
            (attaquant->val == NUMERO_DRAPEAU) ||                            // c'est le drapeau
            (attaquant->val == NUMERO_BOMBE) ||                           // c'est une bombe
            (attaquant->equipe != tour) ||                      // l'attaquant n'apparient pas a l'equipe du joueur
            (defenseur != NULL && defenseur->equipe == tour ) ||    // il y a un pion de la même equipe a l'arrivé
            (defenseur != NULL && defenseur->val == NUMERO_LAC) ||          // case interdite    
            (((abs(c.xd-c.xf) > 1) || (abs(c.yd-c.yf) > 1)) && attaquant->val != 2) || // mouvement de plus d'une case sans 2
            (c.xd != c.xf && c.yd != c.yf)  ||                        // ni sur la même ligne ni sur la même colonne
            (attaquant->val == 2 && !verifie_mouv2(jeu, c, tour))) // mouvement d'un 2

        ) {               
        return false;
    } else if ( factice &&
            (attaquant->equipe != tour) ||                      // l'attaquant n'apparient pas a l'equipe du joueur
            (defenseur != NULL && defenseur->equipe == tour ) ||    // il y a un pion de la même equipe a l'arrivé
            (defenseur != NULL && defenseur->val == NUMERO_LAC) ||          // case interdite    
            (((abs(c.xd-c.xf) > 1) || (abs(c.yd-c.yf) > 1)) && attaquant->val != 2) || // mouvement de plus d'une case sans 2
            (c.xd != c.xf && c.yd != c.yf)  ||                        // ni sur la même ligne ni sur la même colonne
            (attaquant->val == 2 && !verifie_mouv2(jeu, c, tour)) // mouvement d'un 2
    ) {
        return false;        
    }else {
        return true;
    }
};

bool action(plateau * jeu, coup c, int tour, bool factice) { // fait bouger une piece (xd, yd) -> (xf, yf) et gère l’éventuelle combat
    // Si renvoie true, il y a eu un combat sinon il n'y en a pas eu
    piece *attaquant = jeu->scene[c.xd][c.yd].pion;
    piece *defenseur = jeu->scene[c.xf][c.yf].pion;

    //afficher_plateau(jeu);
    attaquant->bouger = true;
    
    if(!mouvement_valide(jeu,c,tour, factice)){
        printf("!!!!!!!!!!!!!!!!!!!!!! coup illégal !!!!!!!!!!!!!!!!!!!!!");
        //afficher_plateau(jeu);
        //afficher_coup(c);
        printf("tour %d \n" , tour);
        printf("!!!!!!!!!!!!!!!!!!!!!! coup illégal !!!!!!!!!!!!!!!!!!!!!");
        exit(1);
    }
    
    if (defenseur == NULL) {                             // CAS D'UN DÉPLACEMENT VERS CASE VIDE
        attaquant->cell = &jeu->scene[c.xf][c.yf];                   // déplace le pion 
        jeu->scene[c.xf][c.yf].pion = attaquant;                    
        jeu->scene[c.xd][c.yd].pion = NULL;                      // Vide la case d'avant
        // Vérifie qu'il n e s'agit pas d'un deux qui a bouger de plus de deux cases
        // le mouvement est valide (précondition) 
        if (abs(c.xd - c.xf) > 1 || abs(c.yd - c.yf) > 1 )
        {
            if (attaquant->val != 2){printf("valeur incohérente du pion"); exit(1);}
            attaquant->devoile = true;
        }
        return false;
                                                            // CAS OU L'ATTAQUANT GAGNE
    } else {
        if ( defenseur->val < attaquant->val ||                         // cas de base
                    (defenseur->val == 10 && attaquant->val == 1) ||    // 1 attaque le 10
                    (defenseur->val == NUMERO_BOMBE && attaquant->val == 3)       // 3 attaque bombe
        ){                 
            if (defenseur->val == NUMERO_DRAPEAU && !factice) {                              // TEST SI VICTOIRE PAR PRISE DU DRAPEAU
                victoire = true;
                //afficher_coup(c);
                //printf("Drapeau conquis \n");
                gagnant = attaquant->equipe;
            }
            defenseur->cell = NULL;                                     // On tue le perdant
            jeu->scene[c.xd][c.yd].pion = NULL;                             // On enlève le mort
            attaquant->cell = &jeu->scene[c.xf][c.yf];                      // On le remplace par le gagnant
            jeu->scene[c.xf][c.yf].pion = attaquant;                        
            attaquant->devoile = true;                                  // On dévoile le gagnant
            
        } else if ( defenseur->val > attaquant->val) {          // CAS OU LE DEFENSEUR GAGNE
            jeu->scene[c.xd][c.yd].pion->cell = NULL;                       // On tue le perdant
            jeu->scene[c.xd][c.yd].pion = NULL;                             // On vide sa case
            defenseur->devoile = true;                   // on devoile le gagnant
        } else {                                                  // CAS D'UN DÉPLACEMENT VERS CASE ÉGALE
            jeu->scene[c.xd][c.yd].pion->cell = NULL;                       // On tue les pions
            jeu->scene[c.xf][c.yf].pion->cell = NULL;
            jeu->scene[c.xd][c.yd].pion = NULL;                             // On vide les cases
            jeu->scene[c.xf][c.yf].pion = NULL;
        }
        return true;
    }

    //afficher_plateau(jeu);
    //printf("\n\n_\n\n");
};

bool coupinverse( coup coup1, coup coup2) {
    return ( ( ( coup1.xd == coup2.xf ) && ( coup1.xf == coup2.xd ) ) && ( ( coup1.yd == coup2.yf ) && ( coup1.yf == coup2.yd ) )  ); 
}

bool coupegal( coup coup1, coup coup2) {
    return ( ( ( coup1.xd == coup2.xd ) && ( coup1.xf == coup2.xf ) ) && ( ( coup1.yf == coup2.yf ) && ( coup1.yd == coup2.yd ) )  );
}

bool repetition( tableau_dyn* coups_joues, bool actioneffectuee) {
    if ( actioneffectuee ) {
        return false;
    } else if ( coups_joues->nbelt > 7 ) {
        return (  coupinverse(coups_joues->tab[0], coups_joues->tab[2])
        &&   coupinverse(coups_joues->tab[4], coups_joues->tab[6])
        &&   coupinverse(coups_joues->tab[1], coups_joues->tab[3]) 
        &&   coupinverse(coups_joues->tab[5], coups_joues->tab[7])
        &&   coupegal(coups_joues->tab[0], coups_joues->tab[4])
        &&   coupegal(coups_joues->tab[2], coups_joues->tab[6])
        &&   coupegal(coups_joues->tab[1], coups_joues->tab[5])
        &&   coupegal(coups_joues->tab[3], coups_joues->tab[7]));
    } else {
        return false;
    }
}


void coup_case(plateau* P, piece p, tableau_dyn* t, int tour) { 
    // La première partie teste les coups pour un 2 pour une distance > 1 dans toutes les directions
    // La seconde partie teste les coups à une distance de 1
    if (p.cell == NULL) {return;}
    int i = 1;
    coup c = {
        .xd = p.cell->x,
        .yd = p.cell->y,
        .xf = -1,
        .yf = -1 };
    if (p.cell != NULL &&  p.val == 2 ) {
        c.xf = c.xd + 1;
        c.yf = c.yd;
        while ( mouvement_valide(P, c, tour%2, false ) && ( P->scene[p.cell->x + i - 1][p.cell->y].pion == NULL || P->scene[p.cell->x + i - 1][p.cell->y].pion->equipe != (1 - p.equipe) )) {
            // Teste si le mouvement est possible et que la case de départ n'est pas une case ennemie ( Afin de garder la dernière case possible )
            tableau_dyn_ajoute(t, c);
            i += 1;
            c.xf = p.cell->x + i;
            c.yf = p.cell->y;
        }; i = 1;
        c.xf = p.cell->x - 1;
        c.yf = p.cell->y;
        while ( mouvement_valide(P, c, tour%2, false ) && ( P->scene[p.cell->x - i + 1][p.cell->y].pion == NULL || P->scene[p.cell->x - i + 1][p.cell->y].pion->equipe != (1 - p.equipe) )) {
            tableau_dyn_ajoute(t, c);
            i += 1;
            c.xf = p.cell->x - i;
            c.yf = p.cell->y;
        }; i = 1;
        c.xf = p.cell->x;
        c.yf = p.cell->y + 1;
        while ( mouvement_valide(P, c, tour%2, false ) && ( P->scene[p.cell->x][p.cell->y + i - 1].pion == NULL || P->scene[p.cell->x][p.cell->y + i - 1].pion->equipe != (1 - p.equipe) ) ) {
            tableau_dyn_ajoute(t, c);
            i += 1;
            c.xf = p.cell->x;
            c.yf = p.cell->y + i;
        }; i = 1;
        c.xf = p.cell->x;
        c.yf = p.cell->y - 1;
        while ( mouvement_valide(P, c, tour%2, false ) && ( P->scene[p.cell->x][p.cell->y - i + 1].pion == NULL || P->scene[p.cell->x][p.cell->y - i + 1].pion->equipe != (1 - p.equipe) ) ) {
            tableau_dyn_ajoute(t, c);
            i += 1;
            c.xf = p.cell->x;
            c.yf = p.cell->y - i;
        }
    } else {
        c.xf = p.cell->x + 1;
        c.yf = p.cell->y;
        if (p.cell != NULL && mouvement_valide(P, c, tour%2, false )) {  // Teste le mouvement en bas
                tableau_dyn_ajoute(t, c);
            };

            c.xf = p.cell->x - 1;
            c.yf = p.cell->y;
            if (p.cell != NULL && mouvement_valide(P, c, tour%2, false)) { // Teste le mouvement en haut
                tableau_dyn_ajoute(t, c);
            };

            c.xf = p.cell->x;
            c.yf = p.cell->y + 1;
            if (p.cell != NULL && mouvement_valide(P, c, tour%2, false)) { // Teste le mouvement à droite
                tableau_dyn_ajoute(t, c);
            };

            c.xf = p.cell->x;
            c.yf = p.cell->y - 1;
            if (p.cell != NULL && mouvement_valide(P, c, tour%2, false )) { // Teste le mouvement à gauche
                tableau_dyn_ajoute(t, c);
            };
    }
};

void liste_coup_possible(plateau P, tableau_dyn * l_coups, piece* equipe0[18], piece* equipe1[18],int tour){
        //Création de la liste des coups possibles 
        tableau_dyn_vider(l_coups);
        for (int i=0; i<18; i++) {
            if ( tour%2 == 0 && equipe0[i] != NULL ) {
                coup_case(&P, *equipe0[i], l_coups, tour);
            } else if ( tour%2 == 1 && equipe1[i] != NULL ) {
                coup_case(&P, *equipe1[i], l_coups, tour);
            }
        };
}

void libere_plateau(plateau *jeu){ // libere la mémoire des pieces du tableau et le plateau lui même
    for (int i = 0; i < NBLIGNES; i++) {
        for (int j = 0; j < NBCOLONNES; j++) {
            if (jeu->scene[i][j].pion != NULL) {
                free(jeu->scene[i][j].pion);                            // Libère la mémoire de la pièce    
            }
        }
    }
}

void vider_buffer() { // vide la mémoire du buffer
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}// Lire les caractères du buffer jusqu'à la fin de la ligne ou la fin du fichier
}

coup mouvement_joueur(plateau *P, int equipe, int tour) { // Récupère le mouvement du joueur
    coup c ;
    do {
        afficher_plateau_version_joueur(P, tour);
        afficher_plateau(P);

        //changement de couleur
        if (equipe % 2 == 0) { printf("\033[34m");} // bleu
        else {printf("\033[31m");}; // rouge

        printf("Quelle case de départ (x/y) : ");
        // Saisie de la case de départ (x, y)
        while (scanf("%d/%d", &c.xd, &c.yd) != 2){
            vider_buffer();
            printf("Quelle case de départ (x/y) : ");
        }

        // Saisie de la case d'arrivée (x, y)
        do {
            vider_buffer();
            printf("Quelle case d'arrivée (x/y) : ");
        } while (scanf("%d/%d", &c.xf, &c.yf) != 2);
    } while (!mouvement_valide(P, c, tour%2, false));

    printf("\033[0m");

    return c;
}

coup mouvement_aleatoire(plateau P, piece* equipe0[18], piece* equipe1[18], int tour) { // Récupère un mouvement aleatoire
    tableau_dyn liste_coup = tableau_dyn_initialisation(1);
    liste_coup_possible(P, &liste_coup, equipe0, equipe1, tour);
    int n = generer_entier_aleatoire(0, liste_coup.nbelt - 1);
    coup retour = liste_coup.tab[n];
    tableau_dyn_supp(&liste_coup);
    return retour;
} 

int jouer() { // permet de jouer une partie renvoie 0 si le premier joueur gagne 1 si le second joueur gagne

    struct timeval start;
    gettimeofday(&start, NULL);

    ia ia_test = lire_ia_dans_fichier(0, NOM_DOSSIER_IA_SAUVEGARDE, INDICATIF_SAUVEGARDE);
    int graine =  start.tv_usec +time(NULL);//1711915685;//s  // 1711419624; //
    printf(" Graine : %d", graine);
    // printf("%d\n", graine);
    srand(graine); // Initialise le générateur de nombres aléatoires avec une graine basée sur l'horloge système

    coup c;
    coupMM cmm;
    plateau P;
    int tour = 0;

    initialisation_plateau(&P);             // Initialise le plateau vide

    tableau_dyn l_coups = tableau_dyn_initialisation(1);    // Initialisation de la liste des coups possibles

    piece **equipe0 = malloc(sizeof(piece*) * NBPIECES);
    if (equipe0 == NULL) {
        printf("Erreur d'allocation mémoire\n");
        exit(1);
    }
    pseudo_alea(&P, 0, equipe0); // Place équipe 0
    
                        
    piece **equipe1 = malloc(sizeof(piece*) * NBPIECES);  
    if (equipe1 == NULL) {
        printf("Erreur d'allocation mémoire\n");
        exit(1);
    }
    pseudo_alea(&P, 1, equipe1);// Place équipe 1   
    int e = 12;

/*
    for (int i=0; i<NBPARAMETRES; i++) {
        parametres[i] = generer_valeur_aleatoire_0_1();
    }

    printf(" Evaluation - %d -\n", evaluation( &P, equipe0, equipe1, , tour));
*/
    //for (int i = 0; i < NBPIECES ; i++){afficher_pion(equipe0[i]);}
    //afficher_plateau(&P);
    while( !victoire && tour<NBCOUPMAX) {
        
        liste_coup_possible(P, &l_coups, equipe0, equipe1, tour%2);
        if (l_coups.nbelt == 0){
            victoire = true;
            gagnant = (tour+1) % 2;
            printf("plus de coup \n");
            break;
        }
        //affiche_tableau_dyn(&l_coups); 

        // fait jouer
        if (tour%2 == 0){
            if (TYPE_JOUEUR_0 == TYPE_HUMAIN)
                {action(&P, mouvement_joueur(&P, tour%2, tour), tour%2, false);}         // Réalise le mouvement
            else if (TYPE_JOUEUR_0 == TYPE_ALEATOIRE){
                if (ia_test.version >= 10 && ia_test.version <=19){
                    cmm = MinMaxDeBoer(&P, ia_test, tour, equipe0, equipe1);
                }

                else {
                    cmm = MinMax(&P, equipe0, equipe1, ia_test, 0 , tour, PROFONDEUR_MIN_MAX); 
                }
                action(&P, c, tour%2, false);
            }
            else if (TYPE_JOUEUR_0 == TYPE_IA_MM) {
                printf(" TOUR : %d \n", tour);
                if (ia_test.version >= 10 && ia_test.version <=19){
                    cmm = MinMaxDeBoer(&P, ia_test, tour, equipe0, equipe1);
                }

                else {
                    cmm = MinMax(&P, equipe0, equipe1, ia_test, 0 , tour, PROFONDEUR_MIN_MAX); 
                }
                //afficher_coupMM(cmm);
                action(&P, cmm.c, tour%2, false);
                //if ( tour < 10 ) { afficher_plateau(&P);}
            }
            else {printf("Type de joueur inconnu"); exit(3); }                                                  // Incrémente le nombre tour
        }
        else {
            if (TYPE_JOUEUR_1 == TYPE_HUMAIN)
                {action(&P, mouvement_joueur(&P, tour%2, tour), tour%2, false);}         // Réalise le mouvement
            else if (TYPE_JOUEUR_1 == TYPE_ALEATOIRE) {
                coup c = mouvement_aleatoire(P, equipe0, equipe1, tour%2); 
                action(&P, c, tour%2, false);
            }
            else if (TYPE_JOUEUR_1 == TYPE_IA_MM) {
                //printf(" TOUR : %d \n ", tour);
                coupMM cmm = MinMax(&P, equipe0, equipe1, ia_test, 1 , tour, PROFONDEUR_MIN_MAX); 
                //afficher_coupMM(cmm);
                action(&P, cmm.c, tour%2, false);
            }
            else {printf("Type de joueur inconnu \n "); exit(3); }    
        }    

        if ( true ) {
            //affiche_tableau_dyn(&l_coups);
            //afficher_plateau(&P);
        }

        tour += 1;
        
        //printf("tour : %d \n\n", tour);                                               // Incrémente le nombre tour
        if ( false ) { afficher_plateau(&P);}
    };
    if(tour == NBCOUPMAX){printf("nb tour epuisé");};
    //afficher_plateau(&P);
    //printf("tour %d eval : %lf", tour, evaluation(&P, equipe0, equipe1,ia_test,tour));

    for (int i = 0 ; i < NBPIECES; i++){
        if (equipe0[i] != NULL && equipe0[i]->cell == NULL){free(equipe0[i]);}
        if (equipe1[i] != NULL && equipe1[i]->cell == NULL){free(equipe1[i]);}
    }
    free(equipe0);
    free(equipe1);
    printf(" Le joueur %d a gagné ! graine : %d\n", gagnant, graine);
    printf(" Nombre de coups : %d", tour);
    tableau_dyn_supp(&l_coups);
    libere_plateau(&P);                      // Libère le plateau

    printf(" Graine : %d", graine);

    return gagnant;
}

int jouer_ia_contre_ia(ia ia1, ia ia2, int * nbtour) { // permet de jouer une partie renvoie 0 si le premier joueur gagne 1 si le second joueur gagne
    victoire = false;
    gagnant = 2;

    coup c;
    coup ctmp;
    plateau P;
    int tour = 0;

    coupMM cmm;

    initialisation_plateau(&P);             // Initialise le plateau vide

    tableau_dyn l_coups = tableau_dyn_initialisation(1);    // Initialisation de la liste des coups possibles
    tableau_dyn coups_joues = tableau_dyn_initialisation(1);

    piece **equipe0 = malloc(sizeof(piece*) * NBPIECES);
    if (equipe0 == NULL) {
        printf("Erreur d'allocation mémoire\n");
        exit(1);
    }
    pseudo_alea(&P, 0, equipe0); // Place équipe 0
    
                        
    piece **equipe1 = malloc(sizeof(piece*) * NBPIECES);  
    if (equipe1 == NULL) {
        printf("Erreur d'allocation mémoire\n");
        exit(1);
    }
    pseudo_alea(&P, 1, equipe1);// Place équipe 1   
    int e = 12;

    /*
    for (int i=0; i<NBPARAMETRES; i++) {
        parametres[i] = generer_valeur_aleatoire_0_1();
    }

    printf(" Evaluation - %d -\n", evaluation( &P, equipe0, equipe1, , tour));
    */
    //for (int i = 0; i < NBPIECES ; i++){afficher_pion(equipe0[i]);}
    //afficher_plateau(&P);
    while( !victoire && tour<NBCOUPMAX) {
        
        liste_coup_possible(P, &l_coups, equipe0, equipe1, tour%2);
        if (l_coups.nbelt == 0){
            victoire = true;
            gagnant = (tour+1) % 2;
            //printf("plus de coup \n");
            break;
        }
        //affiche_tableau_dyn(&l_coups); 

        // fait jouer
        if (tour%2 == 0){
            if (ia1.version >= 10 && ia1.version <=19){
                cmm = MinMaxDeBoer(&P, ia1, tour, equipe0, equipe1);
            }

            else {
                cmm = MinMax(&P, equipe0, equipe1, ia1, 0 , tour, PROFONDEUR_MIN_MAX); 
            }
        }
        else {
            if (ia2.version >= 10 && ia2.version <=19){
                cmm = MinMaxDeBoer(&P, ia2, tour, equipe0, equipe1);
            }
            else{
                cmm = MinMax(&P, equipe0, equipe1, ia2, 1 , tour, PROFONDEUR_MIN_MAX); 
            }
            //afficher_coupMM(cmm);
        }    

        if ( coups_joues.nbelt < 8 ) {
            tableau_dyn_ajoute( &coups_joues, cmm.c);
        } else {
            //printf(" nombre : %d ", coups_joues.nbelt);
            for ( int i=0; i<7; i++) {
                coups_joues.tab[i] = coups_joues.tab[i+1];
            }
            coups_joues.tab[7] = cmm.c;
        }

        if ( repetition(&coups_joues, action(&P, cmm.c, tour%2, false)) ) {
            for (int i=0; i<1; i++) {
                //printf(" NULLE par répétition ! \n");
            };
            break;
        }

        if ( false ) {
            //affiche_tableau_dyn(&l_coups);
            afficher_plateau(&P);
        }

        tour += 1; 
        //printf("tour : %d \n\n", tour);                                               // Incrémente le nombre tour
        //if (tour %100 == 0) { afficher_plateau(&P);}
    };
    //afficher_plateau(&P);
    //if(tour == NBCOUPMAX){printf("nb tour epuisé");};
    //afficher_plateau(&P);
    //printf("tour %d eval : %lf", tour, evaluation(&P, equipe0, equipe1,ia_test,tour));
    for (int i = 0 ; i < NBPIECES; i++){
        if (equipe0[i] != NULL && equipe0[i]->cell == NULL){free(equipe0[i]);}
        if (equipe1[i] != NULL && equipe1[i]->cell == NULL){free(equipe1[i]);}
    }
    free(equipe0);
    free(equipe1);
    //printf(" Nombre de coups : %d \n gagnant : %d \n", tour, gagnant);
    tableau_dyn_supp(&l_coups);
    tableau_dyn_supp(&coups_joues);
    libere_plateau(&P);                      // Libère le plateau

    if (nbtour != NULL)
    {
        *nbtour += tour;
    }
    return gagnant;
}


int jouer_ia_contre_random(ia ia1) { // permet de jouer une partie renvoie 0 si le premier joueur gagne 1 si le second joueur gagne

    victoire = false;
    gagnant = 2;

    coup c;
    coup ctmp;
    plateau P;
    int tour = 0;

    coupMM cmm;

    initialisation_plateau(&P);             // Initialise le plateau vide

    tableau_dyn l_coups = tableau_dyn_initialisation(1);    // Initialisation de la liste des coups possibles
    tableau_dyn coups_joues = tableau_dyn_initialisation(1);

    piece **equipe0 = malloc(sizeof(piece*) * NBPIECES);
    if (equipe0 == NULL) {
        printf("Erreur d'allocation mémoire\n");
        exit(1);
    }
    pseudo_alea(&P, 0, equipe0); // Place équipe 0
    
                        
    piece **equipe1 = malloc(sizeof(piece*) * NBPIECES);  
    if (equipe1 == NULL) {
        printf("Erreur d'allocation mémoire\n");
        exit(1);
    }
    pseudo_alea(&P, 1, equipe1);// Place équipe 1   

/*
    for (int i=0; i<NBPARAMETRES; i++) {
        parametres[i] = generer_valeur_aleatoire_0_1();
    }

    printf(" Evaluation - %d -\n", evaluation( &P, equipe0, equipe1, , tour));
*/
    //for (int i = 0; i < NBPIECES ; i++){afficher_pion(equipe0[i]);}
    //afficher_plateau(&P);
    while( !victoire && tour<NBCOUPMAX) {
        
        liste_coup_possible(P, &l_coups, equipe0, equipe1, tour%2);
        if (l_coups.nbelt == 0){
            victoire = true;
            gagnant = (tour+1) % 2;
            //printf("plus de coup \n");
            break;
        }
        //affiche_tableau_dyn(&l_coups); 

        // fait jouer
        if (tour%2 == 0){
            if (ia1.version >= 10 && ia1.version <=19){
                cmm = MinMaxDeBoer(&P, ia1, tour, equipe0, equipe1);
            }

            else {
                cmm = MinMax(&P, equipe0, equipe1, ia1, 0 , tour, PROFONDEUR_MIN_MAX); 
            }
        }
        else {
            coup c = mouvement_aleatoire(P, equipe0, equipe1, tour%2); 
            cmm.c = c;
            cmm.val = 0.0;
        }    

        if ( coups_joues.nbelt < 8 ) {
            tableau_dyn_ajoute( &coups_joues, cmm.c);
        } else {
            //printf(" nombre : %d ", coups_joues.nbelt);
            for ( int i=0; i<7; i++) {
                coups_joues.tab[i] = coups_joues.tab[i+1];
            }
            coups_joues.tab[7] = cmm.c;
        }

        if ( repetition(&coups_joues, action(&P, cmm.c, tour%2, false)) ) {
            for (int i=0; i<1; i++) {
                //printf(" NULLE par répétition ! \n");
            };
            break;
        }

        if ( false ) {
            //affiche_tableau_dyn(&l_coups);
            afficher_plateau(&P);
        }

        tour += 1; 
        //printf("tour : %d \n\n", tour);                                               // Incrémente le nombre tour
        //if (tour %100 == 0) { afficher_plateau(&P);}
    };
    //afficher_plateau(&P);
    //if(tour == NBCOUPMAX){printf("nb tour epuisé");};
    //afficher_plateau(&P);
    //printf("tour %d eval : %lf", tour, evaluation(&P, equipe0, equipe1,ia_test,tour));
    for (int i = 0 ; i < NBPIECES; i++){
        if (equipe0[i] != NULL && equipe0[i]->cell == NULL){free(equipe0[i]);}
        if (equipe1[i] != NULL && equipe1[i]->cell == NULL){free(equipe1[i]);}
    }
    free(equipe0);
    free(equipe1);
    //printf(" Nombre de coups : %d \n gagnant : %d \n", tour, gagnant);
    tableau_dyn_supp(&l_coups);
    libere_plateau(&P);                      // Libère le plateau



    return gagnant;
}


//int main(){jouer();return 0;}