#include "comparer_historique_ia.h"

int main(){
    srand(time(NULL));

    int colonne[TAILLE_TABLEAU_NUMERO] = TABLEAU_NUMERO;
    int ligne[TAILLE_TABLEAU_NUMERO]   = TABLEAU_NUMERO;
    int resultats_match[TAILLE_TABLEAU_NUMERO][TAILLE_TABLEAU_NUMERO][3] = {0};

    // case 0 proportion d'égalité case 1 proportion de victoire
    double analyse_resultat[TAILLE_TABLEAU_NUMERO][TAILLE_TABLEAU_NUMERO][2] = {0}; 

    // charger les ia
    ia tab_ia[TAILLE_TABLEAU_NUMERO];
    for (int i = 0; i<TAILLE_TABLEAU_NUMERO; i++){
        tab_ia[i] = lire_ia_dans_fichier(colonne[i], NOM_DOSSIER_IA_HISTORIQUE, INDICATIF_HISTORIQUE);
    }

    for (int i = 0; i<TAILLE_TABLEAU_NUMERO ; i++){
        for (int j = 0; j<TAILLE_TABLEAU_NUMERO ; j++){
            printf("i : %d j : %d\n", i, j );
            for (int k = 0; k < NOMBRE_DE_MATCH; k++){
                resultats_match[i][j][jouer_ia_contre_ia(tab_ia[i], tab_ia[j], NULL)]++;
            }
            analyse_resultat[i][j][0] = (float)resultats_match[i][j][0]/(resultats_match[i][j][0]+resultats_match[i][j][1]);
            analyse_resultat[i][j][1] = (float)resultats_match[i][j][2]/NOMBRE_DE_MATCH;
        }
    }

    enregistrer_csv("formation/tableau", TAILLE_TABLEAU_NUMERO, ligne, TAILLE_TABLEAU_NUMERO, colonne, analyse_resultat);

    // printf("%d victoire de %d sur %d \n", resultat[0], NUMERO1, NUMERO2 );
    // printf("%d defaites de %d sur %d \n", resultat[1], NUMERO1, NUMERO2 );
    // printf("%d égalités de %d sur %d \n", resultat[2], NUMERO1, NUMERO2 );
}