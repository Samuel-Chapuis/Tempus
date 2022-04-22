#ifndef DEFINITION_H_INCLUDED
#define DEFINITION_H_INCLUDED

#define TECH 10 //d�finit le nombre d'�tudiant maxium.

/* D�finition des cases des de la carte */

/// Reference des couleurs utilis�es pour les joueurs ///
    /*
    1-Violet
	2-Turquoise
	3-Rouge
	4-Jaune
	5-Blanc
	6-Fushia
	*/
/// --------------------------------------------- ///

/* D�finition des cases de jeux */
struct villes
{
    int habitants;
    int joueur; //Couleurs
    int gen; //1 peut generer un villageois ce tour, 0 ne peut pas
};
struct unites
{
    int classe; //0=>Rien 1=>Villageois 2=>Chevaliers
    int joueur; //Couleurs
    int pm; //1 l'unit� peut se d�placer 0 l'unit� ne peut pas
};

typedef struct
{
    int hauteur; //par d�faut entre 0 et +infini, et qui permet de creer les oc�ans,
    //les prairies, les for�ts et les montagnes, les valeurs qui sont rajout� par la suite sont n�gatives,
    //-1 pour les champs

    struct villes ville;
    int territoire; //Couleurs
    struct unites unite;
}bric;
/*--------------- ---------------*/

/* D�finition des joeurs */

 typedef struct
 {
    int couleur; //Couleurs
    int science_total;
    int nb_habitants; // => directement correller � la generation de science par tour, sert aussi de dans la comptabilisation du score en fin de partie
    int nb_villes;
 }joueur;
 /*--------------- ---------------*/

#endif // DEFINITION_H_INCLUDED
