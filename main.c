#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define DEBUG 1
#define COLOR_MAP 1
#define MAP_H 18
#define MAP_W 24
#define MAP_ITEM 4
#define MAP_J1_PLACEMENT 0
#define MAP_J2_PLACEMENT 1
#define MAP_J1_TIRE 2
#define MAP_J2_TIRE 3
#define JOUEUR1 0
#define JOUEUR2 1
#define JOUEUR_NBR 2
#define JOUEUR_ITEM 4 // l'item 0 cause des problèmes à l'affichage il est donc un espace inutile...
#define JOUEUR_COUP 1
#define JOUEUR_POSY 2
#define JOUEUR_POSX 3
#define HUMAIN 0
#define IA 1

int main()
{

    menu();

}

void waitFor (unsigned int secs) {
    unsigned int retTime = time(0) + secs;   // Get finishing time.
    while (time(0) < retTime);               // Loop until it arrives.
}
int doRand(int startVal, int endVal){
    waitFor(0.05);
    srand(time(NULL)*rand());
    if(startVal == 0 && endVal == 1){
        return rand() % 2;
    }else{
        return (rand() % ((endVal + startVal -1)))+ startVal;
    }
}
void color(int t,int f){
        HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(H,f*16+t);
}
void debug(const char* texte){
    if (DEBUG == 1){
        color(14,0);
        printf("%s\n",texte);
        color(7,0);
    }
}
int erreur(const char* texte){
        color(12,0);
        printf("%s\n",texte);
        color(7,0);
        return 1;
}
void purge(int map[MAP_H][MAP_W][MAP_ITEM],int player[JOUEUR_NBR][JOUEUR_ITEM]){
    int i = 0;
    int j = 0;
    int k = 0;
    for(i=0; i<MAP_H; i++){
        for(j=0; j<MAP_W; j++){
            for(k=0; k<MAP_ITEM; k++){
                map[i][j][k] = 0;
            }
        }
    }
    for(i=0; i<JOUEUR_NBR; i++){
        for(j=0; j<JOUEUR_ITEM; j++){
            player[JOUEUR_NBR][JOUEUR_ITEM] = 0;
        }
    }

}

void printGame(int map[MAP_H][MAP_W][MAP_ITEM], int niveau){
    int i = 0;
    int j = 0;
    //printf("Y/X|A.B.C.D.E.F.G.H.I.J.K.L.M.N.O.P.Q.R.S.T.U.V.W.X.\n");
    for(i=-1; i<MAP_H; i++){
            if (i == -1){
              printf("Y/X|");
            }else if (i<10){
                printf(" %d |",i);
            }else {
            printf("%d |",i);
            }
        for(j=0; j<MAP_W; j++){
            if (i ==-1){
                if (j < 10){
                    printf(" %d ",j);
                }else {
                    printf("%d ",j);
                }

            }
            if (COLOR_MAP == 1){
                if (map[i][j][niveau] == 0){
                    color(3,3);
                }else if (map[i][j][niveau] == 1 || map[i][j][niveau] == 2 || map[i][j][niveau] == 3 || map[i][j][niveau] == 4){
                    color(7,2);
                }else if (map[i][j][niveau] == 9){
                    color(12,12);
                }else if (map[i][j][niveau] == 8){
                    color(11,11);
                }
            }
            if (i != -1){
                printf(" %d ", map[i][j][niveau]);
            }

            color(7,0);
        }printf("\n");
    }
}

void placementCorvette(int map[MAP_H][MAP_W][MAP_ITEM], int niveau, int typeplayer){
    debug("Entre dans PlacementCorvette");
    int placement = 0;
    int coordX = 0;
    int coordY = 0;
    while (placement == 0){
        if (typeplayer == IA){
            coordX = doRand(0,MAP_W-1);
            coordY = doRand(0,MAP_H-1);
            if (!(coordX < 0 || coordX >= MAP_W || coordY < 0 || coordY >= MAP_H)){
                placement = 1;
            }
        }else if (typeplayer == HUMAIN){
            printf("Placement du Corvette (taille 1)\n");
            printf("\nEntrer coordonner X entre 0 et %d :", MAP_W-1);
            scanf("%d", &coordX);
            fflush(stdin);
            printf("Entrer coordonner Y entre 0 et %d :", MAP_H-1);
            scanf("%d", &coordY);
            fflush(stdin);
            if (coordX < 0 || coordX >= MAP_W || coordY < 0 || coordY >= MAP_H){
                erreur("Position Invalide !");
            }
            else {
                placement = 1;
            }
        }
    }
    if (map[coordY][coordX][niveau] == 0){
        map[coordY][coordX][niveau] = 1;
        placement = 1;
        debug("Bateau Corvette placer");
        printf("coordX %d, coordY %d\n",coordX,coordY);
    }

}

void placementDestroyer(int map[MAP_H][MAP_W][MAP_ITEM], int niveau, int typeplayer){
    debug("Entre dans PlacementDestroyer");
    int placement = 0;
    int coordX = 0;
    int coordY = 0;
    int sens = 0;
    while (placement == 0){
        int verif = 0;
        if (typeplayer == IA){
            coordX = doRand(0,MAP_W-1);
            coordY = doRand(0,MAP_H-1);
            sens = doRand(0,1);
            if (!(coordX < 0 || coordX >= MAP_W || coordY < 0 || coordY >= MAP_H) && !(sens < 0 || sens > 1)){
                placement = 1;
            }
        }else if ( typeplayer == HUMAIN){
            printf("Placement du Destroyer (taille 3)\n");
            printf("\nEntrer coordonner X entre 0 et %d :", MAP_W-1);
            scanf("%d", &coordX);
            fflush(stdin);
            printf("Entrer coordonner Y entre 0 et %d :", MAP_H-1);
            scanf("%d", &coordY);
            fflush(stdin);
            printf("Entrer le sens du bateau, 0 = bas 1 = droite :");
            scanf("%d", &sens);
            fflush(stdin);
            if (map[coordY][coordX][niveau] != 0){
                verif = erreur("Vous ne pouvez pas placer de bateau ici !");
            }
            if (coordX < 0 || coordX >= MAP_W || coordY < 0 || coordY >= MAP_H){
                verif = erreur("Position Invalide !");
            }
            if (sens < 0 || sens > 1){
                verif = erreur("Sens du bateau Invalide !");
            }
            if (verif == 0) {
                placement = 1;
            }
        }
    }
    switch(sens){
    case 0:
        if (coordY+2 < MAP_H && map[coordY][coordX][niveau] == 0 && map[coordY+1][coordX][niveau] == 0 && map[coordY+2][coordX][niveau] == 0){
            map[coordY][coordX][niveau] = 2;
            map[coordY+1][coordX][niveau] = 2;
            map[coordY+2][coordX][niveau] = 2;
            debug("Bateau Destroyer placer");
            printf("coordX %d, coordY %d, sens %d\n",coordX,coordY,sens);
        }
        break;
    case 1:
        if (coordX+2 < MAP_H && map[coordY][coordX][niveau] == 0&& map[coordY][coordX+1][niveau] == 0 && map[coordY][coordX+2][niveau] == 0 ){
            map[coordY][coordX][niveau] = 2;
            map[coordY][coordX+1][niveau] = 2;
            map[coordY][coordX+2][niveau] = 2;
            debug("Bateau Destroyer placer");
            printf("coordX %d, coordY %d, sens %d\n",coordX,coordY,sens);
        }
        break;
    default:
        debug("Parametre invalide !");
        break;
    }
}

void placementCroiseur(int map[MAP_H][MAP_W][MAP_ITEM], int niveau, int typeplayer){
    debug("Entre dans PlacementCroiseur");
    int placement = 0;
    int coordX = 0;
    int coordY = 0;
    int sens = 0;
    while (placement == 0){
        int verif = 0;
        if (typeplayer == IA){
            coordX = doRand(0,MAP_W-1);
            coordY = doRand(0,MAP_H-1);
            sens = doRand(0,1);
            if (!(coordX < 0 || coordX >= MAP_W || coordY < 0 || coordY >= MAP_H) && !(sens < 0 || sens > 1)){
                placement = 1;
            }
        }else if ( typeplayer == HUMAIN){
            printf("Placement du Croiseur (taille 4)\n");
            printf("\nEntrer coordonner X entre 0 et %d :", MAP_W-1);
            scanf("%d", &coordX);
            fflush(stdin);
            printf("Entrer coordonner Y entre 0 et %d :", MAP_H-1);
            scanf("%d", &coordY);
            fflush(stdin);
            printf("Entrer le sens du bateau, 0 = bas 1 = droite :");
            scanf("%d", &sens);
            fflush(stdin);
            if (map[coordY][coordX][niveau] != 0){
                verif = erreur("Vous ne pouvez pas placer de bateau ici !");
            }
            if (coordX < 0 || coordX >= MAP_W || coordY < 0 || coordY >= MAP_H){
                verif = erreur("Position Invalide !");
            }
            if (sens < 0 || sens > 1){
                verif = erreur("Sens du bateau Invalide !");
            }
            if (verif == 0) {
                placement = 1;
            }
        }
    }
    switch(sens){
    case 0:
        if (coordY+3 < MAP_H && map[coordY][coordX][niveau] == 0 && map[coordY+1][coordX][niveau] == 0
               && map[coordY+2][coordX][niveau] == 0 && map[coordY+3][coordX][niveau] == 0){
            map[coordY][coordX][niveau] = 3;
            map[coordY+1][coordX][niveau] = 3;
            map[coordY+2][coordX][niveau] = 3;
            map[coordY+3][coordX][niveau] = 3;
            debug("Bateau Croiseur placer");
            printf("coordX %d, coordY %d, sens %d\n",coordX,coordY,sens);
        }
        break;
    case 1:
        if (coordX+3 < MAP_W && map[coordY][coordX][niveau] == 0&& map[coordY][coordX+1][niveau] == 0
            && map[coordY][coordX+2][niveau] == 0 && map[coordY][coordX+3][niveau] == 0){
            map[coordY][coordX][niveau] = 3;
            map[coordY][coordX+1][niveau] = 3;
            map[coordY][coordX+2][niveau] = 3;
            map[coordY][coordX+3][niveau] = 3;
            debug("Bateau Croiseur placer");
            printf("coordX %d, coordY %d, sens %d\n",coordX,coordY,sens);
        }
        break;
    default:
        debug("Parametre invalide !");
        break;
    }
}

void placementPorteAvion(int map[MAP_H][MAP_W][MAP_ITEM], int niveau, int typeplayer){
    debug("Entre dans PlacementPorteAvion");
    int placement = 0;
    int coordX = 0;
    int coordY = 0;
    int sens = 0;
    while (placement == 0){
        int verif = 0;
        if (typeplayer == IA){
            coordX = doRand(0,MAP_W-1);
            coordY = doRand(0,MAP_H-1);
            sens = doRand(0,1);
            if (!(coordX < 0 || coordX >= MAP_W || coordY < 0 || coordY >= MAP_H) && !(sens < 0 || sens > 1)){
                placement = 1;
            }
        }else if ( typeplayer == HUMAIN){
            printf("Placement du Porte-avion (taille 6)\n");
            printf("\nEntrer coordonner X entre 0 et %d :", MAP_W-1);
            scanf("%d", &coordX);
            fflush(stdin);
            printf("Entrer coordonner Y entre 0 et %d :", MAP_H-1);
            scanf("%d", &coordY);
            fflush(stdin);
            printf("Entrer le sens du bateau, 0 = bas 1 = droite :");
            scanf("%d", &sens);
            fflush(stdin);
            if (map[coordY][coordX][niveau] != 0){
                verif = erreur("Vous ne pouvez pas placer de bateau ici !");
            }
            if (coordX < 0 || coordX >= MAP_W || coordY < 0 || coordY >= MAP_H){
                verif = erreur("Position Invalide !");
            }
            if (sens < 0 || sens > 1){
                verif = erreur("Sens du bateau Invalide !");
            }
            if (verif == 0) {
                placement = 1;
            }
        }
    }
    switch(sens){
    case 0:
        if (coordY+5 < MAP_H && map[coordY][coordX][niveau] == 0 && map[coordY+1][coordX][niveau] == 0 && map[coordY+2][coordX][niveau] == 0
            && map[coordY+3][coordX][niveau] == 0 && map[coordY+4][coordX][niveau] == 0 && map[coordY+5][coordX][niveau] == 0){
            map[coordY][coordX][niveau] = 4;
            map[coordY+1][coordX][niveau] = 4;
            map[coordY+2][coordX][niveau] = 4;
            map[coordY+3][coordX][niveau] = 4;
            map[coordY+4][coordX][niveau] = 4;
            map[coordY+5][coordX][niveau] = 4;
            debug("Bateau Porte-avion placer");
            printf("coordX %d, coordY %d, sens %d\n",coordX,coordY,sens);
        }
        break;
    case 1:
        if (coordX+5 < MAP_W && map[coordY][coordX][niveau] == 0&& map[coordY][coordX+1][niveau] == 0 && map[coordY][coordX+2][niveau] == 0
            && map[coordY][coordX+3][niveau] == 0 && map[coordY][coordX+4][niveau] == 0 && map[coordY][coordX+5][niveau] == 0){
            map[coordY][coordX][niveau] = 4;
            map[coordY][coordX+1][niveau] = 4;
            map[coordY][coordX+2][niveau] = 4;
            map[coordY][coordX+3][niveau] = 4;
            map[coordY][coordX+4][niveau] = 4;
            map[coordY][coordX+5][niveau] = 4;
            debug("Bateau Porte-avion placer");
            printf("coordX %d, coordY %d, sens %d\n",coordX,coordY,sens);
        }
        break;
    default:
        debug("Parametre invalide !");
        break;
        }
}

void placementBateau(int map[MAP_H][MAP_W][MAP_ITEM], int niveau, int typeplayer){
    placementCorvette(map, niveau, typeplayer);
    if (typeplayer == HUMAIN){
        system("cls");
        printGame(map, niveau);
    }
    placementDestroyer(map, niveau, typeplayer);
    if (typeplayer == HUMAIN){
        system("cls");
        printGame(map, niveau);
    }
    placementDestroyer(map, niveau, typeplayer);
    if (typeplayer == HUMAIN){
        system("cls");
        printGame(map, niveau);
    }
    placementCroiseur(map, niveau, typeplayer);
    if (typeplayer == HUMAIN){
        system("cls");
        printGame(map, niveau);
    }
    placementCroiseur(map, niveau, typeplayer);
    if (typeplayer == HUMAIN){
        system("cls");
        printGame(map, niveau);
    }
    placementPorteAvion(map, niveau, typeplayer);
}

void action(int map[MAP_H][MAP_W][MAP_ITEM], int player[JOUEUR_NBR][JOUEUR_ITEM], int J1Tire, int J2Placement, int joueur, int typeplayer){
    debug("Entre dans Action");
    int tire = 0;
    int coordX = 0;
    int coordY = 0;
    while (tire == 0){
        if (typeplayer == IA){
            coordX = doRand(0,MAP_W+1);
            coordY = doRand(0,MAP_H+1);
        if (map[coordY][coordX][J1Tire] == 0){
            tire = 1;
        }
        }else if (typeplayer == HUMAIN){
            printf("Position du tire\n");
            printf("Entrer coordonné X entre 0 et %d :", MAP_W-1);
            scanf("%d", &coordX);
            fflush(stdin);
            printf("\nEntrer coordonné Y entre 0 et %d :", MAP_H-1);
            scanf("%d", &coordY);
            fflush(stdin);
        }
        if (map[coordY][coordX][J1Tire] == 0){
            tire = 1;
        }
        if (coordX >= MAP_W || coordY >= MAP_H || coordX < 0 || coordY < 0){
            erreur("\nPosition Invalide !");
            tire = 0;
        }
    }
    if (map[coordY][coordX][J2Placement] == 1 || map[coordY][coordX][J2Placement] == 2
        || map[coordY][coordX][J2Placement] == 3 || map[coordY][coordX][J2Placement] == 4 ){
        map[coordY][coordX][J1Tire] = 9;
        printf("Bateau toucher !\n");
        debug("Action tire toucher effectuer");
        printf("coordX %d, coordY %d\n",coordX,coordY);
    }else {
        map[coordY][coordX][J1Tire] = 8;
        printf("Tire rater !\n");
        debug("Action tire rate effectuer");
        printf("coordX %d, coordY %d\n",coordX,coordY);
    }
    if (map[coordY][coordX][J1Tire] == 9){
        player[joueur][JOUEUR_COUP] ++ ;
        player[joueur][JOUEUR_POSX] = coordX;
        player[joueur][JOUEUR_POSY] = coordY;
    }
    if (typeplayer == HUMAIN){
        printGame(map, J1Tire);
    }
}

void iaVSia(){
    int player[JOUEUR_NBR][JOUEUR_ITEM] = {0};
    int map[MAP_H][MAP_W][MAP_ITEM] = {0};
    placementBateau(map, MAP_J1_PLACEMENT, IA);
    printGame(map, MAP_J1_PLACEMENT);
    placementBateau(map, MAP_J2_PLACEMENT, IA);
    printGame(map, MAP_J2_PLACEMENT);
    while (player[JOUEUR1][JOUEUR_COUP] < 21 && player[JOUEUR2][JOUEUR_COUP] < 21){
        printf("Tour Joueur 1\n");
        action(map, player, MAP_J1_TIRE, MAP_J2_PLACEMENT, JOUEUR1, IA);
        printf("Joueur 1 : %d\n",player[JOUEUR1][JOUEUR_COUP]);
        printf("Tour Joueur 2\n");
        action(map, player, MAP_J2_TIRE, MAP_J1_PLACEMENT, JOUEUR2, IA);
        printf("Joueur 2 : %d\n",player[JOUEUR2][JOUEUR_COUP]);
    }
    if (player[JOUEUR1][JOUEUR_COUP] == 21){
        printf("\nLe Joueur 1 a gagner !!\n");
        printGame(map, MAP_J1_TIRE);
    }else {
        printf("\nLe Joueur 2 a gagner !!\n");
        printGame(map, MAP_J2_TIRE);
    }
    getchar();;
    system("cls");
    menu(map,player);
}

void j1VSj2(){
    int player[JOUEUR_NBR][JOUEUR_ITEM] = {0};
    int map[MAP_H][MAP_W][MAP_ITEM] = {0};
    system("cls");
    printGame(map, MAP_J1_PLACEMENT);
    printf("Placement Joueur 1:\n");
    placementBateau(map, MAP_J1_PLACEMENT, HUMAIN);
    printGame(map, MAP_J1_PLACEMENT);
    system("cls");
    printGame(map, MAP_J2_PLACEMENT);
    printf("Placement Joueur 2:\n");
    placementBateau(map, MAP_J2_PLACEMENT, HUMAIN);
    printGame(map, MAP_J2_PLACEMENT);
    getchar();
    system("cls");
    while (player[JOUEUR1][JOUEUR_COUP] < 21 && player[JOUEUR2][JOUEUR_COUP] < 21){
        printf("Tour Joueur 1\n");
        action(map, player, MAP_J1_TIRE, MAP_J2_PLACEMENT, JOUEUR1, HUMAIN);
        printf("Joueur 1 : %d\n",player[JOUEUR1][JOUEUR_COUP]);
        printf("Tour Joueur 2\n");
        action(map, player, MAP_J2_TIRE, MAP_J1_PLACEMENT, JOUEUR2, HUMAIN);
        printf("Joueur 2 : %d\n",player[JOUEUR2][JOUEUR_COUP]);
    }
    if (player[JOUEUR1][JOUEUR_COUP] == 21){
        printf("\nLe Joueur 1 a gagner !!\n");
        printGame(map, MAP_J1_TIRE);
    }else {
        printf("\nLe Joueur 2 a gagner !!\n");
        printGame(map, MAP_J2_TIRE);
    }
    getchar();;
    system("cls");
    menu(map,player);
}

void j1VSia(){
    int player[JOUEUR_NBR][JOUEUR_ITEM] = {0};
    int map[MAP_H][MAP_W][MAP_ITEM] = {0};
    system("cls");
    printGame(map, MAP_J1_PLACEMENT);
    printf("Placement Joueur 1:\n");
    placementBateau(map, MAP_J1_PLACEMENT, HUMAIN);
    printGame(map, MAP_J1_PLACEMENT);
    printf("Placement Joueur 2:\n");
    placementBateau(map, MAP_J2_PLACEMENT, IA);
    system("cls");
    while (player[JOUEUR1][JOUEUR_COUP] < 21 && player[JOUEUR2][JOUEUR_COUP] < 21){
        printf("Tour Joueur 1\n");
        action(map, player, MAP_J1_TIRE, MAP_J2_PLACEMENT, JOUEUR1, HUMAIN);
        printf("Joueur 1 : %d\n",player[JOUEUR1][JOUEUR_COUP]);
        printf("Tour Joueur 2\n");
        action(map, player, MAP_J2_TIRE, MAP_J1_PLACEMENT, JOUEUR2, IA);
        printf("Joueur 2 : %d\n",player[JOUEUR2][JOUEUR_COUP]);
    }
    if (player[JOUEUR1][JOUEUR_COUP] == 21){
        printf("\nLe Joueur 1 a gagner !!\n");
        printGame(map, MAP_J1_TIRE);
    }else {
        printf("\nLe Joueur 2 a gagner !!\n");
        printGame(map, MAP_J2_TIRE);
    }
    getchar();;
    system("cls");
    menu(map,player);
}

void menu(int map[MAP_H][MAP_W][MAP_ITEM], int player[JOUEUR_NBR][JOUEUR_ITEM]){
    int titre[7][55] = {{0,0,1,1,1,0,0,0,1,1,0,0,1,1,1,1,1,0,1,1,1,1,1,0,1,0,0,0,0,1,1,1,1,0,0,1,1,1,1,0,1,0,0,1,0,1,1,1,0,1,1,1,0,0,0},
                    {0,0,1,0,0,1,0,1,0,0,1,0,0,0,1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0},
                    {0,0,1,1,1,0,0,1,1,1,1,0,0,0,1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,1,1,1,0,0,0,1,1,1,1,0,1,1,1,1,0,0,1,0,0,1,1,1,0,0,0},
                    {0,0,1,0,0,1,0,1,0,0,1,0,0,0,1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,1,0,0,1,0,0,1,0,0,1,0,0,0,0,0},
                    {0,0,1,1,1,0,0,1,0,0,1,0,0,0,1,0,0,0,0,0,1,0,0,0,1,1,1,1,0,1,1,1,1,0,0,1,1,1,1,0,1,0,0,1,0,1,1,1,0,1,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
                    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,}};
    int i = 0;
    int j = 0;
    for(i=0; i<7; i++){
        for(j=0; j<55; j++){
            if (titre[i][j] == 0){
                color(0,0);
            }else if (titre[i][j] == 1){
                color(12,12);
            }
            printf("%d", titre[i][j]);
            color(7,0);
        }
        printf("\n");
    }

    printf("\n    1- Joueur VS Joueur     3- Ordi VS Ordi\n");
    printf("    2- Joueur VS Ordi       4- Undefined\n\n");
    int choix = -1;
    scanf("%d", &choix);
    fflush(stdin);
    switch(choix){
    case 0:
        break;
    case 1:
        j1VSj2();
        break;
    case 2:
        j1VSia();
        break;
    case 3:
        iaVSia();
        break;
    case 4:
        break;
    }
}

int testRand(){
    #define numberOfRand 10000
    #define numberOfValues 100
    int i = 0;
    int j = 0;
    int tab[numberOfRand] = {0};
    for(i = 0; i < numberOfRand; i++){
        tab[i] = doRand(0,numberOfValues);
    }

    int result[numberOfValues] = {0};
    for(i = 0; i < numberOfValues; i++){
        for(j = 0; j < numberOfRand; j++){
            if(tab[j] == i){
                result[i]++;
            }
        }
    }

    for(i = 0; i < numberOfValues; i++){
        printf("Valeur %d occurence %d\n",i,result[i]);
    }
}
