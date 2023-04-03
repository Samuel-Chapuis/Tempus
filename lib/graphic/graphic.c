/* ---- Fonction d'affichage Graphique ----*/

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "../../definition.h"

//Charge en mémoire l'image du type de la case, exemple une prairie ou une forêt
SDL_Texture* graphic_case_fond(bric bk, SDL_Renderer *r)
{
    SDL_Texture* tutur = NULL;
    SDL_Surface* image = NULL;


    if(bk.hauteur>=0&&bk.hauteur<=1)
        image = SDL_LoadBMP("sprite/case/eau.bmp");
    else if(bk.hauteur>1&&bk.hauteur<=4)
        image = SDL_LoadBMP("sprite/case/prairie.bmp");
    else if(bk.hauteur>4&&bk.hauteur<=6)
        image = SDL_LoadBMP("sprite/case/foret.bmp");
    else if(bk.hauteur>6&&bk.hauteur<=8)
        image = SDL_LoadBMP("sprite/case/colline.bmp");
    else if(bk.hauteur>8)
        image = SDL_LoadBMP("sprite/case/montagne.bmp");
    else if(bk.hauteur==-1)
        image = SDL_LoadBMP("sprite/case/champ.bmp");

    tutur = SDL_CreateTextureFromSurface(r,image);
    SDL_FreeSurface(image);

    return tutur;
    SDL_DestroyTexture(tutur);
}

//Charge en mémoire l'image de la ville de la couleur du joueur
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
            image = SDL_LoadBMP("sprite/chateau/chateau_violet.bmp");
            break;
        }
    case 2:
        {
            image = SDL_LoadBMP("sprite/chateau/chateau_cyan.bmp");
            break;
        }
    case 3:
        {
            image = SDL_LoadBMP("sprite/chateau/chateau_rouge.bmp");
            break;
        }
    case 4:
        {
            image = SDL_LoadBMP("sprite/chateau/chateau_jaune.bmp");
            break;
        }
    case 5:
        {
            image = SDL_LoadBMP("sprite/chateau/chateau_blanc.bmp");
            break;
        }
    case 6:
        {
            image = SDL_LoadBMP("sprite/chateau/chateau_bleu.bmp");
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

//Charge en mémoire l'image de l'unité dans la case de la couleur du joueur
SDL_Texture* graphic_case_unite(bric bk, SDL_Renderer *r)
{
    SDL_Texture* tutur = NULL;
    SDL_Surface* image = NULL;

    switch(bk.unite.classe)
    {
    case 0:
        //Il ne se passe rien dans ce cas mais je précise le case 0 dans le cas ou il faudrait faire des test d'erreurs
        break;
    case 1:
            switch(bk.unite.joueur)
            {
            case 1:
                {
                    image = SDL_LoadBMP("sprite/personage/villageois_violet.bmp");
                    break;

                }
            case 2:
                {
                    image = SDL_LoadBMP("sprite/personage/villageois_cyan.bmp");
                    break;
                }
            case 3:
                {
                    image = SDL_LoadBMP("sprite/personage/villageois_rouge.bmp");
                    break;
                }
            case 4:
                {
                    image = SDL_LoadBMP("sprite/personage/villageois_jaune.bmp");
                    break;
                }
            case 5:
                {
                    image = SDL_LoadBMP("sprite/personage/villageois_blanc.bmp");
                    break;
                }
            case 6:
                {
                    image = SDL_LoadBMP("sprite/personage/villageois_bleu.bmp");
                    break;
                }
            }
        break;
    case 2:
            switch(bk.unite.joueur)
            {
            case 1:
                {
                    image = SDL_LoadBMP("sprite/personage/chevalier_violet.bmp");
                    break;
                }
            case 2:
                {
                    image = SDL_LoadBMP("sprite/personage/chevalier_cyan.bmp");
                    break;
                }
            case 3:
                {
                    image = SDL_LoadBMP("sprite/personage/chevalier_rouge.bmp");
                    break;
                }
            case 4:
                {
                    image = SDL_LoadBMP("sprite/personage/chevalier_jaune.bmp");
                    break;
                }
            case 5:
                {
                    image = SDL_LoadBMP("sprite/personage/chevalier_blanc.bmp");
                    break;
                }
            case 6:
                {
                    image = SDL_LoadBMP("sprite/personage/chevalier_bleu.bmp");
                    break;
                }
            }
        break;
    case 3:
            switch(bk.unite.joueur)
            {
            case 1:
                {
                    image = SDL_LoadBMP("sprite/personage/bateau_violet.bmp");
                    break;
                }
            case 2:
                {
                    image = SDL_LoadBMP("sprite/personage/bateau_cyan.bmp");
                    break;
                }
            case 3:
                {
                    image = SDL_LoadBMP("sprite/personage/bateau_rouge.bmp");
                    break;
                }
            case 4:
                {
                    image = SDL_LoadBMP("sprite/personage/bateau_jaune.bmp");
                    break;
                }
            case 5:
                {
                    image = SDL_LoadBMP("sprite/personage/bateau_blanc.bmp");
                    break;
                }
            case 6:
                {
                    image = SDL_LoadBMP("sprite/personage/bateau_bleu.bmp");
                    break;
                }
            }
        break;
    case 4:
            switch(bk.unite.joueur)
            {
            case 1:
                {
                    image = SDL_LoadBMP("sprite/personage/bateau_civil_violet.bmp");
                    break;
                }
            case 2:
                {
                    image = SDL_LoadBMP("sprite/personage/bateau_civil_cyan.bmp");
                    break;
                }
            case 3:
                {
                    image = SDL_LoadBMP("sprite/personage/bateau_civil_rouge.bmp");
                    break;
                }
            case 4:
                {
                    image = SDL_LoadBMP("sprite/personage/bateau_civil_jaune.bmp");
                    break;
                }
            case 5:
                {
                    image = SDL_LoadBMP("sprite/personage/bateau_civil_blanc.bmp");
                    break;
                }
            case 6:
                {
                    image = SDL_LoadBMP("sprite/personage/bateau_civil_bleu.bmp");
                    break;
                }
            }
        break;
   default:
       {
           printf("erreur graphic case");
       }
        break;
    }

    tutur = SDL_CreateTextureFromSurface(r,image);
    SDL_FreeSurface(image);

    return tutur;
    SDL_DestroyTexture(tutur);
}

//Charge en mémoire l'image du territoire de la case de la couleur du joueur
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
            image = SDL_LoadBMP("sprite/bordure/bordure_violet.bmp");
            break;
        }
    case 2:
        {
            image = SDL_LoadBMP("sprite/bordure/bordure_cyan.bmp");
            break;
        }
    case 3:
        {
            image = SDL_LoadBMP("sprite/bordure/bordure_rouge.bmp");
            break;
        }
    case 4:
        {
            image = SDL_LoadBMP("sprite/bordure/bordure_jaune.bmp");
            break;
        }
    case 5:
        {
            image = SDL_LoadBMP("sprite/bordure/bordure_blanc.bmp");
            break;
        }
    case 6:
        {
            image = SDL_LoadBMP("sprite/bordure/bordure_bleu.bmp");
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

//Affiche les images charger en mémoire sur une case
void graphic_case(bric **carte, int x, int y, SDL_Renderer *r)
{
    SDL_Texture* fond = NULL;
    SDL_Texture* ville = NULL;
    SDL_Texture* bordure = NULL;
    SDL_Texture* troupe = NULL;

    fond = graphic_case_fond(carte[x][y],r);
    ville = graphic_case_ville(carte[x][y],r);
    bordure = graphic_case_bordure(carte[x][y],r);
    troupe = graphic_case_unite(carte[x][y],r);

    SDL_Rect dst = {32*x, 32*y, 32, 32};
    SDL_RenderCopy(r, fond, NULL, &dst);
    SDL_RenderCopy(r, ville, NULL, &dst);
    SDL_RenderCopy(r, bordure, NULL, &dst);
    SDL_RenderCopy(r, troupe, NULL, &dst);
    SDL_RenderPresent(r);

    SDL_DestroyTexture(fond);
    SDL_DestroyTexture(ville);
    SDL_DestroyTexture(bordure);
    SDL_DestroyTexture(troupe);
}

//Affiche le plateau dans son intégralité
void graphic_plateau(bric **carte, int TC, SDL_Renderer *r)
{

    SDL_Texture* fond = NULL;
    SDL_Texture* ville = NULL;
    SDL_Texture* bordure = NULL;
    SDL_Texture* troupe = NULL;

    for(int i=0;i<TC;i++)
    {
        for(int j=0;j<TC*0.75;j++) // Pour la carte est bien un rapport de 3/4 on tronque 1/4 du bas de la carte initialement carré:
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
    SDL_DestroyTexture(ville);
    SDL_DestroyTexture(bordure);
    SDL_DestroyTexture(troupe);
}

