/* ---- Fonction d'affichage Graphique ----*/

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "../definition.h"

SDL_Texture* graphic_case_fond(bric bk, SDL_Renderer *r)
{
    SDL_Texture* tutur = NULL;
    SDL_Surface* image = NULL;


    if(bk.hauteur>=0&&bk.hauteur<=1)
        image = SDL_LoadBMP("sprite/eau.bmp");
    else if(bk.hauteur>1&&bk.hauteur<=4)
        image = SDL_LoadBMP("sprite/prairie.bmp");
    else if(bk.hauteur>4&&bk.hauteur<=6)
        image = SDL_LoadBMP("sprite/foret.bmp");
    else if(bk.hauteur>6&&bk.hauteur<=8)
        image = SDL_LoadBMP("sprite/colline.bmp");
    else if(bk.hauteur>8)
        image = SDL_LoadBMP("sprite/montagne.bmp");

    tutur = SDL_CreateTextureFromSurface(r,image);
    SDL_FreeSurface(image);

    return tutur;
    SDL_DestroyTexture(tutur);
}

SDL_Texture* graphic_case_ville(bric bk, SDL_Renderer *r)
{
    SDL_Texture* tutur = NULL;
    SDL_Surface* image = NULL;

    switch(bk.ville.joueur)
    {
    case 0:
        {
           //Il ne se passe rien dans ce cas mais je précise le case 0 dans le cas ou il faudrait faire des test d'erreurs
           break;
        }
    case 1:
        {
            image = SDL_LoadBMP("sprite/chateau_violet.bmp");
            break;
        }
    case 2:
        {
            image = SDL_LoadBMP("sprite/chateau_cyan.bmp");
            break;
        }
    case 3:
        {
            image = SDL_LoadBMP("sprite/chateau_rouge.bmp");
            break;
        }
    case 4:
        {
            image = SDL_LoadBMP("sprite/chateau_jaune.bmp");
            break;
        }
    case 5:
        {
            image = SDL_LoadBMP("sprite/chateau_blanc.bmp");
            break;
        }
    case 6:
        {
            image = SDL_LoadBMP("sprite/chateau_bleu.bmp");
            break;
        }
   default:
        {
            break;
        }
    }

    tutur = SDL_CreateTextureFromSurface(r,image);
    SDL_FreeSurface(image);

    return tutur;
    SDL_DestroyTexture(tutur);
}

SDL_Texture* graphic_case_unite(bric bk, SDL_Renderer *r)
{
    SDL_Texture* tutur = NULL;
    SDL_Surface* image = NULL;

    switch(bk.unite.classe)
    {
    case 0:
        {
           //Il ne se passe rien dans ce cas mais je précise le case 0 dans le cas ou il faudrait faire des test d'erreurs
           break;
        }
    case 1:
        {
            switch(bk.unite.joueur)
            {
            case 1:
                {
                    image = SDL_LoadBMP("sprite/villageois_violet.bmp");
                    break;
                }
            case 2:
                {
                    image = SDL_LoadBMP("sprite/villageois_cyan.bmp");
                    break;
                }
            case 3:
                {
                    image = SDL_LoadBMP("sprite/villageois_rouge.bmp");
                    break;
                }
            case 4:
                {
                    image = SDL_LoadBMP("sprite/villageois_jaune.bmp");
                    break;
                }
            case 5:
                {
                    image = SDL_LoadBMP("sprite/villageois_blanc.bmp");
                    break;
                }
            case 6:
                {
                    image = SDL_LoadBMP("sprite/villageois_bleu.bmp");
                    break;
                }
            }
        }
    case 2:
        {
            switch(bk.unite.joueur)
            {
            case 1:
                {
                    image = SDL_LoadBMP("sprite/chevalier_violet.bmp");
                    break;
                }
            case 2:
                {
                    image = SDL_LoadBMP("sprite/chevalier_cyan.bmp");
                    break;
                }
            case 3:
                {
                    image = SDL_LoadBMP("sprite/chevalier_rouge.bmp");
                    break;
                }
            case 4:
                {
                    image = SDL_LoadBMP("sprite/chevalier_jaune.bmp");
                    break;
                }
            case 5:
                {
                    image = SDL_LoadBMP("sprite/chevalier_blanc.bmp");
                    break;
                }
            case 6:
                {
                    image = SDL_LoadBMP("sprite/chevalier_bleu.bmp");
                    break;
                }
            }
        }
   default:
        {
            break;
        }
    }

    tutur = SDL_CreateTextureFromSurface(r,image);
    SDL_FreeSurface(image);

    return tutur;
    SDL_DestroyTexture(tutur);
}

SDL_Texture* graphic_case_bordure(bric bk, SDL_Renderer *r)
{
    SDL_Texture* tutur = NULL;
    SDL_Surface* image = NULL;

    switch(bk.territoire)
    {
    case 0:
        {
           //Il ne se passe rien dans ce cas mais je précise le case 0 dans le cas ou il faudrait faire des test d'erreurs
           break;
        }
    case 1:
        {
            image = SDL_LoadBMP("sprite/bordure_violet.bmp");
            break;
        }
    case 2:
        {
            image = SDL_LoadBMP("sprite/bordure_cyan.bmp");
            break;
        }
    case 3:
        {
            image = SDL_LoadBMP("sprite/bordure_rouge.bmp");
            break;
        }
    case 4:
        {
            image = SDL_LoadBMP("sprite/bordure_jaune.bmp");
            break;
        }
    case 5:
        {
            image = SDL_LoadBMP("sprite/bordure_blanc.bmp");
            break;
        }
    case 6:
        {
            image = SDL_LoadBMP("sprite/bordure_bleu.bmp");
            break;
        }
   default:
        {
            break;
        }
    }
    tutur = SDL_CreateTextureFromSurface(r,image);
    SDL_FreeSurface(image);

    return tutur;
    SDL_DestroyTexture(tutur);
}


void graphic_plateau(bric **carte, int TC, SDL_Renderer *r)
{

    SDL_Texture* fond = NULL;
    SDL_Texture* ville = NULL;
    SDL_Texture* bordure = NULL;
    SDL_Texture* troupe = NULL;

    for(int i=0;i<TC;i++)
    {
        for(int j=0;j<TC;j++)
        {
            fond = graphic_case_fond(carte[i][j],r);
            ville = graphic_case_ville(carte[i][j],r);
            bordure = graphic_case_bordure(carte[i][j],r);
            troupe = graphic_case_unite(carte[i][j],r);

            SDL_Rect dst = {32*i, 32*j, 32, 32};
            SDL_RenderCopy(r, fond, NULL, &dst);
            SDL_RenderCopy(r, ville, NULL, &dst);
            SDL_RenderCopy(r, bordure, NULL, &dst);
            SDL_RenderCopy(r, troupe, NULL, &dst);
            SDL_RenderPresent(r);

        }
    }
    SDL_DestroyTexture(fond);
}

