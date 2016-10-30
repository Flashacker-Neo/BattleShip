#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

//#define DEBUG 0
//#define COLOR_MAP 1
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
#define JOUEUR_ITEM 2 // l'item 0 cause des problèmes à l'affichage il est donc un espace inutiliser...
#define JOUEUR_COUP 1
#define HUMAIN 0
#define IA 1
#define NONE -1
#define EASY 0
#define HARD 1
#define MAX_CHANCE 5 // Une chance sur Max_chance de tirer sur un bateau. (règle le niveau de l'ia)
//#define MAX_CORVETTE 1
//#define MAX_DESTROYER 2
//#define MAX_CROISEUR 2
//#define MAX_PORTEAVION 1

int COLOR_MAP = 1;
int DEBUG = 0;
int MAX_CORVETTE = 1;
int MAX_DESTROYER = 2;
int MAX_CROISEUR = 2;
int MAX_PORTEAVION = 1;
int COUP_MAX = 21;

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
void titre(){
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
                debug("Entre dans condition boucle");
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
        printf("Bateau Corvette placer\n");
        printf("coordX %d, coordY %d\n",coordX,coordY);
    }

}

void placementDestroyer(int map[MAP_H][MAP_W][MAP_ITEM], int niveau, int typeplayer){
    debug("Entre dans PlacementDestroyer");
    int placement = 0;
    int coordX = 0;
    int coordY = 0;
    int sens = 0;
    int verifpos = 0;
    while (verifpos == 0){
        placement = 0;
        while (placement == 0){
            int verif = 0;
            if (typeplayer == IA){
                    debug("Entre dans condition boucle");
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
                printf("Bateau Destroyer placer\n");
                printf("coordX %d, coordY %d, sens %d\n",coordX,coordY,sens);
                verifpos = 1;
            }
            break;
        case 1:
            if (coordX+2 < MAP_H && map[coordY][coordX][niveau] == 0&& map[coordY][coordX+1][niveau] == 0 && map[coordY][coordX+2][niveau] == 0 ){
                map[coordY][coordX][niveau] = 2;
                map[coordY][coordX+1][niveau] = 2;
                map[coordY][coordX+2][niveau] = 2;
                printf("Bateau Destroyer placer\n");
                printf("coordX %d, coordY %d, sens %d\n",coordX,coordY,sens);
                verifpos = 1;
            }
            break;
        default:
            debug("Parametre invalide !");
            break;
        }
    }
}

void placementCroiseur(int map[MAP_H][MAP_W][MAP_ITEM], int niveau, int typeplayer){
    debug("Entre dans PlacementCroiseur");
    int placement = 0;
    int coordX = 0;
    int coordY = 0;
    int sens = 0;
    int verifpos = 0;
    while (verifpos == 0){
        placement = 0;
        while (placement == 0){
            int verif = 0;
            if (typeplayer == IA){
                    debug("Entre dans condition boucle");
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
                       debug("Entre dans switch");
                map[coordY][coordX][niveau] = 3;
                map[coordY+1][coordX][niveau] = 3;
                map[coordY+2][coordX][niveau] = 3;
                map[coordY+3][coordX][niveau] = 3;
                printf("Bateau Croiseur placer\n");
                printf("coordX %d, coordY %d, sens %d\n",coordX,coordY,sens);
                verifpos = 1;
            }
            break;
        case 1:
            if (coordX+3 < MAP_W && map[coordY][coordX][niveau] == 0&& map[coordY][coordX+1][niveau] == 0
                && map[coordY][coordX+2][niveau] == 0 && map[coordY][coordX+3][niveau] == 0){
                    debug("Entre dans switch");
                map[coordY][coordX][niveau] = 3;
                map[coordY][coordX+1][niveau] = 3;
                map[coordY][coordX+2][niveau] = 3;
                map[coordY][coordX+3][niveau] = 3;
                printf("Bateau Croiseur placer\n");
                printf("coordX %d, coordY %d, sens %d\n",coordX,coordY,sens);
                verifpos = 1;
            }
            break;
        default:
            debug("Parametre invalide !");
            break;
        }
    }
}

void placementPorteAvion(int map[MAP_H][MAP_W][MAP_ITEM], int niveau, int typeplayer){
    debug("Entre dans PlacementPorteAvion");
    int placement = 0;
    int coordX = 0;
    int coordY = 0;
    int sens = 0;
    int verifpos = 0;
    while (verifpos == 0){
        placement = 0;
        while (placement == 0){
            int verif = 0;
            if (typeplayer == IA){
                    debug("Entre dans condition boucle");
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
                    debug("Entre dans switch");
                map[coordY][coordX][niveau] = 4;
                map[coordY+1][coordX][niveau] = 4;
                map[coordY+2][coordX][niveau] = 4;
                map[coordY+3][coordX][niveau] = 4;
                map[coordY+4][coordX][niveau] = 4;
                map[coordY+5][coordX][niveau] = 4;
                printf("Bateau Porte-avion placer\n");
                printf("coordX %d, coordY %d, sens %d\n",coordX,coordY,sens);
                verifpos = 1;
            }
            break;
        case 1:
            if (coordX+5 < MAP_W && map[coordY][coordX][niveau] == 0&& map[coordY][coordX+1][niveau] == 0 && map[coordY][coordX+2][niveau] == 0
                && map[coordY][coordX+3][niveau] == 0 && map[coordY][coordX+4][niveau] == 0 && map[coordY][coordX+5][niveau] == 0){
                    debug("Entre dans switch");
                map[coordY][coordX][niveau] = 4;
                map[coordY][coordX+1][niveau] = 4;
                map[coordY][coordX+2][niveau] = 4;
                map[coordY][coordX+3][niveau] = 4;
                map[coordY][coordX+4][niveau] = 4;
                map[coordY][coordX+5][niveau] = 4;
                printf("Bateau Porte-avion placer\n");
                printf("coordX %d, coordY %d, sens %d\n",coordX,coordY,sens);
                verifpos = 1;
            }
            break;
        default:
            debug("Parametre invalide !");
            break;
            }
        }
}

void placementBateau(int map[MAP_H][MAP_W][MAP_ITEM], int niveau, int typeplayer){
    int i = 0;

    for(i=0; i<MAX_CORVETTE; i++){
        placementCorvette(map, niveau, typeplayer);
        if (typeplayer == HUMAIN){
            system("cls");
            printGame(map, niveau);
        }
    }
    for(i=0; i<MAX_DESTROYER; i++){
        placementDestroyer(map, niveau, typeplayer);
        if (typeplayer == HUMAIN){
            system("cls");
            printGame(map, niveau);
        }
    }
    for(i=0; i<MAX_CROISEUR; i++){
        placementCroiseur(map, niveau, typeplayer);
        if (typeplayer == HUMAIN){
            system("cls");
            printGame(map, niveau);
        }
    }
    for(i=0; i<MAX_PORTEAVION; i++){
        placementPorteAvion(map, niveau, typeplayer);
        if (typeplayer == HUMAIN){
            system("cls");
            printGame(map, niveau);
        }
    }
}

void action(int map[MAP_H][MAP_W][MAP_ITEM], int player[JOUEUR_NBR][JOUEUR_ITEM], int J1Tire, int J2Placement, int joueur, int typeplayer, int diff){
    debug("Entre dans Action");
    int tire = 0;
    int coordX = -1;
    int coordY = -1;
    int chance = 1;
    while (tire == 0){
        if (typeplayer == IA){
            if (diff == EASY){
                coordX = doRand(0,MAP_W+1);
                coordY = doRand(0,MAP_H+1);
                if (map[coordY][coordX][J1Tire] == 0){
                    tire = 1;
                }
            }else{
                chance = doRand(1,MAX_CHANCE);
                switch (chance){
                    case 1:
                        debug("Tire precis #");
                        for(coordY=0; coordY<MAP_H; coordY++){
                            for(coordX=0; coordX<MAP_W; coordX++){
                                if((map[coordY][coordX][J1Tire] == 0) && (map[coordY][coordX][J2Placement] == 1 || map[coordY][coordX][J2Placement] == 2 ||
                                map[coordY][coordX][J2Placement] == 3 || map[coordY][coordX][J2Placement] == 4)){
                                    tire = 1;
                                    break;
                                }
                            }
                            if(tire == 1){
                                break;
                            }
                        }
                        break;
                    default:
                        debug("Tire aleatoire #");
                        coordX = doRand(0,MAP_W+1);
                        coordY = doRand(0,MAP_H+1);
                        if (map[coordY][coordX][J1Tire] == 0){
                            tire = 1;
                        }
                        break;
                }
            }
        }else if (typeplayer == HUMAIN){
            printf("Position du tir\n");
            printf("Entrer coordonner X entre 0 et %d :", MAP_W-1);
            scanf("%d", &coordX);
            fflush(stdin);
            printf("\nEntrer coordonner Y entre 0 et %d :", MAP_H-1);
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
        debug("Action tir toucher effectuer");
        printf("coordX %d, coordY %d\n",coordX,coordY);
    }else {
        map[coordY][coordX][J1Tire] = 8;
        printf("Tir rater !\n");
        debug("Action tir rate effectuer");
        printf("coordX %d, coordY %d\n",coordX,coordY);
    }
    if (map[coordY][coordX][J1Tire] == 9){
        player[joueur][JOUEUR_COUP] ++ ;
    }
    if (typeplayer == HUMAIN){
        printGame(map, J1Tire);
    }
}

void iaVSia(int load){
    COUP_MAX = MAX_CORVETTE + MAX_DESTROYER*3 + MAX_CROISEUR*4 + MAX_PORTEAVION*6;
    int player[JOUEUR_NBR][JOUEUR_ITEM] = {0};
    int map[MAP_H][MAP_W][MAP_ITEM] = {0};
    if (load != 1){
        placementBateau(map, MAP_J1_PLACEMENT, IA);
        printGame(map, MAP_J1_PLACEMENT);
        placementBateau(map, MAP_J2_PLACEMENT, IA);
        printGame(map, MAP_J2_PLACEMENT);
    }else{
        loadGame(map,player);
    }
    while (player[JOUEUR1][JOUEUR_COUP] < COUP_MAX && player[JOUEUR2][JOUEUR_COUP] < COUP_MAX){
        printf("Tour Joueur 1\n");
        action(map, player, MAP_J1_TIRE, MAP_J2_PLACEMENT, JOUEUR1, IA, EASY);
        printf("Coup joueur 1 : %d\n",player[JOUEUR1][JOUEUR_COUP]);
        printf("===========================\n");
        printf("Tour Joueur 2\n");
        action(map, player, MAP_J2_TIRE, MAP_J1_PLACEMENT, JOUEUR2, IA, EASY);
        printf("Coup joueur 2 : %d\n",player[JOUEUR2][JOUEUR_COUP]);
        printf("===========================\n");
        saveGame(map, player);
    }
    if (player[JOUEUR1][JOUEUR_COUP] == COUP_MAX){
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

void j1VSj2(int load){
    COUP_MAX = MAX_CORVETTE + MAX_DESTROYER*3 + MAX_CROISEUR*4 + MAX_PORTEAVION*6;
    int player[JOUEUR_NBR][JOUEUR_ITEM] = {0};
    int map[MAP_H][MAP_W][MAP_ITEM] = {0};
    int choix = 0;
    if (load != 1){
        system("cls");
        titre();
        printf("Placement Joueur 1:\n\n");
        printf("Voulez-vous placer vos bateaux aleatoirement ?\n");
        printf("    1- Oui      2- Non\n");
        scanf("%d", &choix);
        if(choix == 1){
            placementBateau(map, MAP_J1_PLACEMENT, IA);
        }else{
            system("cls");
            printGame(map, MAP_J1_PLACEMENT);
            printf("Placement Joueur 1:\n");
            placementBateau(map, MAP_J1_PLACEMENT, HUMAIN);
        }
        system("cls");
        titre();
        printf("Placement Joueur 2:\n\n");
        printf("Voulez-vous placer vos bateaux aleatoirement ?\n");
        printf("    1- Oui      2- Non\n");
        scanf("%d", &choix);
        if(choix == 1){
            placementBateau(map, MAP_J1_PLACEMENT, IA);
        }else{
            system("cls");
            printGame(map, MAP_J2_PLACEMENT);
            printf("Placement Joueur 1:\n");
            placementBateau(map, MAP_J2_PLACEMENT, HUMAIN);
        }
        system("cls");
    }else{
        loadGame(map,player);
    }
    while (player[JOUEUR1][JOUEUR_COUP] < COUP_MAX && player[JOUEUR2][JOUEUR_COUP] < COUP_MAX){
        printf("Tour Joueur 1\n");
        action(map, player, MAP_J1_TIRE, MAP_J2_PLACEMENT, JOUEUR1, HUMAIN, NONE);
        printf("Coup joueur 1 : %d\n",player[JOUEUR1][JOUEUR_COUP]);
        printf("===========================\n");
        printf("Tour Joueur 2\n");
        action(map, player, MAP_J2_TIRE, MAP_J1_PLACEMENT, JOUEUR2, HUMAIN, NONE);
        printf("Coup joueur 2 : %d\n",player[JOUEUR2][JOUEUR_COUP]);
        printf("===========================\n");
    }
    if (player[JOUEUR1][JOUEUR_COUP] == COUP_MAX){
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

void j1VSia_diff0(int load){
    COUP_MAX = MAX_CORVETTE + MAX_DESTROYER*3 + MAX_CROISEUR*4 + MAX_PORTEAVION*6;
    int player[JOUEUR_NBR][JOUEUR_ITEM] = {0};
    int map[MAP_H][MAP_W][MAP_ITEM] = {0};
    int choix = 0;
    if (load != 1){
        system("cls");
        titre();
        printf("Placement Joueur 1:\n\n");
        printf("Voulez-vous placer vos bateaux aleatoirement ?\n");
        printf("    1- Oui      2- Non\n");
        scanf("%d", &choix);
        if(choix == 1){
            placementBateau(map, MAP_J1_PLACEMENT, IA);
        }else{
            system("cls");
            printGame(map, MAP_J1_PLACEMENT);
            printf("Placement Joueur 1:\n");
            placementBateau(map, MAP_J1_PLACEMENT, HUMAIN);
        }
        system("cls");
        printf("Placement Joueur 2:\n");
        placementBateau(map, MAP_J2_PLACEMENT, IA);
        system("cls");
    }else{
        loadGame(map,player);
    }
    while (player[JOUEUR1][JOUEUR_COUP] < COUP_MAX && player[JOUEUR2][JOUEUR_COUP] < COUP_MAX){
        printf("Tour Joueur 1\n");
        action(map, player, MAP_J1_TIRE, MAP_J2_PLACEMENT, JOUEUR1, HUMAIN, NONE);
        printf("Coup joueur 1 : %d\n",player[JOUEUR1][JOUEUR_COUP]);
        printf("===========================\n");
        printf("Tour Joueur 2\n");
        action(map, player, MAP_J2_TIRE, MAP_J1_PLACEMENT, JOUEUR2, IA, EASY);
        printf("Coup joueur 2 : %d\n",player[JOUEUR2][JOUEUR_COUP]);
        printf("===========================\n");
    }
    if (player[JOUEUR1][JOUEUR_COUP] == COUP_MAX){
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

void j1VSia_diff1(int load){
    COUP_MAX = MAX_CORVETTE + MAX_DESTROYER*3 + MAX_CROISEUR*4 + MAX_PORTEAVION*6;
    int player[JOUEUR_NBR][JOUEUR_ITEM] = {0};
    int map[MAP_H][MAP_W][MAP_ITEM] = {0};
    int choix = 0;
    if (load != 1){
        system("cls");
        titre();
        printf("Placement Joueur 1:\n\n");
        printf("Voulez-vous placer vos bateaux aleatoirement ?\n");
        printf("    1- Oui      2- Non\n");
        scanf("%d", &choix);
        if(choix == 1){
            placementBateau(map, MAP_J1_PLACEMENT, IA);
        }else{
            system("cls");
            printGame(map, MAP_J1_PLACEMENT);
            printf("Placement Joueur 1:\n");
            placementBateau(map, MAP_J1_PLACEMENT, HUMAIN);
        }
        system("cls");
        printf("Placement Joueur 2:\n");
        placementBateau(map, MAP_J2_PLACEMENT, IA);
        system("cls");
    }else{
        loadGame(map,player);
    }
    while (player[JOUEUR1][JOUEUR_COUP] < COUP_MAX && player[JOUEUR2][JOUEUR_COUP] < COUP_MAX){
        printf("Tour Joueur 1\n");
        action(map, player, MAP_J1_TIRE, MAP_J2_PLACEMENT, JOUEUR1, HUMAIN, NONE);
        printf("Coup joueur 1 : %d\n",player[JOUEUR1][JOUEUR_COUP]);
        printf("===========================\n");
        printf("Tour Joueur 2\n");
        action(map, player, MAP_J2_TIRE, MAP_J1_PLACEMENT, JOUEUR2, IA, HARD);
        printf("Coup joueur 2 : %d\n",player[JOUEUR2][JOUEUR_COUP]);
        printf("===========================\n");
    }
    if (player[JOUEUR1][JOUEUR_COUP] == COUP_MAX){
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

void saveGame(int map[MAP_H][MAP_W][MAP_ITEM], int player[JOUEUR_NBR][JOUEUR_ITEM]){
    int item = 0;
    int i = 0;
    int j = 0;
    FILE* save = NULL;
    save = fopen("map.svbs", "w");
    if (save != NULL){
        for(item=0; item<MAP_ITEM; item++){
            for(i=0; i<MAP_H; i++){
                for(j=0; j<MAP_W; j++){
                    fprintf(save, "%d", map[i][j][item]);
                }
            }
        }
        fclose(save);
    }else{
        erreur("Impossible de sauvegarder !");
    }
    FILE* save2 = NULL;
    save2 = fopen("player.svbs", "w");
    if (save2 != NULL){
        for(i=0; i<JOUEUR_NBR; i++){
            for(j=1; j<JOUEUR_ITEM; j++){
                fprintf(save2, "%d ", player[i][j]);
            }
        }
        fclose(save2);
    }else{
        erreur("Impossible de sauvegarder !");
    }
}

void loadGame(int map[MAP_H][MAP_W][MAP_ITEM], int player[JOUEUR_NBR][JOUEUR_ITEM]){
    int item = 0;
    int i = 0;
    int j = 0;
    int val = 0;
    char c;
    FILE* save = NULL;
    save = fopen("map.svbs", "r");
    if (save != NULL){
        for(item=0; item<MAP_ITEM; item++){
            for(i=0; i<MAP_H; i++){
                for(j=0; j<MAP_W; j++){
                    c = fgetc(save);
                    if( feof(save) ){
                        break;
                    }
                    switch (c){
                        case 48:
                            val = 0;
                            break;
                        case 49:
                            val = 1;
                            break;
                        case 50:
                            val = 2;
                            break;
                        case 51:
                            val = 3;
                            break;
                        case 52:
                            val = 4;
                            break;
                        case 53:
                            val = 5;
                            break;
                        case 54:
                            val = 6;
                            break;
                        case 55:
                            val = 7;
                            break;
                        case 56:
                            val = 8;
                            break;
                        case 57:
                            val = 9;
                            break;

                    }
                    map[i][j][item] = val;
                }
            }
        }
    //fscanf(save, "%d %d", player[JOUEUR1][JOUEUR_COUP],player[JOUEUR2][JOUEUR_COUP]);
    fclose(save);
    }else{
        erreur("Erreur MAP : Impossible de charger la partie !");
    }
    FILE* save2 = NULL;
    save2 = fopen("player.svbs", "r");
    if (save2 != NULL){
        fscanf(save2, "%d %d", &player[JOUEUR1][JOUEUR_COUP], &player[JOUEUR2][JOUEUR_COUP]);
    }else{
        erreur("Erreur PLAYER : Impossible de charger la partie !");
    }
}

void menu(/*int map[MAP_H][MAP_W][MAP_ITEM], int player[JOUEUR_NBR][JOUEUR_ITEM]*/){
    titre();

    FILE* save = NULL;
    save = fopen("map.svbs", "r");
    fclose(save);
    int load = 0;
    if (save != NULL){

        printf("\nSauvegarde trouver, voulez-vous la charger ?\n    1- Charger la partie    2- Nouvelle partie\n\n");
        scanf("%d", &load);
        fflush(stdin);
        system("cls");
        titre();
        if (load == 1){
            printf("Partie charger !\n");
        }else{
            printf("Nouvelle partie...\n");
        }
    }

    printf("\n    1- Joueur VS Joueur     3- Ordi VS Ordi\n");
    printf("    2- Joueur VS Ordi       4- Option\n\n");
    int choix = -1;
    scanf("%d", &choix);
    fflush(stdin);
    switch(choix){
    case 0:
        break;
    case 1:
        system("cls");
        j1VSj2(load);
        break;
    case 2:
        system("cls");
        titre();
        printf("Veuillez choisir un niveau de difficulter :\n");
        printf("\n    1- Ordi Facile     2- Ordi Hardcore\n");
        scanf("%d", &choix);
        fflush(stdin);
        if (choix == 2){
            j1VSia_diff1(load);
        }else{
            j1VSia_diff0(load);
        }
        break;
    case 3:
        system("cls");
        titre();
        iaVSia(load);
        break;
    case 4:
        option();
        break;
    }
}

void option(){
    int choix = -1;
    system("cls");
    titre();
    printf("Option du jeu :\n\n");
    printf("    1- Couleur carte        2- Nombres de bateaux\n");
    printf("    3- Valeur par defaut    4- Retour au menu\n");
    scanf("%d", &choix);
    fflush(stdin);
    switch (choix){
        case 1:
            system("cls");
            titre();
            printf("Voulez-vous une carte en couleur ? :\n\n");
            printf("    1- Oui        2- Non\n");
            scanf("%d", &choix);
            fflush(stdin);
            if(choix == 2){
                COLOR_MAP = 0;
                printf("\nLes couleurs sont desactiver !");
            }else{
                COLOR_MAP = 1;
                printf("\nLes couleurs sont activer !");
            }
            getchar();
            option();
            break;
        case 2:
            nbrbateau();
            break;
        case 3:
            system("cls");
            titre();
            printf("Etes vous sur de vouloir remettre les parametres a 0 ? :\n\n");
            printf("    1- Oui        2- Non\n");
            scanf("%d", &choix);
            fflush(stdin);
            if(choix == 1){
                COLOR_MAP = 1;
                DEBUG = 0;
                MAX_CORVETTE = 1;
                MAX_DESTROYER = 2;
                MAX_CROISEUR = 2;
                MAX_PORTEAVION = 1;
                printf("\nLes parametres ont bien ete remis a 0 !");
            }
            getchar();
            option();
            break;
        case 7:
            system("cls");
            titre();
            if(DEBUG == 1){
                printf("Mode debug desactiver !");
                DEBUG = 0;
            }else{
                printf("Mode debug activer !");
                DEBUG = 1;
            }
            getchar();
            option();
            break;
        default:
            system("cls");
            menu();
            break;

    }
}

void nbrbateau(){
    int choix = 0;
    int nbr = 0;
    system("cls");
    titre();
    printf("Quel bateau voulez-vous changer ? :\n\n");
    printf("    1- Corvette\n    2- Destroyer\n    3- Croiseur\n    4- Porte-avion\n");
    scanf("%d", &choix);
    fflush(stdin);
    switch (choix){
        case 1:
            system("cls");
            titre();
            printf("\nVeuillez entrer le nombre de Corvette :\n");
            scanf("%d", &nbr);
            fflush(stdin);
            MAX_CORVETTE = nbr;
            printf("Le nombre de Corvette a bien ete modifier a %d", nbr);
            getchar();
            system("cls");
            titre();
            printf("\nVoulez-vous modifier un autre bateau ?\n");
            printf("    1- Oui      2- Non\n");
            scanf("%d", &choix);
            fflush(stdin);
            switch (choix){
                case 1:
                    nbrbateau();
                    break;
                default :
                    option();
                    break;
            }
            break;
        case 2:
            system("cls");
            titre();
            printf("\nVeuillez entrer le nombre de Destroyer :\n");
            scanf("%d", &nbr);
            fflush(stdin);
            MAX_DESTROYER = nbr;
            printf("Le nombre de Destroyer a bien ete modifier a %d", nbr);
            getchar();
            system("cls");
            titre();
            printf("\nVoulez-vous modifier un autre bateau ?\n");
            printf("    1- Oui      2- Non\n");
            scanf("%d", &choix);
            fflush(stdin);
            switch (choix){
                case 1:
                    nbrbateau();
                    break;
                default :
                    option();
                    break;
            }
            break;
        case 3:
            system("cls");
            titre();
            printf("\nVeuillez entrer le nombre de Croiseur :\n");
            scanf("%d", &nbr);
            fflush(stdin);
            MAX_CROISEUR = nbr;
            printf("Le nombre de Croiseur a bien ete modifier a %d", nbr);
            getchar();
            system("cls");
            titre();
            printf("\nVoulez-vous modifier un autre bateau ?\n");
            printf("    1- Oui      2- Non\n");
            scanf("%d", &choix);
            fflush(stdin);
            switch (choix){
                case 1:
                    nbrbateau();
                    break;
                default :
                    option();
                    break;
            }
            break;
        case 4:
            system("cls");
            titre();
            printf("\nVeuillez entrer le nombre de Porte-avion :\n");
            scanf("%d", &nbr);
            fflush(stdin);
            MAX_PORTEAVION = nbr;
            printf("Le nombre de Porte-avion a bien ete modifier a %d", nbr);
            getchar();
            system("cls");
            titre();
            printf("\nVoulez-vous modifier un autre bateau ?\n");
            printf("    1- Oui      2- Non\n");
            scanf("%d", &choix);
            fflush(stdin);
            switch (choix){
                case 1:
                    nbrbateau();
                    break;
                default :
                    option();
                    break;
            }
            break;
        default:
            option();
            break;
    }
    option();
}
