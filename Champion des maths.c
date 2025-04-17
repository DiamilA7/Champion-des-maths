#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

// Constantes pour la logique du jeu
#define MAX_ESSAIS 3       // Nombre maximum d'essais par question
#define POINT_BONUS 1      // Point attribue pour terminer un mini-jeu
#define NOM_MAX 30         // Longueur maximale du nom du joueur
#define LIGNE_MAX 100      // Longueur maximale d'une ligne dans scores.txt

// Variable globale pour le score du joueur
int score_global = 0;

// Structure pour stocker les informations d'un score
typedef struct {
    char nom[NOM_MAX];  // Nom du joueur
    char date[20];      // Date de la sauvegarde
    int score;          // Score obtenu
} Joueur;

// Vide le buffer d'entree pour eviter les erreurs de scanf
void vider_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Lit un entier valide depuis l'entree utilisateur
int lire_entier() {
    int valeur;
    char buffer[32];
    while (1) {
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            // Verifie si l'entree est un entier valide
            char *endptr;
            long val = strtol(buffer, &endptr, 10);
            if (endptr != buffer && (*endptr == '\n' || *endptr == '\0')) {
                valeur = (int)val;
                return valeur;
            }
        }
        printf("Entree invalide, entrez un nombre : ");
        vider_buffer();
    }
}

// Lit une chaine securisee pour le nom du joueur
void lire_nom(char *nom, int taille) {
    if (fgets(nom, taille, stdin) != NULL) {
        // Supprime le '\n' final
        nom[strcspn(nom, "\n")] = '\0';
        // Verifie si la chaine est vide
        if (strlen(nom) == 0) {
            strcpy(nom, "Anonyme");
        }
    } else {
        strcpy(nom, "Anonyme");
    }
}

// Sauvegarde le score dans scores.txt
void sauvegarder_score(char *nom, int score) {
    // Ouvre le fichier en mode ajout
    FILE *fichier = fopen("scores.txt", "a");
    if (fichier == NULL) {
        printf("Erreur : impossible d'ouvrir scores.txt pour sauvegarde.\n");
        return;
    }
    // Obtient la date actuelle
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    char date[20];
    strftime(date, sizeof(date), "%Y-%m-%d %H:%M:%S", tm);
    // Ecrit le score au format : nom date score
    fprintf(fichier, "%s %s %d\n", nom, date, score);
    fclose(fichier);
}

// Charge le dernier score d’un joueur depuis scores.txt
int charger_score(char *nom) {
    // Ouvre le fichier en mode lecture
    FILE *fichier = fopen("scores.txt", "r");
    if (fichier == NULL) {
        return 0; // Fichier inexistant, score initial = 0
    }
    char ligne[LIGNE_MAX];
    int score = 0;
    // Parcourt chaque ligne du fichier
    while (fgets(ligne, LIGNE_MAX, fichier)) {
        char nom_fichier[NOM_MAX];
        char date[20];
        int score_lu;
        // Extrait les informations de la ligne
        if (sscanf(ligne, "%29s %19s %d", nom_fichier, date, &score_lu) == 3) {
            if (strcmp(nom, nom_fichier) == 0) {
                score = score_lu; // Met a jour avec le dernier score trouve
            }
        }
    }
    fclose(fichier);
    return score;
}

// Mini-jeu : Addition de nombres entiers
void Jouer_Addition() {
    int x, y, reponse, essais, points;
    char continuer;
    do {
        // Genere deux nombres aleatoires entre 0 et 100
        x = rand() % 101;
        y = rand() % 101;
        essais = 0;
        points = 0;

        printf("\nCombien fait %d + %d ? ", x, y);
        do {
            essais++;
            reponse = lire_entier();
            printf("Tu as entre : %d\n", reponse);

            if (reponse == x + y) {
                // Attribue des points selon l'essai
                if (essais == 1) points = 10;
                else if (essais == 2) points = 5;
                else points = 1;
                printf("^_^ Bravo, c'est correct ! (%d points)\n", points);
                score_global += points;
                break;
            } else {
                printf("T_T Incorrect. Essaie encore (essai %d/%d) : ", essais, MAX_ESSAIS);
                if (essais == MAX_ESSAIS) {
                    printf("\nPerdu ! La bonne reponse etait %d.\n", x + y);
                    break;
                }
            }
        } while (essais < MAX_ESSAIS);

        printf("On continue ? (O = Oui / N = Non) ");
        scanf(" %c", &continuer);
        vider_buffer();
    } while (continuer != 'N' && continuer != 'n');
    score_global += POINT_BONUS; // Bonus pour avoir joue
    printf("Ton score total est de %d\n", score_global);
}

// Mini-jeu : Soustraction de nombres entiers
void Jouer_Soustraction() {
    int x, y, reponse, essais, points;
    char continuer;
    do {
        // Genere deux nombres, x >= y pour eviter les negatifs
        x = rand() % 101;
        y = rand() % 101;
        if (x < y) {
            int temp = x;
            x = y;
            y = temp;
        }
        essais = 0;
        points = 0;

        printf("\nCombien fait %d - %d ? ", x, y);
        do {
            essais++;
            reponse = lire_entier();
            printf("Tu as entre : %d\n", reponse);

            if (reponse == x - y) {
                if (essais == 1) points = 10;
                else if (essais == 2) points = 5;
                else points = 1;
                printf("^_^ Bravo, c'est correct ! (%d points)\n", points);
                score_global += points;
                break;
            } else {
                printf("T_T Incorrect. Essaie encore (essai %d/%d) : ", essais, MAX_ESSAIS);
                if (essais == MAX_ESSAIS) {
                    printf("\nPerdu ! La bonne reponse etait %d.\n", x - y);
                    break;
                }
            }
        } while (essais < MAX_ESSAIS);

        printf("On continue ? (O = Oui / N = Non) ");
        scanf(" %c", &continuer);
        vider_buffer();
    } while (continuer != 'N' && continuer != 'n');
    score_global += POINT_BONUS;
    printf("Ton score total est de %d\n", score_global);
}

// Mini-jeu : Multiplication de nombres
void Jouer_Multiplication() {
    int x, y, reponse, essais, points;
    char continuer;
    do {
        // Genere deux nombres entre 1 et 10
        x = rand() % 10 + 1;
        y = rand() % 10 + 1;
        essais = 0;
        points = 0;

        printf("\nCombien fait %d x %d ? ", x, y);
        do {
            essais++;
            reponse = lire_entier();
            printf("Tu as entre : %d\n", reponse);

            if (reponse == x * y) {
                if (essais == 1) points = 10;
                else if (essais == 2) points = 5;
                else points = 1;
                printf("^_^ Bravo, c'est correct ! (%d points)\n", points);
                score_global += points;
                break;
            } else {
                printf("T_T Incorrect. Essaie encore (essai %d/%d) : ", essais, MAX_ESSAIS);
                if (essais == MAX_ESSAIS) {
                    printf("\nPerdu ! La bonne reponse etait %d.\n", x * y);
                    break;
                }
            }
        } while (essais < MAX_ESSAIS);

        printf("On continue ? (O = Oui / N = Non) ");
        scanf(" %c", &continuer);
        vider_buffer();
    } while (continuer != 'N' && continuer != 'n');
    score_global += POINT_BONUS;
    printf("Ton score total est de %d\n", score_global);
}

// Mini-jeu : Division entiere
void Jouer_Division() {
    int x, y, reponse, essais, points;
    char continuer;
    do {
        // Genere un diviseur (1-10) et un dividende divisible
        y = rand() % 10 + 1;
        x = y * (rand() % 11);
        essais = 0;
        points = 0;

        printf("\nCombien fait %d / %d ? ", x, y);
        do {
            essais++;
            reponse = lire_entier();
            printf("Tu as entre : %d\n", reponse);

            if (reponse == x / y) {
                if (essais == 1) points = 10;
                else if (essais == 2) points = 5;
                else points = 1;
                printf("^_^ Bravo, c'est correct ! (%d points)\n", points);
                score_global += points;
                break;
            } else {
                printf("T_T Incorrect. Essaie encore (essai %d/%d) : ", essais, MAX_ESSAIS);
                if (essais == MAX_ESSAIS) {
                    printf("\nPerdu ! La bonne reponse etait %d.\n", x / y);
                    break;
                }
            }
        } while (essais < MAX_ESSAIS);

        printf("On continue ? (O = Oui / N = Non) ");
        scanf(" %c", &continuer);
        vider_buffer();
    } while (continuer != 'N' && continuer != 'n');
    score_global += POINT_BONUS;
    printf("Ton score total est de %d\n", score_global);
}

// Mini-jeu : Apprentissage et test d'une table de multiplication
void Table_de_Multiplication() {
    int choix, i, reponse, correct, tout_correct = 1;
    // Demande une table valide (1-10)
    do {
        printf("Sur quelle table veux-tu bosser ? Choisis un nombre entre 1 et 10 : ");
        choix = lire_entier();
    } while (choix < 1 || choix > 10);

    // Affiche la table
    printf("\nTable de %d :\n", choix);
    for (i = 1; i <= 10; i++) {
        printf("%d x %d = %d\n", choix, i, choix * i);
    }

    // Teste les connaissances
    printf("\nMaintenant, testons tes connaissances !\n");
    for (i = 1; i <= 10; i++) {
        printf("%d x %d = ", choix, i);
        reponse = lire_entier();
        correct = choix * i;

        if (reponse == correct) {
            printf("Gagne !\n");
        } else {
            printf("T_T Perdu ! La bonne reponse etait %d.\n", correct);
            tout_correct = 0;
        }
    }

    // Bonus si toutes les reponses sont correctes
    if (tout_correct) {
        printf("\nFelicitations, tu as tout juste !\n");
        score_global += 10;
    } else {
        printf("\nDommage, tu as fait des erreurs.\n");
    }
    score_global += POINT_BONUS;
    printf("Ton score total est de %d\n", score_global);
}

// Mini-jeu : Addition de fractions avec meme denominateur
void Jouer_Fractions() {
    int num1, num2, denom, reponse_num, reponse_denom, essais, points;
    char continuer;
    do {
        // Genere une fraction simple (denominateur 2-6)
        denom = rand() % 5 + 2;
        num1 = rand() % denom;
        num2 = rand() % denom;
        essais = 0;
        points = 0;

        printf("\nCombien fait %d/%d + %d/%d ? ", num1, denom, num2, denom);
        printf("Entrez le numerateur et le denominateur (separes par un espace) : ");
        do {
            essais++;
            reponse_num = lire_entier();
            reponse_denom = lire_entier();
            printf("Tu as entre : %d/%d\n", reponse_num, reponse_denom);

            if (reponse_num == num1 + num2 && reponse_denom == denom) {
                if (essais == 1) points = 10;
                else if (essais == 2) points = 5;
                else points = 1;
                printf("^_^ Bravo, c'est correct ! (%d points)\n", points);
                score_global += points;
                break;
            } else {
                printf("T_T Incorrect. Essaie encore (essai %d/%d) : ", essais, MAX_ESSAIS);
                if (essais == MAX_ESSAIS) {
                    printf("\nPerdu ! La bonne reponse etait %d/%d.\n", num1 + num2, denom);
                    break;
                }
            }
        } while (essais < MAX_ESSAIS);

        printf("On continue ? (O = Oui / N = Non) ");
        scanf(" %c", &continuer);
        vider_buffer();
    } while (continuer != 'N' && continuer != 'n');
    score_global += POINT_BONUS;
    printf("Ton score total est de %d\n", score_global);
}

// Mini-jeu : Comparaison de nombres
void Jouer_Comparaison() {
    int n1, n2, essais, points;
    char reponse, correct;
    char continuer;
    do {
        // Genere deux nombres entre 1 et 100
        n1 = rand() % 100 + 1;
        n2 = rand() % 100 + 1;
        essais = 0;
        points = 0;

        // Determine la reponse correcte
        if (n1 > n2) correct = '>';
        else if (n1 < n2) correct = '<';
        else correct = '=';

        printf("\nComparez %d et %d. Entrez >, < ou = : ", n1, n2);
        do {
            essais++;
            scanf(" %c", &reponse);
            printf("Tu as entre : %c\n", reponse);
            vider_buffer();

            if (reponse == correct) {
                if (essais == 1) points = 10;
                else if (essais == 2) points = 5;
                else points = 1;
                printf("^_^ Bravo, c'est correct ! (%d points)\n", points);
                score_global += points;
                break;
            } else {
                printf("T_T Incorrect. Essaie encore (essai %d/%d) : ", essais, MAX_ESSAIS);
                if (essais == MAX_ESSAIS) {
                    printf("\nPerdu ! La bonne reponse etait %c.\n", correct);
                    break;
                }
            }
        } while (essais < MAX_ESSAIS);

        printf("On continue ? (O = Oui / N = Non) ");
        scanf(" %c", &continuer);
        vider_buffer();
    } while (continuer != 'N' && continuer != 'n');
    score_global += POINT_BONUS;
    printf("Ton score total est de %d\n", score_global);
}

// Menu principal du jeu
void Menu() {
    int choix;
    char nom[NOM_MAX];

    // Verifie si scores.txt peut etre cree
    FILE *fichier = fopen("scores.txt", "a");
    if (fichier == NULL) {
        printf("Erreur : impossible de creer scores.txt. Les scores ne seront pas sauvegardes.\n");
    } else {
        fclose(fichier);
    }

    // Demande et lit le nom du joueur
    printf("Comment vous appelez-vous ? ");
    lire_nom(nom, NOM_MAX);
    score_global = charger_score(nom);
    printf("\nSalut %s, bienvenue dans CHAMPION DES MATHS !\n", nom);
    printf("Score actuel : %d\n", score_global);

    // Boucle du menu
    do {
        // Affiche le menu avec cadre ASCII
        printf("+-----------------------------------+\n");
        printf("|1 : Addition                     |\n");
        printf("|2 : Soustraction                 |\n");
        printf("|3 : Multiplication               |\n");
        printf("|4 : Division                     |\n");
        printf("|5 : Tables de multiplication      |\n");
        printf("|6 : Fractions                    |\n");
        printf("|7 : Comparaison de nombres        |\n");
        printf("|0 : Sortir du jeu                |\n");
        printf("+-----------------------------------+\n");
        printf("Quel est votre choix ? ");
        choix = lire_entier();

        // Traite le choix de l'utilisateur
        switch (choix) {
            case 1:
                printf("Addition\n");
                Jouer_Addition();
                sauvegarder_score(nom, score_global);
                break;
            case 2:
                printf("Soustraction\n");
                Jouer_Soustraction();
                sauvegarder_score(nom, score_global);
                break;
            case 3:
                printf("Multiplication\n");
                Jouer_Multiplication();
                sauvegarder_score(nom, score_global);
                break;
            case 4:
                printf("Division\n");
                Jouer_Division();
                sauvegarder_score(nom, score_global);
                break;
            case 5:
                printf("Tables de multiplication\n");
                Table_de_Multiplication();
                sauvegarder_score(nom, score_global);
                break;
            case 6:
                printf("Fractions\n");
                Jouer_Fractions();
                sauvegarder_score(nom, score_global);
                break;
            case 7:
                printf("Comparaison de nombres\n");
                Jouer_Comparaison();
                sauvegarder_score(nom, score_global);
                break;
            case 0:
                printf("Ton score final est de %d points.\n", score_global);
                printf("Merci de votre visite\n");
                break;
            default:
                printf("Choix invalide, reessayez.\n");
        }
    } while (choix != 0);
}

// Point d'entree du programme
int main() {
    // Initialise le generateur de nombres aleatoires
    srand(time(NULL));
    Menu();
    return 0;
}
