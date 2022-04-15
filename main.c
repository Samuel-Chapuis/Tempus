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
#include "lib/color.h"
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

    SDL_Window* fennetre = NULL;
    SDL_Renderer* rendu = NULL;


    fennetre = SDL_CreateWindow("TestWidow", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,542, 542, SDL_WINDOW_SHOWN);
    rendu = SDL_CreateRenderer(fennetre,-1,SDL_RENDERER_ACCELERATED);


    hauteur_max=2.9;
    coef_aleatoire=1.9;
    taille_carte=4;

/* Defition du nombre de joueurs et de la taille de la carte relativement à ça */


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

    graphic_plateau(carte,taille_carte,rendu);


/*--------------- ---------------*/


/* Initialisation des tours */

    joueur player_tab[nb_joeurs];
    for(int i=1; i<=nb_joeurs; i++)
    {
        player_tab[i].couleur=i;
    }

/*--------------- ---------------*/








/* Libération de la mémoire */

    for(int i=0;i<taille_carte;i++)
    {
        free(carte[i]);
    }
    free(carte);

/*--------------- ---------------*/

    SDL_Delay(50000);

/* Fin du programe */

    SDL_DestroyRenderer(rendu);
    SDL_DestroyWindow(fennetre);
    SDL_Quit();

    return 0;
/*--------------- ---------------*/
}




