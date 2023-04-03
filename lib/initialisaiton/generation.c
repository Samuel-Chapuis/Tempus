/* ---- Fonctions de generation de la carte ----*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <math.h>
#include <dos.h>
#define CRASH 100

#include "../../definition.h"
#include "../gestion_tour/gestion_ville.h"


void generationcarte(bric **carte,int TC,int roughness,int HI,int joueurs)
{
/* --------- videur de mémoire --------- */

    for(int i=0;i<TC;i++)
    {
        for(int j=0;j<TC;j++)
        {
            carte[i][j].hauteur=0;
            carte[i][j].territoire=0;
            carte[i][j].ville.habitants=0;
            carte[i][j].ville.joueur=0;
            carte[i][j].unite.classe=0;
            carte[i][j].unite.joueur=0;
        }
    }


    //initialisation des coins de manière aléatoires.
    srand(time(NULL));
    carte[0][0].hauteur=rand()%(HI+1); //associe au coin droit une valeur aléatoire
    carte[TC-1][0].hauteur=rand()%(HI+1);
    carte[0][TC-1].hauteur=rand()%(HI+1);
    carte[TC-1][TC-1].hauteur=rand()%(HI+1);

/* --------- Phase de géneration de la carte --------- */

    //Carré
    int half;
    int x,y;
    int moyenne=-1;

    for(int sl=TC-1; sl>=2;sl/=2,roughness/=2) //Permet de passer par toute les case du tableau
    {
        half=sl/2; //demi taille de tableau

        //Carré
        for(x=0;x<TC-1;x+=sl)
        {
           for(y=0;y<TC-1;y+=sl) //x et y sont les coordonné du sommet gauche.
           {
               moyenne=(carte[x][y].hauteur+carte[x+sl][y].hauteur+carte[x][y+sl].hauteur+carte[x+sl][y+sl].hauteur)/4;
               carte[x+half][y+half].hauteur=moyenne+(rand()%(roughness+1));
               //On dertermine la moyenne des sommet et on l'implante au millieu
               //printf("moyenne : %d\n",moyenne);
           }
        }

    //Diamant
        for(x=0;x<TC-1;x+=half)
        {
            for(y=(x+half)%sl;y<TC-1;y+=half) //permet d'aller en diagonal pour trouver le centre.
            {
                moyenne=(carte[(x-half+TC)%TC][y].hauteur           /*sommet gauche du losange*/
                         +carte[(x+TC)%TC][y].hauteur               /*sommet droit du losange*/
                         +carte[x][(y+TC)%TC].hauteur               /*sommet du bas*/
                         +carte[x][(y-half+TC)%TC].hauteur)/4;      /*sommet du haut*/

                moyenne=moyenne+(rand()%(roughness+1));
                carte[x][y].hauteur=moyenne; //On implante la moyenne au sommet du diamant
                if(x==0) //Gestion des cas particuliers
                    carte[TC-1][y].hauteur=moyenne;
                if(y==0)
                    carte[x][TC-1].hauteur=moyenne;
            }
        }
    }
/// Pour la carte est bien un rapport de 3/4 on tronque 1/4 du bas de la carte initialement carré:
    for(int i=0;i<TC;i++)
    {
        for(int j=0.75+1*TC;j<TC;j++)
        {
            carte[i][j].hauteur=0;
            carte[i][j].territoire=0;
            carte[i][j].ville.habitants=0;
            carte[i][j].ville.joueur=0;
            carte[i][j].unite.classe=0;
            carte[i][j].unite.joueur=0;
        }
    }

}

/*--------------- ---------------*/


void generationposition(bric **carte,int TC,int roughness,int HI,int nb_joueurs)
{
    int temp_i=0;
    int temp_j=0;
    int eau=0;
    int enemie=0;
    int crash=0;
    int u = -1;
    int v = -1;
    srand(time(NULL));

    for(int couleur=1;couleur<=nb_joueurs;couleur++)
    {
        do
        {
            eau=0;
            enemie=0;
            temp_i=(rand()%(TC-4))+2;
            temp_j=(rand()%(TC-4-TC/3))+2;

            for(int ui=-2;ui<=2;ui++) //Test de la proximité des ville adverses
            {
                for(int uj=-2;uj<=2;uj++)
                {
                    if((carte[ui+temp_i][uj+temp_j].ville.joueur!=couleur)&&(carte[ui+temp_i][uj+temp_j].ville.joueur!=0))
                    {
                        enemie++;
                    }
                }
            }
            for(int ui=-1;ui<=1;ui++) //Test de la proximité de l'eau
            {
                for(int uj=-1;uj<=1;uj++)
                {
                    if(carte[ui+temp_i][uj+temp_j].hauteur<=1)
                    {
                        eau++;
                    }
                }
            }
            crash++;
        }while((eau>=3||enemie!=0)&&crash<CRASH);

        creation_ville(carte, temp_i, temp_j, couleur);
        carte[temp_i][temp_j].ville.gen = 1;
        do{
        u=rand()%3;
        v=rand()%3;
        }while((u==1||v==1)||(carte[temp_i-1+u][temp_j-1+v].hauteur==1)||(carte[temp_i-1+u][temp_j-1+v].hauteur==0));

        carte[temp_i-1+u][temp_j-1+v].unite.classe=2;
        carte[temp_i-1+u][temp_j-1+v].unite.pm=2;
        carte[temp_i-1+u][temp_j-1+v].unite.deplacement=1;
        carte[temp_i-1+u][temp_j-1+v].unite.joueur=couleur;

   }
   // Ecriture dans les logs //
    FILE* log = NULL;
    log = fopen("log.txt", "r+");
    fseek(log, 0, SEEK_END);
    printf("\nhello");
    if(crash>=CRASH)
    {
        fprintf(log, "FATAL ERROR : La Carte n'a étée pas créée\n");
        position_curseur = ftell(log);
        fclose(log);
        return;
    }
    else
    {
        fprintf(log, "La carte à étée créée avec succès \n");
        position_curseur = ftell(log);
        fclose(log);
        return;
    }
}
