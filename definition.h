#ifndef DEFINITION_H_INCLUDED
#define DEFINITION_H_INCLUDED

/* Définition des cases des de la carte */

struct villes
{
    int habitants;
    int joueur;
};
struct unites
{
    int classe; //0=>Rien 1=>Villageois 2=>Chevaliers
    int joueur;
};

typedef struct
{
    int hauteur;
    struct villes ville;
    int territoire;
    struct unites unite;
}bric;
/*--------------- ---------------*/

/* Définition des joeurs */

 typedef struct
 {
     int couleur;
    /*
    1-Violet
	2-Turquoise
	3-Rouge
	4-Jaune
	5-Blanc
	6-Fushia
	*/
    int science;
 }joueur;
 /*--------------- ---------------*/

#endif // DEFINITION_H_INCLUDED
