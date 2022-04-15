/* ---- Fonction generationcarte ----*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <math.h>
#include <dos.h>
#define CRASH 100

#include "../definition.h"


void generationcarte(bric **carte,int TC,int roughness,int HI,int joueurs)
{
/* ===== videur de m�moire =====*/

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


    //initialisation des coins de mani�re al�atoires.
    srand(time(NULL));
    carte[0][0].hauteur=rand()%(HI+1); //associe au coin droit une valeur al�atoire entre 0 et 41
    carte[TC-1][0].hauteur=rand()%(HI+1);
    carte[0][TC-1].hauteur=rand()%(HI+1);
    carte[TC-1][TC-1].hauteur=rand()%(HI+1);

//    carte[0][0].hauteur=10;
//    carte[TC-1][0].hauteur=10;
//    carte[0][TC-1].hauteur=10;
//    carte[TC-1][TC-1].hauteur=10;

/* ===== Phase de g�neration de la carte ===== */

//commande de test
//printf("\t%d\t%d\t%d\t%d\n\n",carte[0][0].hauteur,carte[0][TC-1].hauteur,carte[TC-1][0].hauteur,carte[TC-1][TC-1].hauteur);

    //Carr�
    int half;
    int x,y;
    int moyenne=-1;

    for(int sl=TC-1; sl>=2;sl/=2,roughness/=2)
    {
        half=sl/2;

        //Carr�
        for(x=0;x<TC-1;x+=sl)
        {
           for(y=0;y<TC-1;y+=sl) //x et y sont les coordonn� du sommet gauche.
           {
               moyenne=(carte[x][y].hauteur+carte[x+sl][y].hauteur+carte[x][y+sl].hauteur+carte[x+sl][y+sl].hauteur)/4;
               carte[x+half][y+half].hauteur=moyenne+(rand()%(roughness+1));
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
                carte[x][y].hauteur=moyenne;
                if(x==0)
                    carte[TC-1][y].hauteur=moyenne;
                if(y==0)
                    carte[x][TC-1].hauteur=moyenne;
            }
        }
    }
}

/*--------------- ---------------*/

int generationposition(bric **carte,int TC,int roughness,int HI,int joueurs)
{
    int temp_i=0;
    int temp_j=0;
    int eau=0;
    int enemie=0;
    int crash=0;
    int u=0;
    int v=0;
    srand(time(NULL));

    for(int michel=1;michel<=joueurs;michel++)
   {
        do
        {
            eau=0;
            enemie=0;
            temp_i=(rand()%(TC-4))+2;
            temp_j=(rand()%(TC-4))+2;

            for(int ui=-2;ui<=2;ui++) //Test de la proximit� des ville adverses
            {
                for(int uj=-2;uj<=2;uj++)
                {
                    if((carte[ui+temp_i][uj+temp_j].ville.joueur!=michel)&&(carte[ui+temp_i][uj+temp_j].ville.joueur!=0))
                    {
                        enemie++;
                    }
                }
            }
            for(int ui=-1;ui<=1;ui++) //Test de la proximit� de l'eau
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

        carte[temp_i][temp_j].ville.habitants=1;
        carte[temp_i][temp_j].ville.joueur=michel;



        do{
            u=rand()%3;
            v=rand()%3;
        }while((u==1||v==1)||(carte[temp_i-1+u][temp_j-1+v].hauteur<=1));

        carte[temp_i-1+u][temp_j-1+v].unite.classe=2;
        carte[temp_i-1+u][temp_j-1+v].unite.joueur=michel;

        for(int ui=-1;ui<=1;ui++)
            {
                for(int uj=-1;uj<=1;uj++)
                {
                    carte[ui+temp_i][uj+temp_j].territoire=michel;
                }
            }
   }

   if(crash>=CRASH){ return 2001; }
   return 0;
}