/* ---- Fonction d'affichage de l'info bulle ----*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "graphic.h"
#include "../../definition.h"

void info_bulle(bric** carte, joueur player, SDL_Renderer* rendu_info_case, int* x, int* y)
{
//Déclatation

    SDL_Color Black = {0, 0, 0};
    SDL_Color Blue = {0, 153, 203};

    TTF_Init();
    TTF_Font* font = TTF_OpenFont("sprite/Austein.ttf", 50);
// -------------- //

//Image de fond

    SDL_Texture* texture_back = NULL;
    SDL_Surface* image_back = NULL;

    image_back = SDL_LoadBMP("sprite/info_bulle/info_carte.bmp");
    texture_back = SDL_CreateTextureFromSurface(rendu_info_case,image_back);
    SDL_Rect dst = {0, 0, 225, 330};
    SDL_RenderCopy(rendu_info_case, texture_back, NULL, &dst);
// -------------- //

//Couleur de joueur

    SDL_Texture* texture_banniere = NULL;
    SDL_Surface* image_banniere = NULL;
    switch(player.couleur)
    {
    case 1:
        image_banniere = SDL_LoadBMP("sprite/info_bulle/banniere/Banniere1.bmp");
        break;

    case 2:
        image_banniere = SDL_LoadBMP("sprite/info_bulle/banniere/Banniere2.bmp");
        break;

    case 3:
        image_banniere = SDL_LoadBMP("sprite/info_bulle/banniere/Banniere3.bmp");
        break;

    case 4:
        image_banniere = SDL_LoadBMP("sprite/info_bulle/banniere/Banniere4.bmp");
        break;

    case 5:
        image_banniere = SDL_LoadBMP("sprite/info_bulle/banniere/Banniere5.bmp");
        break;

    case 6:
        image_banniere = SDL_LoadBMP("sprite/info_bulle/banniere/Banniere6.bmp");
        break;
    }
    SDL_Rect dst_banniere = {18, 70, 189, 16};
    texture_banniere = SDL_CreateTextureFromSurface(rendu_info_case,image_banniere);
    SDL_RenderCopy(rendu_info_case, texture_banniere, NULL, &dst_banniere);

    SDL_DestroyTexture(texture_banniere);
    SDL_FreeSurface(image_banniere);
// -------------- //


//Science du joueur

    char science[3];
    sprintf(science,"%d",player.science_total);

    SDL_Surface* image_text_science = TTF_RenderText_Solid(font, science, Blue);
    SDL_Texture* texture_text_science = SDL_CreateTextureFromSurface(rendu_info_case, image_text_science);
    SDL_Rect dst_test_science = {35, 205, 32, 32};
    SDL_RenderCopy(rendu_info_case, texture_text_science, NULL, &dst_test_science);
// -------------- //


//Population du joueur

    char population[3];
    sprintf(population,"%d",player.pop);

    SDL_Surface* image_text_population = TTF_RenderText_Solid(font, population, Black);
    SDL_Texture* texture_text_population = SDL_CreateTextureFromSurface(rendu_info_case, image_text_population);
    SDL_Rect dst_test_population = {100, 250, 32, 32};
    SDL_RenderCopy(rendu_info_case, texture_text_population, NULL, &dst_test_population);
// -------------- //


//Image issus de la carte

    SDL_Texture* fond = NULL;
    SDL_Texture* ville = NULL;
    SDL_Texture* troupe = NULL;

    fond = graphic_case_fond(carte[*x][*y], rendu_info_case);
    ville = graphic_case_ville(carte[*x][*y], rendu_info_case);
// -------------- //


//gestion des evenement lorsqu'il y'a une ville sur la case selectionné
    if(ville != NULL)
    {
        //affiche si la ville peut generé un villageois à ce tour
        if(carte[*x][*y].ville.gen == 1)
        {
            SDL_Texture* texture_habitant = NULL;
            SDL_Surface* image_habitant = NULL;

            image_habitant = SDL_LoadBMP("sprite/info_bulle/habitant.bmp");
            texture_habitant = SDL_CreateTextureFromSurface(rendu_info_case,image_habitant);
            SDL_Rect dst_habitant = {100, 150, 32, 32};
            SDL_RenderCopy(rendu_info_case, texture_habitant, NULL, &dst_habitant);

            SDL_FreeSurface(image_habitant);
            SDL_DestroyTexture(texture_habitant);
        }

        //affiche le nombre d'habitant de la ville
        char habitants[3];
        sprintf(habitants,"%.2d",carte[*x][*y].ville.habitants);

        SDL_Surface* image_text_habitant = TTF_RenderText_Solid(font, habitants, Black);
        SDL_Texture* texture_text_habitant = SDL_CreateTextureFromSurface(rendu_info_case, image_text_habitant);
        SDL_Rect dst_test_habitant = {144, 155, 32, 32};
        SDL_RenderCopy(rendu_info_case, texture_text_habitant, NULL, &dst_test_habitant);

        SDL_FreeSurface(image_text_habitant);
        SDL_DestroyTexture(texture_text_habitant);
    }
// -------------- //


//Gestion des evenement lorsqu'il y'a une troupe sur la case selectionné

    troupe = graphic_case_unite(carte[*x][*y], rendu_info_case);
    if(troupe != NULL )
    {
        SDL_Texture* texture_deplacement = NULL;
        SDL_Surface* image_deplacement = NULL;
        SDL_Rect dst_deplacement = {120, 150, 32, 32};
        if(carte[*x][*y].unite.deplacement == 1) //Affiche si l'unité peut se déplacer ou non
            image_deplacement = SDL_LoadBMP("sprite/info_bulle/deplacement1.bmp");
        else
            image_deplacement = SDL_LoadBMP("sprite/info_bulle/deplacement0.bmp");
        texture_deplacement = SDL_CreateTextureFromSurface(rendu_info_case,image_deplacement);
        SDL_RenderCopy(rendu_info_case, texture_deplacement, NULL, &dst_deplacement);
        SDL_FreeSurface(image_deplacement);
        SDL_DestroyTexture(texture_deplacement);
    }

    SDL_Rect dst_fond = {100, 100, 32, 32};
    SDL_Rect dst_troupe = {80, 150, 32, 32};
    SDL_Rect dst_ville = {60, 150, 32, 32};

    SDL_RenderCopy(rendu_info_case, fond, NULL, &dst_fond);
    SDL_RenderCopy(rendu_info_case, ville, NULL, &dst_ville);
    SDL_RenderCopy(rendu_info_case, troupe, NULL, &dst_troupe);
// -------------- //



    TTF_Quit();
    SDL_RenderPresent(rendu_info_case);

    SDL_FreeSurface(image_back);
    SDL_DestroyTexture(texture_back);
    SDL_DestroyTexture(fond);
    SDL_DestroyTexture(ville);
    SDL_DestroyTexture(troupe);
}
