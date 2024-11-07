#ifndef _SCRABBLE_H_
#define _SCRABBLE_H_

#define TAILLE_JETON 102
#define TAILLE_CHEVALET 7
#define TAILLE_PLATEAU 15
#define TAILLE_MOT 20
#define NOMBRE_MOTS 1

// Structure pour représenter une lettre avec sa valeur
typedef struct lettre {
    char lettre;
    int valeur;
} t_Lettre;

// Structure pour représenter le chevalet d'un joueur
typedef struct Chevalet {
    t_Lettre lettres[7];
    char pseudo[20];
    int score;
} t_Chevalet;



int menu();
void melangerPioche(t_Lettre pioche[TAILLE_JETON]);
void distribuerLettres(t_Chevalet *joueurs, t_Lettre pioche[TAILLE_JETON]);
void afficher_plateau(char plateau[TAILLE_PLATEAU][TAILLE_PLATEAU]);
int verifierMotDictionnaire(char *mot);
int placer_mot(t_Chevalet *joueurs,char plateau[TAILLE_PLATEAU][TAILLE_PLATEAU], char mot[TAILLE_MOT], int ligne, char colonne, char sens);
int mot_sort_du_plateau(int ligne, char colonne, char sens, int longueur);
int RecupereScoreLettre(t_Chevalet chevalet, char lettre);
void tour_de_jeu(t_Lettre pioche[TAILLE_JETON],t_Chevalet *joueurs, char plateau[TAILLE_PLATEAU][TAILLE_PLATEAU], int nbJoueur);


#endif 

