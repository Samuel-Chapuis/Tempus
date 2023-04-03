/*
--------- Projet 1er année ---------

 Nom du projet : Tempus
 Createurs: Romane Boudet et Samuel Chapuis
 Dernière mis à jour le 11/05/2022

--------- ----------------- ---------
*/


#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <dos.h>
#include <SDL2/SDL.h>


/* ------- Déclaration des sous libs ------- */
#include "lib/initialisaiton/generation.h"
#include "definition.h"
#include "lib/graphic/graphic.h"
#include "lib/graphic/color.h"
#include "lib/gestion_tour/evenement.h"
#include "lib/graphic/mise_a_jour_de_la_carte.h"
#include "lib/gestion_tour/deplacement.h"
#include "lib/gestion_tour/fin_de_partie.h"


int main(int argc, char **argv)
{

/* Initialisation de la console qui permettra de debugger */

    AllocConsole();
    /// Appuyer sur F10 doit permettre d'afficher la console sinon suprimé la ligne si dessous ///
    ShowWindow(GetConsoleWindow(),SW_HIDE);
    int console = 0;

/*--------------- ---------------*/




/* Generation d'un fichier log.txt qui permettra de debugger */

    FILE* log = NULL;

    log = fopen("log.txt", "w+");
    if(log != NULL)
        fprintf(log, "Le Fichier log a été créé avec succès\n");
    else
    {
        fprintf(log, "FATAL ERROR : Les logs ne se sont pas créés\n");
        return -1;
    }
    fclose(log);

/*--------------- ---------------*/






/* Déclaration de toute les variables */

    unsigned int hauteur_max=2.9;
    unsigned int coef_aleatoire=1.9;
    unsigned int taille_carte=0;
    unsigned int nb_joueurs=4; /// Peut aller jusqu'a 6 !
    /** IMPORTANT EN FONCTION DU NOMBRE DE JOEUEUR LA GENERATION DE LA CARTE PEUX ECHOUER IL EST DONC TRES FORTEMEN DECONSEILLER
    DE GENERER UNE CARTE D'UNE TAILLE INFERIEUR A 2^3 **/

    taille_carte=5; // aurait pu être modifié via un menu


    //initialisation des fenètres
    int carte_x = 1055;
    int carte_y = 800;

    SDL_Window* fenetre_carte = NULL;
    SDL_Renderer* rendu_carte = NULL;
    SDL_Surface* icone_carte = NULL;

    SDL_Window* fenetre_info_case = NULL;
    SDL_Renderer* rendu_info_case = NULL;

    //création de la carte
    bric** carte;

    //création du tableau de joueurs
    joueur* player_tab = NULL;

    //gestion de la partie
    int end = 0;
    int tour_du_joueur = 1;
    int fin_tour = 0;

    //pointeur position souris
    int* xg = NULL;
    int* yg = NULL;
    int je_sais_pas_pourquoi_j_ai_besoin_de_mettre_ca_mais_sinon_ca_crash = 0;
    int si_je_ne_met_pas_ce_truc_un_peu_etrange_ca_crash = 0;
    xg = &je_sais_pas_pourquoi_j_ai_besoin_de_mettre_ca_mais_sinon_ca_crash;
    yg = &si_je_ne_met_pas_ce_truc_un_peu_etrange_ca_crash;





/* Definition du nombre de joueurs et de la taille de la carte via un menu */

    ///N'était pas necessairement à implémenter mais ça aurait pu être interessant
    ///Cela aurait pu aussi implémenter un système de sauvegarde

/*--------------- ---------------*/


/* Definition des valeurs des objets relative au paramèter de la partie */

    coef_aleatoire=coef_aleatoire*(pow(2,taille_carte)+1)/2; //Coefficient qui l'aléatoire du relief de la carte
    hauteur_max=hauteur_max*(pow(2,taille_carte)+1)/2;
    taille_carte=pow(2,taille_carte)+1;

/*--------------- ---------------*/



/* Initialisation des fenètres de jeux */

//fenetre principale
    fenetre_carte = SDL_CreateWindow("TEMPUS", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, carte_x, carte_y, SDL_WINDOW_SHOWN /*| SDL_WINDOW_RESIZABLE */);
    rendu_carte = SDL_CreateRenderer(fenetre_carte,-1,SDL_RENDERER_ACCELERATED);

    icone_carte = SDL_LoadBMP("sprite/icon.bmp");
    SDL_SetWindowIcon(fenetre_carte, icone_carte);
    SDL_FreeSurface(icone_carte);

//Récupération de la taille de l'écran
    SDL_DisplayMode ecran;
    SDL_GetCurrentDisplayMode(0, &ecran);
    printf("Taille de l'ecran x = %d ; y = %d \n", ecran.w, ecran.h);


//fenetre info
    fenetre_info_case = SDL_CreateWindow("Info Case", ecran.w-225, SDL_WINDOWPOS_CENTERED,225 , 330, SDL_WINDOW_SHOWN | SDL_WINDOW_BORDERLESS);
    rendu_info_case = SDL_CreateRenderer(fenetre_info_case,-1,SDL_RENDERER_ACCELERATED);




    // Ecriture dans les logs //
    log = fopen("log.txt", "r+");
    fseek(log, 0, SEEK_END);
    if(fenetre_carte != NULL && fenetre_info_case != NULL)
        fprintf(log, "Les Fenêtres ont été créés avec succès\n");
    else
    {
        fprintf(log, "FATAL ERROR : Les Fennêtres ne se sont pas créés\n");
        return -1;
    }
    fclose(log);
    // --------------------- //

/*--------------- ---------------*/




/* Création de la carte et allocution de la mémoire */


    carte=(bric**)malloc(taille_carte*sizeof(bric*));
    for(int i=0;i<taille_carte;i++)
    {
        carte[i]=(bric*)malloc(taille_carte*sizeof(bric));
    }
    //Les deux lignes précedente permettent de definire la carte sous la forme d'un tableau a deux dimensions

    ///Permet de verifier l'allocation ci dessus
    // Ecriture dans les logs //
    log = fopen("log.txt", "r+");
    fseek(log, 0, SEEK_END);
    if(carte == NULL)
    {
        fprintf(log, "FATAL ERROR : La carte n'a pas été créé\n");
        return -1;
    }
    else
        fprintf(log, "La carte a été créée avec succès\n");
    fclose(log);
    // --------------------- //

    generationcarte(carte, taille_carte, coef_aleatoire, hauteur_max, nb_joueurs);
    generationposition(carte, taille_carte, coef_aleatoire, hauteur_max,nb_joueurs);
    graphic_plateau(carte,taille_carte,rendu_carte);


/*--------------- ---------------*/




/* Initialisation des joueurs */

    player_tab=(joueur*)malloc((nb_joueurs+1)*sizeof(joueur));

    //attribution des valeurs par défaut
    for(int i=1; i<=nb_joueurs; i++)
    {
        player_tab[i].couleur = i;
        player_tab[i].pop = 1;
        player_tab[i].villes = 1;
        player_tab[i].science_total = 0;
        for(int u=0; u<=TECH; u++)
        {
            player_tab[i].tech[u] = 0;
        }
    }

    ///Permet de verifier l'allocation ci dessus
    // Ecriture dans les logs //
    log = fopen("log.txt", "r+");
    fseek(log, 0, SEEK_END);
    if(player_tab == NULL)
    {
        fprintf(log, "FATAL ERROR : Le Tableau des joueurs n'a pas été créé\n");
        return -1;
    }
    else
        fprintf(log, "Le Tableau des joueurs a été créé avec succès\n");
    fclose(log);
    // --------------------- //

/*--------------- ---------------*/




/* Gestion de la partie */

//Gestion des tours
    while( end == 0 ) //la partie n'est pas fini
    {
        // Ecriture dans les logs //
        log = fopen("log.txt", "r+");
        fseek(log, 0, SEEK_END);
        fprintf(log, "\n- Nous entrons dans le tour du joueur %d -\n", tour_du_joueur);
        position_curseur = ftell(log);
        fclose(log);
        // --------------------- //

        while( fin_tour != -1 ) //le joueur appui sur fin de tour
        {
            fin_tour = event(&console, xg, yg, &player_tab[tour_du_joueur], carte, fenetre_carte, rendu_info_case, fenetre_info_case, rendu_carte, player_tab);
            if(player_tab[tour_du_joueur].tech[9] == 1) //test si le joueur a débloqué l'aviation, si oui mes fin à la partie
            {
                end = tour_du_joueur;
            }
        }

        fin_tour = 0;
        tour_du_joueur++;
        if(tour_du_joueur == nb_joueurs+1)
        {
            tour_du_joueur = 1;
            map_updating(carte, player_tab, taille_carte, nb_joueurs); //permet de remettre des points déplacment aux unités, de generation aux villes ect
        }
    }

//Gestion de fin de partie

    fin_partie(fenetre_carte, fenetre_info_case, nb_joueurs, player_tab, end);

/*--------------- ---------------*/



/* Libération de la mémoire */

    free(player_tab);

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
    exit(0);
/*--------------- ---------------*/
}




