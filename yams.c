/**
 * \file yams.c
 * \author Romain Rodrigues
 * \brief Jeu de Yams
 * \version 1.0
 * \date 28 novembre 2021
 * 
 * \copyright Copyright (c) 2021
 * 
 * Ce programme permet de réaliser une partie de Yams
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>

/**
 * \def MAX_CAR
 * \brief nombre de caractère des combinaison de la feuille de marque
 * 
 */
#define MAX_CAR 25  
/**
 * \def MAX_L
 * \brief nombre de ligne de la feuille de marque
 * 
 */
#define MAX_L 17
/**
 * \def MAX
 * \brief largeur de la feuille de marque
 * 
 */
#define MAX 42
/**
 * \def MAX_PRENOM
 * \brief nombre de caractère maximum d'un prénom pour entrer dans la feuille de marque
 * 
 */
#define MAX_PRENOM 9
/**
 * \def DES
 * \brief score max d'un dés
 * 
 */
#define DES 6

/**
 * \fn void prenom(char prenom1[50], char prenom2[50])
 * 
 * \brief Procédure qui permet de saisir les deux noms.
 * 
 * \param prenom1   nom du premier joueur 
 * \param prenom2   nom du deuxième joueur 
 * 
 * Demande le premier nom puis vérifie si il est trop long et si oui alors elle demande un nom plus court,
 * pareil pour le deuxième nom. Ensuite elle vérifie si ces noms sont identique et si c'est le cas 
 * elle demande au deuxième joueur de changer son nom.
 */
void prenom(char prenom1[50], char prenom2[50]){  //procédure qui s'occupe de l'attribution des prénoms
    printf("Entrez le premier prénom :");
    scanf("%s", prenom1);
    while (strlen(prenom1)>MAX_PRENOM){     //boucle qui verifie la longueur du premier prénom (changement si trop long)
        printf("Le prénom est trop long, entrez un prénom plus court.\n");
        printf("Modifié le premier prénom :");
        scanf("%s", prenom1);
    }
    printf("Entrez le deuxième prénom :");
    scanf("%s", prenom2);
    while (strlen(prenom2)>MAX_PRENOM){     //boucle qui verifie la longueur du deuxième prénom (changement si trop long)
        printf("Le prénom est trop long, entrez un prénom plus court.\n");
        printf("Modifié le deuxième prénom :");
        scanf("%s", prenom2);
    }
    while ((strcmp(prenom1, prenom2)==0)){      //boucle qui vérifie que les prénom ne sont pas identique (changement si identique)
        printf("Erreur les deux prénoms sont identique, joueur 2 modifié votre prénom :");
        scanf("%s", prenom2);
        while (strlen(prenom2)>MAX_PRENOM){
            printf("Le prénom est trop long, entrez un prénom plus court.\n");
            printf("Modifié le deuxième prénom :");
            scanf("%s", prenom2);
        }
    }
}

/**
 * \fn void affichage(int tabJ1[MAX_L], int tabJ2[MAX_L], char prenom1[50], char prenom2[50])
 * 
 * \brief Affichage de la feuille de marque.
 * 
 * \param tabJ1 tableau des scrores du premier joueur
 * \param tabJ2 tableau des scrores du deuxième joueur
 * \param prenom1 nom du premier joueur
 * \param prenom2 nom du deuxième joueur
 * 
 * Affichage de la feuille de marque sous forme de tableau.
 */
void affichage(int tabJ1[MAX_L], int tabJ2[MAX_L], char prenom1[50], char prenom2[50]){     //procédure qui affiche la feuille de marque
    int i;
    int a;
    int longueur;
    for(i=1; i<=9; i++){    //boucle qui adapte la longueur du prénom pour éviter les décalages dans la feuille de marque
        if(strlen(prenom1)==i){
            for(a=0; a<(9-i); a++){
                strcat(prenom1," ");
            }
        }
    }
    for(i=1; i<=9; i++){    //boucle qui adapte la longueur du prénom pour éviter les décalages dans la feuille de marque
        if(strlen(prenom2)==i){
            for(a=0; a<(9-i); a++){
                strcat(prenom2," ");
            }
        }
    }
    
    char combinaison[MAX_L][MAX_CAR]={ {"1 [total de 1]      "}, // combinaisons de la feuille de marque 
                                    {"2 [total de 2]      "},
                                    {"3 [total de 3]      "},
                                    {"4 [total de 4]      "}, 
                                    {"5 [total de 5]      "}, 
                                    {"6 [total de 6]      "},
                                    {"Bonus si > à 62 [35]"},
                                    {"Total supérieur     "},
                                    {"Brelan       [total]"},
                                    {"Carre        [total]"},
                                    {"Full house   [25]   "},
                                    {"Petite suite [30]   "},
                                    {"Grande suite [40]   "},
                                    {"Yams         [50]   "},
                                    {"Chance       [total]"},
                                    {"Total inférieur     "},
                                    {"Total               "} };

    for (longueur=0; longueur < MAX; longueur++){   //boucle qui trace une de la largeur du tableau 
        printf("-");
    }
    printf("\n");
    printf("|                    |%s|%s|\n", prenom1, prenom2); //première ligne du tableau avec les noms des joueurs
    for (i=0; i <= 16; i++){    //boucle qui affiche le corp de la feuille 
        for (longueur=0; longueur < MAX; longueur++){   //boucle qui trace une ligne 
            printf("-");
        }
        printf("\n");
        printf("|%s|   %3d   |   %3d   |\n", combinaison[i], tabJ1[i], tabJ2[i]);   //contenu de chaque ligne du tableau
        if ((i==7)||(i==15)){ // division de la feuille de marque (partie supérieur et inférieur)
            for (longueur=0; longueur < MAX; longueur++){   //boucle qui trace une ligne
                printf("-");
            }
            printf("\n");
        }
    }
    for (longueur=0; longueur < MAX; longueur++){   //boucle qui trace une ligne
        printf("-");
    }
    printf("\n\n"); //saut de ligne
}

/**
 * \fn void des(int tabD[5])
 * 
 * @brief Lancer des dés.
 * 
 * @param tabD tableau contenant le score des 5 dés
 * 
 * La procédure lance et les dés et peut ensuite les relancer (2 fois max) si le joueur le souhaite en lui demandent les dés qu'il veut conserver
 * avant de relancer. 
 */
void des(int tabD[5]){      //procédure qui lance les dés et qui peut relancer certain dés ou tous celon les choix de l'utilisateur
    int a;
    int i;
    int sort;
    int longueur;
    bool sorti;
    char valide[10];
    a=0;
    sorti=false;
    srand(time(NULL));
    for (longueur=0; longueur < (MAX-11); longueur++){ //boucle qui trace une ligne 
        printf("-");
    }
    printf("\n");
    printf("|Voici le score des dés :     |\n");
    for (longueur=0; longueur < (MAX-11); longueur++){  //boucle qui trace une ligne
        printf("-");
    }
    printf("\n|");
    for (i=0; i<=4; i++){       //boucle qui lance les dés et attribue ces valeur dans un tableau puis affiche ces valeurs
        tabD[i]=1+(rand() % DES);
        printf("  %d  |",tabD[i]);
    }
    printf("\n");
    for (longueur=0; longueur < (MAX-11); longueur++){  //boucle qui trace une ligne
        printf("-");
    }
    printf("\n\n");
    printf("Voulez-vous relancer (oui ou non) : "); //demande au joueur si il veut relancer
    scanf("%s", valide);
    while((strcmp(valide, "non")!=0)&&(strcmp(valide, "oui")!=0)){
        printf("Erreur veuillez répondre par oui ou non : ");
        scanf("%s", valide);
    }
    printf("\n");
    if(strcmp(valide, "oui")==0){   //boucle qui permet de relancer les dés si le joueur a dit oui 
        while ((a<2)&&(!sorti)){    //boucle qui permet de limiter a deux relance ou une si le joueur le souhaite
            sort=0;
            for ( i = 0; i <= 4; i++)   //boucle qui demande au joueur si il veut conserver les dés un par un et qui relance 
            {
                printf("Voulez vous garder le dé %d (oui ou non) : ", i+1);   //question pour conserver un dés 
                scanf("%s", valide);
                while((strcmp(valide, "non")!=0)&&(strcmp(valide, "oui")!=0)){
                    printf("Erreur veuillez répondre par oui ou non : ");
                    scanf("%s", valide);
                }
                if (strcmp(valide,"non")==0){   //relance le dés la réponse précédente est non
                    tabD[i]=1+(rand() % DES);
                }
                else{
                    sort=sort+1;
                }
            }
            if (sort==5){   //si le veut garder tus ces dés alors on sort on peut sortir de la boucle
                sorti=true;
            }
            printf("\n");
            for (longueur=0; longueur < (MAX-11); longueur++){  //boucle qui trace une ligne
            printf("-");
            }
            printf("\n");
            printf("|Voici le score des dés :     |\n");
            for (longueur=0; longueur < (MAX-11); longueur++){  //boucle qui trace une ligne
                printf("-");
            }
            printf("\n|");
            for (i=0; i<=4; i++){   //affichage des dés
                printf("  %d  |",tabD[i]);
            }
            printf("\n");
            for (longueur=0; longueur < (MAX-11); longueur++){  //boucle qui trace une ligne
                printf("-");
            }
            printf("\n\n");
            if((sorti==false)&&(a==0)){   //boucle qui demande au joueur si il veut effectuer sa deuxieme relance 
                printf("Voulez-vous relancer (oui ou non) : ");
                scanf("%s", valide);
                while((strcmp(valide, "non")!=0)&&(strcmp(valide, "oui")!=0)){
                    printf("Erreur veuillez répondre par oui ou non : ");
                    scanf("%s", valide);
                }
                printf("\n");
                if(strcmp(valide, "non")==0){   //si il ne veut pas on sort de la boucle
                    sorti=true;
                }
            }
            a=a+1;  //incrémentation 
        }
    }
}

/**
 * \fn void echange(int tabD[4], int i, int a)
 * 
 * \brief Echange deux valeur.
 * 
 * \param tabD tableau contenant le score des 5 dés
 * \param i position du premier dés à échanger
 * \param a position du deuxième dés à échanger
 * 
 * Echange deux valeur dont la position est donnée, cette échange est utiliser pour trier.
 */
void echange(int tabD[4], int i, int a){    //procédure qui échange deux valeur d'un tableau (utiliser pour trier)
    int tmp;
    tmp=tabD[i];
    tabD[i]=tabD[a];
    tabD[a]=tmp;
}

/**
 * \fn void combinaison(int tab[MAX_L], int tabDes[4], int tabUtiliser[MAX_L])
 * 
 * @brief Choix de la combinaison et affectation du score associé.
 * 
 * @param tab tableau des scores du joueur en cours de jeu 
 * @param tabDes tableau contenant le score des 5 dés
 * @param tabUtiliser tableau qui répertorie les combinaison déjà utiliser 
 * 
 * Cette procédure demande une combinaison au joueur si celle ci est déjà utiliser alors une autre combinaison est demandée et si elle n'est pas utiliser
 * alors la procédure calcul le score associé et met a jour la feuille de marque du joueur.
 */
void combinaison(int tab[MAX_L], int tabDes[4], int tabUtiliser[MAX_L]){    //procédure qui demande la combinaison, calcul le score associé a celle ci et met a jour le feuille de marque
    char comb[20];
    int pos;
    int compteur;
    int minTri, indminTri;
    int full1, full2;
    int i;
    int a;
    int score;
    bool combTrouve;
    bool sortir;
    printf("Entrez la combinaison que vous voulez utiliser : ");    //demande la combinaison
    scanf("%s", comb);
    sortir=false;
    score=0;
    for(i=0; i<4; i++){     //tri des dés par odre croissant avec un tri par sélection
        minTri=tabDes[i];
        indminTri=i;
        for(a=i+1; a<5; a++){
            if (tabDes[a]<minTri){
                minTri=tabDes[a];
                indminTri=a;
            }
        }
        echange(tabDes,i, indminTri);
    }
    while(!(sortir)){   //boucle qui calcul le score de la combinaison ou qui en demande une autre si elle est déjà utilisé
        a=0;
        combTrouve=false;
        if(strcmp(comb, "1")==0){   //calcul de la combinaison "1"
            pos=0;
            if(tabUtiliser[pos]!=0){    //demande autre combinaison si celle ci est déja utilisé
                printf("Cette combinaison est déjà utilser.\n");
                printf("Entrez une autre combinaison : ");
                scanf("%s", comb);
            }
            else{
                for(i=0; i<5; i++){   //boucle qui ajoute 1 au score si le dés vaut 1
                    if(tabDes[i]==1){
                        score=score+1;
                    }
                }
                sortir=true;
                tabUtiliser[pos]=1;   //on place un 1 dans un autre tableau pour indiquer que cette combinaison a été utiliser
            }
        }
        else if(strcmp(comb, "2")==0){  //calcul de la combinaison "2"
            pos=1;
            if(tabUtiliser[pos]!=0){    //demande autre combinaison si celle ci est déja utilisé
                printf("Cette combinaison est déjà utilser.\n");
                printf("Entrez une autre combinaison : ");
                scanf("%s", comb);
            }
            else{
                for(i=0; i<5; i++){    //boucle qui ajoute 2 au score si le dés vaut 2
                    if(tabDes[i]==2){
                        score=score+2;
                    }
                }
                sortir=true;
                tabUtiliser[pos]=1;    //on place un 1 dans un autre tableau pour indiquer que cette combinaison a été utiliser
            }
        }
        else if(strcmp(comb, "3")==0){  //calcul de la combinaison "3"
            pos=2;
            if(tabUtiliser[pos]!=0){    //demande autre combinaison si celle ci est déja utilisé
                printf("Cette combinaison est déjà utilser.\n");
                printf("Entrez une autre combinaison : ");
                scanf("%s", comb);
            }
            else{
                for(i=0; i<5; i++){    //boucle qui ajoute 3 au score si le dés vaut 3
                    if(tabDes[i]==3){
                        score=score+3;
                    }
                }
                sortir=true;
                tabUtiliser[pos]=1;    //on place un 1 dans un autre tableau pour indiquer que cette combinaison a été utiliser
            }
        }
        else if(strcmp(comb, "4")==0){  //calcul de la combinaison "4"
            pos=3;
            if(tabUtiliser[pos]!=0){    //demande autre combinaison si celle ci est déja utilisé
                printf("Cette combinaison est déjà utilser.\n");
                printf("Entrez une autre combinaison : ");
                scanf("%s", comb);
            }
            else{
                for(i=0; i<5; i++){    //boucle qui ajoute 4 au score si le dés vaut 4
                    if(tabDes[i]==4){
                        score=score+4;
                    }
                }
                sortir=true;
                tabUtiliser[pos]=1;    //on place un 1 dans un autre tableau pour indiquer que cette combinaison a été utiliser
            }
        }
        else if(strcmp(comb, "5")==0){  //calcul de la combinaison "5"
            pos=4;
            if(tabUtiliser[pos]!=0){    //demande autre combinaison si celle ci est déja utilisé
                printf("Cette combinaison est déjà utilser.\n");
                printf("Entrez une autre combinaison : ");
                scanf("%s", comb);
            }
            else{
                for(i=0; i<5; i++){    //boucle qui ajoute 5 au score si le dés vaut 5
                    if(tabDes[i]==5){
                        score=score+5;
                    }
                }
                sortir=true;
                tabUtiliser[pos]=1;    //on place un 1 dans un autre tableau pour indiquer que cette combinaison a été utiliser
            }
        }
        else if(strcmp(comb, "6")==0){  //calcul de la combinaison "6"
            pos=5;
            if(tabUtiliser[pos]!=0){    //demande autre combinaison si celle ci est déja utilisé
                printf("Cette combinaison est déjà utilser.\n");
                printf("Entrez une autre combinaison : ");
                scanf("%s", comb);
            }
            else{
                for(i=0; i<5; i++){    //boucle qui ajoute 6 au score si le dés vaut 6
                    if(tabDes[i]==6){
                        score=score+6;
                    }
                }
                sortir=true;
                tabUtiliser[pos]=1;    //on place un 1 dans un autre tableau pour indiquer que cette combinaison a été utiliser
            }
        }
        else if(strcmp(comb, "brelan")==0){     //calcul de la combinaison "brelan"
            pos=8;
            if(tabUtiliser[pos]!=0){    //demande autre combinaison si celle ci est déja utilisé
                printf("Cette combinaison est déjà utilser.\n");
                printf("Entrez une autre combinaison : ");
                scanf("%s", comb);
            }
            else{
                while((a<5)&&(!(combTrouve))){    //boucle de calcul
                    compteur=0;
                    for(i=0; i<5; i++){    //boucle qui compare les dés et ajoute 1 au compteur si deux dés sont identique
                        if(tabDes[a]==tabDes[i]){
                            compteur=compteur+1;
                        }
                    }
                    if(compteur==3){    //si trois dés sont identique on arrete la recherche et le score vaut le total des dés
                        for(i=0; i<5; i++){
                            score=score+tabDes[i];
                        }
                        combTrouve=true;
                    }
                    a=a+1;
                }
                sortir=true;
                tabUtiliser[pos]=1;   //on place un 1 dans un autre tableau pour indiquer que cette combinaison a été utiliser
            }
        }
        else if(strcmp(comb, "carre")==0){      //calcul de la combinaison "carre"
            pos=9;
            if(tabUtiliser[pos]!=0){    //demande autre combinaison si celle ci est déja utilisé
                printf("Cette combinaison est déjà utilser.\n");
                printf("Entrez une autre combinaison : ");
                scanf("%s", comb);
            }
            else{
                while((a<5)&&(!(combTrouve))){    //boucle de calcul
                    compteur=0;
                    for(i=0; i<5; i++){    //boucle qui compare les dés et ajoute 1 au compteur si deux dés sont identique
                        if(tabDes[a]==tabDes[i]){
                            compteur=compteur+1;
                        }
                    }
                    if(compteur==4){    //si quatres dés sont identique on arrete la recherche et le score vaut le total des dés
                        for(i=0; i<5; i++){
                            score=score+tabDes[i];
                        }
                        combTrouve=true;
                    }
                    a=a+1;
                }
                sortir=true;
                tabUtiliser[pos]=1;   //on place un 1 dans un autre tableau pour indiquer que cette combinaison a été utiliser
            }
        }
        else if(strcmp(comb, "full")==0){     //calcul de la combinaison "full house"
            pos=10;
            full1=0;
            if(tabUtiliser[pos]!=0){    //demande autre combinaison si celle ci est déja utilisé
                printf("Cette combinaison est déjà utilser.\n");
                printf("Entrez une autre combinaison : ");
                scanf("%s", comb);
            }
            else{
                while((a<5)&&(!(combTrouve))){    //boucle de calcul
                    compteur=0;
                    for(i=0; i<5; i++){    //boucle qui compare les dés et ajoute 1 au compteur si deux dés sont identique
                        if(tabDes[a]==tabDes[i]){
                            compteur=compteur+1;
                        }
                    }
                    if(compteur==3){    //si trois dés sont identique on compare les deux autres dés et si ils sont identiques le score vaut 25
                        for(i=0; i<5; i++){
                            if(tabDes[a]!=tabDes[i]){   //on place les deux autres valeurs dans des variables hors du tableau
                                if(full1==0){
                                    full1=tabDes[i];
                                }
                                else{
                                    full2=tabDes[i];
                                }
                            }
                        }
                        if(full1==full2){   //attribution du score
                            score=25;
                            combTrouve=true;
                        }
                    }
                    a=a+1;
                }
                sortir=true;
                tabUtiliser[pos]=1;    //on place un 1 dans un autre tableau pour indiquer que cette combinaison a été utiliser
            }
        }
        else if(strcmp(comb, "petite")==0){     //calcul de la combinaison "petite suite"
            pos=11;
            if(tabUtiliser[pos]!=0){    //demande autre combinaison si celle ci est déja utilisé
                printf("Cette combinaison est déjà utilser.\n");
                printf("Entrez une autre combinaison : ");
                scanf("%s", comb);
            }
            else{
                compteur=0;
                for(i=0; i<4; i++){    //on compare un dés et le suivant et on ajoute 1 au compteur si sa valeur est inférieur 
                    if(tabDes[i]==(tabDes[i+1])-1){
                        compteur=compteur+1;
                    }
                }
                if(compteur==3){    //si il y a une chaine de 4 dés qui se suivent le score vaut 30
                    score=30;
                }
                sortir=true;
                tabUtiliser[pos]=1;    //on place un 1 dans un autre tableau pour indiquer que cette combinaison a été utiliser
            }
        }
        else if(strcmp(comb, "grande")==0){     //calcul de la combinaison "grande suite"
            pos=12;
            if(tabUtiliser[pos]!=0){    //demande autre combinaison si celle ci est déja utilisé
                printf("Cette combinaison est déjà utilser.\n");
                printf("Entrez une autre combinaison : ");
                scanf("%s", comb);
            }
            else{
                compteur=0;
                for(i=0; i<4; i++){    //on compare un dés et le suivant et on ajoute 1 au compteur si sa valeur est inférieur
                    if(tabDes[i]<tabDes[i+1]){
                        compteur=compteur+1;
                    }
                }
                if(compteur==4){    //si il y a une chaine de 5 dés qui se suivent le score vaut 40
                    score=40;
                }
                sortir=true;
                tabUtiliser[pos]=1;    //on place un 1 dans un autre tableau pour indiquer que cette combinaison a été utiliser
            }
        }
        else if(strcmp(comb, "yams")==0){     //calcul de la combinaison "yams"
            pos=13;
            if(tabUtiliser[pos]!=0){    //demande autre combinaison si celle ci est déja utilisé
                printf("Cette combinaison est déjà utilser.\n");
                printf("Entrez une autre combinaison : ");
                scanf("%s", comb);
            }
            else{
                compteur=0;
                for(i=0; i<4; i++){    //on compare un dés et le suivant et on ajoute 1 au compteur si leur valeur son égal
                    if(tabDes[i]==tabDes[i+1]){
                        compteur=compteur+1;
                    }
                }
                if(compteur==4){    //si les 5 dés sont identiques le score vaut 50
                    score=50;
                }
                sortir=true;
                tabUtiliser[pos]=1;    //on place un 1 dans un autre tableau pour indiquer que cette combinaison a été utiliser
            }
        }
        else if(strcmp(comb, "chance")==0){     //calcul de la combinaison "chance"
            pos=14;
            if(tabUtiliser[pos]!=0){    //demande autre combinaison si celle ci est déja utilisé
                printf("Cette combinaison est déjà utilser.\n");
                printf("Entrez une autre combinaison : ");
                scanf("%s", comb);
            }
            else{
                for(i=0; i<5; i++){    //le scrore vaut le total des dés 
                    score=score+tabDes[i];
                }
                sortir=true;
                tabUtiliser[pos]=1;    //on place un 1 dans un autre tableau pour indiquer que cette combinaison a été utiliser
            }
        }
        else{
            printf("Cette combinaison n'éxiste pas.\n");
            printf("Entrez une autre combinaison : ");
            scanf("%s", comb);
        }
    }
    printf("\n");
    for (i=0; i < (MAX-11); i++){   //boucle qui trace une ligne
        printf("-");
    }
    printf("\n");
    printf("|Voici le score obtenu :      |\n");
    for (i=0; i < (MAX-11); i++){
        printf("-");
    }
    printf("\n|        score = %2d           |\n", score);   //affichage du score de la combinaison
    for (i=0; i < (MAX-11); i++){   //boucle qui trace une ligne
        printf("-");
    }
    printf("\n\n");    //saut de ligne
    tab[pos]=score;
}


/**
 * \fn void score(int tabJ1[MAX_L], int tabJ2[MAX_L])
 * 
 * \brief Calcul des bonus et scores finaux.
 * 
 * \param tabJ1 tableau des scrore du premier joueur
 * \param tabJ2 tableau des scrore du deuxième joueur
 * 
 * La procédure vérifie si les joueurs sont éligibles au bonus, si oui ils obtiennent le bonus. Cette procédure calcul également les score finaux
 * et met a jour la feuille de marque.
 */
void score(int tabJ1[MAX_L], int tabJ2[MAX_L]){   //boucle qui calcul le bonus et les scores finaux et met a jour la feuille de marque
    int scoreJ1;
    int scoreJ2;
    int i;
    scoreJ1=0;
    scoreJ2=0;
    for (i=0; i<6; i++){    //boucle qui calcul le score supérieur
        scoreJ1=scoreJ1+tabJ1[i];
        scoreJ2=scoreJ2+tabJ2[i];
    }
    if(scoreJ1>62){    //calcul du bonus pour le joueur 1 si le score supérieur est supérieur a 62
        tabJ1[6]=35;
        scoreJ1=scoreJ1+35;
    }
    if(scoreJ2>62){    //calcul du bonus pour le joueur 2 si le score supérieur est supérieur a 62
        tabJ2[6]=35;
        scoreJ2=scoreJ2+35;
    }
    tabJ1[7]=scoreJ1;
    tabJ2[7]=scoreJ2;
    scoreJ1=0;
    scoreJ2=0;
    for (i=8; i<15; i++){   //boucle qui calcul le score inférieur 
        scoreJ1=scoreJ1+tabJ1[i];
        scoreJ2=scoreJ2+tabJ2[i];
    }
    tabJ1[15]=scoreJ1;
    tabJ2[15]=scoreJ2;
    tabJ1[16]=tabJ1[15]+tabJ1[7];   //calcul du score final pour le joueur 1
    tabJ2[16]=tabJ2[15]+tabJ2[7];   //calcul du score final pour le joueur 2
}

/**
 * \fn void listeCombinaison()
 * 
 * \brief Liste des combinaison
 * 
 * Affiche la liste des combinaison a utiliser pour le jeu de yams
 */
void listeCombinaison(){    //procédure qui affiche la liste des combinaisons
    int i;
    printf("\n");    //saut de ligne
    printf("Saisir ce qui est entre apostrophe.\n");
    for (i=0; i < 75; i++){
        printf("-");
    }
    printf("\n");
    printf("|Combinaison n°1 : '1'   |Combinaison n°7  : 'brelan'                     |\n");
    printf("|Combinaison n°2 : '2'   |Combinaison n°8  : 'carre'                      |\n");
    printf("|Combinaison n°3 : '3'   |Combinaison n°9  : 'full'   pour le full house  |\n");
    printf("|Combinaison n°4 : '4'   |Combinaison n°10 : 'petite' pour la petite suite|\n");
    printf("|Combinaison n°5 : '5'   |Combinaison n°11 : 'grande' pour la grande suite|\n");
    printf("|Combinaison n°6 : '6'   |Combinaison n°12 : 'yams'                       |\n");
    printf("|                        |Combinaison n°13 : 'chance'                     |\n");
    for (i=0; i < 75; i++){
        printf("-");
    }
    printf("\n\n");
}

/**
 * \fn int main()
 * 
 * \brief Programme principal du jeu
 * 
 * \return int  Fin du programme
 * 
 * Programme qui réalise les 13 tours de la partie de yams en faisant jouer les deux jouer l'un après l'autres et affiche le vainqueur à la fin de la partie
 */
int main(){     //programme principal
    char joueur1[50];   //nom du joueur 1
    char joueur2[50];   //nom du joueur 2
    char lancer[20];
    char comb[20];
    int tabCombUtiliser1[MAX_L];    //tableau des combinaison utiliser ou non du joueur 1
    int tabCombUtiliser2[MAX_L];    //tableau des combinaison utiliser ou non du joueur 1
    int tableauJ1[MAX_L];   //tableau des scores du joueur 1
    int tableauJ2[MAX_L];   //tableau des scores du joueur 1
    int tableauDes[5];   //tableau pour le score des dés
    int tour;
    int tourJoueur;
    int i;
    for ( i = 0; i <= (MAX_L-1); i++){  //initialisation des tableaux 
        tabCombUtiliser1[i]=0;
        tabCombUtiliser2[i]=0;
        tableauJ1[i]=0;
        tableauJ2[i]=0;
    }
    prenom(joueur1, joueur2);   //attribution du nom des joueurs
    for(tour=1; tour<=13; tour++){     //boucle qui réalise les 13 tours de jeux
        for(tourJoueur=1; tourJoueur<=2; tourJoueur++){    //boucle qui fait les joueur chacun leur tour
            if(tourJoueur==1){
                printf("C'est au tour de %s de jouer.\n\n", joueur1);
            }
            else{
                printf("C'est au tour de %s de jouer.\n\n", joueur2);
            }
            sleep(3);   //pause de trois seconde pour que l'utilisateur ait le temps de voir c'est a qui de joué
            affichage(tableauJ1, tableauJ2, joueur1, joueur2);    //affichage de la feuille de marque
            printf("\nTaper 'lancer' lorsque vous voulez lancer les dés : ");   //demande de lancer de dés 
            scanf("%s", lancer);
            printf("\n");
            while(strcmp(lancer, "lancer")!=0){
                printf("Erreur, taper 'lancer' lorsque vous voulez lancer les dés : ");
                scanf("%s", lancer);
            }
            printf("\n");
            des(tableauDes);    //lancer des dés quand l'utilisateur l'aura décidés et relancer des dés si l'utilisateur le veut 
            printf("Voulez-vous voir la liste des combinaisons avant de la choisir : ");   //demande pour voir la liste des combinaisons
            scanf("%s", comb);
            while((strcmp(comb, "oui")!=0)&&(strcmp(comb, "non")!=0)){
                printf("Erreur, taper 'oui si vous voulez voir la liste et 'non' sinon : ");
                scanf("%s", comb);
            }
            if(strcmp(comb, "oui")==0){    //affichage de la liste des combinaisons si l'utilisateur a dit oui 
                listeCombinaison();
            }
            if(tourJoueur==1){    //choix de la combinaison et calcul de celle ci des joueurs selon le tour
                combinaison(tableauJ1, tableauDes, tabCombUtiliser1);
            }
            else{
                combinaison(tableauJ2, tableauDes, tabCombUtiliser2);
            }
            sleep(5);   //pause de 5 secondes pour que l'utilisateur ait le temps de voir le score de sa combinaison 
        }
    }
    score(tableauJ1, tableauJ2);    //calcul des des bonus et scores finaux
    printf("Voici la feuille de marque finale.\n\n");
    affichage(tableauJ1, tableauJ2, joueur1, joueur2);   //affichage de la feuille de marque remplie
    if(tableauJ1[16]<tableauJ2[16]){    
        printf("Le vainqueur de la partie est %s\n", joueur2);  //affichage du vainqueur
    }
    else{
        printf("Le vainqueur de la partie est %s\n", joueur1);  //affichage du vainqueur
    }
    return EXIT_SUCCESS;
}