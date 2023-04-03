/* ---- Fonction de gestion de la Fin de la Partie ----*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "../../definition.h"

void fin_partie(SDL_Window* fenetre_carte, SDL_Window* fenetre_info_case, int nb, joueur* player_tab, int couleur)
{
    SDL_HideWindow(fenetre_carte);
    SDL_HideWindow(fenetre_info_case);

    // Ecriture dans les logs //
    FILE* log = NULL;
    log = fopen("log.txt", "r+");
    fseek(log, 0, SEEK_END);
    fprintf(log, "\n\n !! Victoire du joueur %d !!", couleur);
    position_curseur = ftell(log);
    fclose(log);
    // --------------------- //

    int curseur = -1;
    int gagnant = -1;

    player_tab[couleur].pop = player_tab[couleur].pop + 10;


    for(int i = 1; i <= nb; i++)
    {
        if(curseur < player_tab[i].pop)
        {
            gagnant = i;
            curseur = player_tab[i].pop;
        }
    }

    TTF_Init();
    TTF_Font* font = TTF_OpenFont("sprite/Austein.ttf", 50);

    SDL_Window* fenetre = NULL;
    SDL_Renderer* rendu = NULL;

    fenetre = SDL_CreateWindow("TEMPUS", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800, SDL_WINDOW_SHOWN | SDL_WINDOW_BORDERLESS );
    rendu = SDL_CreateRenderer(fenetre,-1,SDL_RENDERER_ACCELERATED);

    SDL_Texture* texture_back = NULL;
    SDL_Surface* image_back = NULL;

    SDL_Texture* texture_explosion = NULL;
    SDL_Surface* image_explosion = NULL;

    SDL_Texture* texture = NULL;
    SDL_Surface* text = NULL;

    SDL_Color Violet = {203, 128, 213};
    SDL_Color Cyan = {145, 241, 244};
    SDL_Color Rouge = {255, 59, 59};
    SDL_Color Jaune = {250, 250, 106};
    SDL_Color Blanc = {255, 255, 255};
    SDL_Color Bleu = {53, 68, 178};

    SDL_Rect dst_text = {150, 250, 500, 156};

    char winner[7];
    char adresse[40];



    for(int i = 1; i <= 8; i++)
    {
        image_back = SDL_LoadBMP("sprite/victoire/victoire.bmp");
        texture_back = SDL_CreateTextureFromSurface(rendu,image_back);
        SDL_Rect dst_back = {0, 0, 800, 800};
        SDL_RenderCopy(rendu, texture_back, NULL, &dst_back);




        switch(gagnant)
        {
        case 1:
            sprintf(winner,"Violet");
            text = TTF_RenderText_Solid(font, winner, Violet);
            texture = SDL_CreateTextureFromSurface(rendu, text);
            SDL_RenderCopy(rendu, texture, NULL, &dst_text);
            break;
        case 2:
            sprintf(winner,"Cyan");
            text = TTF_RenderText_Solid(font, winner, Cyan);
            texture = SDL_CreateTextureFromSurface(rendu, text);
            SDL_RenderCopy(rendu, texture, NULL, &dst_text);
            break;
        case 3:
            sprintf(winner,"Rouge");
            text = TTF_RenderText_Solid(font, winner, Rouge);
            texture = SDL_CreateTextureFromSurface(rendu, text);
            SDL_RenderCopy(rendu, texture, NULL, &dst_text);
            break;
        case 4:
            sprintf(winner,"Jaune");
            text = TTF_RenderText_Solid(font, winner, Jaune);
            texture = SDL_CreateTextureFromSurface(rendu, text);
            SDL_RenderCopy(rendu, texture, NULL, &dst_text);
            break;
        case 5:
            sprintf(winner,"Blanc");
            text = TTF_RenderText_Solid(font, winner, Blanc);
            texture = SDL_CreateTextureFromSurface(rendu, text);
            SDL_RenderCopy(rendu, texture, NULL, &dst_text);
            break;
        case 6:
            sprintf(winner,"Bleu");
            text = TTF_RenderText_Solid(font, winner, Bleu);
            texture = SDL_CreateTextureFromSurface(rendu, text);
            SDL_RenderCopy(rendu, texture, NULL, &dst_text);
            break;
        }
    //Explosion
        sprintf(adresse, "sprite/victoire/e%d.bmp",i);
        image_explosion = SDL_LoadBMP(adresse);
        texture_explosion = SDL_CreateTextureFromSurface(rendu,image_explosion);
        SDL_RenderCopy(rendu, texture_explosion, NULL, &dst_back);

        SDL_RenderPresent(rendu);

        SDL_Delay(150);
    }

    SDL_Delay(10000);
    TTF_Quit();



}
