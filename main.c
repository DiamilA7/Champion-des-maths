#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Fonction Addition
void Jouer_Addition() {
    int x, y, reponse;
    char continuer;
    do {
        x = rand() % 101;
        y = rand() % 101;

        printf("\nCombien fait %d + %d ? ", x, y);
        scanf("%d", &reponse);
        printf("Tu as entré : %d\n", reponse);

        if (reponse == x + y) {
            printf("^_^ Bravo, c'est correct !\n");
            score1++;
        } else {
            printf("T_T Perdu ! La bonne réponse était %d.\n", x + y);
        }

        printf("On continue ? (O = Oui / N = Non) ");
        scanf(" %c", &continuer);
    } while (continuer != 'N' && continuer != 'n');
    printf("Ton score en addition est de %d\n", score1);
}

// Fonction Soustraction
void Jouer_Soustraction() {
    int x, y, reponse;
    char continuer;
    int score2 = 0;
    do {
        x = rand() % 101;
        y = rand() % 101;
        if (x < y) {
            int temp = x;
            x = y;
            y = temp;
        }

        printf("\nCombien fait %d - %d ? ", x, y);
        scanf("%d", &reponse);
        printf("Tu as entré : %d\n", reponse);

        if (reponse == x - y) {
            printf("^_^ Bravo, c'est correct !\n");
            score2++;
        } else {
            printf("T_T Perdu ! La bonne réponse était %d.\n", x - y);
        }

        printf("On continue ? (O = Oui / N = Non) ");
        scanf(" %c", &continuer);

    } while (continuer != 'N' && continuer != 'n');
    printf("Ton score en soustraction est de %d\n", score2);
}

// Fonction Multiplication
void Jouer_Multiplication() {
    int x, y, reponse;
    char continuer;
    int score3 = 0;
    do {
        x = rand() % 11;
        y = rand() % 11;

        printf("\nCombien fait %d x %d ? ", x, y);
        scanf("%d", &reponse);
        printf("Tu as entré : %d\n", reponse);

        if (reponse == x * y) {
            printf("^_^ Bravo, c'est correct !\n");
            score3++;
        } else {
            printf("T_T Perdu ! La bonne réponse était %d.\n", x * y);
        }

        printf("On continue ? (O = Oui / N = Non) ");
        scanf(" %c", &continuer);
    } while (continuer != 'N' && continuer != 'n');
    printf("Ton score en multiplication est de %d\n", score3);
}

// Fonction Division
void Jouer_Division() {
    int x, y, reponse;
    char continuer;
    int score4 = 0;
    do {
        y = (rand() % 10) + 1;
    int score1 = 0;
        x = y * (rand() % 11);

        printf("\nCombien fait %d / %d ? ", x, y);
        scanf("%d", &reponse);
        printf("Tu as entré : %d\n", reponse);

        if (reponse == x / y) {
            printf("^_^ Bravo, c'est correct !\n");
            score4++;
        } else {
            printf("T_T Perdu ! La bonne réponse était %d.\n", x / y);
        }

        printf("On continue ? (O = Oui / N = Non) ");
        scanf(" %c", &continuer);
    } while (continuer != 'N' && continuer != 'n');
    printf("Ton score en division est de %d\n", score4);
}

// Table de multiplication
void Table_de_Multiplication() {
    int choix, i, reponse, correct;
    int score5 = 0;

    do {
        printf("Sur quelle table veux-tu bosser cette fois-ci ? Choisis un nombre entre 1 et 10 : ");
        scanf("%d", &choix);
    } while (choix < 1 || choix > 10);

    printf("\nTable de %d :\n", choix);
    for (i = 1; i <= 10; i++) {
        printf("%d x %d = %d\n", choix, i, choix * i);
    }

    printf("\nMaintenant, testons tes connaissances !\n");

    for (i = 1; i <= 10; i++) {
        printf("%d x %d = ", choix, i);
        scanf("%d", &reponse);
        correct = choix * i;

        if (reponse == correct) {
            score5++;
        } else {
            printf("T_T Oups... Perdu ! La bonne réponse était %d.\n", correct);
        }
    }

    printf("\nTon score en table de multiplication est de %d\n", score5);
}

// Menu principal
void Menu() {
    int choix;
    char prenom[30];

    printf("Comment tu t'appelles ? \n");
    scanf("%s", prenom);
    printf("\nSalut %s, bienvenue dans CALCULO : le jeu qui va faire de toi un super héros en maths !\n", prenom);

    do {
        printf("1 - Addition\n");
        printf("2 - Soustraction\n");
        printf("3 - Multiplication\n");
        printf("4 - Division\n");
        printf("5 - Table de multiplication\n");
        printf("6 - Quitter\n");
        printf("\nChoisissez une option : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                Jouer_Addition();
                break;
            case 2:
                Jouer_Soustraction();
                break;
            case 3:
                Jouer_Multiplication();
                break;
            case 4:
                Jouer_Division();
                break;
            case 5:
                Table_de_Multiplication();
                break;
            case 6:
                printf("Tu nous quittes déjà ? T_T Merci d'avoir joué ! \xc0 bientôt !\n");
                break;
            default:
                printf(":| Choix invalide, réessaie.\n");
        }
    } while (choix != 6);
}

// Fonction main
int main() {
    srand(time(NULL));
    Menu();
    return 0;
}