#ifndef GENERATION_H_INCLUDED
#define GENERATION_H_INCLUDED

#include "../definition.h"

void generationcarte(bric **carte,int TC,int roughness,int HI,int joueurs); //Permet de generer une carte avec de hauteurs.

int generationposition(bric **carte,int TC,int roughness,int HI,int joueurs); //Permet de placer les premi�re villes et unit�s des joeur sur le plateau (revoi 0 si l'�xecution c'est pass� sans erreurs)

#endif // GENERATION_H_INCLUDED
