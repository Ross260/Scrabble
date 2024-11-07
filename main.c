#include <stdio.h>
#include <stdlib.h>
#include "scrabble.h"
#include "string.h"


#define TAILLE_JETON 102
#define TAILLE_CHEVALET 7
#define TAILLE_PLATEAU 15
#define TAILLE_MOT 20
#define NOMBRE_MOTS 1

// Types de cases
#define START '#' // Point de départ
#define LETTER_DOUBLE '&' // Lettre compte double
#define LETTER_TRIPLE '%' // Lettre compte triple
#define WORD_DOUBLE '@' // Mot compte double
#define WORD_TRIPLE '$' // Mot compte triple

int main()
{
    int choix;
    int nbJoueurs;
    // Tableau de toutes les lettres du jeu avec leur valeur et leur occurrence (le sac de lettre)
    t_Lettre pioche[TAILLE_JETON] = {
        {'A', 1}, {'A', 1}, {'A', 1}, {'A', 1}, {'A', 1}, {'A', 1}, {'A', 1}, {'A', 1}, {'A', 1},
        {'B', 3}, {'B', 3},
        {'C', 3}, {'C', 3},
        {'D', 2}, {'D', 2}, {'D', 2}, {'D', 2},
        {'E', 1}, {'E', 1}, {'E', 1}, {'E', 1}, {'E', 1}, {'E', 1}, {'E', 1}, {'E', 1}, {'E', 1},
        {'E', 1}, {'E', 1}, {'E', 1}, {'E', 1}, {'E', 1}, {'E', 1}, {'E', 1}, {'E', 1}, {'E', 1},
        {'F', 4}, {'F', 4},
        {'G', 2}, {'G', 2}, {'G', 2},
        {'H', 4}, {'H', 4},
        {'I', 1}, {'I', 1}, {'I', 1}, {'I', 1}, {'I', 1}, {'I', 1}, {'I', 1}, {'I', 1},
        {'J', 8},
        {'K', 10},
        {'L', 1}, {'L', 1}, {'L', 1}, {'L', 1},
        {'M', 2}, {'M', 2},
        {'N', 1}, {'N', 1}, {'N', 1}, {'N', 1}, {'N', 1}, {'N', 1},
        {'O', 1}, {'O', 1}, {'O', 1}, {'O', 1}, {'O', 1}, {'O', 1}, {'O', 1}, {'O', 1},
        {'P', 3}, {'P', 3},
        {'Q', 8},
        {'R', 1}, {'R', 1}, {'R', 1}, {'R', 1}, {'R', 1}, {'R', 1},
        {'S', 1}, {'S', 1}, {'S', 1}, {'S', 1},
        {'T', 1}, {'T', 1}, {'T', 1}, {'T', 1}, {'T', 1}, {'T', 1},
        {'U', 1}, {'U', 1}, {'U', 1}, {'U', 1},
        {'V', 4}, {'V', 4},
        {'W', 10},
        {'X', 10},
        {'Y', 10},
        {'Z', 10},
        {'_', 0}, {'_', 0}

};

    // Déclaration d'un plateau de jeu de 15 lignes et 15 colonnes
    char plateau[TAILLE_PLATEAU][TAILLE_PLATEAU];

// Initialiser le plateau avec des cases vides
    for (int i = 0; i < TAILLE_PLATEAU; i++) {
        for (int j = 0; j < TAILLE_PLATEAU; j++) {
            plateau[i][j] = ' ';
        }
    }

    plateau[7][7] = '#';
    // Lignes avec des cases lettre double
    plateau[0][3] = plateau[0][11]= plateau[11][0]= plateau[11][14] = LETTER_DOUBLE;
    plateau[2][6] = plateau[2][8] = LETTER_DOUBLE;
    plateau[3][0] = plateau[3][7] = plateau[3][14] = LETTER_DOUBLE;
    plateau[6][2] = plateau[6][6] = plateau[6][8] = plateau[6][12] = LETTER_DOUBLE;
    plateau[7][3] = plateau[7][11] = LETTER_DOUBLE;
    plateau[8][2] = plateau[8][6] = plateau[8][8] = plateau[8][12] = LETTER_DOUBLE;
    plateau[14][3] = plateau[14][11] = LETTER_DOUBLE;

    // Lignes avec des cases lettre triple
    plateau[1][5] = plateau[1][9] = LETTER_TRIPLE;
    plateau[5][1] = plateau[5][5] = plateau[5][9] = plateau[5][13] = LETTER_TRIPLE;
    plateau[9][1] = plateau[9][5] = plateau[9][9] = plateau[9][13] = LETTER_TRIPLE;
    plateau[12][6] = plateau[12][8] = LETTER_DOUBLE;
    plateau[11][7] = LETTER_DOUBLE;
    plateau[13][5] = plateau[13][9] = LETTER_TRIPLE;

    // Lignes avec des cases mot double
    plateau[1][1] = plateau[1][13] = WORD_DOUBLE;
    plateau[2][2] = plateau[2][12] = WORD_DOUBLE;
    plateau[3][3] = plateau[3][11] = WORD_DOUBLE;
    plateau[4][4] = plateau[4][10] = WORD_DOUBLE;

    plateau[10][4] = plateau[10][10] = WORD_DOUBLE;
    plateau[11][3] = plateau[11][11] = WORD_DOUBLE;
    plateau[12][2] = plateau[12][12] = WORD_DOUBLE;
    plateau[13][1] = plateau[13][13] = WORD_DOUBLE;

    // Lignes avec des cases mot triple
    plateau[0][0] = plateau[0][7] = plateau[0][14] = WORD_TRIPLE;
    plateau[7][0] = plateau[7][14] = WORD_TRIPLE;
    plateau[14][0] = plateau[14][7] = plateau[14][14] = WORD_TRIPLE;


   do
   {
        int nombre1 = 0; 
        int nombre2 = 0;
        int nombre3 = 0;
        int nombre4 = 0;

        //les scores finaux
        int scoreFinal1 = 0; 
        int scoreFinal2 = 0;
        int scoreFinal3 = 0;
        int scoreFinal4 = 0;

        int tableauScore[4];

         choix = menu();
         t_Chevalet joueurs[4];

         switch(choix)
         {
            case 1:

                do
                {
                    printf("\nNombre de joueurs: ");
                    scanf("%d", &nbJoueurs);
                } while (nbJoueurs > 4 || nbJoueurs < 1);
                

                //declaration du tableau de joueurs
                joueurs[nbJoueurs];
                

                Afficher_chevaletPourLeMain(pioche,joueurs,nbJoueurs);
//********************
                //noms des joueurs
                // for (int i = 0; i < nbJoueurs; i++)
                // {
                //     printf("Entrez le nom du joueur %d: ", i+1);
                //     scanf("%s", joueurs[i].pseudo);


                //     //melange du sac de pioche
                //     melangerPioche(pioche);

                //     // printf("nouvelle pioche");
                //     // for (int j = 0; j < TAILLE_JETON ; j++)
                //     // {
                //     //     printf("{%c,%d}",pioche[j].lettre, pioche[j].valeur);
                //     // }

                //     distribuerLettres(&joueurs[i],pioche); 


                //     printf("Joueur %d(%s) : ", i+1, joueurs[i].pseudo);
                //     Afficher_chevalet(joueurs,i);


                // //     //affichage des joueurs et leurs chevalets

                // //     for (int j = 0; j < TAILLE_CHEVALET; j++) {
                // //         printf("{%c, ", joueurs[i].lettres[j].lettre);
                // //         printf("%d } ", joueurs[i].lettres[j].valeur);

                // //     }
                //     // printf("\n\n");

                // }
//***********************

                // Afficher le plateau de jeu
                afficher_plateau(plateau);
                
                //lancement du tour de jeu
                tour_de_jeu(pioche,joueurs,plateau, nbJoueurs);

                break;

            case 2:
                
               printf("\n Salut si tu est ici c est que tu a besoin d'aide tu trouveras tous les informations dont tu besoin.\n \n");
                 printf("\033[31m Joueurs \033[39m");
                  printf("\n Il y a 2 joueurs, 3 joueurs ou 4 joueurs possibles dans une partie. Les joueurs jouent a tour de role");
                         printf("\n tel que defini dans les regles. C est le joueur1 qui commence. Le nombre de joueurs est saisi avant");
                         printf("\n le lancement de la partie. De meme que le pseudo de chaque joueur. Ce pseudo sera stocke pour la ");
                         printf("\n partie. \n \n ");
                         printf("\033[31m Chevalet \033[39m");
                         printf("\n Dans le jeu du joueur, chaque lettre est accompagnee par son score : ex A1 reprsente le jeton A de");
                         printf("\n score 1, G2, represente le jeton G de score 2, etc. \n\n ");
                         printf("\033[31m Le plateau de jeu \033[39m ");
                         printf("\n Le plateau de jeu est constitue de cases rangees dans 15 lignes et 15 colonnes (soit 225 cases en");
                         printf("\n tout). Les lignes sont precedees d un nombre et les colonnes d une lettre. Le type de ses cases est ");
                         printf("\n soit simple, soit complexe (dites  multiplicatrices ). Elles valorisent la lettre ou le mot qui les ");
                         printf("\n recouvrent en multipliant sa valeur par deux ou par trois.  ");
                         printf("\n\033[32m ");
                         printf("# : point de depart  \n ");
                         printf("& : lettre double  \n ");
                         printf("%c :lettre triple  \n ",37);
                         printf("@ : mot double  \n ");
                         printf("$ : mot triple  ");
                         printf("\033[31m\n\n Placement d un mot \033[39m");
                         printf("\n \n Quand un joueur a choisi un mot il le saisit a l ecran. Ensuite il saisit l emplacement sur le plateau ");
                         printf("\n en ligne (chiffre) et en colonne (lettre) ainsi que le sens vertical (de haut en bas) ou horizontal (de la");
                         printf("\n gauche vers la droite) : v ou h.  \n En jouant les mot entrer doivent etre en majuscule \n\n ");
                         printf("\033[31m Fin de partie \033[39m");
                         printf("\n \n La partie s acheve quand le sac est vide et qu un joueur place ses dernieres lettres sur la grille. Il");
                         printf("\n ajoute a son score la valeur des lettres restant a ses adversaires, qui dans le meme temps, doivent ");
                         printf("\n deduire de leur score la valeur des lettres qui leur restent. Le vainqueur est celui qui totalise le plus");
                         printf("\n de points a la fin de la partie. \n ");
                         printf("\033[33mApres avoir quitter une partie, vous aurez la possibilite de voir les scores finaux des joueurs ainsi que le gagnant \033[0m \n");
                         printf("\n \033[5m  Bon courage \033[0m \n\n\n\n");

                break;

            case 3:
                

                // Afficher les scores des joueurs
                printf("\033[36m\n\n______________________\n");
                printf("|                    |");
                printf("\n| Score des joueurs  |\n");
                printf("|____________________|\n\n\033[0m");

                
                //lecture du fichier des scores et affichage en fonction du gagnant
                // Lecture du nombre depuis le fichier

                char motFichier[100];
                FILE *fichier = fopen("SCORE.txt", "r");
                if (fichier == NULL) {
                    printf("Erreur lors de l'ouverture du fichier.\n");
                    return 1;
                }

                // Parcourir chaque ligne du fichier
                while(fscanf(fichier,"%d;%d;%d;%d\n", &nombre1,&nombre2,&nombre3,&nombre4) != EOF) {
                
                   scoreFinal1 = scoreFinal1 + nombre1; 
                   scoreFinal2 = scoreFinal2 + nombre2;
                   scoreFinal3 = scoreFinal3 + nombre3;
                   scoreFinal4 = scoreFinal4 + nombre4;

                }

                printf("Les differents score sont : %d, %d, %d, %d\n\n", scoreFinal1,scoreFinal2,scoreFinal3,scoreFinal4);

                tableauScore[0] = scoreFinal1;
                tableauScore[1] = scoreFinal2;
                tableauScore[2] = scoreFinal3;
                tableauScore[3] = scoreFinal4;

                for (int i = 0; i < nbJoueurs; i++)
                {
                    joueurs[i].score = tableauScore[i];
                }
                


                trierTableau(tableauScore, 4);
                
                // printf("le gagnant a : %d points \n", tableauScore[0]);
                // printf("le 2e a : %d points \n", tableauScore[1]);
                // printf("le 3e a : %d points \n", tableauScore[2]);
                // printf("le gagnant a : %d points \n", tableauScore[3]);

                
                for (int i = 0; i < nbJoueurs; i++) {
                    if( joueurs[i].score == tableauScore[0]){
                        printf(" =>\033[32m Gagnant (%s) : %d \n \033[0m",joueurs[i].pseudo, joueurs[i].score);
                    }else{
                        printf(" => %s : %d \n",joueurs[i].pseudo, joueurs[i].score);
                    }
                }




                printf("\033[36m \n______________________ \033[0m \n\n\n");
                break;
                
            case 4:
                printf(" A bientot !");
                break;

            default:
                printf("Choisir une option entre  (1 et 4)");
                break;
        }
   } while (choix != 4);







    return 0;
}
