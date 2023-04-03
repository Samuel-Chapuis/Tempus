/* ---- Fonction de mise a jour de la carte ----*/

#include <stdio.h>
#include <stdlib.h>

#include "../../definition.h"

void map_updating(bric** carte,joueur* player_tab, int TC, int nb_joueur)
{
    for(int i=0; i<TC; i++)
    {
        for(int j=0; j<TC; j++)
        {
            carte[i][j].unite.deplacement = 1; //redonne la possibilit� de ce d�placer � toute les unit�s
            carte[i][j].ville.gen = 1; //redonne la possibilit� de generer des nouveau villageois � toutes les villes
            //printf("%d;%d ", i, j);
        }
        //printf("\n");
    }

    for(int u=1; u<=nb_joueur; u++)
    {
        player_tab[u].science_total = player_tab[u].science_total + player_tab[u].pop;
    }
}
