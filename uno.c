#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include "ANSI-color-codes.h"

int TableMere[2]; //Tableau mére
int MatCarteCoul[4][13]; //Matrice des couleurs
char MIC[4][6] = {"Rouge","Bleu","Vert","Jaune"}; //Matrice des indices couleurs
char MIN[13][8] = {"0","1","2","3","4","5","6","7","8","9","Block","Reverse","+2"}; //Matrice des indices Numeros
char NomCartee[20]="";
char J1[20][20]; //Matrice 1er joueur
int J1N=6; //Taille du matrice 1er joueur
char J2[20][20]; //Matrice 2eme joueur
int J2N=6; //Taille du matrice 2eme joueur
char CarteJouees[100][20]; //Matrice des cartes deja jouée
int NCJ=0; //Taille du Matrice des cartes deja jouée
int quiJoue;
int joue=1;
int CombienDeCartes[4] = {0,0,0,0};

void Welcome();
void affCarte(int num,char carte[20]);
char * CarteAleatoire();
void DistCartes(char joueur[][20]);
void RempTableMere();
int RempMatCarteCoul();
char * NomCarte(int couleur,int numero);
char * CopierApresEspace(char ch[]);
int PosEspace(char ch[]);
int plus4possible(char joueur[][20],int joueurN);
int CartePossible(char carte[20],char joueur[][20],int joueurN);
void effaceCarte(char joueur[][20], int joueurN, int carte);
void EffetCarte (char carte[],char JoueurInfecte[][20],int JoueurInfecteN);
void bubbleSort(char joueur[][20], int joueurN);
void CarteMax();

//Test
int main() { 

    srand(time(NULL));

                

    int i,j;  
    RempTableMere();
    for ( i = 0; i < 2; i++) {
        printf(" %d ", TableMere[i]);
    };

    printf("\n");

    RempMatCarteCoul(); 
    for (i = 0; i < 4;  i++) {
        for ( j = 0; j < 13; j++)
        {
            printf(" %d ", MatCarteCoul[i][j]);
        }
        printf("\n");
    }

    printf("\n");

    for ( i = 0; i < 4; i++) {
        for ( j = 0; j < 13; j++) {
            printf("- %s %s -", MIC[i] , MIN[j] );
        }
        printf("\n");
    }

    printf("\n");

    DistCartes(J1);
    DistCartes(J2);

    printf("Main du 1er joueur :");
    for ( i = 0; i <= J1N; i++) {
        printf(" --%s-- ", J1[i]);
    }
    printf("\n");
    printf("Main du 2eme joueur :");
    for ( i = 0; i <= J2N; i++) {
        printf(" --%s-- ", J2[i]);
    }

    printf("\n");

    // Affichage du matrice carte couleur apres al distribution
    printf("Matrice des cartes couleurs apres la distribution : \n");
    for (i = 0; i < 4;  i++) {
        for ( j = 0; j < 13; j++) {
            printf(" %d ", MatCarteCoul[i][j]);
        }
        printf("\n");
    }

    // Affichage du tableau mere apres la distibution
    printf("Table mere apres la distribution : \n");
    for ( i = 0; i < 2; i++) {
        printf("--%d--", TableMere[i]);
    }


    Welcome();
    char enter = 0;
    while (enter != '\r' && enter != '\n') { 
        enter = getchar(); 
    }

    system("cls");

    int fois= 0;
    int score2=0;
    int score1=0;
    quiJoue = 0;
    NCJ = 0;
    int choix2;
    int test1ertour = 0;
    int machine;
    
    /*
    do {
        strcpy(CarteJouees[0],CarteAleatoire());
    } while (strcmp(CarteJouees[0],"+4") == 0 );
    */

    strcpy(CarteJouees[0],"Joker");

    do {
        printf("Voulez-vous jouer contre le machine(1) ou contre un ami(0)");
        scanf("%d",&machine);
    } while (machine != 1 && machine != 0);

    if (machine == 0) {
        printf("*************************** Joueur contre joueur ***************************");    
    } else {
        printf("*************************** Joueur contre machine ***************************");   
    }

    do {
        if (quiJoue % 2 == 0) {
            //Joueur 1 qui joue

            //Tri a bulles
            bubbleSort(J1,J1N);

            //Affichage de la main
            printf("\n%d cartes restantes pour J2\n",J2N + 1);

            printf("Main du 1er joueur : \n");
            for ( i = 0; i <= J1N; i++) {
                affCarte(i+1,J1[i]);
                printf("\n");
            }
            printf("\nDernier Carte Jouee : %s \n",CarteJouees[NCJ]);

            if (test1ertour == 0 && strcmp(CarteJouees[NCJ],"Joker") == 0) {
                //Si la premier carte est Joker
                char couleurJoker[6];
                do {
                    printf("Choisir une couleur : ! khater quijoue=0");
                    scanf(" %s",&couleurJoker);
                } while (strcmp(couleurJoker,"Rouge") != 0 && strcmp(couleurJoker,"Bleu") != 0 && strcmp(couleurJoker,"Jaune") != 0 && strcmp(couleurJoker,"Vert") != 0);
                NCJ++;
                strcpy(CarteJouees[NCJ],couleurJoker);
                quiJoue++;
                test1ertour == 1;
            } else if (test1ertour == 0 && strcmp(CopierApresEspace(CarteJouees[NCJ]),"+2") == 0) {
                //Si la permier carte est +2
                printf("+2 et passe ton tour ! khater quijoue=0");
                for (i = 0; i < 2; i++) {
                    J1N++;
                    strcpy(J1[J1N],CarteAleatoire());
                }
                quiJoue++;
                test1ertour == 1;
            } else if (test1ertour == 0 && (strcmp(CopierApresEspace(CarteJouees[NCJ]),"Reverse") == 0 || strcmp(CopierApresEspace(CarteJouees[NCJ]),"Block") == 0)) {
                //Si la premier carte est reverse ou block
                printf("Passe ton tour ! khater quijoue=0");
                quiJoue++;
                test1ertour == 1;
            } else {
                int choix;
                test1ertour == 1;
                printf("Choisir une carte ou pour prendre une carte tapez 0 : ");
                scanf("%d",&choix);
                choix--;
                if (choix + 1 == 0) {
                    int test = 0;
                    J1N++;
                    strcpy(J1[J1N],CarteAleatoire());
                    printf("\nDernier Carte Jouee : %s \n",CarteJouees[NCJ]);
                    //Affichage de la main apres carte
                    for ( i = 0; i <= J1N; i++) {
                        affCarte(i+1,J1[i]);
                        printf("\n");
                    }
                    do {
                        printf("\n Choisir une carte ou appuyer 0 pour passer ton tour : ");
                        scanf("%d",&choix2);
                        choix2--;
                        if (choix2 + 1 == 0) {
                            quiJoue++;
                            test = 1;
                            printf("Passit");
                        } else if(CartePossible(J1[choix2],J1,J1N) == 1) {
                            NCJ++;
                            test1ertour = 1;
                            test = 1;
                            strcpy(CarteJouees[NCJ],J1[choix2]);
                            //EffetCarte(J1[choix2], J2, J2N);
                            ////////////////////////
                            int i;char rep2;char couleur2[6];char rep;char couleur[6]="";
                            if (strcmp(J1[choix2],"+4") == 0) {
                                printf("\nda5let +4\n");
                                for ( i=0; i<4; i++) {
                                    J2N++;
                                    strcpy(J2[J2N],CarteAleatoire());
                                    printf("+4*");
                                }
                                printf("Voulez-vous changer la couleur ? (O/N) : ");
                                scanf(" %c",&rep);
                                if (rep == 'O') {
                                    printf("Saisir la couleur qui vous voulez changer : ");
                                    scanf(" %s",couleur);
                                    strcat(couleur," ");
                                    NCJ++;
                                    strcpy(CarteJouees[NCJ],couleur);
                                } else if(rep == 'N') {
                                    NCJ++;
                                    memmove( CarteJouees[NCJ] ,CarteJouees[NCJ-2] ,PosEspace(CarteJouees[NCJ-2]) );
                                }
                            } else if(strcmp(CopierApresEspace(J1[choix2]),"+2") == 0) {
                                printf("\nda5let +2\n");
                                for ( i = 0; i < 2; i++) {
                                    J2N++;
                                    strcpy(J2[J2N],CarteAleatoire());
                                    printf("+2");
                                }
                            }  else if(strcmp(J1[choix2],"Joker") == 0) {
                                printf("\nda5let Joker\n");
                                printf("Voulez-vous changer la couleur ? (O/N) : ");
                                scanf(" %c",&rep2);
                                if (rep2 == 'O') {
                                    printf("Saisir la couleur qui vous voulez changer : ");
                                    scanf(" %s",couleur2);
                                    strcat(couleur2," ");
                                    NCJ++;
                                    strcpy(CarteJouees[NCJ],couleur2);
                                } else if(rep2 == 'N') {
                                    NCJ++;
                                    memmove( CarteJouees[NCJ] ,CarteJouees[NCJ-2] ,PosEspace(CarteJouees[NCJ-2]) );
                                }
                                quiJoue++;
                            } else if (strcmp(CopierApresEspace(J1[choix2]),"Block") != 0 && strcmp(CopierApresEspace(J1[choix2]),"Reverse") != 0){
                                quiJoue++;
                                printf("\nda5let carte adeya\n");
                            } else {
                                printf("\nda5let block wala reverse\n");
                            }
                            ////////////////////////
                            effaceCarte(J1,J1N,choix2);
                            J1N--;
                        }
                    } while(test == 0);
                } else if(CartePossible(J1[choix],J1,J1N) == 1) {
                    NCJ++;
                    test1ertour = 1;    
                    strcpy(CarteJouees[NCJ],J1[choix]);
                    //EffetCarte(J1[choix2], J2, J2N);
                    ////////////////////////
                    int i;char rep2;char couleur2[6];char rep;char couleur[6]="";
                    if (strcmp(J1[choix],"+4") == 0) {
                        printf("\nda5let +4\n");
                        for ( i=0; i<4; i++) {
                            J2N++;
                            strcpy(J2[J2N],CarteAleatoire());
                            printf("+4*");
                        }
                        printf("Voulez-vous changer la couleur ? (O/N) : ");
                        scanf(" %c",&rep);
                        if (rep == 'O') {
                            printf("Saisir la couleur qui vous voulez changer : ");
                            scanf(" %s",couleur);
                            strcat(couleur," ");
                            NCJ++;
                            strcpy(CarteJouees[NCJ],couleur);
                        } else if(rep == 'N') {
                            NCJ++;
                            memmove( CarteJouees[NCJ] ,CarteJouees[NCJ-2] ,PosEspace(CarteJouees[NCJ-2]) );
                        }
                    } else if(strcmp(CopierApresEspace(J1[choix]),"+2") == 0) {
                        printf("\nda5let +2\n");
                        for ( i = 0; i < 2; i++) {
                            J2N++;
                            strcpy(J2[J2N],CarteAleatoire());
                            printf("+2");
                        }
                    }  else if(strcmp(J1[choix],"Joker") == 0) {
                        printf("\nda5let Joker\n");
                        printf("Voulez-vous changer la couleur ? (O/N) : ");
                        scanf(" %c",&rep2);
                        if (rep2 == 'O') {
                            printf("Saisir la couleur qui vous voulez changer : ");
                            scanf(" %s",couleur2);
                            strcat(couleur2," ");
                            NCJ++;
                            strcpy(CarteJouees[NCJ],couleur2);
                        } else if(rep2 == 'N') {
                            NCJ++;
                            memmove( CarteJouees[NCJ] ,CarteJouees[NCJ-2] ,PosEspace(CarteJouees[NCJ-2]) );
                        }
                        quiJoue++;
                    } else if (strcmp(CopierApresEspace(J1[choix]),"Block") != 0 && strcmp(CopierApresEspace(J1[choix]),"Reverse") != 0){
                        quiJoue++;
                        printf("\nda5let carte adeya\n");
                    } else {
                        printf("\nda5let block wala reverse\n");
                    };
                    ////////////////////////
                    effaceCarte(J1,J1N,choix);
                    J1N--;
                } else {
                    printf("Impossible d'inserer cette carte \n");
                }
            }
            printf("\nTest : taille du J1 %d cases\n",J1N);


            //test UNO!
            if (J1N == 0) {
                char stop;
                clock_t x_startTime,x_finishTime;
                x_startTime=clock();  // start clock
                printf("%ld",x_startTime);
                scanf(" %c",&stop);
                x_finishTime=clock();  // finish clock
                printf("%ld",x_finishTime);

                if(x_finishTime - x_startTime > 3000 && (stop != 'u' || stop == 'U') ) {
                    printf("khoudh nayek +2");
                    for (i=0;i<2;i++) {
                        J1N++;
                        strcpy(J1[J1N],CarteAleatoire());
                        quiJoue++;
                    }
                }
            }
        } else if(quiJoue % 2 != 0 && machine == 0) {
            //Joueur 2 qui joue

            //Tri a bulles
            bubbleSort(J2,J2N);

            printf("\n%d cartes restantes pour J1",J1N + 1);            
            printf("\nDernier Carte Jouee : %s \n",CarteJouees[NCJ]);
            //Affichage de la main
            printf("Main du 2eme joueur : \n");
            for ( i = 0; i <= J2N; i++) {
                affCarte(i+1,J2[i]);
                printf("\n");
            }
            int choix;
            printf("\nChoisir une carte ou pour prendre une carte tapez 0 : ");
            scanf("%d",&choix);
            choix--;
            if (choix + 1 == 0) {
                int test = 0;
                J2N++;
                strcpy(J2[J2N],CarteAleatoire());
                printf("\nDernier Carte Jouee : %s \n",CarteJouees[NCJ]);
                for ( i = 0; i <= J2N; i++) {
                    affCarte(i+1,J2[i]);
                    printf("\n");
                }
                do {
                    printf("\n Choisir une carte ou appuyer 0 pour passer ton tour : ");
                    scanf("%d",&choix2);
                    choix2--;
                    if (choix2 + 1 == 0) {
                        quiJoue++;
                        test = 1;
                    } else if(CartePossible(J2[choix2],J2,J2N) == 1) {
                        NCJ++;
                        test = 1;
                        strcpy(CarteJouees[NCJ],J2[choix2]);
                        //EffetCarte(J2[choix2],J1,J1N);
                        ////////////////////////
                        int i;char rep2;char couleur2[6];char rep;char couleur[6]="";
                        if (strcmp(J2[choix2],"+4") == 0) {
                            printf("\nda5let +4\n");
                            for ( i=0; i<4; i++) {
                                J1N++;
                                strcpy(J1[J1N],CarteAleatoire());
                                printf("+4*");
                            }
                            printf("Voulez-vous changer la couleur ? (O/N) : ");
                            scanf(" %c",&rep);
                            if (rep == 'O') {
                                printf("Saisir la couleur qui vous voulez changer : ");
                                scanf(" %s",couleur);
                                strcat(couleur," ");
                                NCJ++;
                                strcpy(CarteJouees[NCJ],couleur);
                            } else if(rep == 'N') {
                                NCJ++;
                                memmove( CarteJouees[NCJ] ,CarteJouees[NCJ-2] ,PosEspace(CarteJouees[NCJ-2]) );
                            }
                        } else if(strcmp(CopierApresEspace(J2[choix2]),"+2") == 0) {
                            printf("\nda5let +2\n");
                            for ( i = 0; i < 2; i++) {
                                J1N++;
                                strcpy(J1[J1N],CarteAleatoire());
                                printf("+2");
                            }
                        }  else if(strcmp(J2[choix2],"Joker") == 0) {
                            printf("\nda5let Joker\n");
                            printf("Voulez-vous changer la couleur ? (O/N) : ");
                            scanf(" %c",&rep2);
                            if (rep2 == 'O') {
                                printf("Saisir la couleur qui vous voulez changer : ");
                                scanf(" %s",couleur2);
                                strcat(couleur2," ");
                                NCJ++;
                                strcpy(CarteJouees[NCJ],couleur2);
                            } else if(rep2 == 'N') {
                                NCJ++;
                                memmove( CarteJouees[NCJ] ,CarteJouees[NCJ-2] ,PosEspace(CarteJouees[NCJ-2]) );
                            }
                            quiJoue++;
                        } else if (strcmp(CopierApresEspace(J2[choix2]),"Block") != 0 && strcmp(CopierApresEspace(J2[choix2]),"Reverse") != 0){
                            quiJoue++;
                            printf("\nda5let carte adeya\n");
                        } else {
                            printf("\nda5let block wala reverse\n");
                        }
                        ////////////////////////
                        effaceCarte(J2,J2N,choix2);
                        J2N--;
                    } 
                } while(test != 1);
            } else if(CartePossible(J2[choix],J2,J2N) == 1) {
                NCJ++;
                strcpy(CarteJouees[NCJ],J2[choix]);
                //EffetCarte(J2[choix],J1,J1N);
                ////////////////////////
                int i;char rep2;char couleur2[6];char rep;char couleur[6]="";
                if (strcmp(J2[choix],"+4") == 0) {
                    printf("\nda5let +4\n");
                    for ( i=0; i<4; i++) {
                        J1N++;
                        strcpy(J1[J1N],CarteAleatoire());
                        printf("+4*");
                    }
                    printf("Voulez-vous changer la couleur ? (O/N) : ");
                    scanf(" %c",&rep);
                    if (rep == 'O') {
                        printf("Saisir la couleur qui vous voulez changer : ");
                        scanf(" %s",couleur);
                        strcat(couleur," ");
                        NCJ++;
                        strcpy(CarteJouees[NCJ],couleur);
                    } else if(rep == 'N') {
                        NCJ++;
                        memmove( CarteJouees[NCJ] ,CarteJouees[NCJ-2] ,PosEspace(CarteJouees[NCJ-2]) );
                    }
                } else if(strcmp(CopierApresEspace(J2[choix]),"+2") == 0) {
                    printf("\nda5let +2\n");
                    for ( i = 0; i < 2; i++) {
                        J1N++;
                        strcpy(J1[J1N],CarteAleatoire());
                        printf("+2");
                    }
                }  else if(strcmp(J2[choix],"Joker") == 0) {
                    printf("\nda5let Joker\n");
                    printf("Voulez-vous changer la couleur ? (O/N) : ");
                    scanf(" %c",&rep2);
                    if (rep2 == 'O') {
                        printf("Saisir la couleur qui vous voulez changer : ");
                        scanf(" %s",couleur2);
                        strcat(couleur2," ");
                        NCJ++;
                        strcpy(CarteJouees[NCJ],couleur2);
                    } else if(rep2 == 'N') {
                        NCJ++;
                        memmove( CarteJouees[NCJ] ,CarteJouees[NCJ-2] ,PosEspace(CarteJouees[NCJ-2]) );
                    }
                    quiJoue++;
                } else if (strcmp(CopierApresEspace(J2[choix]),"Block") != 0 && strcmp(CopierApresEspace(J2[choix]),"Reverse") != 0){
                    quiJoue++;
                    printf("\nda5let carte adeya\n");
                } else {
                    printf("\nda5let block wala reverse\n");
                };
                ////////////////////////
                effaceCarte(J2,J2N,choix);
                J2N--;
            } else {
                printf("Impossible d'inserer cette carte \n");
            }
            //test UNO!
            if (J2N == 0) {
                char stop;
                clock_t x_startTime,x_finishTime;
                x_startTime=clock();  // start clock
                scanf(" %c",&stop);
                x_finishTime=clock();  // finish clock
                if(x_finishTime - x_startTime > 3000 && (stop != 'u' || stop == 'U') ) {
                    for(i = 0; i < 2; i++) {
                        J2N++;
                        strcpy(J2[J2N],CarteAleatoire());
                        quiJoue++;
                    }
                }
            }
        } else if (quiJoue % 2 != 0 && machine == 1) {
            //Machine qui joue
            printf("Main du 2eme joueur :");
            for ( i = 0; i <= J2N; i++) {
                printf(" --%s-- ", J2[i]);
            }
            printf("\n");
            //Combien de couleur la machine 3andha
            printf("Combien de couleur la machine 3andha : ");
            CarteMax();
            bubbleSort(J2,J2N);
            for ( i = 0; i <= 3; i++) {
                printf("-%d-",CombienDeCartes[i]);
            }

            int jouable = 0;

            //Combien de carte Rouge jouable
            int nCouleurJouable=0; char couleurJouable[6],couleur[6];
            for (i=0;i<=J2N;i++) {
                memmove(couleur,J2[i],PosEspace(J2[i]));
                if (strcmp(couleur,"Rouge") == 0) {
                    printf("une carte rouge est jouable\n");
                    nCouleurJouable++;
                    if (CartePossible(J2[i],J2,J2N) == 1) {
                        strcpy(couleurJouable,"Rouge");
                    }
                }
            }
            //Combien de carte Bleu jouable
            int x=0;
            for (i=0;i<=J2N;i++) {
                memmove(couleur,J2[i],PosEspace(J2[i]));
                if (strcmp(couleur,"Bleu") == 0 ) {
                    x++;
                    printf("une carte Bleu est jouable\n");
                    if (CartePossible(J2[i],J2,J2N) == 1) {
                        jouable = 1;
                    }
                }
            }
            if (jouable == 1) {
                nCouleurJouable = x;
                strcpy(couleurJouable,"Bleu");
            }
            //Combien de carte Vert jouable
            x=0;jouable=0;
            for (i=0;i<=J2N;i++) {
                memmove(couleur,J2[i],PosEspace(J2[i]));
                if (strcmp(couleur,"Vert") == 0 && CartePossible(J2[i],J2,J2N) == 1) {
                    x++;
                    printf("une carte Vert est jouable\n");
                    if (CartePossible(J2[i],J2,J2N) == 1) {
                        jouable = 1;
                    }
                }
            }
            if (jouable == 1) {
                nCouleurJouable = x;
                strcpy(couleurJouable,"Vert");
            }
            //Combien de carte Jaune jouable
            x=0;jouable=0;
            for (i=0;i<=J2N;i++) {
                memmove(couleur,J2[i],PosEspace(J2[i]));
                if (strcmp(couleur,"Jaune") == 0 && CartePossible(J2[i],J2,J2N) == 1) {
                    x++;
                    printf("une carte Jaune est jouable\n");
                    if (CartePossible(J2[i],J2,J2N) == 1) {
                        jouable = 1;
                    }
                }
            }
            if (jouable == 1) {
                nCouleurJouable = x;
                strcpy(couleurJouable,"Jaune");
            }

            //Joker jouable ou +4 jouable 
            if (strlen(couleurJouable) == 0 && plus4possible(J2,J2N) == 0) {
                strcpy(couleurJouable,'+4');
            } else {
                strcpy(couleurJouable,'Joker');
            }

            printf("\nCouleur Jouable : |%s|",couleurJouable);

            if (strcmp(couleurJouable,'Rouge') == 0) {
                i=0;
                int test = 0;
                do {
                    if(strcmp(memmove(couleur,J2[i],PosEspace(J2[i])),"Rouge") == 0 && CartePossible(J2[i],J2,J2N) == 1) {
                        NCJ++;
                        strcpy(CarteJouees[NCJ],J2[i]);
                        //effet carte
                        quiJoue++;
                        effaceCarte(J2,J2N,i);
                        J2N--;
                        test = 1;
                    }
                    i++;
                } while(test == 0);
            } else if (strcmp(couleurJouable,"Bleu") == 0) {
                i=0;
                int test = 0;
                do {
                    if(strcmp(memmove(couleur,J2[i],PosEspace(J2[i])),"Bleu") == 0 && CartePossible(J2[i],J2,J2N) == 1) {
                        NCJ++;
                        strcpy(CarteJouees[NCJ],J2[i]);
                        //effet carte
                        quiJoue++;
                        effaceCarte(J2,J2N,i);
                        J2N--;
                        test = 1;
                    }
                    i++;
                } while(test == 0);
            } else if (strcmp(couleurJouable,"Vert") == 0) {
                i=0;
                int test = 0;
                do {
                    if(strcmp(memmove(couleur,J2[i],PosEspace(J2[i])),"Vert") == 0 && CartePossible(J2[i],J2,J2N) == 1) {
                        NCJ++;
                        strcpy(CarteJouees[NCJ],J2[i]);
                        //effet carte
                        quiJoue++;
                        effaceCarte(J2,J2N,i);
                        J2N--;
                        test = 1;
                    }
                    i++;
                } while(test == 0);
            } else if (strcmp(couleurJouable,"Jaune") == 0) {
                i=0;
                int test = 0;
                do {
                    if(strcmp(memmove(couleur,J2[i],PosEspace(J2[i])),"Jaune") == 0 && CartePossible(J2[i],J2,J2N) == 1) {
                        NCJ++;
                        strcpy(CarteJouees[NCJ],J2[i]);
                        //effet carte
                        quiJoue++;
                        effaceCarte(J2,J2N,i);
                        J2N--;
                        test = 1;
                    }
                    i++;
                } while(test == 0);
            }
            
            
        }
        
        if(J1N == -1 || J2N == -1) {
            fois++;
            for ( i = 0; i < J2N; i++) {
                if(strcmp(J2[i],"+4") == 0 || strcmp(J2[i],"Joker") == 0) {
                    score2 =+ 50;
                } else if(strcmp(CopierApresEspace(J2[i]),"Block") == 0 || strcmp(CopierApresEspace(J2[i]),"Reverse") == 0 || strcmp(CopierApresEspace(J2[i]),"+2") == 0) {
                    score2 =+ 20;
                } else {
                    char num;
                    num = CopierApresEspace(J1[i])[0];
                    switch (num) {
                    case '1':
                        score2 ++;
                        break;
                    case '2':
                        score2 =+ 2;
                        break;
                    case '3':
                        score2 =+ 3;
                        break;
                    case '4':
                        score2 =+ 4;
                        break;
                    case '5':
                        score2 =+ 5;
                        break;
                    case '6':
                        score2 =+ 6;
                        break;
                    case '7':
                        score2 =+ 7;
                        break;
                    case '8':
                        score2 =+ 8;
                        break;
                    case '9':
                        score2 =+ 9;
                        break;
                    }
                }
            }
            for ( i = 0; i < J2N; i++)
            {
                if(strcmp(J1[i],"+4") == 0 || strcmp(J1[i],"Joker") == 0) {
                    score1 =+ 50;
                } else if(strcmp(CopierApresEspace(J1[i]),"Block") == 0 || strcmp(CopierApresEspace(J1[i]),"Reverse") == 0 || strcmp(CopierApresEspace(J1[i]),"+2") == 0) {
                    score1 =+ 20;
                } else {
                    char num;
                    num = CopierApresEspace(J1[i])[0];
                    switch (num) {
                    case '1':
                        score2 ++;
                        break;
                    case '2':
                        score2 =+ 2;
                        break;
                    case '3':
                        score2 =+ 3;
                        break;
                    case '4':
                        score2 =+ 4;
                        break;
                    case '5':
                        score2 =+ 5;
                        break;
                    case '6':
                        score2 =+ 6;
                        break;
                    case '7':
                        score2 =+ 7;
                        break;
                    case '8':
                        score2 =+ 8;
                        break;
                    case '9':
                        score2 =+ 9;
                        break;
                    }
                }
            }
            if (score1 < score2) {
                printf("\n\n BRAVO joueur 1 est le gagnat avec un score : %d",score1);
                printf("\nScore du 2eme joueur : %d",score2);
            } else if (score2 < score1) {
                printf("\n\n BRAVO joueur 2 est le gagnat avec un score : %d",score2);
                printf("\nScore du 1er joueur : %d",score1);
            } else {
                printf("\n\nEGALITE !!");
                printf("\nScore du 1er joueur : %d, Score du 2eme joueur : %d",score1,score2);
            }
        }

        if (fois >= 2) {
            printf("Saisir 1 pour continuer; 0 pour finir");
            scanf(" %d",&joue);
            if(joue == 1) {
                RempMatCarteCoul();
                RempTableMere();
                J1N=6;
                DistCartes(J1);
                J2N=6;
                DistCartes(J2);
                do {
                    strcpy(CarteJouees[0],CarteAleatoire());
                } while (strcmp(CarteJouees[0],"+4") == 0 );
            } else {
                printf("Au revoir");
            }
        }
    } while (joue == 1);

    printf("Jeu wfet. taille du J1 %d, taille du J2 %d",J1N,J2N);

    return 0;
}


// Position de l'espace
int PosEspace(char ch[]) {
    int i,flag,length;
    length = strlen(ch);
    for (i = 0 ; i <= length ; i++) {
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
    copied = (char*)malloc(20);
    int c = 0;
    int i;
    int length = strlen(ch);
    for ( i = flag; i <= length ; i++) {
        copied[c] = ch[i];
        c++;
    }
    return (char*)copied;
}

// Carte possible ou nn
int CartePossible(char carte[20],char joueur[][20],int joueurN) {
    int test = 0;
    if (strcmp(carte,"Joker") == 0) {
            test = 1;
    } else if(strcmp(carte,"+4") == 0 && plus4possible(joueur,joueurN) == 0) {
        printf("+4possible");
        test = 1;
    } else {
        char carte_1[10],carte_2[10],carte_jouee_1[6],carte_jouee_2[10];
        memmove(carte_1,CarteJouees[NCJ],PosEspace(CarteJouees[NCJ]));  //couleur de la derniere carte jouée
        memmove(carte_jouee_1,carte,PosEspace(carte)); //couleur de la carte à tester
        strcpy(carte_2 ,CopierApresEspace(CarteJouees[NCJ])); //numero de la derniere carte jouée
        strcpy(carte_jouee_2 ,CopierApresEspace(carte)); // numero de la carte à tester
        int resCoul = strcmp(carte_1,carte_jouee_1);
        int resNum = strcmp(carte_2,carte_jouee_2);
        if (resCoul == 0 || resNum == 0) {
            test = 1;
        }
    }
    return test;
}

//Nom de la carte;
char * NomCarte(int couleur,int numero) {
    strcpy(NomCartee,MIC[couleur]);
    strcat(NomCartee," ");
    strcat(NomCartee,MIN[numero]);  
}

//Une carte aleatoire
char * CarteAleatoire() {
    char * carte;
    int x,y,z;
    carte = (char*)malloc(20);
    int test = 0;
    x = rand()%108 + 1;
    do {
        if (x >= 1 && x <= 4) {
            if (TableMere[0] > 0) {
                test = 1;
                TableMere[0]--;
                strcpy(carte,"Joker");
            } 
        } else if (x>4 && x<=8) {
            if (TableMere[1] > 0) {
                test = 1;
                TableMere[1]--;
                strcpy(carte,"+4");
            } 
        } else if (x>8) {
            y = rand()%4;  z = rand()%13;
            if (MatCarteCoul[y][z] > 0) {
                test = 1;
                strcpy(carte,NomCarte(y,z));
                MatCarteCoul[y][z]--;
            }
        }
    } 
    while (test == 0);
    return (char*)carte;
}

//Distribution des cartes
void DistCartes(char joueur[][20]) {
    int i;
    char carte[20];
    // Distribution joueur 1    
    for (i = 0;i <= 6;i++) {
        strcpy(carte,CarteAleatoire());
        strcpy(joueur[i],carte);
    }

    

    /*
    // Distribution joueur 2
    for (i = 0;i < 7;i++) {
        int test = 0;
        do {
            x = rand()%108 + 1;
            if (x >= 1 && x <= 4) {
                if (TableMere[0] > 0) {
                            test = 1;
                            TableMere[0]--;
                            strcat(J2[J2N],"Joker");
                            J2N ++;
                        } 
            } else if (x>4 && x<=8) {
                if (TableMere[1] > 0) {
                            test = 1;
                            TableMere[1]--;
                            strcat(J2[J2N],"+4");
                            J2N ++;
                        } 
            } else if (x>8) {
                y = rand()%4;  z = rand()%13;
                        if (MatCarteCoul[y][z] > 0) {
                            test = 1;
                            strcat(J2[J2N],NomCarte(y,z));
                            J2N ++; MatCarteCoul[y][z]--;
                        }
            }
    
        } while (test == 0);   
    }
    */
}

//Remplissage le tableau mere(1er tableau)
void RempTableMere() {
    TableMere[0] = 4; //+4
    TableMere[1] = 4; //Joker
}

//Remplisse Matrice Cartes Couleurs
int RempMatCarteCoul() {
    int i,j;
    for ( i = 0; i < 4; i++) {
        MatCarteCoul[i][0] = 1;    
    };
    for (i = 0; i < 4; i++){
        for ( j = 1; j < 13; j++){
            MatCarteCoul[i][j] = 2;
        } 
    }
    return 0;
}



//Effet d'une carte
void EffetCarte (char carte[20],char JoueurInfecte[][20],int JoueurInfecteN) {
    int i;char rep2;char couleur2[6];char rep;char couleur[6]="";
    if (strcmp(carte,"+4") == 0) {
        printf("\nda5let +4\n");
        for ( i=0; i<4; i++) {
            JoueurInfecteN++;
            strcpy(JoueurInfecte[JoueurInfecteN],CarteAleatoire());
            printf("+4");
        }
        printf("Voulez-vous changer la couleur ? (O/N) : ");
        scanf(" %c",&rep);
        if (rep == 'O') {
            printf("Saisir la couleur qui vous voulez changer : ");
            scanf(" %s",couleur);
            strcat(couleur," ");
            NCJ++;
            strcpy(CarteJouees[NCJ],couleur);
        } else if(rep == 'N') {
            NCJ++;
            memmove( CarteJouees[NCJ] ,CarteJouees[NCJ-2] ,PosEspace(CarteJouees[NCJ-2]) );
        }
    } else if(strcmp(CopierApresEspace(carte),"+2") == 0) {
        printf("\nda5let +2\n");
        for ( i = 0; i < 2; i++) {
            JoueurInfecteN++;
            strcpy(JoueurInfecte[JoueurInfecteN],CarteAleatoire());
            printf("+2");
        }
    }  else if(strcmp(carte,"Joker") == 0) {
        printf("\nda5let Joker\n");
        printf("Voulez-vous changer la couleur ? (O/N) : ");
        scanf(" %c",&rep2);
        if (rep2 == 'O') {
            printf("Saisir la couleur qui vous voulez changer : ");
            scanf(" %s",couleur2);
            strcat(couleur2," ");
            NCJ++;
            strcpy(CarteJouees[NCJ],couleur2);
        } else if(rep2 == 'N') {
            NCJ++;
            memmove( CarteJouees[NCJ] ,CarteJouees[NCJ-2] ,PosEspace(CarteJouees[NCJ-2]) );
        }
        quiJoue++;
    } else if (strcmp(CopierApresEspace(carte),"Block") != 0 && strcmp(CopierApresEspace(carte),"Reverse") != 0){
        quiJoue++;
        printf("\nda5let carte adeya\n");
    } else {
        printf("\nda5let block wala reverse\n");
        
    }
}

//Efface une carte
void effaceCarte(char joueur[][20], int joueurN, int carte) {
    int i;
    for (i = carte; i <= joueurN; i++) {
        strcpy(joueur[i],joueur[i+1]);
    }
}


//+4 possible ou nn
int plus4possible(char joueur[][20],int joueurN) {
    int i = 1,test = 0;
    do {
        char carte[10];
        strcpy(carte,joueur[i]);
        char carte_1[10],carte_2[10],carte_jouee_1[6],carte_jouee_2[10];
        memmove(carte_1,CarteJouees[NCJ],PosEspace(CarteJouees[NCJ]));  //couleur de la derniere carte jouée
        memmove(carte_jouee_1,carte,PosEspace(carte)); //couleur de la carte à tester
        strcpy(carte_2 ,CopierApresEspace(CarteJouees[NCJ])); //numero de la derniere carte jouée
        strcpy(carte_jouee_2 ,CopierApresEspace(carte)); // numero de la carte à tester
        int resCoul = strcmp(carte_1,carte_jouee_1);
        int resNum = strcmp(carte_2,carte_jouee_2);
        if (resCoul == 0 || resNum == 0 || strcmp(carte,"Joker") == 0) {
            test = 1;
        } 
        i++;
    } while (i <= joueurN && test == 0);
    return test;
}

void Welcome() {
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
    printf("**********************************************************************|                Abene Sebei & Eya Jammoussi                 |*******************************************************************************\n");
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

void affCarte(int num,char carte[20]) {
    printf("%d **********************\n",num);
    printf("*************************\n");
    printf("*******  %s  *******\n",carte);
    printf("*************************\n");
    printf("*************************\n");
}

void bubbleSort(char joueur[][20], int joueurN) {
    int i,test;
    char aux[20];
    do {
        test = 0;
        for ( i = 0; i <= joueurN - 1; i++) {
            if (strcmp(joueur[i+1],joueur[i]) < 0) {
                strcpy(aux,joueur[i]);
                strcpy(joueur[i],joueur[i+1]);
                strcpy(joueur[i+1],aux);
                test = 1;
            }
        } 
    } while (test == 1 );
}

void CarteMax() {
    int i;
    for ( i=0 ; i<=J2N ; i++) {
        if(J2[i][0] == 'R') {
            CombienDeCartes[0]++;
        } else if (J2[i][0] == 'B'){
            CombienDeCartes[1]++;
        } else if (J2[i][0] == 'V'){
            CombienDeCartes[2]++;
        } else if (J2[i][0] == 'J'){
            CombienDeCartes[3]++;
        }
    }
}

int maxCarte() {
    int i,max = 0;
    for ( i = 0; i < 4; i++ ) {
        if (CombienDeCartes[i] > max) {
            max = i;
        }
    }
    return max;
}