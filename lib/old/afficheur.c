/* ---- Fonction Afficheur Console ----*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <math.h>
#include <dos.h>
#include <string.h>

#include "../definition.h"
#include "color.h"

void unit_ville (int position,int habitant);

void afficheur_bric(bric bk)
{
    int back=0;
    int front=15;
    char texte[]="   ";
    switch(bk.ville.joueur)
            {
                case 0:
                    {
                        //Mise en forme du fond d'écran en fonction du type de case
                        if(bk.hauteur>=0&&bk.hauteur<=1)
                        back=1;
                        else if(bk.hauteur>1&&bk.hauteur<=4)
                        back=10;
                        else if(bk.hauteur>4&&bk.hauteur<=6)
                        back=2;
                        else if(bk.hauteur>6&&bk.hauteur<=8)
                        back=6;
                        else if(bk.hauteur>8)
                        back=8;


                        switch(bk.unite.classe)
                        {
                        case 0:
                        {
                                   //Affichage des territoires autoures des villes
                                    switch(bk.territoire)
                                    {
                                    case 1:
                                        {
                                            front=5;
                                            texte[0]=177; texte[1]=177; texte[2]=177;
                                            break;

                                        }
                                    case 2:
                                        {
                                            front=3;
                                            texte[0]=177; texte[1]=177; texte[2]=177;
                                            break;

                                        }
                                    case 3:
                                        {
                                            front=12;
                                            texte[0]=177; texte[1]=177; texte[2]=177;
                                            break;

                                        }
                                    case 4:
                                        {
                                            front=14;
                                            texte[0]=177; texte[1]=177; texte[2]=177;
                                            break;

                                        }
                                    case 5:
                                        {
                                            front=15;
                                            texte[0]=177; texte[1]=177; texte[2]=177;
                                            break;

                                        }
                                    case 6:
                                        {
                                            front=13;
                                            texte[0]=177; texte[1]=177; texte[2]=177;
                                            break;

                                        }
                                    default :
                                        {
                                            front=15;
                                            texte[0]=32; texte[1]=32; texte[2]=32;
                                            break;
                                        }
                                    }
                                break;
                            }
                        case 1:
                            {
                                printf(" p ");
                                break;
                            }
                        case 2:
                            {
                                printf(" P ");
                                break;
                            }
                        }

                        color(front,back);
                        printf("%s",texte);

                        break;


                //Affichage des villes
                    }
                case 1:
                    {
                        color(15,5);
                        unit_ville(bk.unite.classe,bk.ville.habitants);
                        break;
                    }
                case 2:
                    {
                        color(15,3);
                        unit_ville(bk.unite.classe,bk.ville.habitants);
                        break;
                    }
                case 3:
                    {
                        color(15,12);
                        unit_ville(bk.unite.classe,bk.ville.habitants);
                        break;
                    }
                case 4:
                    {
                        color(0,14);
                        unit_ville(bk.unite.classe,bk.ville.habitants);
                        break;
                    }
                case 5:
                    {
                        color(0,15);
                        unit_ville(bk.unite.classe,bk.ville.habitants);
                        break;
                    }
                case 6:
                    {
                        color(15,13);
                        unit_ville(bk.unite.classe,bk.ville.habitants);
                        break;
                    }
            }
}

void afficheur_plateau(bric **carte,int TC)
{
    int back=0;

    //Affichage du némro des colonnes
//    printf("\n\t");
//    for(int k=0;k<TC;k++)
//    {
//        color(15,0);
//        if(k>=9)
//            printf(" %i",k);
//        else
//            printf(" %i ",k);
//    }

    printf("\n  ");

    for(int i=0;i<TC;i++)
    {
//        //Affichage du numéro des lignes
//        color(15,0);
//        printf("%i\t",i);
        color(15,0);

        for(int j=0;j<TC;j++)
        {
            afficheur_bric(carte[i][j]);
        }
        color(15,0);
        printf("\n  ");
    }
    color(15,0);
    printf("\n\n");
}

void unit_ville (int position,int habitant)
{
    switch(position)
    {
        case 0:
        {
            printf(" %d ",habitant);
        }
        case 1:
        {
            printf(" p ");
        }
        case 2:
        {
            printf(" P ");
        }
    }
}
