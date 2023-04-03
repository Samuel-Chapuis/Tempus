#ifndef DEFINITION_H_INCLUDED
#define DEFINITION_H_INCLUDED

#define TECH 10 //définit le nombre de technologies maxium.

static long int position_curseur; //position du curseur dans le fichier log

/// Reference des couleurs utilisées pour les joueurs ///
    /*
    1-Violet
	2-Cyan
	3-Rouge
	4-Jaune
	5-Blanc
	6-Bleu
	*/
/// --------------------------------------------- ///

/* Définition des cases des de la carte */
struct villes
{
    int habitants;
    int joueur; //Couleurs
    int gen; //1 peut generer un villageois ce tour, 0 ne peut pas
};
struct unites
{
    int classe; //0=>Rien 1=>Villageois 2=>Chevaliers 3=>Bateaux militaires 4=>Bateaux Civile
    int joueur; //Couleurs
    int deplacement; //1 l'unité peut se déplacer 0 l'unité ne peut pas
    int pm; //nombre de case sur lequel l'unité peu se deplacer
};

typedef struct
{
    int hauteur; //par défaut entre 0 et +infini, et qui permet de creer les océans,
    //les prairies, les forêts et les montagnes, les valeurs qui sont rajouté par la suite sont négatives,
    //-1 pour les champs

    struct villes ville;
    int territoire; //Couleurs
    struct unites unite;
}bric;
/*--------------- ---------------*/

/* Définition des joeurs */

 typedef struct
 {
    int couleur; //Couleurs
    int science_total;
    int tech[TECH]; //représente l'arbre de tech 1 si le joueur possède la tech 0 sinon
    int villes; ///N'est pas utilisé mais pourrais servir à d'éventulles améliorations
    int pop; // => directement correller à la generation de science par tour,
    //sert aussi de dans la comptabilisation du score en fin de partie

 }joueur;
 /*--------------- ---------------*/

#endif // DEFINITION_H_INCLUDED
