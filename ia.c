#include "ia.h"

/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
//////////////////// Gestion IA /////////////////////////
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////

int nombre_familles_differentes(const ia tableau_famille[NBSURVIVANTS]){
    int nbr = NBSURVIVANTS;
    int tab[NBSURVIVANTS];

    for (int i =0; i< NBSURVIVANTS; i++){
        tab[i] = tableau_famille[i].famille;
    }
   for (int i = 0; i < nbr; i++) {
      for (int j = i + 1; j < nbr;) {
         if (tab[j] == tab[i]) {
            for (int k = j; k < nbr; k++) {
               tab[k] = tab[k + 1];
            }
            nbr--;
         } else
            j++;
      }
   }
    return nbr;
}

ia creer_ia_aleatoire( int version ){
    ia ia_aleatoire;
    ia_aleatoire.version = version;
    for (int j=0; j<NBPARAMETRES; j++) {
        ia_aleatoire.parametres[j] = generer_valeur_aleatoire_0_1() * (ALEAMAX - ALEAMIN) + ALEAMIN;
    }
    ia_aleatoire.famille = rand();
    return ia_aleatoire;
}

ia muter_ia(ia pere){// donne une ia 'fils' generer a partir d'une ia 'pere'
    ia fils;
    fils.version = pere.version;

    for ( int i=0; i<NBPARAMETRES; i++) {
        float alea = generer_valeur_aleatoire_0_1();
        if ( alea < PROBABILITEMUTATIONA) {
            fils.parametres[i] = pere.parametres[i]+ VARIATIONMUTATIONA * generer_valeur_aleatoire_0_1() * generer_signe_aleatoire();
        }
        else if (alea < PROBABILITEMUTATIONA + PROBABILITEMUTATIONB){
            fils.parametres[i] = generer_valeur_aleatoire_0_1() * (ALEAMAX - ALEAMIN) + ALEAMIN;
        }
        else {fils.parametres[i] = pere.parametres[i];}
    }
    fils.famille = pere.famille;
    return fils;
}

// Fonction pour trouver les indices des N plus grands éléments d'un tableau d'entier
void recuperer_indices_N_plus_grands_elements(int tableau[], int indices[], int taille, int N) {
    for (int i = 0; i < taille; i++) {
        indices[i] = i; // Initialisez le tableau d'indices avec les indices d'origine
    }

    for (int i = 0; i < taille - 1; i++) {
        for (int j = 0; j < taille - i - 1; j++) {
            if (tableau[j] < tableau[j + 1]) {
                // Échangez les éléments du tableau et les indices correspondants
                int temp = tableau[j];
                tableau[j] = tableau[j + 1];
                tableau[j + 1] = temp;

                temp = indices[j];
                indices[j] = indices[j + 1];
                indices[j + 1] = temp;
            }
        }
    }
}

void jouer_poule(ia tableau_ia[NBJOUEURPARPOULE], int nombre_joueur_sortie, ia vainqueurs[NBJOUEURPARPOULE]){//renvoie un tableau avec les n meilleurs joueurs
    int nb_victoire = 0;
    int nb_egalite = 0;
    int nb_tour = 0;
    time_t debut = time (NULL);

    int resultat[NBJOUEURPARPOULE] = {0};
    int resultat_combat = -1;// ne dois pas être utilisé tel quelle
    for (int s = 0; s<DEGRESDESURETE ; s++) {//effectue DEGRESDESURETE fois chaque match 
        // effectue tous les matchs possibles entre deux ia
        for (int i = 0; i<NBJOUEURPARPOULE ; i++){
            for (int j = i+1; j<NBJOUEURPARPOULE ; j++){
                //ajoute un point au vainqueur
                //printf("i : %d, j : %d \n", i, j);
                resultat_combat = jouer_ia_contre_ia(tableau_ia[i] , tableau_ia[j], &nb_tour);
                if (resultat_combat == 0){
                    resultat[i] += 10;
                    nb_victoire++;
                }
                else if (resultat_combat == 1) {
                    resultat[j] += 10;
                    nb_victoire++;
                }
                else {
                    resultat[i] += 1;
                    resultat[j] += 1;
                    nb_egalite++;
                }
            }
        }
    }

    time_t fin = time (NULL);

    // renvoie les données liées à la génération 
    printf("temps de formation (en seconde) : %ld\n", fin - debut );
    printf("nombre de victoire : %d\n",nb_victoire);
    printf("nombre d'égalité : %d\n",nb_egalite);
    printf("nombre de coup moyen : %d\n",(2*nb_tour)/(NBJOUEURPARPOULE*(NBJOUEURPARPOULE-1)));
    printf("nombre de famille differentes : %d\n", nombre_familles_differentes(vainqueurs));

    for (int i = 0; i<NBJOUEURPARPOULE ; i++){
        printf("i : %d, resultat : %d \n ", i, resultat[i]);
    }

    // récupère la liste des vainqueurs du tournois et la range dans le tableau vainqueur
    int tableau_indice[NBJOUEURPARPOULE];
    recuperer_indices_N_plus_grands_elements(resultat, tableau_indice,NBJOUEURPARPOULE ,nombre_joueur_sortie);
    for (int i = 0 ; i < nombre_joueur_sortie ; i++){
        vainqueurs[i] = tableau_ia[tableau_indice[i]];
    }
}

void jouer_poule_random(ia tableau_ia[NBJOUEURPARPOULE], int nombre_joueur_sortie, ia vainqueurs[NBJOUEURPARPOULE]){//renvoie un tableau avec les n meilleurs joueurs
    int resultat[NBJOUEURPARPOULE] = {0};
    int resultat_combat = -1;// ne dois pas être utilisé tel quelle
    for (int i=0; i<NBJOUEURPARPOULE; i++) {
        for (int j=0; j<10; j++) {
                printf("i : %d, j : %d \n", i, j);
                resultat_combat = jouer_ia_contre_random(tableau_ia[i]);
                if (resultat_combat == 0){
                    resultat[i] += 10;
                } else if ( resultat_combat == 2) {
                    resultat[i] += 1;
                }
        }
    }
    for (int i = 0; i<NBJOUEURPARPOULE ; i++){
        printf("i : %d, resultat : %d \n ", i, resultat[i]);
    }
    // récupère la liste des vainqueurs du tournois et la range dans le tableau vainqueur
    int tableau_indice[NBJOUEURPARPOULE];
    recuperer_indices_N_plus_grands_elements(resultat, tableau_indice,NBJOUEURPARPOULE ,nombre_joueur_sortie);
    for (int i = 0 ; i < nombre_joueur_sortie ; i++){
        vainqueurs[i] = tableau_ia[tableau_indice[i]];
    }
}

/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
/////////////////////// Main ////////////////////////////
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////


int main(int argc, char const *argv[])
{   
    srand(time(NULL)); // Initialise le générateur de nombres aléatoires avec une graine basée sur l'horloge système

    // Initialisation des ia
    ia tableau[NBJOUEURPARPOULE];
    for (int i = 0 ; i<NBJOUEURPARPOULE ; i++){ 
        ia intelligence;
        if (i < NBJOUEURSACHARGER) {// joueur déjà préformer
            intelligence = lire_ia_dans_fichier(i, NOM_DOSSIER_IA_SAUVEGARDE, INDICATIF_SAUVEGARDE);
        }
        else{// joueurs aleatoires pour completer
            intelligence = creer_ia_aleatoire(TYPEIA);
        }
        tableau[i] = intelligence;
    }

    //fait muter generation apres generation 
    for(int generation = 0; generation < NBGENERATION; generation++ ){

        printf("\n\n\nGENERATION %d \n\n" , generation);
        ia vainqueur[NBJOUEURPARPOULE];
        jouer_poule(tableau, NBSURVIVANTS, vainqueur);
        for(int i = 0; i < NBSURVIVANTS; i++ ){
            tableau[i] = vainqueur[i];
        }
        for(int i = NBSURVIVANTS; i < NBJOUEURPARPOULE - NBALEATOIREPARGENERATION; i++ ){
            tableau[i] = muter_ia(vainqueur[i%NBSURVIVANTS]);
        }
        for(int i = NBJOUEURPARPOULE - NBALEATOIREPARGENERATION; i < NBJOUEURPARPOULE; i++ ){
            tableau[i] = creer_ia_aleatoire(TYPEIA);
        }

        for(int i = 0; i < NBJOUEURASAUVEGARDER; i++ ){
            enregistrer_ia_dans_fichier(i,tableau[i],NOM_DOSSIER_IA_SAUVEGARDE, INDICATIF_SAUVEGARDE);
        }
        enregistrer_ia_dans_fichier(generation,tableau[0],NOM_DOSSIER_IA_HISTORIQUE, INDICATIF_HISTORIQUE);
    }
   
}
