/* ---- Fonction de gestion des villes----*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "../../definition.h"

void creation_de_villageois(bric** carte, joueur player, int xg, int yg, int xd, int yd)
{
    if(carte[xd][yd].unite.classe == 0 &&
       carte[xd][yd].hauteur == -1 &&
       carte[xd][yd].hauteur <= 8 &&
       carte[xg][yg].ville.joueur == player.couleur
       )
    {
    for(int i = -1; i <= 1; i++)
        {
            for(int j = -1; j <= 1; j++)
            {
                if(xd+i == xg && yg+j == yd && (i != 0 || j != 0))
                {
                    carte[xg][yg].ville.gen = 0;

                    carte[xd][yd].unite.classe = 1;
                    carte[xd][yd].unite.deplacement = 0;
                    carte[xd][yd].unite.pm = 1;
                    carte[xd][yd].unite.joueur = player.couleur;

                    // Ecriture dans les logs //
                    FILE* log = NULL;
                    log = fopen("log.txt", "r+");
                    fseek(log, 0, SEEK_END);
                    fprintf(log, "\t Creation d'un villageois sur la case %d %d \n", xd, yd);
                    position_curseur = ftell(log);
                    fclose(log);
                    // --------------------- //
                }
            }
        }
    }

}

void creation_ville(bric **carte,int x, int y, int couleur)
{
    carte[x][y].ville.habitants=1;
    carte[x][y].ville.joueur=couleur;
    carte[x][y].ville.gen=0;
    carte[x][y].hauteur = -1;

    for(int ui=-1;ui<=1;ui++)
        {
            for(int uj=-1;uj<=1;uj++)
            {
                carte[ui+x][uj+y].territoire=couleur;
                if(carte[ui+x][uj+y].hauteur>1&&carte[ui+x][uj+y].hauteur<=4)
                    carte[ui+x][uj+y].hauteur=-1;
            }
        }


    // Ecriture dans les logs //
    FILE* log = NULL;
    log = fopen("log.txt", "r+");
    fseek(log, 0, SEEK_END);
    fprintf(log, "\t Ville générée sur la case %d %d \n", x, y);
    position_curseur = ftell(log);
    fclose(log);
    // --------------------- //
}
