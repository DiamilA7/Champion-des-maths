// Inclusion des bibliotheques standard
#include <stdio.h>      // Pour afficher (printf) et lire (scanf) du texte
#include <stdlib.h>     // Pour les nombres aleatoires (rand) et autres outils
#include <time.h>       // Pour obtenir la date et l'heure (time)
#include <string.h>     // Pour manipuler des chaines (strlen, strcpy)
#include <ctype.h>      // Pour travailler avec des caracteres (non utilise ici)

// Constantes du jeu (valeurs fixes)
#define MAX_ESSAIS 3    // Nombre max d'essais pour une question (3 chances)
#define POINT_BONUS 1   // Point donne a la fin d'un mini-jeu, meme si echec
#define NOM_MAX 30      // Longueur max du nom du joueur (30 lettres)
#define LIGNE_MAX 100   // Longueur max d'une ligne dans scores.txt (100 caracteres)

// Variable globale pour le score total du joueur
int score_global = 0; // Commence a 0, augmente avec les points gagnes

// Structure pour regrouper les infos d'un joueur
typedef struct {
    char nom[NOM_MAX];  // Nom du joueur (max 30 caracteres)
    char date[20];      // Date de la partie (ex. 2025-04-22 14:30:00)
    int score;          // Score obtenu (nombre entier)
} Joueur;               // Nom de la structure : Joueur

// Vide les caracteres restants dans le clavier
void vider_buffer() {
    int c; // Variable pour stocker chaque caractere
    // Lit chaque caractere jusqu'a une nouvelle ligne ou la fin
    while ((c = getchar()) != '\n' && c != EOF);
}

// Lit un nombre entier tape par le joueur
int lire_entier() {
    int valeur;         // Stocke le nombre final
    char buffer[32];    // Stocke la ligne tapee (max 32 caracteres)
    while (1) {         // Boucle jusqu'a obtenir un nombre valide
        // Lit une ligne entiere depuis le clavier
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            char *endptr;   // Pointe vers la fin du nombre converti
            // Convertit la chaine en nombre
            long val = strtol(buffer, &endptr, 10);
            // Verifie que l'entree est un nombre valide
            if (endptr != buffer && (*endptr == '\n' || *endptr == '\0')) {
                valeur = (int)val; // Stocke le nombre
                return valeur;     // Retourne le nombre
            }
        }
        // Si entree invalide, redemande
        printf("Entree invalide, entrez un nombre : ");
        vider_buffer(); // Nettoie le clavier
    }
}

// Lit trois nombres entiers sur une meme ligne
int lire_trois_entiers(int *n1, int *n2, int *n3) {
    char buffer[100];   // Stocke la ligne tapee (max 100 caracteres)
    while (1) {         // Boucle jusqu'a obtenir trois nombres valides
        // Lit une ligne entiere depuis le clavier
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            // Supprime la nouvelle ligne (\n) a la fin
            buffer[strcspn(buffer, "\n")] = '\0';
            // Essaie de lire trois nombres separes par des espaces
            if (sscanf(buffer, "%d %d %d", n1, n2, n3) == 3) {
                return 1; // Succes : trois nombres lus
            }
        }
        // Si entree invalide, redemande
        printf("Entree invalide, entrez trois nombres separes par des espaces : ");
        vider_buffer(); // Nettoie le clavier
    }
}

// Lit le nom du joueur
void lire_nom(char *nom, int taille) {
    // Lit une ligne entiere depuis le clavier
    if (fgets(nom, taille, stdin) != NULL) {
        // Supprime la nouvelle ligne (\n) a la fin
        nom[strcspn(nom, "\n")] = '\0';
        // Si le nom est vide, utilise "Anonyme"
        if (strlen(nom) == 0) {
            strcpy(nom, "Anonyme");
        }
    } else {
        // Si la lecture echoue, utilise "Anonyme"
        strcpy(nom, "Anonyme");
    }
}

// Sauvegarde le score dans le fichier scores.txt
void sauvegarder_score(char *nom, int score) {
    // Ouvre le fichier en mode ajout (ajoute a la fin)
    FILE *fichier = fopen("scores.txt", "a");
    if (fichier == NULL) {
        // Si le fichier ne peut pas etre ouvert, affiche une erreur
        printf("Erreur : impossible d'ouvrir scores.txt pour sauvegarde.\n");
        return;
    }
    // Recupere la date et l'heure actuelles
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    char date[20]; // Stocke la date (max 20 caracteres)
    // Formate la date (ex. 2025-04-22 14:30:00)
    strftime(date, sizeof(date), "%Y-%m-%d %H:%M:%S", tm);
    // Ecrit une ligne : nom date score
    fprintf(fichier, "%s %s %d\n", nom, date, score);
    fclose(fichier); // Ferme le fichier
}

// Charge le dernier score d'un joueur depuis scores.txt
int charger_score(char *nom) {
    // Ouvre le fichier en mode lecture
    FILE *fichier = fopen("scores.txt", "r");
    if (fichier == NULL) {
        return 0; // Si fichier absent, score initial = 0
    }
    char ligne[LIGNE_MAX]; // Stocke chaque ligne lue
    int score = 0;         // Score a retourner
    // Lit chaque ligne du fichier
    while (fgets(ligne, LIGNE_MAX, fichier)) {
        char nom_fichier[NOM_MAX]; // Nom dans le fichier
        char date[20];             // Date dans le fichier
        int score_lu;              // Score dans le fichier
        // Extrait nom, date, score de la ligne
        if (sscanf(ligne, "%29s %19s %d", nom_fichier, date, &score_lu) == 3) {
            // Si le nom correspond, met a jour le score
            if (strcmp(nom, nom_fichier) == 0) {
                score = score_lu;
            }
        }
    }
    fclose(fichier); // Ferme le fichier
    return score;    // Retourne le dernier score trouve
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




// Mini-jeu : Ordre croissant de nombres
void Jouer_Ordre_Croissant() {
    int n1, n2, n3, reponse1, reponse2, reponse3, essais, points;
    char continuer;
    do {
        // Genere trois nombres distincts entre 1 et 100
        n1 = rand() % 100 + 1;
        n2 = rand() % 100 + 1;
        while (n2 == n1) n2 = rand() % 100 + 1;
        n3 = rand() % 100 + 1;
        while (n3 == n1 || n3 == n2) n3 = rand() % 100 + 1;
        essais = 0;
        points = 0;

        printf("\nClassez ces nombres en ordre croissant : %d, %d, %d\n", n1, n2, n3);
        printf("Entrez les nombres (separes par des espaces) : ");
        do {
            essais++;
            // Lit les trois nombres en une seule ligne
            if (lire_trois_entiers(&reponse1, &reponse2, &reponse3)) {
                printf("Tu as entre : %d %d %d\n", reponse1, reponse2, reponse3);

                // Trie les nombres pour comparaison
                int nombres[3] = {n1, n2, n3};
                for (int i = 0; i < 2; i++) {
                    for (int j = 0; j < 2 - i; j++) {
                        if (nombres[j] > nombres[j + 1]) {
                            int temp = nombres[j];
                            nombres[j] = nombres[j + 1];
                            nombres[j + 1] = temp;
                        }
                    }
                }

                // Verifie si la reponse est correcte
                if (reponse1 == nombres[0] && reponse2 == nombres[1] && reponse3 == nombres[2]) {
                    if (essais == 1) points = 10;
                    else if (essais == 2) points = 5;
                    else points = 1;
                    printf("^_^ Bravo, c'est correct ! (%d points)\n", points);
                    score_global += points;
                    break;
                } else {
                    printf("T_T Incorrect. Essaie encore (essai %d/%d) : ", essais, MAX_ESSAIS);
                    if (essais == MAX_ESSAIS) {
                        printf("\nPerdu ! La bonne reponse etait %d %d %d.\n", nombres[0], nombres[1], nombres[2]);
                        break;
                    }
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



// Mini-jeu : Calcul du perimetre de figures
void Jouer_Perimetre() {
    int type, longueur, largeur, cote, reponse, essais, points;
    char continuer;
    do {
        // Choisit aleatoirement entre rectangle (0) ou triangle equilateral (1)
        type = rand() % 2;
        essais = 0;
        points = 0;

        if (type == 0) { // Rectangle
            longueur = rand() % 20 + 1;
            largeur = rand() % 20 + 1;
            printf("\nCalculez le perimetre d'un rectangle de longueur %d et largeur %d\n", longueur, largeur);
            printf("Entrez le perimetre : ");
            do {
                essais++;
                reponse = lire_entier();
                printf("Tu as entre : %d\n", reponse);

                if (reponse == 2 * (longueur + largeur)) {
                    if (essais == 1) points = 10;
                    else if (essais == 2) points = 5;
                    else points = 1;
                    printf("^_^ Bravo, c'est correct ! (%d points)\n", points);
                    score_global += points;
                    break;
                } else {
                    printf("T_T Incorrect. Essaie encore (essai %d/%d) : ", essais, MAX_ESSAIS);
                    if (essais == MAX_ESSAIS) {
                        printf("\nPerdu ! La bonne reponse etait %d.\n", 2 * (longueur + largeur));
                        break;
                    }
                }
            } while (essais < MAX_ESSAIS);
        } else { // Triangle equilateral
            cote = rand() % 20 + 1;
            printf("\nCalculez le perimetre d'un triangle equilateral de cote %d\n", cote);
            printf("Entrez le perimetre : ");
            do {
                essais++;
                reponse = lire_entier();
                printf("Tu as entre : %d\n", reponse);

                if (reponse == 3 * cote) {
                    if (essais == 1) points = 10;
                    else if (essais == 2) points = 5;
                    else points = 1;
                    printf("^_^ Bravo, c'est correct ! (%d points)\n", points);
                    score_global += points;
                    break;
                } else {
                    printf("T_T Incorrect. Essaie encore (essai %d/%d) : ", essais, MAX_ESSAIS);
                    if (essais == MAX_ESSAIS) {
                        printf("\nPerdu ! La bonne reponse etait %d.\n", 3 * cote);
                        break;
                    }
                }
            } while (essais < MAX_ESSAIS);
        }

        printf("On continue ? (O = Oui / N = Non) ");
        scanf(" %c", &continuer);
        vider_buffer();
    } while (continuer != 'N' && continuer != 'n');
    score_global += POINT_BONUS;
    printf("Ton score total est de %d\n", score_global);
}





// Mini-jeu : Problemes de mots simples
void Jouer_Problemes() {
    int type, n1, n2, reponse, essais, points;
    char continuer;
    do {
        // Choisit aleatoirement entre addition (0) ou soustraction (1)
        type = rand() % 2;
        n1 = rand() % 50 + 1;
        n2 = rand() % n1 + 1; // Assure que soustraction donne un resultat positif
        essais = 0;
        points = 0;

        if (type == 0) { // Addition
            printf("\nAnna a %d bonbons, elle en achete %d de plus. Combien en a-t-elle maintenant ?\n", n1, n2);
            printf("Entrez la reponse : ");
            do {
                essais++;
                reponse = lire_entier();
                printf("Tu as entre : %d\n", reponse);

                if (reponse == n1 + n2) {
                    if (essais == 1) points = 10;
                    else if (essais == 2) points = 5;
                    else points = 1;
                    printf("^_^ Bravo, c'est correct ! (%d points)\n", points);
                    score_global += points;
                    break;
                } else {
                    printf("T_T Incorrect. Essaie encore (essai %d/%d) : ", essais, MAX_ESSAIS);
                    if (essais == MAX_ESSAIS) {
                        printf("\nPerdu ! La bonne reponse etait %d.\n", n1 + n2);
                        break;
                    }
                }
            } while (essais < MAX_ESSAIS);
        } else { // Soustraction
            printf("\nAnna a %d pommes, elle en mange %d. Combien en reste-t-il ?\n", n1, n2);
            printf("Entrez la reponse : ");
            do {
                essais++;
                reponse = lire_entier();
                printf("Tu as entre : %d\n", reponse);

                if (reponse == n1 - n2) {
                    if (essais == 1) points = 10;
                    else if (essais == 2) points = 5;
                    else points = 1;
                    printf("^_^ Bravo, c'est correct ! (%d points)\n", points);
                    score_global += points;
                    break;
                } else {
                    printf("T_T Incorrect. Essaie encore (essai %d/%d) : ", essais, MAX_ESSAIS);
                    if (essais == MAX_ESSAIS) {
                        printf("\nPerdu ! La bonne reponse etait %d.\n", n1 - n2);
                        break;
                    }
                }
            } while (essais < MAX_ESSAIS);
        }

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
        printf("|1 : Addition                      |\n");
        printf("|2 : Soustraction                  |\n");
        printf("|3 : Multiplication                |\n");
        printf("|4 : Division                      |\n");
        printf("|5 : Tables de multiplication      |\n");
        printf("|6 : Fractions                     |\n");
        printf("|7 : Comparaison de nombres        |\n");
        printf("|8 : Ordre croissant               |\n");
        printf("|9 : Perimetre de figures          |\n");
        printf("|10 : Problemes de mots            |\n");
        printf("|0 : Sortir du jeu                 |\n");
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
            case 8:
                printf("Ordre croissant\n");
                Jouer_Ordre_Croissant();
                sauvegarder_score(nom, score_global);
                break;
            case 9:
                printf("Perimetre de figures\n");
                Jouer_Perimetre();
                sauvegarder_score(nom, score_global);
                break;
            case 10:
                printf("Problemes de mots\n");
                Jouer_Problemes();
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
