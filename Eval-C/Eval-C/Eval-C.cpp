// Eval-C.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
// Jeu très simple pour l'évaluation en c (le but est d'aller jusqu'au trésor)

#include <stdio.h>

//déclaration des variables constantes
const int GRID_SIZE = 5;
const char PLAYER = '@';
const char TREASURE = 'T';
const char OBSTACLE = '#';
const char EMPTY = '.';
bool WIN = false; //variable booléenne qui représente si le joueur a gagné

//déclaration des fonctions

void initGrid(int grid[GRID_SIZE][GRID_SIZE], int* playerX, int* playerY);
void displayGrid(int grid[GRID_SIZE][GRID_SIZE]);
void movePlayer(int grid[GRID_SIZE][GRID_SIZE], int* playerX, int* playerY, int direction);

/// <summary>
/// Fonction principale
/// </summary>
int main()
{
    int grid[GRID_SIZE][GRID_SIZE]; //déclaration de la grille de jeu
    int direction = 0; //déclaration de la direction qui sera utilisé pour stocker l'entier donné par le joueur
    int playerX = 0; //déclaration du x du joueur
    int playerY = 0; //déclaration du y du joueur
    int* pointeurPlayerX = &playerX; //déclaration du pointeur du x du joueur
    int* pointeurPlayerY = &playerY; //déclaration du pointeur du y du joueur
    int iCompteurDeplacement = 0;

    initGrid(grid, pointeurPlayerX, pointeurPlayerY); //appel de la fonction pour initialiser la grille
    while (!WIN) //tant que le joueur n'a pas gagné (boucle de jeu)
    {
            displayGrid(grid); //appel de la fonction pour afficher la grille

            printf("Deplacement(1:haut, 2:bas, 3:gauche, 4:droite) : "); //on affiche les instructions de déplacements
            scanf_s("%d", &direction); //on demande la direction au joueur
            while (direction < 1 || direction > 4) //si la direction n'est pas valable on continue jusqu'à qu'elle le soit
            {
                printf("Deplacement(1:haut, 2:bas, 3:gauche, 4:droite) : "); //on affiche les instructions de déplacements
                scanf_s("%d", &direction); //on demande la direction au joueur
            }

            movePlayer(grid, pointeurPlayerX, pointeurPlayerY, direction); //appel de la fonction pour déplacer le joueur avec la direction souhaitée
            iCompteurDeplacement++;
    }
    printf("Vous avez gagne avec %d deplacement", iCompteurDeplacement); //on affiche au joueur qu'il a gagné avec quel score
    if (iCompteurDeplacement > 1) //si il y a plusieurs déplacements 
    {
        printf("s"); //on rajoute un s au texte
    }
}

/// <summary>
/// Entrée : une grille (matrice) avec une taille de GRID_SIZE par GRID_SIZE et les coordonnées x et y du joueur
/// Fonction qui initialise la grille de taille GRID_SIZE par GRID_SIZE avec tout les éléments de jeu à l'intérieur
/// Sortie : rien
/// </summary>
void initGrid(int grid[GRID_SIZE][GRID_SIZE], int* playerX, int* playerY)
{
    for (int i = 0; i < GRID_SIZE; i++) //boucle pour parcourir la grille en x
    {
        for (int y = 0; y < GRID_SIZE; y++) //boucle pour parcourir la grille en y
        {
            if (i == *playerX && y == *playerY) //si la case de la grille correspond au coordonnées du joueur alors on l'affiche sur cette case
            {
                grid[i][y] = PLAYER;
            }
            else if ((i == 1 && y == 1) || (i == 2 && y == 3) || (i == 3 && y == 2)) //on affiche les obstacles au coordonnées correspondante 
            {
                grid[i][y] = OBSTACLE;
            }
            else if ((i == GRID_SIZE - 1 && y == GRID_SIZE - 1)) //on affiche le trésor en bas à droite
            {
                grid[i][y] = TREASURE;
            }
            else //pour le reste des cases on affiche le '.'
            {
                grid[i][y] = EMPTY;
            }
        }
    }
}

/// <summary>
/// Entrée : une grille (matrice) avec une taille de GRID_SIZE par GRID_SIZE
/// Fonction qui affiche la grille avec tout les éléments de jeu à l'intérieur
/// Sortie : affichage en texte de la grille et ses éléments et retourne la direction choisie
/// </summary>
void displayGrid(int grid[GRID_SIZE][GRID_SIZE])
{
    for (int i = 0; i < GRID_SIZE; i++) //boucle pour parcourir la grille 
    {
        for (int y = 0; y < GRID_SIZE; y++)
        {
            printf("%c ", grid[y][i]); //on affiche chaque cases 

            if (y == 4) //si on arrive à la dernière case de la ligne 
            {
                printf("\n"); //on passe à la ligne suivante
            }
        }
    }
}

/// <summary>
/// Entrée : une grille (matrice) avec une taille de GRID_SIZE par GRID_SIZE, les coordonnées x et y du joueur et la direction sous forme d'entier
/// Fonction qui bouge le joueur dans la grille par la direction donnée
/// Sortie : rien
/// </summary>
void movePlayer(int grid[GRID_SIZE][GRID_SIZE], int* playerX, int* playerY, int direction)
{
    int newX = *playerX; //on instantie une variable pour la nouvelle coordonnée x par celle actuelle
    int newY = *playerY; //on instantie une variable pour la nouvelle coordonnée y par celle actuelle

    //on gère les nouvelles coordonnées en fonction de l'input du joueur
    if (direction == 1)
    {
        newY--;
    }
    else if (direction == 2)
    {
        newY++;
    }
    else if (direction == 3)
    {
        newX--;
    }
    else if (direction == 4)
    {
        newX++;
    }

    //on s'assure que le joueur ne sors pas de la grille (ses coordonnées)
    if (newX < 0)
    {
        newX = 0;
    }
    else if (newX > 4)
    {
        newX = 4;
    }
    else if (newY < 0)
    {
        newY = 0;
    }
    else if (newY > 4)
    {
        newY = 4;
    }
    
    while (grid[newX][newY] == EMPTY) //tant que la prochaine case est bien vide
    {
        for (int i = 0; i < GRID_SIZE; i++) //on parcours la grille 
        {
            for (int y = 0; y < GRID_SIZE; y++)
            {
                if (grid[i][y] == PLAYER) //si la case actuelle dans la boucle est le joueur
                {
                    grid[i][y] = EMPTY; //on transforme le joueur en case vide '.'
                }
                if (i == newX && y == newY) //si la case actuelle dans la boucle est la prochaine coordonnée
                {
                    grid[i][y] = PLAYER; //on transforme la case en joueur '@'
                }
            }
        }
    }

    if (grid[newX][newY] == OBSTACLE) //si la prochaine coordonnée est un obstacle 
    {
        //les coordonnées actuelles restent les mêmes
        newX = *playerX;
        newY = *playerY;
    }

    if (grid[newX][newY] == TREASURE) //si la prochaine coordonnée est le trésor
    {
        WIN = true; //on active la victoire
    }

    //on met les nouvelles coordonnées dans celles actuelles
    *playerX = newX; 
    *playerY = newY;
}

// Exécuter le programme : Ctrl+F5 ou menu Déboguer > Exécuter sans débogage
// Déboguer le programme : F5 ou menu Déboguer > Démarrer le débogage

// Astuces pour bien démarrer : 
//   1. Utilisez la fenêtre Explorateur de solutions pour ajouter des fichiers et les gérer.
//   2. Utilisez la fenêtre Team Explorer pour vous connecter au contrôle de code source.
//   3. Utilisez la fenêtre Sortie pour voir la sortie de la génération et d'autres messages.
//   4. Utilisez la fenêtre Liste d'erreurs pour voir les erreurs.
//   5. Accédez à Projet > Ajouter un nouvel élément pour créer des fichiers de code, ou à Projet > Ajouter un élément existant pour ajouter des fichiers de code existants au projet.
//   6. Pour rouvrir ce projet plus tard, accédez à Fichier > Ouvrir > Projet et sélectionnez le fichier .sln.
