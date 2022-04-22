#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "graphic.h"
#include "../definition.h"

void info_bulle(bric** carte, SDL_Renderer* rendu_info_case, int* x, int* y)
{
    SDL_Texture* texture_back = NULL;
    SDL_Surface* image_back = NULL;

    image_back = SDL_LoadBMP("sprite/info_carte.bmp");
    texture_back = SDL_CreateTextureFromSurface(rendu_info_case,image_back);
    SDL_Rect dst = {0, 0, 225, 330};
    SDL_RenderCopy(rendu_info_case, texture_back, NULL, &dst);


    SDL_Texture* fond = NULL;
    SDL_Texture* ville = NULL;
    SDL_Texture* troupe = NULL;

    fond = graphic_case_fond(carte[*x/32][*y/32], rendu_info_case);
    ville = graphic_case_ville(carte[*x/32][*y/32], rendu_info_case);
    if(ville != NULL)
    {
        if(carte[*x/32][*y/32].ville.gen == 1)
        {
            SDL_Texture* texture_habitant = NULL;
            SDL_Surface* image_habitant = NULL;

            image_habitant = SDL_LoadBMP("sprite/habitant.bmp");
            texture_habitant = SDL_CreateTextureFromSurface(rendu_info_case,image_habitant);
            SDL_Rect dst_habitant = {100, 200, 32, 32};
            SDL_RenderCopy(rendu_info_case, texture_habitant, NULL, &dst_habitant);

            SDL_FreeSurface(image_habitant);
            SDL_DestroyTexture(texture_habitant);
        }

        SDL_Surface* image_unite = NULL;
        SDL_Texture* texture_unite = NULL;
        SDL_Surface* image_dizaine = NULL;
        SDL_Texture* texture_dizaine = NULL;
        int unite = carte[*x/32][*y/32].ville.habitants%10;
        int dizaine = carte[*x/32][*y/32].ville.habitants/10;

        switch(unite)
        {
            case 0:
            {
                image_unite = SDL_LoadBMP("sprite/nombres/0.bmp");
                break;
            }
            case 1:
            {
                image_unite = SDL_LoadBMP("sprite/nombres/1.bmp");
                break;
            }
            case 2:
            {
                image_unite = SDL_LoadBMP("sprite/nombres/2.bmp");
                break;
            }
            case 3:
            {
                image_unite = SDL_LoadBMP("sprite/nombres/3.bmp");
                break;
            }
            case 4:
            {
                image_unite = SDL_LoadBMP("sprite/nombres/4.bmp");
                break;
            }
            case 5:
            {
                image_unite = SDL_LoadBMP("sprite/nombres/5.bmp");
                break;
            }
            case 6:
            {
                image_unite = SDL_LoadBMP("sprite/nombres/6.bmp");
                break;
            }
            case 7:
            {
                image_unite = SDL_LoadBMP("sprite/nombres/7.bmp");
                break;
            }
            case 8:
            {
                image_unite = SDL_LoadBMP("sprite/nombres/8.bmp");
                break;
            }
            case 9:
            {
                image_unite = SDL_LoadBMP("sprite/nombres/9.bmp");
                break;
            }
        }
//        texture_unite = SDL_CreateTextureFromSurface(rendu_info_case, image_unite);
//        SDL_Rect dst_unite = {164, 200, 32, 32};
//        SDL_RenderCopy(rendu_info_case, texture_unite, NULL, &dst_unite);
//        SDL_FreeSurface(image_unite);
//        SDL_DestroyTexture(texture_unite);


        switch(dizaine)
        {
            case 0:
            {
                //image_dizaine = SDL_LoadBMP("sprite/nombres/0.bmp");
                break;
            }
            case 1:
            {
                image_dizaine = SDL_LoadBMP("sprite/nombres/1.bmp");
                break;
            }
            case 2:
            {
                image_dizaine = SDL_LoadBMP("sprite/nombres/2.bmp");
                break;
            }
            case 3:
            {
                image_dizaine = SDL_LoadBMP("sprite/nombres/3.bmp");
                break;
            }
            case 4:
            {
                image_dizaine = SDL_LoadBMP("sprite/nombres/4.bmp");
                break;
            }
            case 5:
            {
                image_dizaine = SDL_LoadBMP("sprite/nombres/5.bmp");
                break;
            }
            case 6:
            {
                image_dizaine = SDL_LoadBMP("sprite/nombres/6.bmp");
                break;
            }
            case 7:
            {
                image_dizaine = SDL_LoadBMP("sprite/nombres/7.bmp");
                break;
            }
            case 8:
            {
                image_dizaine = SDL_LoadBMP("sprite/nombres/8.bmp");
                break;
            }
            case 9:
            {
                image_dizaine = SDL_LoadBMP("sprite/nombres/9.bmp");
                break;
            }
        }

        texture_dizaine = SDL_CreateTextureFromSurface(rendu_info_case, image_dizaine);
        SDL_Rect dst_dizaine = {132, 200, 32, 32};
        SDL_RenderCopy(rendu_info_case, texture_dizaine, NULL, &dst_dizaine);
        SDL_FreeSurface(image_dizaine);
        SDL_DestroyTexture(texture_dizaine);

        texture_unite = SDL_CreateTextureFromSurface(rendu_info_case, image_unite);
        SDL_Rect dst_unite = {164, 200, 32, 32};
        if(texture_dizaine != NULL )
            SDL_RenderCopy(rendu_info_case, texture_unite, NULL, &dst_unite);
        else
            SDL_RenderCopy(rendu_info_case, texture_unite, NULL, &dst_dizaine);
        SDL_FreeSurface(image_unite);
        SDL_DestroyTexture(texture_unite);

    }

    troupe = graphic_case_unite(carte[*x/32][*y/32], rendu_info_case);
    if(troupe != NULL )
    {
        SDL_Texture* texture_deplacement = NULL;
        SDL_Surface* image_deplacement = NULL;
        SDL_Rect dst_deplacement = {120, 150, 32, 32};
        if(carte[*x/32][*y/32].unite.pm == 1)
            image_deplacement = SDL_LoadBMP("sprite/deplacement1.bmp");
        else
            image_deplacement = SDL_LoadBMP("sprite/deplacement1.bmp");
        texture_deplacement = SDL_CreateTextureFromSurface(rendu_info_case,image_deplacement);
        SDL_RenderCopy(rendu_info_case, texture_deplacement, NULL, &dst_deplacement);
        SDL_FreeSurface(image_deplacement);
        SDL_DestroyTexture(texture_deplacement);
    }

    SDL_Rect dst_fond = {100, 100, 32, 32};
    SDL_Rect dst_troupe = {80, 150, 32, 32};
    SDL_Rect dst_ville = {60, 200, 32, 32};

    SDL_RenderCopy(rendu_info_case, fond, NULL, &dst_fond);
    SDL_RenderCopy(rendu_info_case, ville, NULL, &dst_ville);
    SDL_RenderCopy(rendu_info_case, troupe, NULL, &dst_troupe);

    SDL_RenderPresent(rendu_info_case);

    SDL_FreeSurface(image_back);
    SDL_DestroyTexture(texture_back);
    SDL_DestroyTexture(fond);
    SDL_DestroyTexture(ville);
    SDL_DestroyTexture(troupe);
}
