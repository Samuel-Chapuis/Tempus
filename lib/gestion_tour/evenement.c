/* ---- Fonction de gestion des evenement clavier et souris ----*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <SDL2/SDL.h>

#include "../../definition.h"
#include "../graphic/graphic.h"
#include "deplacement.h"
#include "../graphic/info_bulle.h"
#include "gestion_ville.h"
#include "../graphic/arbre_de_technolgies.h"

int event(int* co, int* xg, int* yg, joueur* player, bric** carte, SDL_Window* fenetre_carte, SDL_Renderer* rendu_info_case, SDL_Window* fenetre_info_case, SDL_Renderer* rendu_carte, joueur* player_tab)
{
    SDL_Event ev;
    //position de la souris
    int x = -1;
    int y = -1;
    int xd = -1;
    int yd = -1;

    if(SDL_PollEvent(&ev))
    {
        if(ev.type == SDL_QUIT){}

        /** -------- Commande Clavier -------- **/
        else if (ev.type == SDL_KEYDOWN)
        {
            /* --- Acceder à la console --- */
            if(SDLK_F10 == ev.key.keysym.sym)
            {
                if(*co == 0)
                {
                    ShowWindow(GetConsoleWindow(),SW_SHOW);
                    *co = 1;
                }
                else
                {
                    *co = 0;
                    ShowWindow(GetConsoleWindow(),SW_HIDE);
                }
            }
            /* ---------------------------- */

            /* --- Autre commande clavier --- */
            else if(SDLK_F11 == ev.key.keysym.sym) ///DEBUG !
            {
                printf("\ncouleur joueur = %d; science = %d; population = %d; nombre de ville = %d; \n", (*player).couleur, (*player).science_total, (*player).pop, (*player).villes);
                for(int u = 0; u <= 9; u++)
                {
                    printf("\ttech%d = %d\n", u, (*player).tech[u]);
                }
            }
            /* ---------------------------- */
        }
        /** -------- Commande Souris ---------- **/
        else if(ev.type == SDL_MOUSEBUTTONDOWN)
        {
            /* --- Click gauche dans la fenetre de la carte --- */
            SDL_GetMouseState(&x, &y);

            //Clique gauche sur la carte
            if(ev.button.button == SDL_BUTTON_LEFT && SDL_GetMouseFocus() == fenetre_carte)
            {
                x = x/32;
                y = y/32;
                info_bulle(carte, *player, rendu_info_case, &x, &y);
                SDL_GetMouseState(xg, yg);
                *xg = *xg/32;
                *yg = *yg/32;
            }
            //Bouton fin de tour
            else if(ev.button.button == SDL_BUTTON_LEFT && SDL_GetMouseFocus() == fenetre_info_case && x>18&&x<208&&y>285&&y<326 )
            {
                return -1;
            }
            //Bouton fin arbre de technologie
            else if(ev.button.button == SDL_BUTTON_LEFT && SDL_GetMouseFocus() == fenetre_info_case && x>94&&x<225&&y>200&&y<232 )
            {
                arbre_tech(player);
            }
            //clique droit sur la carte ( déplacement des unités )
            else if(ev.button.button == SDL_BUTTON_RIGHT && SDL_GetMouseFocus() == fenetre_carte)
            {
                SDL_GetMouseState(&xd, &yd);
                xd = xd/32;
                yd = yd/32;
                if(carte[*xg][*yg].unite.classe != 0 ) //gestion des unités
                {
                    deplacement_unite(carte, fenetre_carte, rendu_carte, player, *xg, *yg, xd, yd, player_tab);
                }
                if(carte[*xg][*yg].ville.gen == 1) //gestion de la création de villageois
                {
                    creation_de_villageois(carte, *player, *xg, *yg, xd, yd);
                    graphic_case(carte, *xg, *yg, rendu_carte);
                    graphic_case(carte, xd, yd, rendu_carte);
                }


            }
        }

    }

    return 0;
}


