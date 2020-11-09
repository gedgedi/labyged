#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

/************************************************************************/
/*                    DECLARATIONS DE CONSTANTES	                    */
/************************************************************************/
// Caractères (lettre) dans le fichier texte.
#define LABYRINTHE_PASSAGE  '0'
#define LABYRINTHE_HEROS    '1'
#define LABYRINTHE_MUR      '2'

// Caractères (ASCII) d'affichage pour avoir quelque chose de sympathique!
#define AFFICHAGE_MUR       219   // Utilisez 35 en cas de problème d'affichage ASCII. 
#define AFFICHAGE_HEROS     42
#define AFFICHAGE_PASSAGE   32

// Dimensions de la grille
#define HAUTEUR			15
#define LARGEUR			30

// Nom du Fichier
#define FICHIER_JEU     "laby.txt"

/************************************************************************/
/*                    DECLARATIONS DE TYPES		                        */
/************************************************************************/
typedef char t_grille[HAUTEUR][LARGEUR];

/************************************************************************/
/*                    DECLARATIONS DE FONCTIONS                         */
/************************************************************************/
// Reçoit une grille et un nom de fichier.
// Initialise la grille à partir du fichier.
// Retourne 0 si le fichier était valide, 1 sinon.
int initialiser_grille(t_grille grille, char* fichier_jeu);

// Reçoit une grille en entrée et l'affiche.
// afficher_grille appelle la fonction get_char_affichage pour faire la
// conversion entre le caractère lu dans le fichier et le caractère qui sera affiché.
void afficher_grille(t_grille grille);

// Fait la conversion entre les caractères lu dans le fichier et ceux affichés.
// Par exemple, si on lit LABYRINTHE_PASSAGE dans le fichier, on affichera AFFICHAGE_PASSAGE à l'écran.
char get_char_affichage(char original);

// Fait se deplacer le joueur
void deplacer_joueur(t_grille grille);

int main()
{
    t_grille grille;

    initialiser_grille(grille, FICHIER_JEU);

    while (1) 
    {
    afficher_grille(grille);
    deplacer_joueur(grille);
    if (grille[10][8] == LABYRINTHE_HEROS)
    {
        printf("\n\nBravo, Vous avez termine ce niveau de Labyged !");
        initialiser_grille(grille, FICHIER_JEU);
        printf("\nAppuyez sur une touche poour recommencer...");
        _getch();
    }

    }
   
   return EXIT_SUCCESS;
}

int initialiser_grille(t_grille grille, char* fichier_jeu)
{
    int i, j;
    FILE* fichier = NULL;

    fichier = fopen(fichier_jeu, "r");


    if (fichier != NULL)
    {
            for (i = 0; i <= HAUTEUR; i++)
            {
                for (j = 0; j < LARGEUR; j++)
                {
                    grille[i][j] = fgetc(fichier);
                }
            }
        fclose(fichier);
        return 1;
    }
    else return 0;

}


void afficher_grille(t_grille grille)
{
    int i, j;
    system("cls");
    for (i = 0; i <= HAUTEUR; i++) 
    {
        for (j = 0; j < LARGEUR; j++) 
        {
            printf("%c", get_char_affichage(grille[i][j]));
        }
           
    }
}

char get_char_affichage(char original)
{
    if (original == LABYRINTHE_HEROS)
    {
        return AFFICHAGE_HEROS;
    }

    if (original == LABYRINTHE_MUR)
    {
        return AFFICHAGE_MUR;
    }

    if (original == LABYRINTHE_PASSAGE) 
    {
        return AFFICHAGE_PASSAGE;
    }
}

void deplacer_joueur(t_grille grille) 
{
    int i, j;
    int ch;
    int ok;
    int mem_i, mem_j;
    ok = 0;
    mem_i = 0;
    mem_j = 0;

    for (i = 0; i <= HAUTEUR; i++)
    {
        for (j = 0; j < LARGEUR; j++)
        {
            if (grille[i][j] == LABYRINTHE_HEROS)
            {
                grille[i][j] = LABYRINTHE_PASSAGE;
                mem_i = i;
                mem_j = j;
            }
        }
    }

    do {
        ch = _getch();
        switch (ch)
        {
        case 'w': 
            if ((grille[mem_i - 1][mem_j-1]) == LABYRINTHE_PASSAGE)
            {
                grille[mem_i - 1][mem_j-1] = LABYRINTHE_HEROS;
                ok = 1;
                break;
            }
            else 
                break;

        case 'a':
            if ((grille[mem_i][mem_j - 1]) == LABYRINTHE_PASSAGE)
            {
                grille[mem_i][mem_j - 1] = LABYRINTHE_HEROS;
                ok = 1;
                break;
            }
            else
                break;

        case 'd':
            if (grille[mem_i][mem_j + 1] == LABYRINTHE_PASSAGE)
            {
                grille[mem_i][mem_j + 1] = LABYRINTHE_HEROS;
                ok = 1;
                break;
            }
            else
                break;

        case 's':
            if (grille[mem_i + 1][mem_j+1] == LABYRINTHE_PASSAGE)
            {
                grille[mem_i + 1][mem_j+1] = LABYRINTHE_HEROS;
                ok = 1;
                break;
            }
            else
                break;

        default:
            break;
        }
    } while (ok == 0);
}