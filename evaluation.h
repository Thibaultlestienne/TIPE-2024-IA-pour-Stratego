#ifndef EVALUATION
#define EVALUATION

#include <stdio.h>
#include <stdlib.h>
#include "stratego.h"
#include "ia.h"
#include <time.h>


int distance3B(int maximisateur, int nbimmobile, piece** equipe0, piece** equipe1);
float evaluation(plateau* P, piece** equipe0, piece** equipe1, ia intelligence, int maximisateur, int tour);
float evaluationV1(plateau* P, piece** equipe0, piece** equipe1, ia intelligence, int maximisateur, int tour);
float evaluationV2(plateau* P, piece** equipe0, piece** equipe1, ia intelligence, int maximisateur, int tour);
float evaluationV10(plateau* P, coup c, ia intelligence, int tour);
float evaluationV11(plateau* P, coup c, ia intelligence, int tour);
float evaluationDeBoer(plateau* P, coup c, ia intelligence, int tour);

#endif