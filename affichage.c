#include "affichage.h"

void afficher_pion(piece *jeton) { // Affiche toutes les information lié a un pion et la case qui le contient
    if (jeton == NULL){
        printf("NULL \n");
    } else {
        printf("affichage pion : \n");
        printf("\t equipe : \t %d \n", jeton->equipe);
        printf("\t val : \t\t %d \n", jeton->val);
        printf("\t devoile : \t %d \n", jeton->devoile);
        printf("\t bouger : \t %d \n", jeton->bouger);
        
        if (jeton->cell != NULL) {
            printf("\t case : \t (x : %d : y : %d )\n", jeton->cell->x, jeton->cell->y);
        } else {
            printf("\t case : \t NULL \n");
        }
    }
}

void afficher_equipe(piece* equipe[NBPIECES]) {
    for (int i=0; i<NBPIECES; i++) {
        printf("--------------------------------- %d *---------------------------\n", i);
        afficher_pion(equipe[i]);
    }
} 

void afficher_case(cellule *cell) { // Affiche toutes les données lié a une cellule eet l’éventuelle pion qu'elle contient
    if (cell == NULL){
        printf("NULL \n");
    } else {
        printf("affichage cellule : \n");
        printf("\t x : \t\t %d \n", cell->x);
        printf("\t y : \t\t %d \n", cell->y);
        if (cell->pion != NULL) {
            printf("\t pion : \t (val : %d : equipe : %d )\n", cell->pion->val, cell->pion->equipe);
        } else {
            printf("\t pion : \t NULL \n");
        }
    }
}

void afficher_coup(coup c) {
    printf(" xd : %d - yd : %d - xf : %d - yf : %d \n", c.xd, c.yd, c.xf, c.yf );
}

void afficher_coupMM(coupMM cmm ) {
    printf("val : %f", cmm.val);
    afficher_coup(cmm.c);
}

void afficher_plateau(const plateau * jeu) { // Affiche le plateau complètement dévoilé
    printf("\033[0m-------------------------"); if (AFFICHAGECOORDONNEES){printf("------------------------------------");} if (AFFICHAGEDEVOILE){printf("------------------------");}; if (AFFICHAGEBOUGER){printf("------------------------"); printf("\n");}
    for (int i = 0 ; i < NBLIGNES ; i++){
        for (int j = 0 ; j < NBCOLONNES ; j++){
            printf("\033[0m|"); // Case Vide
            if (jeu->scene[i][j].pion == NULL){
                if (AFFICHAGECOORDONNEES){printf("(%d/%d) ", i, j);}
                printf("   ");
                if (AFFICHAGEDEVOILE){printf("    ");}
                if (AFFICHAGEBOUGER){printf("    ");}
                continue;
            }
            //printf("\n %d", jeu->scene[i][j].pion->equipe);
            else if (jeu->scene[i][j].pion->equipe == 0){printf("\033[34m");} // bleu
            else if (jeu->scene[i][j].pion->equipe == 1){printf("\033[31m");}//rouge
            else {printf("\033[42m");}//vert d'eau
            if (AFFICHAGECOORDONNEES && jeu->scene[i][j].pion->cell != NULL) {printf("(%d/%d) ", jeu->scene[i][j].pion->cell->x, jeu->scene[i][j].pion->cell->y);};// a virer
            switch (jeu->scene[i][j].pion->val)
            {
                case NUMERO_DRAPEAU  : printf(" D "); break; // Case Drapeau
                case 1  : printf(" 1 "); break;
                case 2  : printf(" 2 "); break;
                case 3  : printf(" 3 "); break;
                case 4  : printf(" 4 "); break;
                case 5  : printf(" 5 "); break;
                case 6  : printf(" 6 "); break;
                case 7  : printf(" 7 "); break;
                case 8  : printf(" 8 "); break;
                case 9  : printf(" 9 "); break;
                case 10 : printf("10 "); break;
                case NUMERO_BOMBE : printf(" B "); if (jeu->scene[i][j].pion->bouger){printf("n");} break;
                case NUMERO_LAC : printf(" X "); break;
                default : afficher_pion(jeu->scene[i][j].pion);printf("Piece inconnu \n "); exit(2); break; // ERREUR
            }
            if (AFFICHAGEDEVOILE){
                if (jeu->scene[i][j].pion->devoile) {printf(" -v ");} //visible
                else {printf(" -c ");} //caché
            }
            if (AFFICHAGEBOUGER){
                if (jeu->scene[i][j].pion->bouger) {printf(" -b ");} //bouge
                else {printf(" -i ");}//immobile
            }

        }
        printf("\033[0m|\n");
    }
    printf("\033[0m-------------------------"); if (AFFICHAGECOORDONNEES){printf("------------------------------------");} if (AFFICHAGEDEVOILE){printf("------------------------");}; if (AFFICHAGEBOUGER){printf("------------------------"); printf("\n");}
    
}

void afficher_plateau_version_joueur(const plateau * jeu, int tour) { // Affiche le plateau partiellement dévoilé
    printf("\033[0m-------------------------"); if (AFFICHAGECOORDONNEES){printf("------------------------------------");} printf("\n");
    for (int i = 0 ; i < NBLIGNES ; i++){
        for (int j = 0 ; j < NBCOLONNES ; j++){
            printf("\033[0m|");
            if (jeu->scene[i][j].pion == NULL) // Case Vide
                {if (AFFICHAGECOORDONNEES){printf("(%d/%d) ", i, j);}; printf("   "); continue;} 
            //printf("\n %d", jeu->scene[i][j].pion->equipe);
            // réglage de la couleur
            else if (jeu->scene[i][j].pion->equipe == 0){printf("\033[34m");} // bleu
            else if (jeu->scene[i][j].pion->equipe == 1){printf("\033[31m");}//rouge
            else {printf("\033[42m");}//vert d'eau

            if (AFFICHAGECOORDONNEES && jeu->scene[i][j].pion->cell != NULL) {printf("(%d/%d) ", jeu->scene[i][j].pion->cell->x, jeu->scene[i][j].pion->cell->y);};              
            if (jeu->scene[i][j].pion->equipe == (tour+1) % 2 && !jeu->scene[i][j].pion->devoile)// Case caché
                {printf(" I "); continue;} 
            switch (jeu->scene[i][j].pion->val)
            {
                case NUMERO_DRAPEAU  : printf(" D "); break; // Case Drapeau
                case 1  : printf(" 1 "); break;
                case 2  : printf(" 2 "); break;
                case 3  : printf(" 3 "); break;
                case 4  : printf(" 4 "); break;
                case 5  : printf(" 5 "); break;
                case 6  : printf(" 6 "); break;
                case 7  : printf(" 7 "); break;
                case 8  : printf(" 8 "); break;
                case 9  : printf(" 9 "); break;
                case 10 : printf("10 "); break;
                case NUMERO_BOMBE : printf(" B "); break;
                case NUMERO_LAC : printf(" X "); break;
                default : printf("Piece inconnu"); exit(2); break; // ERREUR
            }
        }
        printf("\033[0m|\n");
    }
    printf("\033[0m-------------------------"); if (AFFICHAGECOORDONNEES){printf("------------------------------------");} printf("\n");
}

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
    printf("IA : \n");
    printf("\t version : \t %d \n", ia_a_afficher.version);
    printf("\t parametres : \t [");
    for (int i = 0; i < NBPARAMETRES; i++) {
        printf("%d %f\n", i, ia_a_afficher.parametres[i]);
    }
    printf("]\n");
}

void afficher_tableau_ia(ia* tableau, int taille) {// affiche un tableau d ia en console
    printf("[\n");
    for (int i = 0; i < taille; i++) {
        afficher_ia(tableau[i]);
        printf("\n\n");
    }
    printf("]\n");
}