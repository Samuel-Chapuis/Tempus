/* ---- Fonction de gestion des Technologies ----*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../../definition.h"

void arbre_tech(joueur* player)
{
//fenetre tech

    SDL_Event ev;
    int tester = 0;
    int x = -1;
    int y = -1;

//Affiche la fennêtre ainsi que l'image principale
    SDL_Window* fenetre_technologie = NULL;
    SDL_Renderer* rendu_technologie = NULL;

    fenetre_technologie = SDL_CreateWindow("Technologies", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,926 , 400, SDL_WINDOW_SHOWN | SDL_WINDOW_BORDERLESS);
    rendu_technologie = SDL_CreateRenderer(fenetre_technologie,-1,SDL_RENDERER_ACCELERATED);



    SDL_Texture* texture_back = NULL;
    SDL_Surface* image_back = NULL;

    image_back = SDL_LoadBMP("sprite/tech/tech.bmp");
    texture_back = SDL_CreateTextureFromSurface(rendu_technologie, image_back);
    SDL_Rect dst = {0, 0, 926, 400};
    SDL_RenderCopy(rendu_technologie, texture_back, NULL, &dst);

//Afiche les technologie que les joueurs ont déja en leur pocession
    SDL_Texture* texture_claim = NULL;
    SDL_Surface* image_claim = NULL;

    image_claim = SDL_LoadBMP("sprite/tech/claim.bmp");
    texture_claim = SDL_CreateTextureFromSurface(rendu_technologie, image_claim);

BALISE:

    if((*player).tech[0] == 1) //Ecriture
    {
        SDL_Rect dst_tech0 = {36, 192, 65, 65};
        SDL_RenderCopy(rendu_technologie, texture_claim, NULL, &dst_tech0);

        if((*player).tech[1] == 1) //Agriculture
        {
            SDL_Rect dst_tech1 = {192, 92, 65, 65};
            SDL_RenderCopy(rendu_technologie, texture_claim, NULL, &dst_tech1);
        }
        if((*player).tech[2] == 1) //Massonerie
        {
            SDL_Rect dst_tech2 = {192, 193, 65, 65};
            SDL_RenderCopy(rendu_technologie, texture_claim, NULL, &dst_tech2);
        }
        if((*player).tech[3] == 1) //Monaie
        {
            SDL_Rect dst_tech3 = {192, 300, 65, 65};
            SDL_RenderCopy(rendu_technologie, texture_claim, NULL, &dst_tech3);
        }
        if((*player).tech[4] == 1) //Roue
        {
            SDL_Rect dst_tech4 = {354, 193, 65, 65};
            SDL_RenderCopy(rendu_technologie, texture_claim, NULL, &dst_tech4);

            if((*player).tech[6] == 1) //Navigation
            {
                SDL_Rect dst_tech6 = {510, 92, 65, 65};
                SDL_RenderCopy(rendu_technologie, texture_claim, NULL, &dst_tech6);
            }
            if((*player).tech[5] == 1) //Imprimerie
            {
                SDL_Rect dst_tech5 = {510, 193, 65, 65};
                SDL_RenderCopy(rendu_technologie, texture_claim, NULL, &dst_tech5);

                if((*player).tech[8] == 1) //Chemine de Fer
                {
                    SDL_Rect dst_tech8 = {668, 290, 65, 65};
                    SDL_RenderCopy(rendu_technologie, texture_claim, NULL, &dst_tech8);
                }
                if((*player).tech[7] == 1) //Industrie
                {
                    SDL_Rect dst_tech7 = {668, 193, 65, 65};
                    SDL_RenderCopy(rendu_technologie, texture_claim, NULL, &dst_tech7);

                    if((*player).tech[9] == 1) //Aviation
                    {
                        SDL_Rect dst_tech9 = {826, 191, 65, 65};
                        SDL_RenderCopy(rendu_technologie, texture_claim, NULL, &dst_tech9);
                    }
                }
            }
        }
    }
    SDL_RenderPresent(rendu_technologie);


//Permet au joeur d'aquerir de nouvelles technologies
    while(tester == 0)
    {
     if(SDL_PollEvent(&ev))
     {
        if(ev.type == SDL_KEYDOWN && SDLK_ESCAPE == ev.key.keysym.sym) //Permet de sortir de la fennêtre en appuyant sur ecp.
            tester++;

        else if(ev.type == SDL_MOUSEBUTTONDOWN && SDL_GetMouseFocus() == fenetre_technologie)
        {
            SDL_GetMouseState(&x, &y);
            if(y>195 && y<254 && x>39 && x<98) //Ecriture 0
            {
                if((*player).tech[0] == 0 &&
                    (*player).science_total >= 3
                    )
                {
                    (*player).science_total = (*player).science_total-3;
                    (*player).tech[0] = 1;
                    // Ecriture dans les logs //
                    FILE* log = NULL;
                    log = fopen("log.txt", "r+");
                    fseek(log, 0, SEEK_END);
                    fprintf(log, "\t Devellopement de l'écriture\n");
                    position_curseur = ftell(log);
                    fclose(log);
                    // --------------------- //
                }
            }
            else if(y>195 && y<254 && x>197 && x<256) //Massonerie 2
            {
                if((*player).tech[0] == 1 &&
                   (*player).tech[2] == 0 &&
                   (*player).science_total >= 7 )
                {
                    (*player).tech[2] = 1;
                    (*player).science_total = (*player).science_total - 7;
                    // Ecriture dans les logs //
                    FILE* log = NULL;
                    log = fopen("log.txt", "r+");
                    fseek(log, 0, SEEK_END);
                    fprintf(log, "\t Devellopement de la massonerie\n");
                    position_curseur = ftell(log);
                    fclose(log);
                    // --------------------- //
                }
            }
            else if(y>95 && y<154 && x>197 && x<256) //Agriculture 1
            {
                if((*player).tech[0] == 1 &&
                   (*player).tech[1] == 0 &&
                   (*player).science_total >= 5 )
                {
                    (*player).tech[1] = 1;
                    (*player).science_total = (*player).science_total - 5;
                    // Ecriture dans les logs //
                    FILE* log = NULL;
                    log = fopen("log.txt", "r+");
                    fseek(log, 0, SEEK_END);
                    fprintf(log, "\t Devellopement de l'agriculture\n");
                    position_curseur = ftell(log);
                    fclose(log);
                    // --------------------- //
                }
            }
            else if(y>303 && y<362 && x>197 && x<256) //Monaie 3
            {
                if((*player).tech[0] == 1 &&
                   (*player).tech[3] == 0 &&
                   (*player).science_total >= 5 )
                {
                    (*player).tech[3] = 1;
                    (*player).science_total = (*player).science_total - 5;
                    // Ecriture dans les logs //
                    FILE* log = NULL;
                    log = fopen("log.txt", "r+");
                    fseek(log, 0, SEEK_END);
                    fprintf(log, "\t Devellopement de la monaie\n");
                    position_curseur = ftell(log);
                    fclose(log);
                    // --------------------- //
                }
            }
            else if(y>195 && y<254 && x>355 && x<414) //Roue 4
            {
                if((*player).tech[1] == 1 &&
                   (*player).tech[2] == 1 &&
                   (*player).tech[3] == 1 &&
                   (*player).tech[4] == 0 &&
                   (*player).science_total >= 15 )
                {
                    (*player).tech[4] = 1;
                    (*player).science_total = (*player).science_total - 15;
                    // Ecriture dans les logs //
                    FILE* log = NULL;
                    log = fopen("log.txt", "r+");
                    fseek(log, 0, SEEK_END);
                    fprintf(log, "\t Devellopement de la roue\n");
                    position_curseur = ftell(log);
                    fclose(log);
                    // --------------------- //
                }
            }
            else if(y>195 && y<254 && x>514 && x<573) //Imprimerie 5
            {
                if((*player).tech[4] == 1 &&
                   (*player).tech[5] == 0 &&
                   (*player).science_total >= 23 )
                {
                    (*player).tech[5] = 1;
                    (*player).science_total = (*player).science_total - 23;
                    // Ecriture dans les logs //
                    FILE* log = NULL;
                    log = fopen("log.txt", "r+");
                    fseek(log, 0, SEEK_END);
                    fprintf(log, "\t Devellopement de l'imprimerie\n");
                    position_curseur = ftell(log);
                    fclose(log);
                    // --------------------- //
                }
            }
            else if(y>95 && y<154 && x>514 && x<573) //Navigation 6
            {
                if((*player).tech[4] == 1 &&
                   (*player).tech[6] == 0 &&
                   (*player).science_total >= 20 )
                {
                    (*player).tech[6] = 1;
                    (*player).science_total = (*player).science_total - 20;
                    // Ecriture dans les logs //
                    FILE* log = NULL;
                    log = fopen("log.txt", "r+");
                    fseek(log, 0, SEEK_END);
                    fprintf(log, "\t Devellopement de la navigation\n");
                    position_curseur = ftell(log);
                    fclose(log);
                    // --------------------- //
                }
            }
            else if(y>195 && y<254 && x>670 && x<729) //Industrie 7
            {
                if((*player).tech[5] == 1 &&
                   (*player).tech[6] == 1 &&
                   (*player).tech[7] == 0 &&
                   (*player).science_total >= 30 )
                {
                    (*player).tech[7] = 1;
                    (*player).science_total = (*player).science_total - 30;
                    // Ecriture dans les logs //
                    FILE* log = NULL;
                    log = fopen("log.txt", "r+");
                    fseek(log, 0, SEEK_END);
                    fprintf(log, "\t Devellopement de l'industrie\n");
                    position_curseur = ftell(log);
                    fclose(log);
                    // --------------------- //
                }
            }
            else if(y>303 && y<362 && x>670 && x<729) //Chemi de fer 8
            {
                if((*player).tech[5] == 1 &&
                   (*player).tech[8] == 0 &&
                   (*player).science_total >= 39 )
                {
                    (*player).tech[8] = 1;
                    (*player).science_total = (*player).science_total - 39;
                    // Ecriture dans les logs //
                    FILE* log = NULL;
                    log = fopen("log.txt", "r+");
                    fseek(log, 0, SEEK_END);
                    fprintf(log, "\t Devellopement des chemins de fer\n");
                    position_curseur = ftell(log);
                    fclose(log);
                    // --------------------- //
                }
            }
            else if(y>195 && y<254 && x>829 && x<888) //Aviation
            {
                if((*player).tech[7] == 1 &&
                   (*player).tech[8] == 1 &&
                   (*player).tech[9] == 0 &&
                   (*player).science_total >= 30 )
                {
                    (*player).tech[9] = 1;
                    (*player).science_total = (*player).science_total - 50;
                    // Ecriture dans les logs //
                    FILE* log = NULL;
                    log = fopen("log.txt", "r+");
                    fseek(log, 0, SEEK_END);
                    fprintf(log, "\t Devellopement de l'aviation\n");
                    position_curseur = ftell(log);
                    fclose(log);
                    // --------------------- //
                }
            }
        }
     }
    goto BALISE;

    }




    SDL_DestroyTexture(texture_back);
    SDL_FreeSurface(image_back);

    SDL_DestroyRenderer(rendu_technologie);
    SDL_DestroyWindow(fenetre_technologie);

}


