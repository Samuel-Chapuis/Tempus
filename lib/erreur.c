/* ---- Fonction Erreur ----*/

#include <stdio.h>
#include <stdlib.h>

#include "color.h"

/** Zone de gestion des erreurs potentiels **/


/*
Les erreurs code erreurs sont g�r� de la mani�re suivante:
Le code de l'erreur sur les unit�s, dizaines, centaines; la provenances sur les chiffres siuvants

1xxx => Erreur venant de main.c
2xxx => Erreur venant de generation.c
*/

void erreur(int e)
{
    printf("\n\n\n");
    color(15,4);
    printf("    /!\\ FATAL ERROR : %d /!\\    ",e);
    color(7,0);
}
