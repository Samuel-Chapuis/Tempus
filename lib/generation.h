#ifndef GENERATION_H_INCLUDED
#define GENERATION_H_INCLUDED

#include "../definition.h"

void generationcarte(bric **carte,int TC,int roughness,int HI,int joueurs); //Permet de generer une carte avec de hauteurs.

int generationposition(bric **carte,int TC,int roughness,int HI,int joueurs); //Permet de placer les première villes et unités des joeur sur le plateau (revoi 0 si l'éxecution c'est passé sans erreurs)

#endif // GENERATION_H_INCLUDED
