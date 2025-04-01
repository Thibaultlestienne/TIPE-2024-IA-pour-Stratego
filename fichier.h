/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
///////////// lecture et ecriture de fichier ////////////
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////

#ifndef FICHIER
#define FICHIER

// stokage de la derniere generation
#define NOM_DOSSIER_IA_SAUVEGARDE "formation/save_ia"
#define INDICATIF_SAUVEGARDE "sauvegarde"

// stockage du meillleur de chaque generation
#define NOM_DOSSIER_IA_HISTORIQUE "formation/historique"
#define INDICATIF_HISTORIQUE "iéme_generation"

#define EXTENTION "ia"

#include <string.h>
#include <stdio.h>
#include "ia.h"

void enregistrer_ia_dans_fichier(int numero_de_fichier, ia ia_a_stocker, char nom_de_dossier[], char indicatif[]);
ia lire_ia_dans_fichier(int numero_de_fichier, char nom_de_dossier[], char indicatif[]);

void enregistrer_csv(char *nom_fichier, int nb_lignes, int lignes[nb_lignes], int nb_colonnes, int colonnes[nb_colonnes], double matrice[nb_lignes][nb_colonnes][2]);


#endif