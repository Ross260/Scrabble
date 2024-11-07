#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "scrabble.h"
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

int menu(){

    int choix = 0;

        printf("\033[36m ***********************\n");
        printf(" *                     *\n");
        printf(" *~  JEU DE SCRABBLE  ~*\n");
        printf(" *                     *\n");
        printf(" *********************** \033[0m\n");


        printf("\n\n1- Lancer une nouvelle partie \n");
        printf("2- Afficher l'aide \n");
        printf("3- Afficher les scores des joueurs \n");
        printf("4- Quitter le jeu \n");
        printf("Votre choix: ");
        scanf("%d", &choix);

    return choix;
}


// Fonction pour mélanger les lettres de la pioche
void melangerPioche(t_Lettre pioche[TAILLE_JETON]) {
    srand(time(NULL));
    for (int i = 0; i < TAILLE_JETON; i++){
        int j = rand() % TAILLE_JETON;
        t_Lettre temp = pioche[i];
        pioche[i] = pioche[j];
        pioche[j] = temp;

    }
    printf("Melange de la pioche termine \n");

    // printf("nouvelle pioche");
    // for (int i = 0; i < TAILLE_JETON ; i++)
    // {
    //     printf("{%c,%d}",pioche[i].lettre, pioche[i].valeur);
    // }

}

// Fonction pour distribuer les lettres aux joueurs
void distribuerLettres(t_Chevalet *joueurs, t_Lettre pioche[TAILLE_JETON]) {
    int indexPioche = 0;

        indexPioche = 0;
        for (int j = 0; j < TAILLE_CHEVALET; j++) {
            joueurs->lettres[j].lettre = pioche[indexPioche].lettre;
            joueurs->lettres[j].valeur = pioche[indexPioche].valeur;
            indexPioche++;
        }

    printf("Distribution des lettres terminee \n");
}

//############# AFFICHAGE DU TABLEAU ######################################################

// //sous programme qui va permettre d'afficher un mot a une ligne et colonne precise
// void gotoligcol(int lig, int col) {
//     COORD mycoord;
//     mycoord.X = col;
//     mycoord.Y = lig;
//     SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), mycoord);
// }


// Fonction pour afficher le plateau de jeu
void afficher_plateau(char plateau[TAILLE_PLATEAU][TAILLE_PLATEAU]) {
    // Afficher les lettres de la première ligne
    printf("    ");
    for (char lettre = 'A'; lettre <= 'O'; lettre++) {
        printf("  %-2c ", lettre);
    }
    printf("\n");

    // Afficher le reste du plateau avec les numéros de ligne
    for (int i = 0; i < TAILLE_PLATEAU; i++) {
        printf("%2d |", i + 1);
        for (int j = 0; j < TAILLE_PLATEAU; j++) {
            if (plateau[i][j] != ' ') {
                printf("\033[36m %-2c \033[0m|", plateau[i][j]);
            } else {
                printf(" %-2c |", plateau[i][j]);
            }
        }
        printf("\n-------------------------------------------------------------------------------\n");

    }

    printf("\n");

}

int RecupereScoreLettre(t_Chevalet chevalet, char lettre) {
    for (int i = 0; i < 7; i++) {
        if (chevalet.lettres[i].lettre == lettre) {
            return chevalet.lettres[i].valeur;
        }
    }
    return 0; // Si la lettre n'est pas trouvée, retourne 0
}

// Fonction pour vérifier si le mot sort du plateau
int mot_sort_du_plateau(int ligne, char colonne, char sens, int longueur) {
    int index_colonne = colonne - 'A';
    int index_ligne = ligne - 1;

    if (sens == 'h' && (index_colonne + longueur) > TAILLE_PLATEAU) {
        return 1;
    } else if (sens == 'v' && (index_ligne + longueur) > TAILLE_PLATEAU) {
        return 1;
    }

    return 0;
}

// Fonction pour placer un mot dans le plateau
int placer_mot(t_Chevalet *joueurs,char plateau[TAILLE_PLATEAU][TAILLE_PLATEAU], char mot[TAILLE_MOT], int ligne, char colonne, char sens) {
    int longueur = strlen(mot);
    int index_colonne = colonne - 'A';
    int index_ligne = ligne - 1;
    int scoreMot = 0;
    int control = 0;

    int scoreLettreCentre = 0;
    int scoreLettreDouble = 0;
    int scoreLettreTriple = 0;
    int scoreLettre = 0;
    int scoreCasevide = 0;
    int scoreFinal = 0;
    int scoreLettreColision = 0;

    if (mot_sort_du_plateau(ligne, colonne, sens, longueur)) {
        printf("Erreur : Le mot sort du plateau.\n");
        return 0;
    }


    if (sens == 'h') {

        for (int i = 0; i < longueur; i++) {
            if ( (plateau[index_ligne][index_colonne + i] != ' ') && (plateau[index_ligne][index_colonne + i] != mot[i]) && (plateau[index_ligne][index_colonne + i] != '#') && (plateau[index_ligne][index_colonne + i] != '&') && (plateau[index_ligne][index_colonne + i] != '@') && (plateau[index_ligne][index_colonne + i] != '%') && (plateau[index_ligne][index_colonne + i] != '$') ) {

                    printf("Erreur : La lettre '%c' du mot interagit avec une lettre deja presente sur le plateau.\n", mot[i]);
                    return 0;
                
            }

            if (plateau[index_ligne][index_colonne + i] == mot[i])
                {
                    scoreLettre = RecupereScoreLettre(*joueurs, mot[i]);
                    printf("\n\n le score de %c est %d \n", mot[i], scoreLettre);
                    
                    scoreLettreColision += scoreLettre ;

                }

            // && ( plateau[index_ligne][index_colonne + i] == '&' || plateau[index_ligne][index_colonne + i] == '@' || plateau[index_ligne][index_colonne + i] == '%' || plateau[index_ligne][index_colonne + i] == '$')
            if (plateau[index_ligne][index_colonne + i] != ' ' )
            {

                if( plateau[index_ligne][index_colonne + i] == '#' ){
                    scoreLettre = RecupereScoreLettre(*joueurs, mot[i]);
                    printf("\n\n le score de %c est %d \n", mot[i], scoreLettre);
                    
                    scoreLettreCentre += scoreLettre ;

                }

                //multiplication du score par 2 (lettre double)
                if( plateau[index_ligne][index_colonne + i] == '&' ){
                    scoreLettre = RecupereScoreLettre(*joueurs, mot[i]);
                    printf("\n\n le score de %c est %d \n", mot[i], scoreLettre);
                    

                    // printf("\n avant operation(&) %d \n",scoreLettreDouble);
                    scoreLettreDouble += (scoreLettre * 2);
                    // printf("apres operation(&) %d \n",scoreLettreDouble);

                }

                //multiplication du score par 3 (lettre double)
                if( plateau[index_ligne][index_colonne + i] == '%' ){
                    scoreLettre = RecupereScoreLettre(*joueurs, mot[i]);
                    printf("\n\n le score de %c est %d \n", mot[i], scoreLettre);
                    

                    // printf("\navant operation(pourcent) %d \n",scoreLettreTriple);
                    scoreLettreTriple += (scoreLettre * 3);
                    // printf("apres operation(pourcent) %d \n",scoreLettreTriple);
                }

                //multiplication du score de tout le mot par 2
                if( plateau[index_ligne][index_colonne + i] == '@' ){
                    scoreLettre = RecupereScoreLettre(*joueurs, mot[i]);
                    printf("\n\n le score de %c est %d \n", mot[i], scoreLettre);


                    scoreMot += scoreLettre ;
                    // printf("j'arrive ici @");
                    control = 2;
                    // scoreMot += (scoreMot) *2;
                }

                if( plateau[index_ligne][index_colonne + i] == '$' ){
                    scoreLettre = RecupereScoreLettre(*joueurs, mot[i]);
                    printf("\n\n le score de %c est %d \n", mot[i], scoreLettre);


                    scoreMot += scoreLettre ;
                    // printf("j'arrive ici $");
                    control = 3;
                    // scoreMot += (scoreMot) *2;
                }


                //place le mot sur le plateau
                plateau[index_ligne][index_colonne + i] = mot[i];
                
            }else{

                scoreCasevide = RecupereScoreLettre(*joueurs, mot[i]);
                printf("\n\n le score de %c () est %d \n", mot[i], scoreCasevide);

                // \033[36m %-2c \033[0m|
                // printf("\n  \033[33m avant operation( ) %d \n",scoreMot);
                scoreMot = scoreMot + scoreCasevide;
                // printf("\n apres operation( ) %d \033[0m\n",scoreMot);

                // placer le mot sur le plateau
                plateau[index_ligne][index_colonne + i] = mot[i];
                // printf("score du joueur %d : %d ", i, joueurs[i].score );

            }

        }

        scoreFinal= scoreMot + scoreLettreDouble + scoreLettreTriple + scoreLettreCentre + scoreLettreColision;
        joueurs->score = scoreFinal;

        // multiplication du mot 
        if (control == 2)
        {
            joueurs->score = (scoreFinal) * 2;

        }
        
        if (control == 3)
        {
            joueurs->score = (scoreFinal) * 3;

        }
        
        
    //plateau[index_ligne + i][index_colonne]
    } else if (sens == 'v') {
        for (int i = 0; i < longueur; i++) {
            if ( (plateau[index_ligne + i][index_colonne] != ' ') && (plateau[index_ligne + i][index_colonne] != mot[i]) && (plateau[index_ligne + i][index_colonne] != '#') && (plateau[index_ligne + i][index_colonne] != '&') && (plateau[index_ligne + i][index_colonne] != '@') && (plateau[index_ligne + i][index_colonne] != '%') && (plateau[index_ligne + i][index_colonne] != '$') ) {
               
                    printf("Erreur : La lettre '%c' du mot interagit avec une lettre deja presente sur le plateau.\n", mot[i]);
                    return 0;
            }

             if (plateau[index_ligne + i][index_colonne] == mot[i])
                {
                    scoreLettre = RecupereScoreLettre(*joueurs, mot[i]);
                    printf("\n\n le score de %c est %d \n", mot[i], scoreLettre);
                    
                    scoreLettreColision += scoreLettre ;

                }

            // && ( plateau[index_ligne + i][index_colonne] == '&' || plateau[index_ligne + i][index_colonne] == '@' || plateau[index_ligne + i][index_colonne] == '%' || plateau[index_ligne + i][index_colonne] == '$')
            if (plateau[index_ligne + i][index_colonne] != ' ' )
            {

                if( plateau[index_ligne + i][index_colonne] == '#' ){
                    scoreLettre = RecupereScoreLettre(*joueurs, mot[i]);
                    printf("\n\n le score de %c est %d \n", mot[i], scoreLettre);
                    
                    scoreLettreCentre += scoreLettre ;

                }

                //multiplication du score par 2 (lettre double)
                if( plateau[index_ligne + i][index_colonne] == '&' ){
                    scoreLettre = RecupereScoreLettre(*joueurs, mot[i]);
                    printf("\n\n le score de %c est %d \n", mot[i], scoreLettre);
                    

                    // printf("\n avant operation(&) %d \n",scoreLettreDouble);
                    scoreLettreDouble += (scoreLettre * 2);
                    // printf("apres operation(&) %d \n",scoreLettreDouble);

                }

                //multiplication du score par 3 (lettre double)
                if( plateau[index_ligne + i][index_colonne] == '%' ){
                    scoreLettre = RecupereScoreLettre(*joueurs, mot[i]);
                    printf("\n\n le score de %c est %d \n", mot[i], scoreLettre);
                    

                    // printf("\navant operation(pourcent) %d \n",scoreLettreTriple);
                    scoreLettreTriple += (scoreLettre * 3);
                    // printf("apres operation(pourcent) %d \n",scoreLettreTriple);
                }

                //multiplication du score de tout le mot par 2
                if( plateau[index_ligne + i][index_colonne] == '@' ){
                    scoreLettre = RecupereScoreLettre(*joueurs, mot[i]);
                    printf("\n\n le score de %c est %d \n", mot[i], scoreLettre);


                    scoreMot += scoreLettre ;
                    // printf("j'arrive ici @");
                    control = 2;
                    // scoreMot += (scoreMot) *2;
                }

                if( plateau[index_ligne + i][index_colonne] == '$' ){
                    scoreLettre = RecupereScoreLettre(*joueurs, mot[i]);
                    printf("\n\n le score de %c est %d \n", mot[i], scoreLettre);


                    scoreMot += scoreLettre ;
                    // printf("j'arrive ici $");
                    control = 3;
                    // scoreMot += (scoreMot) *2;
                }


                //place le mot sur le plateau
                plateau[index_ligne + i][index_colonne] = mot[i];
                
            }else{

                scoreCasevide = RecupereScoreLettre(*joueurs, mot[i]);
                printf("\n\n le score de %c () est %d \n", mot[i], scoreCasevide);

                // \033[36m %-2c \033[0m|
                // printf("\n  \033[33m avant operation( ) %d \n",scoreMot);
                scoreMot = scoreMot + scoreCasevide;
                // printf("\n apres operation( ) %d \033[0m\n",scoreMot);

                // placer le mot sur le plateau
                plateau[index_ligne + i][index_colonne] = mot[i];
                // printf("score du joueur %d : %d ", i, joueurs[i].score );

            }

        }

        scoreFinal= scoreMot + scoreLettreDouble + scoreLettreTriple + scoreLettreCentre + scoreLettreColision;
        joueurs->score = scoreFinal;

        // multiplication du mot 
        if (control == 2)
        {
            joueurs->score = (scoreFinal) * 2;

        }
        
        if (control == 3)
        {
            joueurs->score = (scoreFinal) * 3;

        }

    }

    return 1;
    
}


//*******************************************************************************************

int verifierMotDictionnaire(char *mot) {

  char motFichier[100];
  FILE *fichier = fopen("DICTIONNAIRE.txt", "r");

  int a = 11;
  int b = 12;

  if(fichier == NULL) {
    printf("Erreur ouverture dictionnaire");
    return 0;
  }

  // Parcourir chaque mot du fichier
  while(fscanf(fichier, "%s", motFichier) != EOF) {

    // Comparaison
    if(strcmp(mot, motFichier) == 0) {
      fclose(fichier);
      return a;
    }

  }

  fclose(fichier);
  return b;

}

//*******************************************************************************************

//menu du tour de jeu
int menu_jeu() {
    int option;

    printf("1- Jouer \n");
    printf("2- passer son tour \n");
    printf("3- quitter la partie \n");
    printf("Votre choix: ");
    scanf("%d", &option);
    printf("\n\n");

    return option;
}


void tour_de_jeu(t_Lettre pioche[TAILLE_JETON],t_Chevalet *joueurs, char plateau[TAILLE_PLATEAU][TAILLE_PLATEAU], int nbJoueur) {

    int option ;
    char mot[TAILLE_MOT];
    int ligne;
    char colonne;
    char sens;
    int val = 0;

    int score ;

    int nombre1 = 0; // les nombres qui vont enregistre les différents scores des joueurs
    int nombre2 = 0;
    int nombre3 = 0;
    int nombre4 = 0;
    
    //reinitialisation du fichier et creation si ca n'existe pas deja
    FILE *fichier = NULL;

    fichier = fopen("SCORE.txt", "w");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return 1;
    }

    fclose(fichier);


    fichier = NULL;
    do
    {
        option = menu_jeu();
        switch (option)
        {
            case 1:
            

            // ouverture du fichier en écriture
            fichier = fopen("SCORE.txt", "a");
            if (fichier == NULL) {
                printf("Erreur lors de l'ouverture du fichier.\n");
                return 1;
            }

                // Demander à l'utilisateur d'entrer les mots
            for (int i = 0; i < nbJoueur; i++) {

                nombre1 = 0; 
                nombre2 = 0;
                nombre3 = 0;
                nombre4 = 0;

                printf("\n  Joueur%d : %s \n", i + 1, joueurs[i].pseudo);

                // Demander à l'utilisateur de saisir les informations du mot
                printf("Entrez le mot : ");
                scanf("%s", mot);

                //passer le tour
                //----------------------------------------------------
                if (strcmp(mot,"RRR") == 0)
                {
                    printf("\033[33m Vous venez de passer votre tour ! \033[0m\n");
                    continue;
                }
                //----------------------------------------------------


                //verification du mot dans le dictionnaire
                //----------------------------------------------------
                val = verifierMotDictionnaire(mot);

                if (val == 11)
                {
                printf("\033[33m Le mot existe dans le dictionnaire \033[0m \n");
                }else{
                    printf("\033[33m Le mot n'est pas dans le dictionnaire \033[0m \n");
                    i--; // Redemander le même mot avec la meme iteration
                    continue;
                }

                //----------------------------------------------------


                printf("Entrez le numero de la ligne : ");
                scanf("%d", &ligne);

                getchar();
                printf("Entrez la lettre de la colonne (majuscule) : ");
                scanf("%c", &colonne);

                getchar();
                printf("Entrez le sens (v pour vertical, h pour horizontal) : ");
                scanf("%c", &sens);

                

                // Placer le mot dans le plateau
                int placement_reussi = placer_mot(&joueurs[i],plateau, mot, ligne, colonne, sens);

                // Vérifier si le placement a réussi
                if (!placement_reussi) {
                    i--; // Redemander le même mot
                    continue;
                }

                printf("\n\nNouvelle pioche :\n");
                Afficher_New_chevalet(pioche,joueurs,i);

                // Afficher le plateau mis à jour
                printf("\033[36m\n\n______________________________\n");
                printf("|                            |");
                printf("\n| Plateau de jeu mis a jour  |\n");
                printf("|____________________________|\n\n\033[0m");

                afficher_plateau(plateau);
                printf("\n");
                printf("\033[33m Score(%s): %d \033[0m \n\n", joueurs[i].pseudo, joueurs[i].score);

                if (nbJoueur == 1)
                {
                    if (i == 0)
                    {
                        fprintf(fichier,"%d;%d;%d;%d\n", joueurs[i].score,nombre2,nombre3,nombre4);
                    }
                    
                    
                    
                }

                if (nbJoueur == 2)
                {
                    if (i == 0)
                    {
                        fprintf(fichier,"%d;%d;%d;%d\n", joueurs[i].score,nombre2,nombre3,nombre4);
                    }
                    if (i==1)
                    {
                        fprintf(fichier,"%d;%d;%d;%d\n", nombre1,joueurs[i].score,nombre3,nombre3,nombre4);
                    }
                    
                    
                }

                if (nbJoueur == 3)
                {
                    if (i == 0)
                    {
                        fprintf(fichier,"%d;%d;%d;%d\n", joueurs[i].score,nombre2,nombre3,nombre4);
                    }
                    if (i==1)
                    {
                        fprintf(fichier,"%d;%d;%d;%d\n", nombre1,joueurs[i].score,nombre3,nombre4);
                    }
                    if (i==2)
                    {
                        fprintf(fichier,"%d;%d;%d;%d\n", nombre1,nombre2,joueurs[i].score,nombre4);
                    }
                    if (i==3)
                    {
                        fprintf(fichier,"%d;%d;%d;%d\n", nombre1,nombre2,nombre3,joueurs[i].score);
                    }
                    
                    
                }
                

            }
            fclose(fichier);



                break;

            case 2:
                printf("\n Pour passer son tour, entrer la chaine 'RRR' a la place de votre mot. \n\n");
                break;

            case 3:
                // redistribure lettre
                // recroit les joueurs et la pioche et redistribut les lettres et affichie les nouveaux chevalet
                break;

        }

    } while (option != 3);

    /*
    PREMIER JOUEUR
    -> initialiser les scores des joueur à 0


    -> jouer
        1 jouer
            entrer le mot a jouer
            enter la lettre qui sera positionner au centre
            verticalement ou horizontalement
            actualiser le plateau avec le mot bien placé
            possibilité de passer le tour

            ->On vérifie la validité du placement : le mot est sur le plateau,
                 relie un mot existant, ne recouvre pas de lettres.

            -> On vérifie l'orthographe du mot dans le dictionnaire.(bonus)



            -> On propose également de passer son tour ou changer des lettres.

            ->  On affiche le gagnant selon le score final le plus élevé.

        2 passer mon tour

        3


    => passer le tour
        -> si le user entre RRR comme son mot on passe à l'iteration suivante et ca passe son tour (deja)

        ICI
        -> à chaque fin de l'option 1 stocker le score des joueur dans un fichier 
        
        -> lire les scores finaux en additionnant en colonne et afficher en determinant le gagnant
        
        
        
        

    */

}

//utilisation du trie bulles pour trier les elements du tableau de scores
void trierTableau(int tableau[4], int taille) {
    int i, j, temp;

    for (i = 0; i < taille - 1; i++) {
        for (j = 0; j < taille - i - 1; j++) {
            if (tableau[j] < tableau[j + 1]) {
                temp = tableau[j];
                tableau[j] = tableau[j + 1];
                tableau[j + 1] = temp;
            }
        }
    }
}


void Afficher_New_chevalet(t_Lettre pioche[TAILLE_JETON],t_Chevalet *joueurs,int g){

    //le g recupere juste l'iteration en cours et travail avec
    for (int i = g; i < g+1; i++)
    {
        //melange du sac de pioche
        melangerPioche(pioche);

        distribuerLettres(&joueurs[i],pioche);

        printf("Joueur %d(%s) : ", i+1, joueurs[i].pseudo);
        //Afficher_chevalet(joueurs,i);


        //affichage des joueurs et leurs chevalets

        for (int j = 0; j < TAILLE_CHEVALET; j++) {
            printf("{%c, ", joueurs[i].lettres[j].lettre);
            printf("%d } ", joueurs[i].lettres[j].valeur);

        } 
        
    printf("\n");
    }

printf("\n\n");
}


void Afficher_chevaletPourLeMain(t_Lettre pioche[TAILLE_JETON],t_Chevalet *joueurs,int nbJoueurs){

    //noms des joueurs
    for (int i = 0; i < nbJoueurs; i++)
    {
        printf("Entrez le nom du joueur %d: ", i+1);
        scanf("%s", joueurs[i].pseudo);


        //melange du sac de pioche
        melangerPioche(pioche);

        // printf("nouvelle pioche");
        // for (int j = 0; j < TAILLE_JETON ; j++)
        // {
        //     printf("{%c,%d}",pioche[j].lettre, pioche[j].valeur);
        // }

        distribuerLettres(&joueurs[i],pioche); 


        printf("Joueur %d(%s) : ", i+1, joueurs[i].pseudo);
        //Afficher_chevalet(joueurs,i);


        //affichage des joueurs et leurs chevalets

        for (int j = 0; j < TAILLE_CHEVALET; j++) {
            printf("{%c, ", joueurs[i].lettres[j].lettre);
            printf("%d } ", joueurs[i].lettres[j].valeur);

        }
        printf("\n\n");

    }



}