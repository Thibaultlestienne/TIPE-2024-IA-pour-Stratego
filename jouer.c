#include "stratego.h"
#include "fichier.h"

int main(){
    ia ia_test = lire_ia_dans_fichier(0, NOM_DOSSIER_IA_SAUVEGARDE, INDICATIF_SAUVEGARDE);
    jouer_humain_contre_ia(ia_test, NULL);
}