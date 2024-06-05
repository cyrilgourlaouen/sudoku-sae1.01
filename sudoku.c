/**
 * @brief Programme d'un Sudoku.
 * 
 * @author Cyril GOURLAOUEN
 * 
 * Ce programme permet de jouer au sudoku, il contient, 
 * plusieur procédures, plusieurs fonctions, ainsi qu'un programme principal.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

const char TROISTIRET[4] = "---";
const char PLUS[2] = "+";

#define N 3
/**
 * @def TAILLE
 * 
 * @brief Taille maximum d'un tableau.
*/
#define TAILLE (N*N)

/**
 * @typedef tGrille
 * 
 * @brief Tableau en 2 dimensions d'entier.
*/
typedef int tGrille[TAILLE][TAILLE];


/**
 * @fn void chargerGrille(tGrille grille)
 * 
 * @brief Procédure qui charge la grille de sudoku.
 * 
 * @param grille : La grille à charger.
 * 
*/
void chargerGrille(tGrille grille){
    char nomFichier[30];
    FILE * f;
    printf("Nom du fichier ? ");
    scanf("%s", nomFichier);
    f = fopen(nomFichier, "rb");
    if (f==NULL){
        printf("\n ERREUR sur le fichier %s\n", nomFichier);
    } else {
        fread(grille, sizeof(int), TAILLE*TAILLE, f);
    }
    fclose(f);
}

/**
 * @fn void afficherGrille(tGrille grille)
 * 
 * @brief Procédure qui permet d'afficher la grille de sudoku.
 * 
 * @param grille : La grille à afficher.
 * 
*/
void afficherGrille(tGrille grille){
    int nb_lig;
    int nb_col;
    int boucle;
    printf("\n   ");

    for (nb_col = 1; nb_col <= TAILLE; nb_col++) {
        printf(" %d ", nb_col);
        if (nb_col % N == 0) {
            printf(" ");
        }
    }
    printf("\n");

    for (nb_lig = 0 ; nb_lig < TAILLE; nb_lig++){

        if(nb_lig % N == 0) {
            printf("  ");
            for (boucle = 0; boucle < TAILLE; boucle++) 
            {
                if (boucle % 3 == 0)
                {
                    printf(PLUS);
                }
                printf(TROISTIRET);
            }
            printf(PLUS);
            printf("\n");
        }
    

        printf("%d |" ,nb_lig + 1);
        for (nb_col = 0 ; nb_col < TAILLE; nb_col++){
            if (grille[nb_lig][nb_col]== 0)
            {
                printf(" . ");
            }
            else{
                printf(" %d ", grille[nb_lig][nb_col]);
            }
            if ((nb_col + 1) % N == 0){
                printf("|");
            }
        }
        printf("\n");

        if (nb_lig == TAILLE - 1) {
            printf("  ");
            for (boucle = 0; boucle < TAILLE; boucle++) {
                if (boucle % N == 0) {
                    printf(PLUS);
                }
                printf(TROISTIRET);
            }
            printf(PLUS);
            printf("\n");
        }
        
    }
}


void saisir(int *coordonne){
    char chaine[49];
    int valeur;
    bool correct = false;
    do
    {
        scanf("%s", chaine);
        if (sscanf(chaine, "%d", &valeur) != 0){
            *coordonne = valeur;
            if(valeur > 0 && valeur < TAILLE+1){
                *coordonne = valeur;
                correct = true;
            }
            else{
                printf("La valeur doit etre comprise en 1 et %d borne incluse.\n", TAILLE);
            }
        }
        else {
            printf("Vous devez saisir un entier.\n");
        }

    } while (correct != true); 
}

bool fini(tGrille grille){
    int nb_lig;
    int nb_col;
    int compteur;
    bool res;
    res = false;
    compteur = 0;
    
    for (nb_lig = 0 ; nb_lig < TAILLE; nb_lig++){
        for (nb_col = 0 ; nb_col < TAILLE; nb_col++){
            if (grille[nb_lig][nb_col] == 0)
            {
                compteur++;
            }
            
        }
    }

    if (compteur == 0)
    {
        res = true;
    }
    
    return res;
}

bool possible(tGrille grille, int numLigne, int numColonne, int valeur){
    int boucle1;
    int boucle2;
    int ligne;
    int colonne;
    bool res;
    ligne = numLigne;
    colonne = numColonne;
    res = true;
    for (boucle1 = 0; boucle1 < TAILLE; boucle1++)
    {
        if (grille[numLigne-1][boucle1] == valeur){
            printf("La valeur %d est déja présente dans la ligne.\n", valeur);
            res = false;
        }

        if(grille[boucle1][numColonne-1] == valeur){
            res = false;
            printf("La valeur %d est déja présente dans la colonne.\n", valeur);
        }
    }

    while (ligne % N != 0)
    {
        ligne++;
    }

    while (colonne % N != 0)
    {
        colonne++;
    }

    for (boucle1 = ligne-1; boucle1 > ligne-4 ; boucle1--)
    {
        for (boucle2 = colonne-1; boucle2 > colonne-4 ; boucle2--)
        {
            if (grille[boucle1][boucle2] == valeur){
                printf("La valeur %d est déja présente dans la case.\n", valeur);
                res = false;
            }
        }
    }
    
    return res;
}


/**
 * @fn int main()
 * 
 * @brief Programme principal.
 * 
 * @return EXIT_SUCCESS
*/
int main(){

    tGrille grille1;
    int numLigne;
    int numColonne;
    int valeur;
    chargerGrille(grille1);
    while (fini(grille1) == false)
    {
        afficherGrille(grille1);
        printf("Veuillez saisir la ligne puis la colonne :\n");
        saisir(&numLigne);
        saisir(&numColonne);
        if (grille1[numLigne-1][numColonne-1]!= 0)
        {
            printf("IMPOSSIBLE, la case n'est pas libre.\n");
        }
        else{
            printf("Quel valeur voulez-vous insérer ? ");
            saisir(&valeur);
            if (possible(grille1, numLigne, numColonne, valeur))
            {
                grille1[numLigne-1][numColonne-1] = valeur;
            }
        }
    }
    
    printf("Grille pleine, fin de partie.\n");

    return EXIT_SUCCESS;
}