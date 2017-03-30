//
//  main.c
//  Projet-bibliothèque
//
//  Created by Paul-Henri Zimmerlin on 16/03/2017.
//  Copyright © 2017 Paul-Henri Zimmerlin. All rights reserved.
//
//

#include <stdio.h>
#include <stdlib.h>

char* creerTab1D(int taille);
void initTab1D(char* tab, int taille);
void affichageTab1D(char* tab, int taille);
char** creerTab2D(int taillex, int tailley);
void init2D(char **x, int taillex, int tailley);
void affichageTab2D(char** tab, int taillex, int tailley);

char* creerTab1D(int taille){
    char* tab = malloc(taille * sizeof(char));
    initTab1D(tab, taille);
    return tab;
}
void initTab1D(char* tab, int taille){
    if(taille > 0){
        *tab = '*';
        initTab1D(tab + 1, taille - 1);
    }
}
void affichageTab1D(char* tab, int taille){
    if(*tab){
        printf("%c ", *tab);
        affichageTab1D(++tab, taille);
    }
}

char** creerTab2D(int taillex, int tailley){
    char** x = malloc(taillex * sizeof(char*));
    init2D(x, taillex, tailley);
    return x;
}

void init2D(char **x, int taillex, int tailley){
    if(taillex > 0){
        *x = creerTab1D(tailley);
        init2D(x + 1, taillex - 1,tailley);
    }
    
}

void AffichageTab2D(char **tab, int ligne, int colonne, int i, int j){
    if((i<ligne) && (j<colonne)){
        printf("%c", *(*(tab +i) + j));
        AffichageTab2D(tab, ligne, colonne, i, j+1);
    }
    else if(i < ligne){
        printf("\n");
        AffichageTab2D(tab, ligne, colonne, i+1, 0);
    }
}

void insererCharDansTab2D(char ***tab, int *taillex, int *tailley, int posx, int posy, char c){
    if(posx >= 0 && posy >= 0){
        
        if (posx + 1 > *taillex) {
            *tab = realloc(*tab, (posx + 1) * sizeof(char **));
            
            for(int i = *taillex; i < posx + 1; i++){
                (*tab)[i] = creerTab1D(*tailley);
            }
            
            *taillex = posx + 1;
        }
        if (posy + 1 > *tailley){
            for(int ligne = 0; ligne < *taillex; ligne++){
                (*tab)[ligne] = realloc((*tab)[ligne], (posy + 1) * sizeof(char *));
                for(int colonne = *tailley; colonne < (posy + 1); colonne++){
                    (*tab)[ligne][colonne] = '*';
                }
            }
            *tailley = posy + 1;
        }
        
        (*tab)[posx][posy] = c;
    }
    else if(DEBUG) printf("\nLa position n'est pas correcte (inférieure à 0)\n");
}

void insererMotDansTab2D(char ***tab, int *taillex, int *tailley, int posx, int posy, int horizontal, char *mot){
    while(*mot){
        insererCharDansTab2D(tab, taillex, tailley, posx, posy, *mot);
        mot++;
        if (horizontal) posy++;
        else posx++;
        
    }
}


char accesTad2D(char **tab, int taillex, int tailley, int posx, int posy){
    if(posx < (taillex - 1) && posy < (tailley - 1)) return *(*(tab + posx) + posy);
    else return '*';
}



int main(int argc, const char * argv[]) {
    int taillex = 5;
    int tailley = 5;
    //affichageTab1D(creerTab1D(4), 4);
    char** test = creerTab2D(taillex, tailley);
    
    AffichageTab2D(test, taillex, tailley, 0, 0);
    char* machin = "coucou";
    printf("\n\n");
    insererMotDansTab2D(&test, &taillex, &tailley, 2, 2, 0, machin);
    
    AffichageTab2D(test, taillex, tailley, 0, 0);
    //printf("Test : %c\n", accesTad2D(test, 4, 5, 2, 2));

    return 0;
    
}
