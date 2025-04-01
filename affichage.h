#ifndef AFFICHAGE
#define AFFICHAGE

#include <stdio.h>
#include <stdlib.h>
#include "parcours.h"
#include "stratego.h"

#define AFFICHAGECOORDONNEES true
#define AFFICHAGEDEVOILE true
#define AFFICHAGEBOUGER true

void afficher_pion(piece *jeton);

void afficher_equipe(piece* equipe[NBPIECES]);

void afficher_case(cellule *cell);

void afficher_coup(coup c);

void afficher_coupMM(coupMM cmm);

void afficher_plateau(const plateau * jeu);

void afficher_plateau_version_joueur(const plateau * jeu, int tour);
#endif // AFFICHAGE