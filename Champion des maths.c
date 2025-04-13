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
        } else {
            printf("T_T Perdu ! La bonne réponse était %d.\n", x + y);
        }

        printf("On continue ? (O = Oui / N = Non) ");
        scanf(" %c", &continuer);
    } while (continuer != 'N' && continuer != 'n');
}

// Fonction Soustraction
void Jouer_Soustraction() {
    int x, y, reponse;
    char continuer;
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
        } else {
            printf("T_T Perdu ! La bonne réponse était %d.\n", x - y);
        }

        printf("On continue ? (O = Oui / N = Non) ");
        scanf(" %c", &continuer);
    } while (continuer != 'N' && continuer != 'n');
}

// Fonction Multiplication
void Jouer_Multiplication() {
    int x, y, reponse;
    char continuer;
    do {
        x = rand() % 11;
        y = rand() % 11;

        printf("\nCombien fait %d x %d ? ", x, y);
        scanf("%d", &reponse);
        printf("Tu as entré : %d\n", reponse);

        if (reponse == x * y) {
            printf("^_^ Bravo, c'est correct !\n");
        } else {
            printf("T_T Perdu ! La bonne réponse était %d.\n", x * y);
        }

        printf("On continue ? (O = Oui / N = Non) ");
        scanf(" %c", &continuer);
    } while (continuer != 'N' && continuer != 'n');
}

// Fonction Division
void Jouer_Division() {
    int x, y, reponse;
    char continuer;
    do {
        y = (rand() % 10) + 1;
        x = y * (rand() % 11);

        printf("\nCombien fait %d / %d ? ", x, y);
        scanf("%d", &reponse);
        printf("Tu as entré : %d\n", reponse);

        if (reponse == x / y) {
            printf("^_^ Bravo, c'est correct !\n");
        } else {
            printf("T_T Perdu ! La bonne réponse était %d.\n", x / y);
        }

        printf("On continue ? (O = Oui / N = Non) ");
        scanf(" %c", &continuer);
    } while (continuer != 'N' && continuer != 'n');
}

// Table de multiplication
void Table_de_Multiplication() {
    int choix, i, reponse, correct;

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

        if (reponse != correct) {
            printf("T_T Oups... Perdu ! La bonne réponse était %d.\n", correct);
            return;
        }
    }

    printf("Bravo ! Tu as réussi la table de %d sans erreur ! Tu es un crack en multiplication !\n", choix);
}

// Menu principal
void Menu() {
    int choix;

    do {
        printf("\nBienvenue dans CALCULO: le jeu qui va faire de toi un super héros en maths !\n");
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
                printf("Tu nous quittes déjà ? T_T Merci d'avoir joué ! À bientôt !\n");
                break;
            default:
                printf(":| Choix invalide, réessaie.\n");
        }
    } while (choix != 6);
}

// Fonction main
int main() {
    srand(time(NULL)); // Initialisation unique du générateur de nombres aléatoires
    Menu();
    return 0;
}








#include <string.h>

#define FILE_NAME "scores.txt"

// Structure pour stocker les scores
typedef struct {
    char nom[35];
    int score;
} Joueur;
Joueur player;
void Sauvegarder_Score(player) {
    FILE *fichier = fopen(FILE_NAME, "a");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier des scores.\n");
        return;
    }
    fprintf(fichier, "%s %d\n", player.nom, player.score);
    fclose(fichier);
}

// Fonction pour récupérer le score d'un joueur
int Recuperer_Score(char *nom) {
    FILE *fichier = fopen(FILE_NAME, "r");
    if (fichier == NULL) {
        return 0; // Pas de score enregistré
    }
 Joueur player;
    while (fscanf(fichier, "%s %d", player.nom, &player.score) != EOF) {
        if (strcmp(player.nom, nom) == 0) {
            fclose(fichier);
            return player.score;
        }
    }
    fclose(fichier);
    return 0;
}

// Fonction pour gérer une opération mathématique
void Jouer_Operation(char *operation, int (*calcul)(int, int)) {
    int x, y, reponse, score = 0;
    char continuer;

    do {
        x = rand() % 101;
        y = rand() % 101;

        printf("\nCombien fait %d %s %d ? ", x, operation, y);
        scanf("%d", &reponse);

        if (reponse == calcul(x, y)) {
            printf("^_^ Bravo, c'est correct !\n");
            score += 10;
        } else {
            printf("T_T Perdu ! La bonne réponse était %d.\n", calcul(x, y));
        }
        printf("On continue ? (O = Oui / N = Non) ");
        scanf(" %c", &continuer);
    } while (continuer != 'N' && continuer != 'n');
}

// Fonctions de calcul
int Addition(int a, int b) { return a + b; }
int Soustraction(int a, int b) { return (a > b) ? a - b : b - a; }
int Multiplication(int a, int b) { return a * b; }
int Division(int a, int b) { return b == 0 ? 1 : a / b; }

void Menu() {
    int choix;
    Joueur player;
    printf("\nBienvenue dans CALCULO: le jeu qui va faire de toi un super héros en maths !\n");
    printf("Comment tu t'appelles ? ");
    scanf("%s", player.nom);

    player.score = Recuperer_Score(player.nom);
    printf("\n%s, tu as actuellement %d points !\n" player.nom, player.score);

    do {
        printf("\n1 - Addition\n");
        printf("2 - Soustraction\n");
        printf("3 - Multiplication\n");
        printf("4 - Division\n");
        printf("5 - Quitter\n");
        printf("\nChoisissez une option : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                Jouer_Operation("+", Addition);
                break;
            case 2:
                Jouer_Operation("-", Soustraction);
                break;
            case 3:
                Jouer_Operation("x", Multiplication);
                break;
            case 4:
                Jouer_Operation("/", Division);
                break;
            case 5:
                printf("Tu nous quittes déjà ? T_T Merci d'avoir joué ! À bientôt !\n");
                Sauvegarder_Score(joueur);
                break;
            default:
                printf(":| Choix invalide, réessaie.\n");
        }
    } while (choix != 5);
}

int main() {
    srand(time(NULL));
    Menu();
    return 0;
}
