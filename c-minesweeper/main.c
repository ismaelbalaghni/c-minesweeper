
#include <stdio.h>

#include <time.h>

#include <stdlib.h>

typedef struct tableau_s tableau_s;

struct tableau_s

{

    char etat;

    int cache;

    int devoile;

    int drapeau;
};

int nb_devoile;

tableau_s tableau[100][100];

void effacer_ecran(void) //fonction pour effacer l'�cran

{

    //printf("%c[2J", 0x1B);

    //system("cls");
}

int nb_aleatoire(int min, int max) //fonction pour g�n�rer un nombre al�atoire

{

    return (rand() % (max - min + 1)) + min;
}

void coordonnee_aleatoire(int tailleX, int tailleY, int *x, int *y) //fonction pour generer des cooordonnees aleatoire

{

    *x = nb_aleatoire(0, tailleX - 1);

    *y = nb_aleatoire(0, tailleY - 1);
}

void affichage_verif(int tailleX, int tailleY)

{

    int i, j;

    for (i = 0; i < tailleX; i++)

    {

        for (j = 0; j < tailleY; j++)

        {

            if (tableau[i][j].etat == 'r' || tableau[i][j].etat == 'b')

            {

                printf("%c ", tableau[i][j].etat);
            }

            else

            {

                printf("%d ", tableau[i][j].etat);
            }
        }

        printf("\n");
    }
}

void affichage_tableau(int tailleX, int tailleY)

{

    int i, j;

    for (i = 0; i < tailleX; i++)

    {

        for (j = 0; j < tailleY; j++)

        {

            if (tableau[i][j].drapeau == 1)
            {

                printf("# ");
            }

            else if (tableau[i][j].cache == 1)

            {

                printf("* ");
            }

            else

            {

                if (tableau[i][j].etat == 'r' || tableau[i][j].etat == 'b')

                {

                    printf("%c ", tableau[i][j].etat);
                }

                else

                {

                    printf("%d ", tableau[i][j].etat);
                }
            }
        }

        printf("\n");
    }
}

void remplissage_tableau(int tailleX, int tailleY)

{

    int i, j, compteur;

    for (i = 0; i < tailleX; i++)

    {

        for (j = 0; j < tailleY; j++)

        {

            compteur = 0;

            if (tableau[i][j].etat == 'r')

            {

                //on compte le nombre de bombe autour de la case

                if (tableau[i + 1][j].etat == 'b' && i + 1 < tailleX)

                {

                    compteur++;
                }

                if (tableau[i + 1][j + 1].etat == 'b' && j + 1 < tailleY && i + 1 < tailleX)

                {

                    compteur++;
                }

                if (tableau[i][j + 1].etat == 'b' && j + 1 < tailleY)

                {

                    compteur++;
                }

                if (tableau[i - 1][j + 1].etat == 'b' && j + 1 < tailleY && i - 1 >= 0)

                {

                    compteur++;
                }

                if (tableau[i - 1][j].etat == 'b' && i - 1 >= 0)

                {

                    compteur++;
                }

                if (tableau[i - 1][j - 1].etat == 'b' && j - 1 >= 0 && i - 1 >= 0)

                {

                    compteur++;
                }

                if (tableau[i][j - 1].etat == 'b' && j - 1 >= 0)

                {

                    compteur++;
                }

                if (tableau[i + 1][j - 1].etat == 'b' && i + 1 < tailleX && j - 1 >= 0)

                {

                    compteur++;
                }

                if (compteur != 0)

                {

                    tableau[i][j].etat = compteur;
                }
            }
        }
    }
}

int saisie_coordonnees(int tailleX, int tailleY, int *coord1, int *coord2)

{

    int ok;

    char action;

    int act;

    do

    {

        printf("\nIndiquer action (bombe ou drapeau) et quelles coordonnees : ");

        scanf("%c %d %d", &action, coord1, coord2);

        if ((*coord1 < 0) || (*coord1 > tailleX))

        {

            printf("\n");

            printf("Coordonnee inexistante\n");

            ok = 0;
        }

        else if ((*coord2 < 0) || (*coord2 > tailleY))

        {

            printf("\n");

            printf("Coordonnee inexistante\n");

            ok = 0;
        }

        /*else if(action!='b' || action!='d')

        {

        	printf("\nAction incorrecte");

        	ok = 0;

        }*/

        else

        {

            printf("\nVous avez selectionne la case %d %d\n", *coord1, *coord2);

            ok = 1;

            while (getchar() != '\n')
            {
            };
        }

    }

    while (ok != 1);

    if (action == 'b')

    {

        act = 1;
    }

    else

    {

        act = 0;
    }

    return act;
}

int devoiler(int tailleX, int tailleY)

{

    int i, j, modif = 0;

    for (i = 0; i < tailleX; i++)

    {

        for (j = 0; j < tailleY; j++)

        {

            if ((tableau[i][j].devoile == 0) && (tableau[i][j].cache == 0) && tableau[i][j].etat == 'r')

            {

                tableau[i][j].devoile = 1;

                modif = 1;

                if ((i) + 1 < tailleX)

                {

                    if (tableau[i + 1][j].cache == 1)
                    {

                        tableau[i + 1][j].cache = 0;

                        nb_devoile++;
                    }
                }

                if ((j) + 1 < tailleY && (i) + 1 < tailleX)

                {

                    if (tableau[i + 1][j + 1].cache == 1)
                    {

                        tableau[i + 1][j + 1].cache = 0;

                        nb_devoile++;
                    }
                }

                if ((j) + 1 < tailleY)

                {

                    if (tableau[i][j + 1].cache == 1)
                    {

                        tableau[i][j + 1].cache = 0;

                        nb_devoile++;
                    }
                }

                if ((j) + 1 < tailleY && (i)-1 >= 0)

                {

                    if (tableau[i - 1][j + 1].cache == 1)
                    {

                        tableau[i - 1][j + 1].cache = 0;

                        nb_devoile++;
                    }
                }

                if ((i)-1 >= 0)

                {

                    if (tableau[i - 1][j].cache == 1)
                    {

                        tableau[i - 1][j].cache = 0;

                        nb_devoile++;
                    }
                }

                if ((j)-1 >= 0 && (i)-1 >= 0)

                {

                    if (tableau[i - 1][j - 1].cache == 1)
                    {

                        tableau[i - 1][j - 1].cache = 0;

                        nb_devoile++;
                    }
                }

                if ((j)-1 >= 0)

                {

                    if (tableau[i][j - 1].cache == 1)
                    {

                        tableau[i][j - 1].cache = 0;

                        nb_devoile++;
                    }
                }

                if ((i) + 1 < tailleX && (j)-1 >= 0)

                {

                    if (tableau[i + 1][j - 1].cache == 1)
                    {

                        tableau[i + 1][j - 1].cache = 0;

                        nb_devoile++;
                    }
                }
            }
        }
    }

    return modif;
}

int main()

{

    int tailleX, tailleY;

    int i, j, x, y, ok;

    int nb_bombe;

    int jeu;

    int entreeX;

    int entreeY;

    int modif;

    int nb_cases;
    char rejouer;
    int rej;

    //int nb_devoile;

    srand(time(NULL)); //g�n�ration al�atoire

    printf("Taille en X et Y : "); //saisie de la taille

    scanf("%d %d", &tailleX, &tailleY);

    effacer_ecran();

    for (i = 0; i < tailleX; i++) // on met des 0 dans tout le tableau

    {

        for (j = 0; j < tailleY; j++)

        {

            tableau[i][j].etat = 'r';

            tableau[i][j].cache = 1;

            tableau[i][j].devoile = 0;
        }
    }

    effacer_ecran();

    //Choix du nombre de bombes

    printf("Nombre de bombes : ");

    scanf("%d", &nb_bombe);

    //ajoute les bombes sur le tableau

    for (i = 0; i < nb_bombe; i++)

    {

        ok = 0;

        while (ok == 0)

        {

            ok = 1;

            coordonnee_aleatoire(tailleX, tailleX, &x, &y); //on genere des coordonn�es au hasard

            if (tableau[x][y].etat == 'b') //si les coordonn�e sont deja utilis� par une bombe, ok ==0

            {

                ok = 0;
            }

        } //si ok = 0, on re genere une autre coordonn�e pour la bombe

        tableau[x][y].etat = 'b';
    }

    //affichage du tableau

    affichage_verif(tailleX, tailleY);

    getchar();

    //remplissage des autres case avec les valeurs

    remplissage_tableau(tailleX, tailleY);

    printf("\n");

    //affichage du tableau

    affichage_tableau(tailleX, tailleY);

    nb_devoile = 0;

    jeu = 0;

    do
    {
        do

        {

            if (saisie_coordonnees(tailleX, tailleY, &entreeY, &entreeX) == 1)

            {

                effacer_ecran();

                tableau[entreeX - 1][entreeY - 1].devoile = 1;

                tableau[entreeX - 1][entreeY - 1].cache = 0;

                nb_cases = tailleX * tailleY;

                nb_devoile++;

                if (tableau[entreeX - 1][entreeY - 1].etat == 'b')

                {

                    jeu = -1;
                }

                else if (tableau[entreeX - 1][entreeY - 1].etat == 'r')

                {

                    if ((entreeX - 1) + 1 < tailleX)

                    {

                        if (tableau[entreeX - 1 + 1][entreeY - 1].cache == 1)
                        {

                            tableau[entreeX - 1 + 1][entreeY - 1].cache = 0;

                            nb_devoile++;
                        }
                    }

                    if ((entreeY - 1) + 1 < tailleY && (entreeX - 1) + 1 < tailleX)

                    {

                        if (tableau[entreeX - 1 + 1][entreeY - 1 + 1].cache == 1)
                        {

                            tableau[entreeX - 1 + 1][entreeY - 1 + 1].cache = 0;

                            nb_devoile++;
                        }
                    }

                    if ((entreeY - 1) + 1 < tailleY)

                    {

                        if (tableau[entreeX - 1][entreeY - 1 + 1].cache == 1)
                        {

                            tableau[entreeX - 1][entreeY - 1 + 1].cache = 0;

                            nb_devoile++;
                        }
                    }

                    if ((entreeY - 1) + 1 < tailleY && (entreeX - 1) - 1 >= 0)

                    {

                        if (tableau[entreeX - 1 - 1][entreeY - 1 + 1].cache == 1)
                        {

                            tableau[entreeX - 1 - 1][entreeY - 1 + 1].cache = 0;

                            nb_devoile++;
                        }
                    }

                    if ((entreeX - 1) - 1 >= 0)

                    {

                        if (tableau[entreeX - 1 - 1][entreeY - 1].cache == 1)
                        {

                            tableau[entreeX - 1 - 1][entreeY - 1].cache = 0;

                            nb_devoile++;
                        }
                    }

                    if ((entreeY - 1) - 1 >= 0 && (entreeX - 1) - 1 >= 0)

                    {

                        if (tableau[entreeX - 1 - 1][entreeY - 1 - 1].cache == 1)
                        {

                            tableau[entreeX - 1 - 1][entreeY - 1 - 1].cache = 0;

                            nb_devoile;
                        }
                    }

                    if ((entreeY - 1) - 1 >= 0)

                    {

                        if (tableau[entreeX - 1][entreeY - 1 - 1].cache == 1)
                        {

                            tableau[entreeX - 1][entreeY - 1 - 1].cache = 0;

                            nb_devoile++;
                        }
                    }

                    if ((entreeX - 1) + 1 < tailleX && (entreeY - 1) - 1 >= 0)

                    {

                        if (tableau[entreeX - 1 + 1][entreeY - 1 - 1].cache == 1)
                        {

                            tableau[entreeX - 1 + 1][entreeY - 1 - 1].cache = 0;

                            nb_devoile++;
                        }
                    }

                    do

                    {

                        modif = devoiler(tailleX, tailleY);

                    }

                    while (modif == 1);
                }
            }

            else

            {

                if (tableau[entreeX - 1][entreeY - 1].drapeau == 0)
                {

                    tableau[entreeX - 1][entreeY - 1].drapeau = 1;
                }

                else
                {

                    tableau[entreeX - 1][entreeY - 1].drapeau = 0;
                }
            }

            affichage_tableau(tailleX, tailleY);

            if (nb_devoile == nb_cases - nb_bombe)
            {
                jeu = 1;
            }

        } while (jeu == 0);
        if (jeu == -1)
        {
            printf("Perdu !\n");
        }
        if (jeu == 1)
        {
            printf("Gagne !\n");
        }
        printf("\nVoulez vous rejouer ? (o/n)");
        scanf("%c", &rejouer);
        if (rejouer == 'o')
        {
            rej = 1;
        }
        else
        {
            rej = 0;
        }
    } while (rej != 0);

    exit(0);

    return 0;
}
