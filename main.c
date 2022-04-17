/*
--------- Projet 1er année ---------

 Createurs: Romane Boudet et Samuel Chapuis

--------- ----------------- ---------
*/


#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <math.h>
#include <dos.h>
#include <SDL2/SDL.h>


/* ------- Déclaration des sous programmes ------- */
#include "lib/generation.h"
#include "definition.h"
#include "lib/graphic.h"
#include "lib/erreur.h"

static int error=-1;



int main(int argc, char **argv)
{
    unsigned int hauteur_max=2.9;
    unsigned int coef_aleatoire=1.9;
    unsigned int taille_carte=0;
    unsigned int nb_joeurs=4; /// Peut aller jusqu'a 6 !
    /** IMPORTANT EN FONCTION DU NOMBRE DE JOEUEUR LA GENERATION DE LA CARTE PEUX ECHOUER IL EST DONC TRES FORTEMEN DECONSEILLER
    DE GENERER UNE CARTE D'UNE TAILLE INFERIEUR A 2^3 **/

    hauteur_max=2.9;
    coef_aleatoire=1.9;
    taille_carte=5;

    AllocConsole();
 
/* Initialisation de la fenètres de debuging */

    SDL_Window* fenetre_debug = NULL;
    SDL_Renderer* rendu_debug = NULL;

    fenetre_debug = SDL_CreateWindow("debug", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 400, SDL_WINDOW_SHOWN /*| SDL_WINDOW_RESIZABLE */);
    rendu_debug = SDL_CreateRenderer(fenetre_debug,-1,SDL_RENDERER_ACCELERATED);

    SDL_Surface* icone_debug = NULL;
    icone_debug = SDL_LoadBMP("sprite/bug.bmp");
    SDL_SetWindowIcon(fenetre_debug, icone_debug);
    SDL_FreeSurface(icone_debug);

/*--------------- ---------------*/


/* Defition du nombre de joueurs et de la taille de la carte relativement à ça */


/*--------------- ---------------*/


/* Initialisation des fenètres de jeux */

    int carte_x = 1055;
    int carte_y = 800;

    SDL_Window* fenetre_carte = NULL;
    SDL_Renderer* rendu_carte = NULL;

    fenetre_carte = SDL_CreateWindow("TEMPUS", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, carte_x, carte_y, SDL_WINDOW_SHOWN /*| SDL_WINDOW_RESIZABLE */);
    rendu_carte = SDL_CreateRenderer(fenetre_carte,-1,SDL_RENDERER_ACCELERATED);

    SDL_Surface* icone_carte = NULL;
    icone_carte = SDL_LoadBMP("sprite/chevalier_rouge.bmp");
    SDL_SetWindowIcon(fenetre_carte, icone_carte);
    SDL_FreeSurface(icone_carte);


    SDL_Window* fenetre_info_case = NULL;
    SDL_Renderer* rendu_info_case = NULL;

    fenetre_info_case = SDL_CreateWindow("Info Case", 1.45*carte_x, SDL_WINDOWPOS_CENTERED,200 , 800, SDL_WINDOW_SHOWN /*| SDL_WINDOW_RESIZABLE */);
    rendu_info_case = SDL_CreateRenderer(fenetre_info_case,-1,SDL_RENDERER_ACCELERATED);

    SDL_Surface* icone_info_case = NULL;
    icone_info_case = SDL_LoadBMP("sprite/parchemin.bmp");
    SDL_SetWindowIcon(fenetre_info_case, icone_info_case);
    SDL_FreeSurface(icone_case);


/*--------------- ---------------*/





/* Definition des valeurs des objets relative au paramèter de la partie */

    coef_aleatoire=coef_aleatoire*(pow(2,taille_carte)+1)/2;
    hauteur_max=hauteur_max*(pow(2,taille_carte)+1)/2;
    taille_carte=pow(2,taille_carte)+1;
/*--------------- ---------------*/


/* Création de la carte et allocution de la mémoire */

    bric** carte; //creer un double pointeur carte
    carte=(bric**)malloc(taille_carte*sizeof(bric*)); //définit un tableau de pointeur de taille "sizeof(bric)*taille_carte" subdivisé en "bric".
    for(int i=0;i<taille_carte;i++)
    {
        carte[i]=(bric*)malloc(taille_carte*sizeof(bric)); //définit un tableau de 1 dim de taille "sizeof(bric)*taille_carte" subdivisé en "bric".
    }
    //Les deux lignes précedente permettent de definire la carte sous la forme d'un tableau a deux dimensions
/*--------------- ---------------*/


/* Initialisation des joeurs */


/*--------------- ---------------*/


/* Initialisation du plateau de jeu */

    generationcarte(carte,taille_carte,coef_aleatoire,hauteur_max,nb_joeurs);
    error = generationposition(carte,taille_carte,coef_aleatoire,hauteur_max,nb_joeurs);
    if(error!=0)
        {
            erreur(error);
            return error;
        }

    graphic_plateau(carte,taille_carte,rendu_carte);


/*--------------- ---------------*/


/* Initialisation des tours */

    joueur player_tab[nb_joeurs];
    for(int i=1; i<=nb_joeurs; i++)
    {
        player_tab[i].couleur=i;
    }

/*--------------- ---------------*/

    int isrunning = 1;
    SDL_Event ev;
    while(isrunning)
    {
        while(SDL_PollEvent(&ev) != 0);
        {
            if(ev.type == SDL_QUIT)
            isrunning = 0;
            else if (ev.type == SDL_KEYDOWN)
            {
                switch(ev.key.keysym.sym)
                {
                case SDLK_F11:
                    return 0;
                    break;
                case SDLK_z:
                    SDL_Delay(500);
                    break;
                }
            }
        }
    }






/* Libération de la mémoire */

    for(int i=0;i<taille_carte;i++)
    {
        free(carte[i]);
    }
    free(carte);

/*--------------- ---------------*/


    SDL_Event event;
    SDL_WaitEvent(&event);
    SDL_bool continuer = SDL_FALSE;
    while(continuer)
    {
        SDL_WaitEvent(&event);
        if(event.type == SDL_QUIT)
            continuer = SDL_FALSE;
        if(event.type == SDL_KEYDOWN)
            printf("appui sur une touche");
    }

/* Fin du programe */
    SDL_DestroyRenderer(rendu_debug);
    SDL_DestroyWindow(fenetre_debug);
    SDL_DestroyRenderer(rendu_carte);
    SDL_DestroyWindow(fenetre_carte);
    SDL_DestroyRenderer(rendu_case);
    SDL_DestroyWindow(fenetre_case);
    SDL_Quit();


    return 0;
/*--------------- ---------------*/
}




