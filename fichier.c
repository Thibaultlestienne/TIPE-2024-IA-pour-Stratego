/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
///////////// lecture et ecriture de fichier ////////////
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////

#include "fichier.h"

void enregistrer_ia_dans_fichier(int numero_de_fichier, ia ia_a_stocker, char nom_de_dossier[], char indicatif[]) {
    char nom_complet[200] ;
    sprintf(nom_complet, "%s/%d_%s_v%d.%s",nom_de_dossier, numero_de_fichier, indicatif, ia_a_stocker.version , EXTENTION);
    FILE *fichier = fopen(nom_complet, "w"); // Ouvre le fichier en mode écriture

    if (fichier != NULL) {
        fprintf(fichier, " VERSION %d \n", ia_a_stocker.version);
        fprintf(fichier, " FAMILLE %d \n", ia_a_stocker.famille);
        for (int i = 0; i< NBPARAMETRES; i++) {
            fprintf(fichier, "[%d] : %f \n", i, ia_a_stocker.parametres[i]); // Écrit le texte dans le fichier
        }
        fclose(fichier); // Ferme le fichier
        
    } 
    else {
        printf("Erreur : Impossible d'ouvrir le fichier %s.\n", nom_complet);
    }
}

ia lire_ia_dans_fichier(int numero_de_fichier, char nom_de_dossier[], char indicatif[]){
    ia retour;
    float val;
    char nom_complet[200] ;
    sprintf(nom_complet, "%s/%d_%s_v%d.%s",nom_de_dossier, numero_de_fichier, indicatif, TYPEIA, EXTENTION);
    FILE *fichier = fopen(nom_complet, "r"); // Ouvre le fichier en mode lecture
    if (fichier != NULL) {
        fscanf(fichier, " VERSION %d", &retour.version);
        fscanf(fichier, " FAMILLE %d", &retour.famille);
        for (int i=0; i<NBPARAMETRES; i++) {
            fscanf(fichier, " [%d] : %f \n", &i, &val);
            retour.parametres[i] = val;
        }
        fclose(fichier); // Ferme le fichier
    } 
    else {
        printf("Erreur : Impossible d'ouvrir le fichier %s   .\n", nom_complet); exit(1);
    }
    return retour;
}

void enregistrer_csv(char *nom_fichier, int nb_lignes, int lignes[nb_lignes], int nb_colonnes, int colonnes[nb_colonnes], double matrice[nb_lignes][nb_colonnes][2]){
    // Ouvrir le fichier CSV en mode écriture
    char nom_complet[200] = "";
    sprintf(nom_complet, "%s.csv", nom_fichier);
    FILE *fichier = fopen(nom_complet, "w");
    if (fichier == NULL) {
        printf("Erreur : impossible d'ouvrir le fichier\n");
        return;
    }

    // Écrire les en-têtes de colonnes dans le fichier CSV
    fprintf(fichier, "vs,"); // Écrire une virgule pour la première colonne vide
    for (int i = 0; i < nb_colonnes; i++) {
        fprintf(fichier, "%d", colonnes[i]);
        if (i < nb_colonnes - 1) {
            fprintf(fichier, ",");
        }
    }
    fprintf(fichier, "\n");

    // Écrire les données dans le fichier CSV
    for (int i = 0; i < nb_lignes; i++) {
        fprintf(fichier, "%d,", lignes[i]); // Écrire le nom de la ligne suivi d'une virgule
        for (int j = 0; j < nb_colonnes; j++) {
            fprintf(fichier, "V : %.1f%% / E : %.1f%%", matrice[i][j][0] * 100, matrice[i][j][1] * 100);
            if (j < nb_colonnes - 1) {
                fprintf(fichier, ",");
            }
        }
        fprintf(fichier, "\n");
    }

    // Fermer le fichier CSV
    fclose(fichier);
}