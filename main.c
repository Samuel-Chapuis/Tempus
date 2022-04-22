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
#include "lib/color.h"
#include "lib/evenement.h"

#include "lib/test.h"

static int error=-1;

int main(int argc, char **argv)
{

/* Initialisation de la console qui permetra de debugger */

    AllocConsole();
    /// Appuyer sur F10 doit permettre d'afficher la console sinon suprimé la ligne si dessous ///
    ShowWindow(GetConsoleWindow(),SW_HIDE);
    int console = 0;

/*--------------- ---------------*/


    unsigned int hauteur_max=2.9;
    unsigned int coef_aleatoire=1.9;
    unsigned int taille_carte=0;
    unsigned int nb_joeurs=6; /// Peut aller jusqu'a 6 !
    /** IMPORTANT EN FONCTION DU NOMBRE DE JOEUEUR LA GENERATION DE LA CARTE PEUX ECHOUER IL EST DONC TRES FORTEMEN DECONSEILLER
    DE GENERER UNE CARTE D'UNE TAILLE INFERIEUR A 2^3 **/

    taille_carte=5;

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

    fenetre_info_case = SDL_CreateWindow("Info Case", 1.25*carte_x, SDL_WINDOWPOS_CENTERED,225 , 330, SDL_WINDOW_SHOWN | SDL_WINDOW_BORDERLESS);
    rendu_info_case = SDL_CreateRenderer(fenetre_info_case,-1,SDL_RENDERER_ACCELERATED);

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

    generationcarte(carte, taille_carte, coef_aleatoire, hauteur_max, nb_joeurs);
    error = generationposition(carte, taille_carte, coef_aleatoire, hauteur_max,nb_joeurs);
    if(error!=0)
        {
            erreur(error);
            return error;
        }

    graphic_plateau(carte,taille_carte,rendu_carte);


/*--------------- ---------------*/


/* Initialisation des tours */
    joueur* player_tab;
    player_tab=(joueur*)malloc(nb_joeurs*sizeof(joueur));
///Permet de verifier l'allocation si dessus
    if(player_tab == NULL)
    {
        erreur(1001);
        return 1001;
    }

    for(int i=1; i<=nb_joeurs; i++)
    {
        player_tab[i].couleur=i;
        player_tab[i].nb_villes=1;
        player_tab[i].nb_habitants=1;
        player_tab[i].science_total=0;
    }

/*--------------- ---------------*/




    int isrunning = 1;

    console = 0;

    while(isrunning)
    {
        event(&console, carte, fenetre_carte, rendu_info_case);
    }






/* Libération de la mémoire */

    for(int i=0;i<taille_carte;i++)
    {
        free(carte[i]);
    }
    free(carte);

/*--------------- ---------------*/


/* Fin du programe */
    SDL_DestroyRenderer(rendu_carte);
    SDL_DestroyWindow(fenetre_carte);
    SDL_DestroyRenderer(rendu_info_case);
    SDL_DestroyWindow(fenetre_info_case);
    SDL_Quit();

    return 0;
/*--------------- ---------------*/
}




