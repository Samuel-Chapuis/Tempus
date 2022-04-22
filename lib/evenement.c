/* ---- Fonction de gestion des evenement clavier et souris ----*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <SDL2/SDL.h>

#include "../definition.h"
#include "info_bulle.h"

void event(int* co, bric** carte, SDL_Window* fenetre_carte, SDL_Renderer* rendu_info_case)
{
    SDL_Event ev;
    //position de la souris
    int x = -1;
    int y = -1;

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
            else if(SDLK_a == ev.key.keysym.sym)
            {

            }
            /* ---------------------------- */
        }
        /** -------- Commande Souris ---------- **/
        else if(ev.type == SDL_MOUSEBUTTONDOWN)
        {
            /* --- Click gauche dans la fenetre de la carte --- */
            if(ev.button.button == SDL_BUTTON_LEFT && SDL_GetMouseFocus() == fenetre_carte)
            {
                SDL_GetMouseState(&x, &y);
                info_bulle(carte, rendu_info_case, &x, &y);
            }
        }

    }
}


