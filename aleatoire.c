/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
///////////// gestion des nombres aléatoires ////////////
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////

#include "aleatoire.h"

float generer_valeur_aleatoire_0_1(){// génères un float entre 0 et 1
    float aleatoire = (double)rand() / RAND_MAX;
    return aleatoire;
}

int generer_entier_aleatoire(int min, int max) {// Génère et retourne un nombre aléatoire dans la plage [| min, max |]
    int entier = rand() % (max - min + 1) + min;
    return entier;
}

int generer_signe_aleatoire(){//renvoie  -1 ou 1
    if (generer_entier_aleatoire(0, 1) == 0){return 1;}
    else {return -1;}
}