/* ---- Fonction de gestion des déplacements ----*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../../definition.h"
#include "gestion_ville.h"
#include "../graphic/graphic.h"

void siege(bric** carte, SDL_Renderer* rendu, joueur player, int x, int y, joueur* player_tab)
{
    int defenseur = -1;
    int attaquant = 0;
    int color_temp = -1;

    //On test si il y'a une ville proche de l'unité déplacé
    for(int i = -1; i <= 1; i++)
    {
        for(int j = -1; j <= 1; j++)
        {
            if(carte[x+i][y+j].ville.joueur != 0 && carte[x+i][y+j].ville.joueur != player.couleur)
            {
                //printf("il y'a une ville enemie dans l'eparage case %d %d\n", x+i, y+j);
                defenseur =  1 + carte[x+i][y+j].ville.habitants/2 ; //On determine le nombre de défenseurs de la ville
                //printf("defenseur = %d\n", defenseur);

                for(int u = -1; u <= 1; u++)
                {
                    for(int w = -1; w <=1 ; w++)
                    {
                        if(carte[x+i+u][y+j+w].unite.classe == 2 && carte[x+i+u][y+j+w].unite.joueur == player.couleur)
                        {
                            attaquant++;
                        }
                    }
                }

                //printf("attaquant = %d\n", attaquant);
                if(attaquant > defenseur)
                {
                    color_temp = carte[x+i][y+j].ville.joueur;
                    player_tab[color_temp].pop = player_tab[color_temp].pop - carte[x+i][y+j].ville.habitants;
                    carte[x+i][y+j].ville.habitants = carte[x+i][y+j].ville.habitants/2;
                     player_tab[player.couleur].pop = player_tab[player.couleur].pop + carte[x+i][y+j].ville.habitants;
                    carte[x+i][y+j].ville.joueur = player.couleur;
                    for(int o = -1; o <= 1; o++)
                    {
                        for(int p = -1; p <= 1; p++)
                        {
                            carte[x+i+o][y+j+p].territoire = player.couleur;
                            graphic_case(carte, x+i+o, y+j+p, rendu);
                        }
                    }

                // Ecriture dans les logs //
                FILE* log = NULL;
                log = fopen("log.txt", "r+");
                fseek(log, 0, SEEK_END);
                fprintf(log, "\t Annexion de la ville du joueur %d sur la case %d, %d\n", color_temp, x+i, y+i);
                position_curseur = ftell(log);
                fclose(log);
                // --------------------- //

                }
            }
        }
    }

}



void deplacement_standard(bric** carte, SDL_Window* fenetre, SDL_Renderer* rendu, joueur* player, int xg, int yg, int xd, int yd, joueur* player_tab)
{
    int pm = carte[xg][yg].unite.pm;

    for(int i = -pm; i <= pm; i++)
        {
            for(int j = -pm; j <= pm; j++)
            {
                if(xd+i == xg && yg+j == yd /*&& (i != 0 || j != 0)*/)
                {
                    struct unites temp;
                    temp = carte[xg][yg].unite;
                    carte[xd][yd].unite = temp;
                    carte[xd][yd].unite.deplacement = 0;


                    carte[xg][yg].unite.classe = 0;
                    carte[xg][yg].unite.deplacement = 0;
                    carte[xg][yg].unite.joueur = 0;
                    carte[xg][yg].unite.pm = 0;
                    siege(carte, rendu, *player, xd, yd, player_tab);

                    graphic_case(carte, xg, yg, rendu);
                    graphic_case(carte, xd, yd, rendu);

                    // Ecriture dans les logs //
                    FILE* log = NULL;
                    log = fopen("log.txt", "r+");
                    fseek(log, 0, SEEK_END);
                    fprintf(log, "\t Deplacement d'un %d de la case %d %d à la case %d %d\n", carte[xd][yd].unite.classe, xg, yg, xd, yd);
                    position_curseur = ftell(log);
                    fclose(log);
                    // --------------------- //
                }
            }
        }
}



void deplacement_chevalier(bric** carte, SDL_Window* fenetre, SDL_Renderer* rendu, joueur* player, int xg, int yg, int xd, int yd, joueur* player_tab)
{
    if(carte[xd][yd].hauteur != 0
       && carte[xd][yd].hauteur != 1
       && carte[xd][yd].ville.joueur == 0
       && ( carte[xd][yd].unite.classe == 0 || carte[xd][yd].unite.classe == 1 )
       )
       {
           deplacement_standard(carte, fenetre, rendu, player, xg, yg, xd, yd, player_tab);
           return;
       }


    //Transformation en bateau
    if( (carte[xd][yd].hauteur == 0 || carte[xd][yd].hauteur == 1 )
        &&(*player).tech[6] == 1
       )
    {
        for(int i = -1; i <= 1; i++)
            {
                for(int j = -1; j <= 1; j++)
                {
                    if(xd==xg+i
                        && yd==yg+j
                       )
                    {
                        carte[xg][yg].unite.classe = 0;
                        carte[xg][yg].unite.deplacement = 0;
                        carte[xg][yg].unite.joueur = 0;
                        carte[xg][yg].unite.pm = 0;

                        carte[xd][yd].unite.classe = 3;
                        carte[xd][yd].unite.pm = 3;
                        carte[xd][yd].unite.joueur = (*player).couleur;

                        carte[xd][yd].unite.deplacement = 0;

                        graphic_case(carte, xg, yg, rendu);
                        graphic_case(carte, xd, yd, rendu);
                    }
                }
            }
        return;
    }

}



void deplacement_villageois(bric** carte, SDL_Window* fenetre, SDL_Renderer* rendu, joueur* player, int xg, int yg, int xd, int yd, joueur* player_tab)
{
    int pm = carte[xg][yg].unite.pm;

    if(carte[xd][yd].hauteur != 0
       && carte[xd][yd].hauteur != 1
       )
    {
        //Transformation des villageois en chevalier
        if( xg == xd
           && yg == yd
           && carte[xd][yd].territoire == carte[xd][yd].unite.joueur
           )
        {
            carte[xg][yg].unite.classe = 2;
            carte[xg][yg].unite.deplacement = 0;
            carte[xg][yg].unite.pm = 2;

            // Ecriture dans les logs //
            FILE* log = NULL;
            log = fopen("log.txt", "r+");
            fseek(log, 0, SEEK_END);
            fprintf(log, "\t Transformation d'un villageoi en chevalier sur la case %d %d\n", xg, yg);
            position_curseur = ftell(log);
            fclose(log);
            // --------------------- //

            return;
        }


        for(int i = -pm; i <= pm; i++)
            {
                for(int j = -pm; j <= pm; j++)
                {
                    if(xd+i == xg && yg+j == yd /*&& (i != 0 || j != 0)*/)
                    {
                        //Gestion de l'augmanatation de la pop
                        if(carte[xd][yd].ville.joueur == carte[xg][yg].unite.joueur)
                        {
                            carte[xg][yg].unite.classe = 0;
                            carte[xg][yg].unite.joueur = 0;
                            carte[xg][yg].unite.deplacement = 0;
                            carte[xg][yg].unite.pm = 0;

                            carte[xd][yd].ville.habitants++;
                            (*player).pop++;
                        }

                        //Gestion de la création des villes
                        if(carte[xg][yg].unite.classe == 1 && carte[xd][yd].unite.classe == 1)
                        {
                            if(carte[xg][yg].unite.joueur == carte[xd][yd].unite.joueur)
                            {
                                int tester = 0;
                                for(int i=-1; i<=1; i++)
                                {
                                    for(int j=-1; j<=1; j++)
                                    {
                                        if(carte[xd+i][yd+j].territoire != 0)
                                            tester++;
                                    }
                                }
                                if(tester == 0)
                                {
                                    carte[xg][yg].unite.classe = 0;
                                    carte[xg][yg].unite.joueur = 0;
                                    carte[xg][yg].unite.deplacement = 0;
                                    carte[xg][yg].unite.pm = 0;

                                    creation_ville(carte, xd, yd, carte[xd][yd].unite.joueur);
                                    (*player).pop++;

                                    carte[xd][yd].unite.classe = 0;
                                    carte[xd][yd].unite.joueur = 0;
                                    carte[xd][yd].unite.deplacement = 0;
                                    carte[xd][yd].unite.pm = 0;

                                    graphic_case(carte, xg, yg, rendu);
                                    for(int i=-1; i<=1; i++)
                                    {
                                        for(int j=-1; j<=1; j++)
                                        {
                                            graphic_case(carte, xd+i, yd+j, rendu);
                                        }
                                    }
                                }
                            }
                            return;
                        }
                    }
                }
            }

    if(carte[xd][yd].ville.joueur == 0 )
    {
        deplacement_standard(carte, fenetre, rendu, player, xg, yg, xd, yd, player_tab);
        return;
    }
    }

    //Transformation en Bateau
    if( (carte[xd][yd].hauteur == 0 || carte[xd][yd].hauteur == 1 )
         &&(*player).tech[6] == 1
       )
    {
        for(int i = -1; i <= 1; i++)
            {
                for(int j = -1; j <= 1; j++)
                {
                    if(xd==xg+i
                        && yd==yg+j
                       )
                    {
                        carte[xg][yg].unite.classe = 0;
                        carte[xg][yg].unite.deplacement = 0;
                        carte[xg][yg].unite.joueur = 0;
                        carte[xg][yg].unite.pm = 0;

                        carte[xd][yd].unite.classe = 4;
                        carte[xd][yd].unite.pm = 2;
                        carte[xd][yd].unite.joueur = (*player).couleur;

                        carte[xd][yd].unite.deplacement = 0;

                        graphic_case(carte, xg, yg, rendu);
                        graphic_case(carte, xd, yd, rendu);
                    }
                }
            }
        return;
    }
}



void deplacement_bateau_civile(bric** carte, SDL_Window* fenetre, SDL_Renderer* rendu, joueur* player, int xg, int yg, int xd, int yd, joueur* player_tab)
{
    if( (carte[xd][yd].hauteur == 0 ||carte[xd][yd].hauteur == 1 )
       )
       {
           deplacement_standard(carte, fenetre, rendu, player, xg, yg, xd, yd, player_tab);
           return;
       }


    //Transformation en Chevalier
    if( (carte[xd][yd].hauteur != 0 || carte[xd][yd].hauteur != 1 )
       )
    {
        for(int i = -1; i <= 1; i++)
            {
                for(int j = -1; j <= 1; j++)
                {
                    if(xd==xg+i
                        && yd==yg+j
                       )
                    {
                        carte[xg][yg].unite.classe = 0;
                        carte[xg][yg].unite.deplacement = 0;
                        carte[xg][yg].unite.joueur = 0;
                        carte[xg][yg].unite.pm = 0;

                        carte[xd][yd].unite.classe = 1;
                        carte[xd][yd].unite.pm = 1;
                        carte[xd][yd].unite.joueur = (*player).couleur;

                        carte[xd][yd].unite.deplacement = 0;

                        graphic_case(carte, xg, yg, rendu);
                        graphic_case(carte, xd, yd, rendu);
                    }
                }
            }
        return;
    }
}



void deplacement_bateau(bric** carte, SDL_Window* fenetre, SDL_Renderer* rendu, joueur* player, int xg, int yg, int xd, int yd, joueur* player_tab)
{
    if( (carte[xd][yd].hauteur == 0 ||carte[xd][yd].hauteur == 1 )
       )
       {
           deplacement_standard(carte, fenetre, rendu, player, xg, yg, xd, yd, player_tab);
           return;
       }


    //Transformation en Chevalier
    if( (carte[xd][yd].hauteur != 0 || carte[xd][yd].hauteur != 1 )
       )
    {
        for(int i = -1; i <= 1; i++)
            {
                for(int j = -1; j <= 1; j++)
                {
                    if(xd==xg+i
                        && yd==yg+j
                       )
                    {
                        carte[xg][yg].unite.classe = 0;
                        carte[xg][yg].unite.deplacement = 0;
                        carte[xg][yg].unite.joueur = 0;
                        carte[xg][yg].unite.pm = 0;

                        carte[xd][yd].unite.classe = 2;
                        carte[xd][yd].unite.pm = 2;
                        carte[xd][yd].unite.joueur = (*player).couleur;

                        carte[xd][yd].unite.deplacement = 0;

                        graphic_case(carte, xg, yg, rendu);
                        graphic_case(carte, xd, yd, rendu);
                    }
                }
            }
        return;
    }
}


void deplacement_unite(bric** carte, SDL_Window* fenetre, SDL_Renderer* rendu, joueur* player, int xg, int yg, int xd, int yd, joueur* player_tab)
{
    if((*player).couleur == carte[xg][yg].unite.joueur
       && carte[xg][yg].unite.deplacement == 1
       && carte[xd][yd].hauteur <= 8
       )
    {
        switch(carte[xg][yg].unite.classe)
        {
        case 1:
            deplacement_villageois(carte, fenetre, rendu, player, xg, yg, xd, yd, player_tab);
            return;
        case 2:
            deplacement_chevalier(carte, fenetre, rendu, player, xg, yg, xd, yd, player_tab);
            return;
        case 3:
            deplacement_bateau(carte, fenetre, rendu, player, xg, yg, xd, yd, player_tab);
            return;
        case 4:
            deplacement_bateau_civile(carte, fenetre, rendu, player, xg, yg, xd, yd, player_tab);
            return;

        }
    }
}



