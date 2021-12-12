#include <stdio.h>

#include <time.h>

#include <string.h>

#include <stdlib.h>

#include <conio.h>

int TableMere[2]; //Tableau mére
int MatCarteCoul[4][13]; //Matrice des couleurs
char MIC[4][6] = {
    "Rouge",
    "Bleu",
    "Vert",
    "Jaune"
}; //Matrice des indices couleurs
char MIN[13][8] = {
    "0",
    "1",
    "2",
    "3",
    "4",
    "5",
    "6",
    "7",
    "8",
    "9",
    "Block",
    "Reverse",
    "+2"
}; //Matrice des indices Numeros
char NomCartee[20] = "";
char J1[20][20];
// char J1[20][20]= {"Rouge 5","Bleu 6","+4","Jaune 7", "Vert 3", "Rouge 3", "Joker"}; //Matrice 1er joueur
int J1N = 6; //Taille du matrice 1er joueur
char J2[20][20]; //Matrice 2eme joueur
// char J2[20][20]= {"Rouge 7","Rouge 7","+4","Rouge 7", "Rouge 3", "Rouge 3", "Joker"}; //Matrice 1er joueur
int J2N = 6; //Taille du matrice 2eme joueur
char CarteJouees[100][20]; //Matrice des cartes deja jouée
int NCJ = 0; //Taille du Matrice des cartes deja jouée
int quiJoue = 0;
int joue = 1;
int CombienDeCartes[4] = {
    0,
    0,
    0,
    0
};
int fois = 0;
int score2 = 0;
int score1 = 0;
int test1ertour = 0;
int machine;
int i;
char un[10], deux[10];

int machineJokP4();
void Welcome();
void affCarte(int num, char carte[20]);
char * CarteAleatoire();
void DistCartes(char joueur[][20]);
void RempTableMere();
int RempMatCarteCoul();
char * NomCarte(int couleur, int numero);
char * CopierApresEspace(char ch[]);
int PosEspace(char ch[]);
int plus4possible(char joueur[][20], int joueurN);
int CartePossible(char carte[20], char joueur[][20], int joueurN);
void effaceCarte(char joueur[][20], int joueurN, int carte);
void EffetCarte(char carte[], char JoueurInfecte[][20], int JoueurInfecteN);
void bubbleSort(char joueur[][20], int joueurN);



//Uno
int main() {

    srand(time(NULL));

    RempTableMere();
    RempMatCarteCoul();

    DistCartes(J1);
    DistCartes(J2);

    printf("\n");

    Welcome();

    char enter = 0;
    while (enter != '\r' && enter != '\n') {
        enter = getchar();
    }

    system("cls");


    do {
        strcpy(CarteJouees[0], CarteAleatoire());
    } while (strcmp(CarteJouees[0], "+4") == 0);


    do {
        printf("Voulez-vous jouer contre le machine(1) ou contre un ami(0)");
        scanf("%d", & machine);
    } while (machine != 1 && machine != 0);

    system("cls");

    if (machine == 0) {
        printf("*************************** Joueur contre joueur ***************************\n");
        printf("Saisir le nom du 1er joueur : ");
        scanf(" %s", un);
        printf("\nSaisir le nom du 2eme joueur : ");
        scanf(" %s", deux);
    } else {
        printf("*************************** Joueur contre machine ***************************\n");
        printf("Saisir le nom du 1er joueur : ");
        scanf(" %s", un);
    }

    do {
        if (quiJoue % 2 == 0) {
            //Joueur 1 qui joue

            //Tri a bulles
            bubbleSort(J1, J1N);

            //Affichage de la main
            printf("\n%d cartes restantes pour J2\n", J2N + 1);

            printf("Main du 1er joueur %s : \n", un);
            for (i = 0; i <= J1N; i++) {
                affCarte(i + 1, J1[i]);
                printf("\n");
            }


            if (test1ertour == 0 && strcmp(CarteJouees[NCJ], "Joker") == 0) {
                printf("\nDernier Carte Jouee : %s \n", CarteJouees[NCJ]);
                //Si la premier carte est Joker
                char couleurJoker[10] = "";
                test1ertour = 1;
                do {
                    printf("%s Choisir une couleur : ", un);
                    scanf(" %s", couleurJoker);
                } while (strcmp(couleurJoker, "Rouge") != 0 && strcmp(couleurJoker, "Bleu") != 0 && strcmp(couleurJoker, "Jaune") != 0 && strcmp(couleurJoker, "Vert") != 0);
                strcat(couleurJoker, " ");
                NCJ++;
                strcpy(CarteJouees[NCJ], couleurJoker);
                quiJoue++;
            } else if (test1ertour == 0 && strcmp(CopierApresEspace(CarteJouees[NCJ]), "+2") == 0) {
                //Si la permier carte est +2
                printf("%s, +2 et passe ton tour ! \n", un);
                for (i = 0; i < 2; i++) {

                    J1N++;
                    strcpy(J1[J1N], CarteAleatoire());
                }
                test1ertour = 1;
                quiJoue++;
            } else if (test1ertour == 0 && (strcmp(CopierApresEspace(CarteJouees[NCJ]), "Reverse") == 0 || strcmp(CopierApresEspace(CarteJouees[NCJ]), "Block") == 0)) {
                //Si la premier carte est reverse ou block
                printf("%s, Passe ton tour ! \n", un);
                quiJoue++;
                test1ertour = 1;
            } else {
                printf("\nDernier Carte Jouee : %s \n", CarteJouees[NCJ]);
                int choix;
                printf("%s, Choisir une carte ou pour prendre une carte tapez 0 : ", un);
                scanf(" %d", & choix);
                choix--;
                if (choix + 1 == 0) {
                    test1ertour = 1;
                    int test = 0;
                    J1N++;
                    strcpy(J1[J1N], CarteAleatoire());
                    printf("\nDernier Carte Jouee : %s \n", CarteJouees[NCJ]);
                    //Affichage de la main apres carte
                    for (i = 0; i <= J1N; i++) {
                        affCarte(i + 1, J1[i]);
                        printf("\n");
                    }
                    int choix2;
                    do {
                        printf("\n%s, Choisir une carte ou appuyer 0 pour passer ton tour : ", un);
                        scanf("%d", & choix2);
                        choix2--;
                        if (choix2 + 1 == 0) {
                            quiJoue++;
                            test = 1;
                        } else if (CartePossible(J1[choix2], J1, J1N) == 1) {
                            NCJ++;
                            test = 1;
                            strcpy(CarteJouees[NCJ], J1[choix2]);
                            //EffetCarte(J1[choix2], J2, J2N);
                            ////////////////////////
                            int i;
                            char rep2;
                            char couleur2[6];
                            char rep;
                            char couleur[6] = "";
                            if (strcmp(J1[choix], "+4") == 0) {
                                for (i = 0; i < 4; i++) {
                                    J2N++;
                                    strcpy(J2[J2N], CarteAleatoire());
                                }
                                getchar();
                                printf("%s, Voulez-vous changer la couleur ? (O/N) : ", deux);
                                scanf(" %c", & rep);
                                if (rep == 'O') {
                                    printf("Saisir la couleur qui vous voulez changer : ");
                                    scanf(" %s", couleur);
                                    strcat(couleur, " ");
                                    NCJ++;
                                    strcpy(CarteJouees[NCJ], couleur);
                                } else if (rep == 'N') {
                                    NCJ++;
                                    memmove(CarteJouees[NCJ], CarteJouees[NCJ - 2], PosEspace(CarteJouees[NCJ - 2]));
                                }

                            } else if (strcmp(CopierApresEspace(J1[choix2]), "+2") == 0) {
                                for (i = 0; i < 2; i++) {
                                    J2N++;
                                    strcpy(J2[J2N], CarteAleatoire());
                                }
                            } else if (strcmp(J1[choix2], "Joker") == 0) {
                                printf("%s, Voulez-vous changer la couleur ? (O/N) : ", un);
                                scanf(" %c", & rep2);
                                if (rep2 == 'O') {
                                    printf("Saisir la couleur qui vous voulez changer : ");
                                    scanf(" %s", couleur2);
                                    strcat(couleur2, " ");
                                    NCJ++;
                                    strcpy(CarteJouees[NCJ], couleur2);
                                } else if (rep2 == 'N') {
                                    NCJ++;
                                    memmove(CarteJouees[NCJ], CarteJouees[NCJ - 2], PosEspace(CarteJouees[NCJ - 2]));
                                }
                                quiJoue++;
                            } else if (strcmp(CopierApresEspace(J1[choix2]), "Block") != 0 && strcmp(CopierApresEspace(J1[choix2]), "Reverse") != 0) {
                                quiJoue++;
                            };
                            ////////////////////////
                            effaceCarte(J1, J1N, choix2);
                            J1N--;
                        }
                    } while (test == 0);
                } else if (CartePossible(J1[choix], J1, J1N) == 1) {
                    NCJ++;
                    test1ertour = 1;
                    strcpy(CarteJouees[NCJ], J1[choix]);
                    ////////////////////////
                    int i;
                    char rep2;
                    char couleur2[6];
                    char rep;
                    char couleur[6] = "";
                    if (strcmp(J1[choix], "+4") == 0) {
                        for (i = 0; i < 4; i++) {
                            J2N++;
                            strcpy(J2[J2N], CarteAleatoire());
                        }
                        getchar();
                        printf("%s, Voulez-vous changer la couleur ? (O/N) : ", deux);
                        scanf(" %c", & rep);
                        if (rep == 'O') {
                            printf("Saisir la couleur qui vous voulez changer : ");
                            scanf(" %s", couleur);
                            strcat(couleur, " ");
                            NCJ++;
                            strcpy(CarteJouees[NCJ], couleur);
                        } else if (rep == 'N') {
                            NCJ++;
                            memmove(CarteJouees[NCJ], CarteJouees[NCJ - 2], PosEspace(CarteJouees[NCJ - 2]));
                        }
                    } else if (strcmp(CopierApresEspace(J1[choix]), "+2") == 0) {
                        for (i = 0; i < 2; i++) {
                            J2N++;
                            strcpy(J2[J2N], CarteAleatoire());
                        }
                    } else if (strcmp(J1[choix], "Joker") == 0) {
                        printf("%s, Voulez-vous changer la couleur ? (O/N) : ", un);
                        scanf(" %c", & rep2);
                        if (rep2 == 'O') {
                            printf("Saisir la couleur qui vous voulez changer : ");
                            scanf(" %s", couleur2);
                            strcat(couleur2, " ");
                            NCJ++;
                            strcpy(CarteJouees[NCJ], couleur2);
                        } else if (rep2 == 'N') {
                            NCJ++;
                            memmove(CarteJouees[NCJ], CarteJouees[NCJ - 2], PosEspace(CarteJouees[NCJ - 2]));
                        }
                        quiJoue++;
                    } else if (strcmp(CopierApresEspace(J1[choix]), "Block") != 0 && strcmp(CopierApresEspace(J1[choix]), "Reverse") != 0) {
                        quiJoue++;
                    }
                    ////////////////////////
                    effaceCarte(J1, J1N, choix);
                    J1N--;
                } else {
                    printf("%s, Impossible d'inserer cette carte \n", un);
                }
            }

            //test UNO!
            if (J1N == 0) {
                char stop;
                int test = 0;
                clock_t x_startTime, x_finishTime;
                x_startTime = clock(); // start clock
                scanf(" %c", & stop);
                x_finishTime = clock(); // finish clock
                if (stop != 'u' && stop != 'U') {
                    test = 1;
                }
                if (x_finishTime - x_startTime > 3000 && test == 1) {
                    printf("+2 penalité");
                    for (i = 0; i < 2; i++) {
                        J1N++;
                        strcpy(J1[J1N], CarteAleatoire());
                    }
                }
            }
            system("cls");
        } else if (quiJoue % 2 != 0 && machine == 0) {
            //Joueur 2 qui joue

            //Tri a bulles
            bubbleSort(J2, J2N);

            //Affichage de la main
            printf("Main du %s: \n", deux);
            for (i = 0; i <= J2N; i++) {
                affCarte(i + 1, J2[i]);
                printf("\n");
            }
            printf("\n%d cartes restantes pour J1", J1N + 1);
            printf("\nDernier Carte Jouee : %s \n", CarteJouees[NCJ]);

            int choix;
            printf("\n%s, Choisir une carte ou pour prendre une carte tapez 0 : ", deux);
            scanf("%d", & choix);
            choix--;
            if (choix + 1 == 0) {
                int test = 0, choix2 = 0;
                J2N++;
                strcpy(J2[J2N], CarteAleatoire());
                for (i = 0; i <= J2N; i++) {
                    affCarte(i + 1, J2[i]);
                    printf("\n");
                }
                do {
                    printf("\n%s, Choisir une carte ou appuyer 0 pour passer ton tour : ", deux);
                    scanf("%d", & choix2);
                    choix2--;
                    if (choix2 + 1 == 0) {
                        quiJoue++;
                        test = 1;
                    } else if (CartePossible(J2[choix2], J2, J2N) == 1) {
                        NCJ++;
                        test = 1;
                        strcpy(CarteJouees[NCJ], J2[choix2]);
                        ////////////////////////
                        int i;
                        char rep2;
                        char couleur2[6];
                        char rep;
                        char couleur[6] = "";
                        if (strcmp(J2[choix], "+4") == 0) {
                            for (i = 0; i < 4; i++) {
                                J1N++;
                                strcpy(J1[J1N], CarteAleatoire());
                            }
                            getchar();
                            printf("%s, Voulez-vous changer la couleur ? (O/N) : ", deux);
                            scanf(" %c", & rep);
                            if (rep == 'O') {
                                printf("Saisir la couleur qui vous voulez changer : ");
                                scanf(" %s", couleur);
                                strcat(couleur, " ");
                                NCJ++;
                                strcpy(CarteJouees[NCJ], couleur);
                            } else if (rep == 'N') {
                                NCJ++;
                                memmove(CarteJouees[NCJ], CarteJouees[NCJ - 2], PosEspace(CarteJouees[NCJ - 2]));
                            }

                        } else if (strcmp(CopierApresEspace(J2[choix2]), "+2") == 0) {
                            for (i = 0; i < 2; i++) {
                                J1N++;
                                strcpy(J1[J1N], CarteAleatoire());
                            }
                        } else if (strcmp(J2[choix2], "Joker") == 0) {
                            printf("%s, Voulez-vous changer la couleur ? (O/N) : ", deux);
                            scanf(" %c", & rep2);
                            if (rep2 == 'O') {
                                printf("Saisir la couleur qui vous voulez changer : ");
                                scanf(" %s", couleur2);
                                strcat(couleur2, " ");
                                NCJ++;
                                strcpy(CarteJouees[NCJ], couleur2);
                            } else if (rep2 == 'N') {
                                NCJ++;
                                memmove(CarteJouees[NCJ], CarteJouees[NCJ - 2], PosEspace(CarteJouees[NCJ - 2]));
                            }
                            quiJoue++;
                        } else if (strcmp(CopierApresEspace(J2[choix2]), "Block") != 0 && strcmp(CopierApresEspace(J2[choix2]), "Reverse") != 0) {
                            quiJoue++;
                        }
                        ////////////////////////
                        effaceCarte(J2, J2N, choix2);
                        J2N--;
                    }
                } while (test != 1);
            } else if (CartePossible(J2[choix], J2, J2N) == 1) {
                NCJ++;
                strcpy(CarteJouees[NCJ], J2[choix]);
                ////////////////////////
                int i;
                char rep2;
                char couleur2[6];
                char rep;
                char couleur[6] = "";
                if (strcmp(J2[choix], "+4") == 0) {
                    for (i = 0; i < 4; i++) {
                        J1N++;
                        strcpy(J1[J1N], CarteAleatoire());
                    }
                    getchar();
                    printf("%s, Voulez-vous changer la couleur ? (O/N) : ", deux);
                    scanf(" %c", & rep);
                    if (rep == 'O') {
                        printf("Saisir la couleur qui vous voulez changer : ");
                        scanf(" %s", couleur);
                        strcat(couleur, " ");
                        NCJ++;
                        strcpy(CarteJouees[NCJ], couleur);
                    } else if (rep == 'N') {
                        NCJ++;
                        memmove(CarteJouees[NCJ], CarteJouees[NCJ - 2], PosEspace(CarteJouees[NCJ - 2]));
                    }

                } else if (strcmp(CopierApresEspace(J2[choix]), "+2") == 0) {
                    for (i = 0; i < 2; i++) {
                        J1N++;
                        strcpy(J1[J1N], CarteAleatoire());
                    }
                } else if (strcmp(J2[choix], "Joker") == 0) {
                    printf("%s, Voulez-vous changer la couleur ? (O/N) : ", deux);
                    scanf(" %c", & rep2);
                    if (rep2 == 'O') {
                        printf("Saisir la couleur qui vous voulez changer : ");
                        scanf(" %s", couleur2);
                        strcat(couleur2, " ");
                        NCJ++;
                        strcpy(CarteJouees[NCJ], couleur2);
                    } else if (rep2 == 'N') {
                        NCJ++;
                        memmove(CarteJouees[NCJ], CarteJouees[NCJ - 2], PosEspace(CarteJouees[NCJ - 2]));
                    }
                    quiJoue++;
                } else if (strcmp(CopierApresEspace(J2[choix]), "Block") != 0 && strcmp(CopierApresEspace(J2[choix]), "Reverse") != 0) {
                    quiJoue++;
                }
                ////////////////////////
                effaceCarte(J2, J2N, choix);
                J2N--;
            } else {
                printf("%s, Impossib le d'inserer cette carte \n", deux);
            }


            //test UNO!
            if (J2N == 0) {
                char stop;
                int test = 0;
                clock_t x_startTime, x_finishTime;
                clock();
                x_startTime = clock(); // start clock
                scanf(" %c", & stop);
                x_finishTime = clock(); // finish clock
                if (stop != 'u' && stop != 'U') {
                    test = 1;
                }
                if (x_finishTime - x_startTime > 3000 && test == 1) {
                    printf("+2 penalite");
                    for (i = 0; i < 2; i++) {
                        J2N++;
                        strcpy(J2[J2N], CarteAleatoire());
                    }
                    quiJoue++;
                }
            }
            system("cls");
        } else if (quiJoue % 2 != 0 && machine == 1) {

            printf("\nMachine qui joue\n");
            for (i = 0; i <= J2N; i++) {
                printf("-- %s --", J2[i]);
            }
            printf("\n");

            int CombienDeCartes[4] = {
                0,
                0,
                0,
                0
            };

            //combien de carte Rouge jouable
            printf("**Rouge en test\n");
            for (i = 0; i <= J2N; i++) {
                if (memcmp("Rouge", J2[i], 5) == 0) {
                    printf("\nvoici une carte rouge : %s,", J2[i]);
                    if (CartePossible(J2[i], J2, J2N) == 1) {
                        printf(" et aussi jouable");
                        CombienDeCartes[0]++;
                    }
                }
                printf("\n");
            }
            printf("les Rouge jouable : %d !", CombienDeCartes[0]);
            printf("\n");
            printf("\n");
            //combien de carte Jaune jouable
            printf("**Jaune en test\n");
            for (i = 0; i <= J2N; i++) {
                if (memcmp("Jaune", J2[i], 5) == 0) {
                    printf("\nvoici une carte Jaune : %s,", J2[i]);
                    if (CartePossible(J2[i], J2, J2N) == 1) {
                        printf(" et aussi jouable");
                        CombienDeCartes[1]++;
                    }
                }
                printf("\n");
            }
            printf("les Jaune jouable : %d !", CombienDeCartes[1]);
            printf("\n");
            printf("\n");
            //combien de carte Vert jouable
            printf("**Vert en test\n");
            for (i = 0; i <= J2N; i++) {
                if (memcmp("Vert", J2[i], 4) == 0) {
                    printf("\nvoici une carte Vert : %s,", J2[i]);
                    if (CartePossible(J2[i], J2, J2N) == 1) {
                        printf(" et aussi jouable");
                        CombienDeCartes[2]++;
                    }
                }
                printf("\n");
            }
            printf("les Vert jouable : %d !", CombienDeCartes[2]);
            printf("\n");
            printf("\n");
            //combien de carte Bleu jouable
            printf("**Bleu en test\n");
            for (i = 0; i <= J2N; i++) {
                if (memcmp("Bleu", J2[i], 4) == 0) {
                    printf("\nvoici une carte Bleu : %s,", J2[i]);
                    if (CartePossible(J2[i], J2, J2N) == 1) {
                        printf(" et aussi jouable");
                        CombienDeCartes[3]++;
                    }
                }
                printf("\n");
            }
            printf("\nLes Bleu jouable : %d !", CombienDeCartes[3]);
            printf("\n");
            printf("\n");
            printf("*********les couleurs jouable*********\n");
            printf("les Rouge jouable : %d !", CombienDeCartes[0]);
            printf("\n");
            printf("les Jaune jouable : %d !", CombienDeCartes[1]);
            printf("\n");
            printf("les Vert jouable : %d !", CombienDeCartes[2]);
            printf("\n");
            printf("les Bleu jouable : %d !", CombienDeCartes[3]);

            printf("\n");

            for (i = 0; i < 4; i++) {
                printf("*%d*", CombienDeCartes[i]);
            }

            printf("\n");

            //joueur une carte

            // carte jouable max 
            int max = 0;
            for (i = 0; i < 4; i++) {
                if (CombienDeCartes[i] > max) {
                    max = CombienDeCartes[i];
                }
            }
            printf("\nmax du akther couleur tnajem thotou = %d\n", max);

            int testMachine = 0;
            char coul[6];
            char texxt[6];
            if (max != 0) {

                if (CombienDeCartes[0] == max) {
                    strcpy(coul, "Rouge");
                }
                if (CombienDeCartes[1] == max) {
                    strcpy(coul, "Jaune");
                }
                if (CombienDeCartes[2] == max) {
                    strcpy(coul, "Vert");
                }
                if (CombienDeCartes[3] == max) {
                    strcpy(coul, "Bleu");
                }

                printf("\n couleur eli bch yhotou : %s\n", coul);
                int k = 0;
                do {
                    printf("\n k = %d \n", k);
                    printf("carte mel kaff eli bch ychoufha %s wale :  %s\n", coul, J2[k]);
                    if (memcmp(J2[k], coul, strlen(coul)) == 0 && CartePossible(J2[k], J2, J2N) == 1) {
                        printf("\ncette carte est valide %s\n", J2[k]);
                        NCJ++;
                        strcpy(CarteJouees[NCJ], J2[k]);
                        ////////////////////////
                        if (strcmp(CopierApresEspace(J2[k]), "+2") == 0) {
                            for (i = 0; i < 2; i++) {
                                J1N++;
                                strcpy(J1[J1N], CarteAleatoire());
                            }
                        } else if (strcmp(CopierApresEspace(J2[k]), "Block") != 0 && strcmp(CopierApresEspace(J2[k]), "Reverse") != 0) {
                            quiJoue++;
                        }
                        ////////////////////////
                        effaceCarte(J2, J2N, k);
                        J2N--;
                        testMachine = 1;
                    }
                    k++;
                } while (k <= J2N && testMachine == 0);
            } else if (max == 0 && machineJokP4() == 1) {
                // une carte joker ou +4
                i = 0;
                char jokcoul[6];
                do {
                    if (strcmp(J2[i], "Joker") == 0) {
                        NCJ++;
                        quiJoue++;
                        effaceCarte(J2, J2N, i);
                        J2N--;
                        int jokmachine = rand() % 3;
                        switch (jokmachine) {
                            case 0:
                                strcpy(jokcoul, "Rouge");
                                break;
                            case 1:
                                strcpy(jokcoul, "Jaune");
                                break;
                            case 2:
                                strcpy(jokcoul, "Vert");
                                break;
                            case 3:
                                strcpy(jokcoul, "Bleu");
                                break;
                        }
                        strcpy(CarteJouees[NCJ], jokcoul);
                    }
                    i++;
                } while (i <= J2N && strlen(jokcoul) == 0);
                if (strlen(jokcoul) == 0) {
                    for (i = 0; i < 4; i++) {
                        J1N++;
                        strcpy(J1[J1N], CarteAleatoire());
                    }

                    int suppr = 0;
                    i = -1;
                    do {
                        i++;
                        if (strcmp(J2[i], "+4") == 0) {
                            suppr = 1;
                        }
                    } while (suppr == 0);

                    effaceCarte(J2, J2N, i);
                    J2N--;

                    NCJ++;
                    int jokmachine = rand() % 3;
                    switch (jokmachine) {
                        case 0:
                            strcpy(jokcoul, "Rouge");
                            break;
                        case 1:
                            strcpy(jokcoul, "Jaune");
                            break;
                        case 2:
                            strcpy(jokcoul, "Vert");
                            break;
                        case 3:
                            strcpy(jokcoul, "Bleu");
                            break;
                    }
                    strcpy(CarteJouees[NCJ], jokcoul);
                }
            } else {
                J2N++;
                strcpy(J2[J2N], CarteAleatoire());
                if (CartePossible(J2[J2N], J2, J2N) == 1) {
                    NCJ++;
                    strcpy(CarteJouees[NCJ], J2[J2N]);
                    ////////////////////////
                    int i;
                    char jokcoul[6];

                    if (strcmp(J2[J2N], "Joker") == 0) {
                        NCJ++;
                        quiJoue++;
                        int jokmachine = rand() % 3;
                        switch (jokmachine) {
                            case 0:
                                strcpy(jokcoul, "Rouge");
                                break;
                            case 1:
                                strcpy(jokcoul, "Jaune");
                                break;
                            case 2:
                                strcpy(jokcoul, "Vert");
                                break;
                            case 3:
                                strcpy(jokcoul, "Bleu");
                                break;
                        }
                        strcpy(CarteJouees[NCJ], jokcoul);
                    } else if (strcmp(J2[J2N], "+4") == 0) {
                        for (i = 0; i < 4; i++) {
                            J1N++;
                            strcpy(J1[J1N], CarteAleatoire());
                        }
                        i = 0;

                        NCJ++;
                        int jokmachine = rand() % 3;
                        switch (jokmachine) {
                            case 0:
                                strcpy(jokcoul, "Rouge");
                                break;
                            case 1:
                                strcpy(jokcoul, "Jaune");
                                break;
                            case 2:
                                strcpy(jokcoul, "Vert");
                                break;
                            case 3:
                                strcpy(jokcoul, "Bleu");
                                break;
                        }
                        strcpy(CarteJouees[NCJ], jokcoul);
                    } else if (strcmp(CopierApresEspace(J2[J2N]), "+2") == 0) {
                        for (i = 0; i < 2; i++) {
                            J1N++;
                            strcpy(J1[J1N], CarteAleatoire());
                        }
                    } else if (strcmp(CopierApresEspace(J2[J2N]), "Block") != 0 && strcmp(CopierApresEspace(J2[J2N]), "Reverse") != 0) {
                        quiJoue++;
                    }
                    ////////////////////////
                    effaceCarte(J2, J2N, J2N);
                    J2N--;
                } else {
                    quiJoue++;
                }
            }
        }
        if (J1N == -1 || J2N == -1) {
            fois++;
            //score du 2eme joueur
            for (i = 0; i <= J2N; i++) {
                if (strcmp(J2[i], "+4") == 0 || strcmp(J2[i], "Joker") == 0) {
                    score2 = +50;
                } else if (strcmp(CopierApresEspace(J2[i]), "Block") == 0 || strcmp(CopierApresEspace(J2[i]), "Reverse") == 0 || strcmp(CopierApresEspace(J2[i]), "+2") == 0) {
                    score2 = +20;
                } else {
                    char num;
                    num = CopierApresEspace(J2[i])[0];
                    switch (num) {
                        case '1':
                            score2++;
                            break;
                        case '2':
                            score2 = +2;
                            break;
                        case '3':
                            score2 = +3;
                            break;
                        case '4':
                            score2 = +4;
                            break;
                        case '5':
                            score2 = +5;
                            break;
                        case '6':
                            score2 = +6;
                            break;
                        case '7':
                            score2 = +7;
                            break;
                        case '8':
                            score2 = +8;
                            break;
                        case '9':
                            score2 = +9;
                            break;
                    }
                }
            }
            for (i = 0; i <= J1N; i++) {
                if (strcmp(J1[i], "+4") == 0 || strcmp(J1[i], "Joker") == 0) {
                    score1 = +50;
                } else if (strcmp(CopierApresEspace(J1[i]), "Block") == 0 || strcmp(CopierApresEspace(J1[i]), "Reverse") == 0 || strcmp(CopierApresEspace(J1[i]), "+2") == 0) {
                    score1 = +20;
                } else {
                    char num;
                    num = CopierApresEspace(J1[i])[0];
                    switch (num) {
                        case '1':
                            score1++;
                            break;
                        case '2':
                            score1 = +2;
                            break;
                        case '3':
                            score1 = +3;
                            break;
                        case '4':
                            score1 = +4;
                            break;
                        case '5':
                            score1 = +5;
                            break;
                        case '6':
                            score1 = +6;
                            break;
                        case '7':
                            score1 = +7;
                            break;
                        case '8':
                            score1 = +8;
                            break;
                        case '9':
                            score1 = +9;
                            break;
                    }
                }
            }
            if (score1 < score2) {
                printf("\n\n BRAVO joueur 1 est le gagnat avec un score : %d", score1);
                printf("\nScore du 2eme joueur : %d", score2);
            } else if (score2 < score1) {
                printf("\n\n BRAVO joueur 2 est le gagnat avec un score : %d", score2);
                printf("\nScore du 1er joueur : %d", score1);
            } else {
                printf("\n\nEGALITE !!");
                printf("\nScore du 1er joueur : %d, Score du 2eme joueur : %d", score1, score2);
            }

            RempMatCarteCoul();
            RempTableMere();
            J1N = 6;
            DistCartes(J1);
            J2N = 6;
            DistCartes(J2);
            quiJoue = 0;
            do {
                strcpy(CarteJouees[0], CarteAleatoire());
            } while (strcmp(CarteJouees[0], "+4") == 0);
        }
        if (fois >= 2) {
            system("cls");
            printf("Saisir 1 pour continuer; 0 pour finir");
            scanf(" %d", & joue);
            if (joue == 1) {
                RempMatCarteCoul();
                RempTableMere();
                J1N = 6;
                DistCartes(J1);
                J2N = 6;
                DistCartes(J2);
                quiJoue = 0;
                do {
                    strcpy(CarteJouees[0], CarteAleatoire());
                } while (strcmp(CarteJouees[0], "+4") == 0);
            } else {
                printf("Au revoir");
            }
        }
    } while (joue == 1);

    return 0;
}

//joker ou +4 disponible
int machineJokP4() {
    int i = 0, test = 0;
    do {
        if (strcmp(J2[i], "+4") == 0 || strcmp(J2[i], "Joker") == 0) {
            test = 1;
        }
        i++;
    } while (test == 0 && i <= J2N);
    return test;
}

// Position de l'espace
int PosEspace(char ch[]) {
    int i, flag, length;
    length = strlen(ch);
    for (i = 0; i <= length; i++) {
        if (ch[i] == ' ') {
            flag = i;
            break;
        }
    }
    return flag;
}

// Copier apres l'esapce
char * CopierApresEspace(char ch[]) {
    int flag = PosEspace(ch) + 1;
    char * copied;
    copied = (char * ) malloc(20);
    int c = 0;
    int i;
    int length = strlen(ch);
    for (i = flag; i <= length; i++) {
        copied[c] = ch[i];
        c++;
    }
    return (char * ) copied;
}

// Carte possible ou nn
int CartePossible(char carte[20], char joueur[][20], int joueurN) {
    int test = 0;
    if (strcmp(carte, "Joker") == 0) {
        test = 1;
        // printf("\ntest joker possible ou nn\n");
    } else if (strcmp(carte, "+4") == 0 && plus4possible(joueur, joueurN) == 0) {
        test = 1;
        // printf("\ntest +4 possible ou nn\n");
    } else {
        // printf("\ntest carte simple possible ou nn\n");
        // printf("la carte est : %s\n",carte);
        // printf("la carte sur table est : %s\n",CarteJouees[NCJ]);
        char carte_1[10], carte_2[10], carte_jouee_1[6], carte_jouee_2[10];
        memmove(carte_1, CarteJouees[NCJ], PosEspace(CarteJouees[NCJ])); //couleur de la derniere carte jouée
        // printf("carte_1 : |%s|\n",carte_1);
        memmove(carte_jouee_1, carte, PosEspace(carte)); //couleur de la carte à tester
        // printf("carte_joue_1 : |%s|\n",carte_jouee_1);
        strcpy(carte_2, CopierApresEspace(CarteJouees[NCJ])); //numero de la derniere carte jouée
        // printf("carte_2 : |%s|\n",carte_2);
        strcpy(carte_jouee_2, CopierApresEspace(carte)); // numero de la carte à tester
        // printf("carte_jouee_2 : |%s|\n",carte_jouee_2);
        int resCoul;
        resCoul = strcmp(carte_1, carte_jouee_1);
        int resNum;
        resNum = strcmp(carte_2, carte_jouee_2);
        // printf("\n resCoul = %d",resCoul);
        // printf("\n resNum = %d\n",resNum);
        if (resCoul == 0 || resNum == 0) {
            test = 1;
        }
    }
    return test;
}

//Nom de la carte;
char * NomCarte(int couleur, int numero) {
    strcpy(NomCartee, MIC[couleur]);
    strcat(NomCartee, " ");
    strcat(NomCartee, MIN[numero]);
}

//Une carte aleatoire
char * CarteAleatoire() {
    char * carte;
    int x, y, z;
    carte = (char * ) malloc(20);
    int test = 0;
    x = rand() % 108 + 1;
    do {
        if (x >= 1 && x <= 4) {
            if (TableMere[0] > 0) {
                test = 1;
                TableMere[0]--;
                strcpy(carte, "Joker");
            }
        } else if (x > 4 && x <= 8) {
            if (TableMere[1] > 0) {
                test = 1;
                TableMere[1]--;
                strcpy(carte, "+4");
            }
        } else if (x > 8) {
            y = rand() % 4;
            z = rand() % 13;
            if (MatCarteCoul[y][z] > 0) {
                test = 1;
                strcpy(carte, NomCarte(y, z));
                MatCarteCoul[y][z]--;
            }
        }
    }
    while (test == 0);
    return (char * ) carte;
}

//Distribution des cartes
void DistCartes(char joueur[][20]) {
    int i;
    char carte[20];
    // Distribution joueur 1    
    for (i = 0; i <= 6; i++) {
        strcpy(carte, CarteAleatoire());
        strcpy(joueur[i], carte);
    }
}

//Remplissage le tableau mere(1er tableau)
void RempTableMere() {
    TableMere[0] = 4; //+4
    TableMere[1] = 4; //Joker
}

//Remplisse Matrice Cartes Couleurs
int RempMatCarteCoul() {
    int i, j;
    for (i = 0; i < 4; i++) {
        MatCarteCoul[i][0] = 1;
    };
    for (i = 0; i < 4; i++) {
        for (j = 1; j < 13; j++) {
            MatCarteCoul[i][j] = 2;
        }
    }
    return 0;
}

//Efface une carte
void effaceCarte(char joueur[][20], int joueurN, int carte) {
    int i;
    for (i = carte; i <= joueurN; i++) {
        strcpy(joueur[i], joueur[i + 1]);
    }
}

//+4 possible ou nn
int plus4possible(char joueur[][20], int joueurN) {
    int i = 1, test = 0;
    do {
        char carte[10];
        strcpy(carte, joueur[i]);
        char carte_1[10], carte_2[10], carte_jouee_1[6], carte_jouee_2[10];
        memmove(carte_1, CarteJouees[NCJ], PosEspace(CarteJouees[NCJ])); //couleur de la derniere carte jouée
        memmove(carte_jouee_1, carte, PosEspace(carte)); //couleur de la carte à tester
        strcpy(carte_2, CopierApresEspace(CarteJouees[NCJ])); //numero de la derniere carte jouée
        strcpy(carte_jouee_2, CopierApresEspace(carte)); // numero de la carte à tester
        int resCoul = strcmp(carte_1, carte_jouee_1);
        int resNum = strcmp(carte_2, carte_jouee_2);
        if (strcmp(carte, "Joker") == 0 || (resCoul == 0 || resNum == 0)) {
            test = 1;
        }
        i++;
    } while (i <= joueurN && test == 0);
    return test;
}

void Welcome() {
    system("COLOR 4");
    printf("*******************************************************************************************************************************************************************************************************************\n");
    printf("*******************************************************************************************************************************************************************************************************************\n");
    printf("*******************************************************************************************************************************************************************************************************************\n");
    printf("*******************************************************************************************************************************************************************************************************************\n");
    printf("*******************************************************************************************************************************************************************************************************************\n");
    printf("*******************************************************************************************************************************************************************************************************************\n");
    printf("*******************************************************************************************************************************************************************************************************************\n");
    printf("*******************************************************************************************************************************************************************************************************************\n");
    printf("*******************************************************************************************************************************************************************************************************************\n");
    printf("*******************************************************************************************************************************************************************************************************************\n");
    printf("*******************************************************************************************************************************************************************************************************************\n");
    printf("**********************************************************************|                                                            |*******************************************************************************\n");
    printf("**********************************************************************|                                                            |*******************************************************************************\n");
    printf("**********************************************************************|                                                            |*******************************************************************************\n");
    printf("**********************************************************************|                         UNO in c                           |*******************************************************************************\n");
    printf("**********************************************************************|                                                            |*******************************************************************************\n");
    printf("**********************************************************************|                                                            |*******************************************************************************\n");
    printf("**********************************************************************|                                                            |*******************************************************************************\n");
    printf("**********************************************************************|                    press Enter to begin                    |*******************************************************************************\n");
    printf("*******************************************************************************************************************************************************************************************************************\n");
    printf("*******************************************************************************************************************************************************************************************************************\n");
    printf("*******************************************************************************************************************************************************************************************************************\n");
    printf("*******************************************************************************************************************************************************************************************************************\n");
    printf("*******************************************************************************************************************************************************************************************************************\n");
    printf("*******************************************************************************************************************************************************************************************************************\n");
    printf("*******************************************************************************************************************************************************************************************************************\n");
    printf("*******************************************************************************************************************************************************************************************************************\n");
    printf("*******************************************************************************************************************************************************************************************************************\n");
    printf("*******************************************************************************************************************************************************************************************************************\n");
    printf("*******************************************************************************************************************************************************************************************************************\n");
}

void affCarte(int num, char carte[20]) {
    printf("%d **********************\n", num);
    printf("*************************\n");
    printf("*******  %s  *******\n", carte);
    printf("*************************\n");
    printf("*************************\n");
}

void bubbleSort(char joueur[][20], int joueurN) {
    int i, test;
    char aux[20];
    do {
        test = 0;
        for (i = 0; i <= joueurN - 1; i++) {
            if (strcmp(joueur[i + 1], joueur[i]) < 0) {
                strcpy(aux, joueur[i]);
                strcpy(joueur[i], joueur[i + 1]);
                strcpy(joueur[i + 1], aux);
                test = 1;
            }
        }
    } while (test == 1);
}